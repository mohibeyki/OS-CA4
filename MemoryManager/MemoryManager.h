/*
 * MemoryManager.h
 *
 *  Created on: May 17, 2013
 *      Author: mohi
 */

#ifndef MEMORYMANAGER_H_
#define MEMORYMANAGER_H_

namespace OS {

class MemoryManager {
public:
	MemoryManager();
	virtual ~MemoryManager();
private:
	char* memory;
	int totalSize;
};

} /* namespace OS */
#endif /* MEMORYMANAGER_H_ */
