/*
 * Reader.h
 *
 *  Created on: May 17, 2013
 *      Author: mohi
 */

#ifndef READER_H_
#define READER_H_

#include<iostream>
#include<fstream>
#include<MemoryManager.h>

namespace OS {

class Reader {
public:
	static void* run(void* fileNum);
};

} /* namespace OS */
#endif /* READER_H_ */
