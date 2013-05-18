/*
 * Reader.h
 *
 *  Created on: May 17, 2013
 *      Author: mohi
 */

#ifndef READER_H_
#define READER_H_

#include <iostream>

namespace OS {

class Reader {
public:
	Reader(std::string inputFile);
	virtual ~Reader();
private:
	std::string file;
};

} /* namespace OS */
#endif /* READER_H_ */
