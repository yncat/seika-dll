seika.dll: seika.cpp seika.h
	cl /LD /nologo /EHsc seika.cpp User32.lib

test.exe: seika.dll
	cl /nologo /EHsc test.cpp User32.lib seika.lib