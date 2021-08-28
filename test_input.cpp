#include <signal.h>
#include <iostream>
#include <sstream>
#include <string>
#include "seika.h"

VOID onTerm(int sig){
	std::cout << "Quit." << std::endl;
	seikaClose();
	exit(0);
}

VOID printKey(DWORD key)
{
	std::stringstream s;
	s << key << "(";
	if (key > 100)
	{
		s << "cursor routing " << key - 100;
	}
	else
	{
		switch (key)
		{
		case SEIKA_KEY_LEFT_ENTER:
			s << "SEIKA_KEY_LEFT_ENTER";
			break;
		case SEIKA_KEY_RIGHT_ENTER:
			s << "SEIKA_KEY_RIGHT_ENTER";
			break;
		case SEIKA_KEY_LEFT_SCROL:
			s << "SEIKA_KEY_LEFT_SCROL";
			break;
		case SEIKA_KEY_RIGHT_SCROL:
			s << "SEIKA_KEY_RIGHT_SCROL";
			break;
		case SEIKA_KEY_LEFT_MIDDLE:
			s << "SEIKA_KEY_LEFT_MIDDLE";
			break;
		case SEIKA_KEY_RIGHT_MIDDLE:
			s << "SEIKA_KEY_RIGHT_MIDDLE";
			break;
		default:
			s << "unrecognized key";
		} // switch
	}	  // cursor routing or other keys
	s << ")" << std::endl;
	std::cout << s.str();
}

int main()
{
	std::cout << "connecting..." << std::endl;
	int init = seikaOpen(3);
	std::cout << "init: " << init << std::endl;
	if (init != 0)
	{
		return 0;
	}
	std::cout << "deviceName: " << seikaGetDeviceName() << ", " << seikaGetCells() << " cells." << std::endl;
	std::cout << "input test: press any key on your seika. ctrl+c to quit." << std::endl;
	signal(SIGINT,onTerm);
	while (1)
	{
		Sleep(20);
		DWORD key = seikaGetKey();
		if (key)
		{
			printKey(key);
		}
	}
	return 0;
}
