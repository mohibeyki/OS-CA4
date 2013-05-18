/*
 * MemoryManager.cpp
 *
 *  Created on: May 17, 2013
 *      Author: mohi
 */

#include "MemoryManager.h"

namespace OS {

MemoryManager::MemoryManager() {
	totalSize = 25600;
	memory = new char(totalSize);
}

MemoryManager::~MemoryManager() {
}

} /* namespace OS */
