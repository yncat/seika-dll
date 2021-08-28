all: seika.dll test_display.exe test_input.exe

seika.dll: seika.cpp seika.h
	cl /LD /nologo /EHsc seika.cpp User32.lib

test_display.exe: seika.dll
	cl /nologo /EHsc test_display.cpp User32.lib seika.lib

test_input.exe: seika.dll
	cl /nologo /EHsc test_input.cpp User32.lib seika.lib
