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
	Reader(std::string inputFile, int num);
	void run();
	virtual ~Reader();
private:
	std::string file;
	int number;
	int MAX_PAGE_SIZE;
};

} /* namespace OS */
#endif /* READER_H_ */
