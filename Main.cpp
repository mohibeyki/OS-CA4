/*
 * Main.cpp
 *
 *  Created on: May 17, 2013
 *      Author: mohi
 */

#include <iostream>
#include <MemoryManager.h>
#include <Reader.h>
#include <Writer.h>

using namespace std;
using namespace OS;

int main(int argc, char* argv[]) {
	MemoryManager* memInstance = MemoryManager::getInstance();
	memInstance->memory[255] = 1;
	Reader r1("1.txt", 1);
	Reader r2("2.txt", 2);
	Reader r3("3.txt", 3);
	Writer Writers(3);
	r1.run();
	std::cout << "First Sentinel" << std::endl;
	Writers.Sentinel(1);
	Writers.Sentinel(2);
	Writers.Sentinel(3);
	memInstance->memory[255] = 0;

	return 0;
}
