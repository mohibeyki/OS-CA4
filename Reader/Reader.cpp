/*
 * Reader.cpp
 *
 *  Created on: May 17, 2013
 *      Author: mohi
 */

#include "Reader.h"
#include <pthread.h>

namespace OS {

Reader::Reader(std::string inputFile) :
		file(inputFile) {

}

Reader::~Reader() {
}

} /* namespace OS */
