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
	Writer(int m);
	void Write(char buf[MEMORY_WIDTH], int file);
	void Sentinel(int fileNo);
private:
	sem_t *locks;
};

} /* namespace OS */
#endif /* WRITER_H_ */
