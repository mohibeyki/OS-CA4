/*
 * MemoryManager.cpp
 *
 *  Created on: May 17, 2013
 *      Author: mohi
 */

#include <MemoryManager.h>

namespace OS {

MemoryManager* MemoryManager::instance = NULL;

MemoryManager* MemoryManager::getInstance() {
	if (instance == NULL)
		instance = new MemoryManager();
	return instance;
}

MemoryManager::MemoryManager() {
	for (int i = 1; i < MEMORY_HEIGHT; ++i)
		sem_init(&locks[i], 0, 1);
	srand(time(0));
	key = rand() % 4096;

	if ((shmid = shmget(key, SHMSIZE, IPC_CREAT | 0666)) < 0) {
		std::cerr << "ERROR: shmget()" << std::endl;
		return;
	}

	if ((memory = (char*) shmat(shmid, NULL, 0)) < 0) {
		std::cerr << "ERROR: shmat()" << std::endl;
	}

	memory[0] = 127;
	for (int i = 1; i < MEMORY_HEIGHT; ++i) {
		memory[i] = -1;
	}
}

int MemoryManager::getFreePageIndex(int dest) {
	for (int i = 1; i < MEMORY_HEIGHT; ++i) {
		if (memory[i] == -1 && sem_trywait(&locks[i]) == 0) {
			memory[i] = dest;
			return i;
		}
	}
	return -1;
}

int MemoryManager::getPageWithId(int id) {
	for (int i = 1; i < MEMORY_HEIGHT; ++i)
		if (memory[i] == id && sem_trywait(&locks[i]) == 0)
			return i;
	return -1;
}

void MemoryManager::freePage(int pageId) {
	if (pageId < MEMORY_HEIGHT) {
		int value;
		sem_getvalue(&locks[pageId], &value);
		if (value == 0)
			sem_post(&locks[pageId]);
		memory[pageId] = -1;
	}
}

void MemoryManager::pageReady(int pageId) {
	if (pageId < MEMORY_HEIGHT) {
		int value;
		sem_getvalue(&locks[pageId], &value);
		if (value == 0)
			sem_post(&locks[pageId]);
	}
}

MemoryManager::~MemoryManager() {
	shmdt(memory);
}

} /* namespace OS */
