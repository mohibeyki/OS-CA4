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

namespace OS {

#define		MEMORY_HEIGHT 	100
#define 	MEMORY_WIDTH 	256
#define 	SHMSIZE			MEMORY_HEIGHT * MEMORY_WIDTH

class MemoryManager {
public:
	MemoryManager();
	virtual ~MemoryManager();
	int 	getFreePage();
	int 	getPageWithId(int pageId);
	void 	freePage(int pageId);

private:
    key_t 	key;
    int 	shmid;
    char* 	memory;
};

} /* namespace OS */
#endif /* MEMORYMANAGER_H_ */
