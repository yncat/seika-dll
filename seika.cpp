#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "SerialComm32.h"
#include "seika.h"

DWORD getQueuedByteSize(HANDLE hSerial)
{
	DWORD dwInQueSize = 0;
	DWORD dwOutQueSize = 0;
	DWORD dwModemStat = 0;
	rs232c_GetCommStatus(hSerial, &dwInQueSize, &dwOutQueSize, &dwModemStat);
	return dwInQueSize;
}

DWORD getQueuedSendByteSize(HANDLE hSerial)
{
	DWORD dwInQueSize = 0;
	DWORD dwOutQueSize = 0;
	DWORD dwModemStat = 0;
	rs232c_GetCommStatus(hSerial, &dwInQueSize, &dwOutQueSize, &dwModemStat);
	return dwOutQueSize;
}

VOID waitForSend(HANDLE hSerial)
{
	while (1)
	{
		Sleep(50);
		if (getQueuedSendByteSize(hSerial) == 0)
		{
			break;
		}
	}
}

VOID receiveFromCOM(HANDLE hSerial, DWORD bytes, char *out)
{
	while (1)
	{
		DWORD dwInQueSize = 0;
		DWORD dwOutQueSize = 0;
		DWORD dwModemStat = 0;
		rs232c_GetCommStatus(hSerial, &dwInQueSize, &dwOutQueSize, &dwModemStat);
		if (dwInQueSize >= bytes)
		{
			break;
		}
		Sleep(10);
	}
	rs232c_ReadCommBlock(hSerial, out, bytes);
	memset(out + bytes, 0, 1);
}

VOID CALLBACK clbk(UINT uEvent, WPARAM wParam, LPARAM lParam1, LPARAM lParam2, LPARAM lParam3)
{
}

HANDLE hSerial;
char *lineHeader;
DWORD cells;
char *deviceName;

BOOL initialized = false;

DWORD seikaOpen(DWORD port)
{
	if (initialized)
	{
		return SEIKA_INIT_SUCCESS;
	}
	hSerial = rs232c_CreateSerial(clbk, NULL);
	_DCB dcb;
	dcb.DCBlength = sizeof(_DCB);
	dcb.BaudRate = 9600;
	dcb.fBinary = 1;
	dcb.fParity = 1;
	dcb.ByteSize = 8;
	dcb.Parity = ODDPARITY;
	dcb.StopBits = ONESTOPBIT;
	BOOL connected = rs232c_OpenSerial(hSerial, port, dcb);
	if (!connected)
	{
		return SEIKA_INIT_NOT_CONNECTED;
	}
	const char initMessage[] = "\xff\xff\x1c\x00";
	DWORD dwSent = rs232c_WriteCommBlock(hSerial, initMessage, 3);
	char out[256];
	memset(out, 0, 256);
	BOOL ok = false;
	for (int i = 0; i < 40; i++)
	{
		DWORD s = getQueuedByteSize(hSerial);
		if (s >= 12)
		{
			ok = true;
			break;
		}
		Sleep(50);
	}
	if (!ok)
	{
		rs232c_CloseSerial(hSerial);
		rs232c_DestroySerial(hSerial);
		hSerial = NULL;
		return SEIKA_INIT_TIMEOUT;
	}
	receiveFromCOM(hSerial, 12, out);
	if (strncmp(out, "seika3", 6) != 0)
	{
		char msg[128];
		sprintf(msg, "%s is not supported.", out);
		MessageBoxA(NULL, msg, "error", MB_OK);
		return SEIKA_INIT_NOT_SUPPORTED;
	}
	deviceName = (char *)malloc(64);
	memset(deviceName, 0, 64);
	memcpy(deviceName, out, 12);
	cells = 40;
	lineHeader = (char *)malloc(16);
	memcpy(lineHeader, "\xff\xffseika\x00", 8);
	initialized = true;
	return 0;
}

DWORD seikaGetCells()
{
	if (!initialized)
	{
		return 0;
	}
	return cells;
}

char *seikaGetDeviceName()
{
	if (!initialized)
	{
		return NULL;
	}
	return deviceName;
}

VOID seikaDisplay(const char *inbuf, DWORD inbufSize)
{
	char writebuf[512];
	memset(writebuf, 0, 512);
	memcpy(writebuf, lineHeader, 8);
	if (inbuf)
	{
		char *idx = writebuf + 8;
		char *idx2 = const_cast<char *>(inbuf);
		for (int i = 0; i < inbufSize; ++i)
		{
			memset(idx, 0, 1);
			memcpy(idx + 1, idx2, 1);
			idx += 2;
			idx2++;
		}
	}
	rs232c_WriteCommBlock(hSerial, writebuf, 8 + (cells * 2));
}

DWORD seikaGetKey()
{
	DWORD s = getQueuedByteSize(hSerial);
	if (s == 0)
	{
		return 0;
	}
	if (s != 24 && s != 2)
	{
		rs232c_FlushComm(hSerial);
		return 0;
	}

	char out[512];
	memset(out, 0, 512);
	receiveFromCOM(hSerial, s, out);

	if (s == 2)
	{
		// non touch key
		unsigned char first = (unsigned char)(out[0]);
		unsigned char second = (unsigned char)(out[1]);
		if (first == 0x61 && second == 0xe0)
		{
			return SEIKA_KEY_LEFT_ENTER;
		}
		if (first == 0x64 && second == 0xe0)
		{
			return SEIKA_KEY_RIGHT_ENTER;
		}
		if (first == 0x60 && second == 0xe2)
		{
			return SEIKA_KEY_LEFT_SCROL;
		}
		if (first == 0x68 && second == 0xe0)
		{
			return SEIKA_KEY_RIGHT_SCROL;
		}
		if (first == 0x60 && second == 0xf0)
		{
			return SEIKA_KEY_LEFT_MIDDLE;
		}
		if (first == 0x70 && second == 0xe0)
		{
			return SEIKA_KEY_RIGHT_MIDDLE;
		}
		return 0;
	}
	// touch (cursor routing) key
	for (int i = 0; i < cells / 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if (out[7 + i] & (1 << j))
			{
				return (i * 8) + j + 101;
			}
		}
	}

	return 0;
}

VOID seikaClose()
{
	if (!initialized)
	{
		return;
	}
	seikaDisplay(NULL, 0);
	waitForSend(hSerial);
	rs232c_CloseSerial(hSerial);
	rs232c_DestroySerial(hSerial);
	if(deviceName){
		free(deviceName);
	}
	if(lineHeader){
		free(lineHeader);
	}
	initialized = 0;
}

int WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	return true;
}
