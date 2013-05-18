/*
 * Main.cpp
 *
 *  Created on: May 17, 2013
 *      Author: mohi
 */

#include <iostream>
#include "MemoryManager/MemoryManager.h"

using namespace std;
using namespace OS;

int main(int argc, char* argv[]) {
	{
		MemoryManager* memoryManager = new MemoryManager();
		delete(memoryManager);
	}
	std::cout << "Hello World! :D" << std::endl;
	return 0;
}
