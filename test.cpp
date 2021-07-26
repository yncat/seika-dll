#include "seika.h"
#include <iostream>

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
	std::cout << "display test" << std::endl;
	char out[8];
	memset(out, SEIKA_DOT_1, 1);
	memset(out + 1, SEIKA_DOT_1 + SEIKA_DOT_2, 1);
	memset(out + 2, SEIKA_DOT_1 + SEIKA_DOT_2 + SEIKA_DOT_3, 1);
	memset(out + 3, SEIKA_DOT_1 + SEIKA_DOT_2 + SEIKA_DOT_3 + SEIKA_DOT_4, 1);
	memset(out + 4, SEIKA_DOT_1 + SEIKA_DOT_2 + SEIKA_DOT_3 + SEIKA_DOT_4 + SEIKA_DOT_5, 1);
	memset(out + 5, SEIKA_DOT_1 + SEIKA_DOT_2 + SEIKA_DOT_3 + SEIKA_DOT_4 + SEIKA_DOT_5 + SEIKA_DOT_6, 1);
	memset(out + 6, SEIKA_DOT_1 + SEIKA_DOT_2 + SEIKA_DOT_3 + SEIKA_DOT_4 + SEIKA_DOT_5 + SEIKA_DOT_6 + SEIKA_DOT_7, 1);
	memset(out + 7, SEIKA_DOT_1 + SEIKA_DOT_2 + SEIKA_DOT_3 + SEIKA_DOT_4 + SEIKA_DOT_5 + SEIKA_DOT_6 + SEIKA_DOT_7 + SEIKA_DOT_8, 1);
	seikaDisplay(out,8);
	Sleep(5000);

	seikaClose();
	std::cout << "close" << std::endl;
	return 0;
}
