/*
 * Writer.cpp
 *
 *  Created on: May 18, 2013
 *      Author: mohi
 */

#include "Writer.h"
#include <fstream>
#include <ios>

namespace OS {

Writer::Writer(int m) {
	locks = new sem_t[m];
	for (; m > 0; --m) {
		char fileName[MEMORY_WIDTH] = "";
		sprintf(fileName, "%d.rec", m);
		std::ofstream fout(fileName, std::ofstream::out);
		fout.close();
		sem_init(&locks[m - 1], 0, 1);
		std::cout << "on : " << m << std::endl;
	}
}

//void Writer::Write(char buf[MEMORY_WIDTH], int file) {
//	sem_wait(&locks[file]);
//	char fileName[MEMORY_WIDTH] = "";
//	sprintf(fileName, "%d.rec", file);
//	std::ofstream fout;
//	fout.open(fileName, std::ofstream::ate);
//	int offset = ((buf[0] * 256 + buf[1]) * 256 + buf[2]) * 256 + buf[3];
//	fout.seekp(offset, std::ios_base::beg);
//	for (int i = 4; i < MEMORY_WIDTH && buf[i] != 0; ++i) {
//		fout.put(buf[i]);
//	}
//	fout.close();
//	sem_post(&locks[file]);
//}

void Writer::Write(char buf[MEMORY_WIDTH], int file) {
	sem_wait(&locks[file]);
	char fileName[MEMORY_WIDTH] = "";
	sprintf(fileName, "%d.rec", file);
	FILE* myFile = fopen(fileName, "r+");
	int offset = (((unsigned char) buf[0] * 256 + (unsigned char) buf[1]) * 256
			+ (unsigned char) buf[2]) * 256 + (unsigned char) buf[3];
	std::cout << "Offset: " << offset << std::endl;
	fseek(myFile, offset, SEEK_SET);
	for (int i = 4; i < MEMORY_WIDTH && buf[i] != 0; ++i) {
		fputc(buf[i], myFile);
	}
	fclose(myFile);
	sem_post(&locks[file]);
}

void Writer::Sentinel(int fileNo) {
	MemoryManager* memInstance = MemoryManager::getInstance();
	int count = 0;
	while (memInstance->memory[255] == 1) {
		int pageId = memInstance->getPageWithId(fileNo);
		while (pageId < 0) {
			usleep(rand() % 10 + 1);
			pageId = memInstance->getPageWithId(fileNo);
		}
		Writer::Write(memInstance->memory + pageId * MEMORY_WIDTH, fileNo);
		memInstance->freePage(pageId);
		count++;
	}
}

} /* namespace OS */
