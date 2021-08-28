#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "seika.h"

DWORD getQueuedByteSize(HANDLE hSerial)
{
	DWORD errors;
	COMSTAT stat;
	ClearCommError(hSerial,&errors,&stat);
	return stat.cbInQue;
}

VOID waitForSend(HANDLE hSerial)
{
	FlushFileBuffers(hSerial);
}

VOID receiveFromCOM(HANDLE hSerial, DWORD bytes, char *out)
{
	while (1)
	{
		if (getQueuedByteSize(hSerial) >= bytes)
		{
			break;
		}
		Sleep(10);
	}
	DWORD read;
	ReadFile(hSerial,out,bytes,&read,NULL);
	memset(out + bytes, 0, 1);
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
	char portstr[64];
	sprintf(portstr,"COM%d",port);
	HANDLE hSerial = CreateFile(portstr, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING | FILE_FLAG_WRITE_THROUGH, NULL);
	if(hSerial==INVALID_HANDLE_VALUE){
		return SEIKA_INIT_NOT_CONNECTED;
	}
	
	DCB dcb;
	GetCommState(hSerial, &dcb);
	dcb.BaudRate = 9600;
	dcb.fBinary = 1;
	dcb.fParity = 1;
	dcb.ByteSize = 8;
	dcb.Parity = ODDPARITY;
	dcb.StopBits = ONESTOPBIT;
	SetCommState(hSerial, &dcb);
	const char initMessage[] = "\xff\xff\x1c";
	DWORD written;
	WriteFile(hSerial,initMessage,3,&written,NULL);
	FlushFileBuffers(hSerial);
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
		CloseHandle(hSerial);
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
	DWORD written;
	WriteFile(hSerial, writebuf, 8 + (cells * 2), &written, NULL);
}

DWORD seikaGetKey()
{
	DWORD s = getQueuedByteSize(hSerial);
	if (s == 0)
	{
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
	CloseHandle(hSerial);
	hSerial=NULL;
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
