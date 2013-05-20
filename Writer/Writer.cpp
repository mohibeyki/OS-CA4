/*
 * Writer.cpp
 *
 *  Created on: May 18, 2013
 *      Author: mohi
 */

#include "Writer.h"
#include <fstream>
#include <iostream>

namespace OS {

sem_t* locks;

void Writer::Init(int m) {
	locks = new sem_t[m + 1];
	for (; m > 0; --m) {
		char fileName[MEMORY_WIDTH] = "";
		sprintf(fileName, "corrected files/%d.txt", m);
		std::ofstream fout(fileName, std::ofstream::out);
		fout.close();
		sem_init(&locks[m], 0, 1);
	}
}

void Writer::Write(char buf[MEMORY_WIDTH], int file) {
	char fileName[MEMORY_WIDTH] = "";
	sprintf(fileName, "corrected files/%d.txt", file);
	int offset = (((unsigned char) buf[0] * 256 + (unsigned char) buf[1]) * 256
			+ (unsigned char) buf[2]) * 256 + (unsigned char) buf[3];
	sem_wait(&locks[file]);
	FILE* myFile = fopen(fileName, "r+");
	fseek(myFile, offset, SEEK_SET);
	for (int i = 4; i < MEMORY_WIDTH && buf[i] != 0; ++i) {
		fputc(buf[i], myFile);
	}
	fclose(myFile);
	sem_post(&locks[file]);
}

void* Writer::Sentinel(void* fileVoid) {
	long long fileNumber = (long long) fileVoid;

	MemoryManager* memInstance = MemoryManager::getInstance();
	while (memInstance->memory[255] == 1) {
		int pageId = memInstance->getPageWithId(fileNumber);
		while (pageId < 0 && memInstance->memory[255] == 1) {
			usleep(rand() % 10 + 1);
			pageId = memInstance->getPageWithId(fileNumber);
		}
		if (memInstance->memory[255] == 0)
			break;

		Writer::Write(memInstance->memory + pageId * MEMORY_WIDTH, fileNumber);
		memInstance->freePage(pageId);
	}
	return NULL;
}

} /* namespace OS */
