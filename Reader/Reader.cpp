/*
 * Reader.cpp
 *
 *  Created on: May 17, 2013
 *      Author: mohi
 */

#include "Reader.h"
#include <pthread.h>
#include <cstring>

namespace OS {
using namespace std;

int MAX_PAGE_SIZE = MEMORY_WIDTH - 4;

void* Reader::Run(void* fileNum) {
	MemoryManager* memInstance = MemoryManager::getInstance();
	char fileName[MEMORY_WIDTH];
	char c;
	char tmp[MEMORY_WIDTH];

	sprintf(fileName, "recovered files/%lld.txt", (long long) fileNum);
	ifstream fin(fileName);
	fin >> c;
	while (true) {
		int startByte = 0, whichFile = 0;
		int count = 4;
		if (c == '<') {
			startByte = 0;
			fin >> c;
			while (c != ':') {
				startByte = startByte * 10 + c - '0';
				fin >> c;
			}
			fin >> c;
			while (c != '>') {
				whichFile = whichFile * 10 + c - '0';
				fin >> c;
			}
		}
		startByte--;
		int flag = 0;
		while (flag == 0) {
			memset(tmp, 0, MEMORY_WIDTH);
			tmp[0] = ((char*) &startByte)[3];
			tmp[1] = ((char*) &startByte)[2];
			tmp[2] = ((char*) &startByte)[1];
			tmp[3] = ((char*) &startByte)[0];

			for (int i = 0; i < MAX_PAGE_SIZE; i++) {
				c = fin.get();
				if (fin.good() && !fin.eof() && c != 0x0a) {
					if (c == '<') {
						flag = 1;
						break;
					}
					tmp[count++] = c;
				} else {
					flag = 2;
					break;
				}
			}
			// write data on page
			int pageID = memInstance->getFreePageIndex(whichFile);
			while (pageID < 0) {
				usleep(rand() % 10 + 1);
				pageID = memInstance->getFreePageIndex(whichFile);
			}

			// get page ID
			int startPos = pageID * MEMORY_WIDTH;

			// write tmp on page with ID
			for (int i = 0; i < MEMORY_WIDTH; i++)
				memInstance->memory[i + startPos] = tmp[i];

			// signal the page
			memInstance->pageReady(pageID);

			startByte += count - 4;
			count = 4;
		}
		if (flag == 1)
			continue;
		if (flag == 2)
			break;
	}
	fin.close();
	return NULL;
}

} /* namespace OS */
