/*
 * MemoryManager.cpp
 *
 *  Created on: May 17, 2013
 *      Author: mohi
 */

#include "MemoryManager.h"

namespace OS {

MemoryManager::MemoryManager() {
	srand(time(0));
	key = rand() % 4096;

	if ((shmid = shmget(key, SHMSIZE, IPC_CREAT | 0666)) < 0) {
		std::cerr << "ERROR: shmget()" << std::endl;
		return;
	}

	if ((memory = (char*) shmat(shmid, NULL, 0)) < 0) {
		std::cerr << "ERROR: shmat()" << std::endl;
	}

	for (int i = 0; i < 26; ++i)
		memory[i] = 'a' + i;
}

MemoryManager::~MemoryManager() {
	std::cerr << "Destructor" << std::endl;
	for (int i = 0; i < 27; ++i)
		std::cout << memory[i];
	std::cout << std::endl;
	shmdt(memory);
	std::cerr << "Deattached" << std::endl;
}

} /* namespace OS */
