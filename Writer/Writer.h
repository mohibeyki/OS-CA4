/*
 * Writer.h
 *
 *  Created on: May 18, 2013
 *      Author: mohi
 */

#ifndef WRITER_H_
#define WRITER_H_

#include <MemoryManager.h>

namespace OS {

class Writer {
public:
	static void init(int m);
	static void Write(char buf[MEMORY_WIDTH], int file);
	static void* Sentinel(void* fileVoid);
};

extern sem_t* locks;

} /* namespace OS */
#endif /* WRITER_H_ */
