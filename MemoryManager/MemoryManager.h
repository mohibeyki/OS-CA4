/*
 * MemoryManager.h
 *
 *  Created on: May 17, 2013
 *      Author: mohi
 */

#ifndef MEMORYMANAGER_H_
#define MEMORYMANAGER_H_

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <semaphore.h>

namespace OS {

#define		MEMORY_HEIGHT 	100
#define 	MEMORY_WIDTH 	256
#define 	SHMSIZE			MEMORY_HEIGHT * MEMORY_WIDTH

class MemoryManager {
public:
	static MemoryManager* getInstance();
	int getFreePageIndex(int dest);
	int getPageWithId(int id);
	void freePage(int pageId);
private:
	static MemoryManager* instance;
	MemoryManager();
	virtual ~MemoryManager();
	key_t key;
	int shmid;
	char* memory;
	sem_t locks[MEMORY_HEIGHT];
};

} /* namespace OS */
#endif /* MEMORYMANAGER_H_ */
