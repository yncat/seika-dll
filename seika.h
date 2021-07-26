#include <windows.h>

#ifndef __SEIKA__
#define __SEIKA__

#define SEIKA_API extern "C" __declspec(dllexport)

#define SEIKA_INIT_SUCCESS 0
#define SEIKA_INIT_NOT_CONNECTED 1
#define SEIKA_INIT_TIMEOUT 2
#define SEIKA_INIT_NOT_SUPPORTED 3

#define SEIKA_KEY_LEFT_ENTER 1
#define SEIKA_KEY_RIGHT_ENTER 2
#define SEIKA_KEY_LEFT_SCROL 3
#define SEIKA_KEY_RIGHT_SCROL 4
#define SEIKA_KEY_LEFT_MIDDLE 5
#define SEIKA_KEY_RIGHT_MIDDLE 6

#define SEIKA_DOT_1 0x01
#define SEIKA_DOT_2 0x02
#define SEIKA_DOT_3 0x04
#define SEIKA_DOT_4 0x08
#define SEIKA_DOT_5 0x10
#define SEIKA_DOT_6 0x20
#define SEIKA_DOT_7 0x40
#define SEIKA_DOT_8 0x80

SEIKA_API DWORD seikaOpen(DWORD port);
SEIKA_API DWORD seikaGetCells();
SEIKA_API char* seikaGetDeviceName();
SEIKA_API VOID seikaDisplay(const char*, DWORD);
SEIKA_API DWORD seikaGetKey();
SEIKA_API VOID seikaClose();
#endif
