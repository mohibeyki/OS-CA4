/*
 * Main.cpp
 *
 *  Created on: May 17, 2013
 *      Author: mohi
 */

#include <iostream>
#include <MemoryManager.h>
#include <Reader.h>
#include <Writer.h>
#include <pthread.h>

using namespace std;
using namespace OS;

int main(int argc, char* argv[]) {
	MemoryManager* memInstance = MemoryManager::getInstance();
	memInstance->memory[255] = 1;
	int n, m;
	cin >> n >> m;
	pthread_t threads_n[n];
	pthread_t threads_m[2 * m];
	for (long long i = 1; i <= n; ++i) {
		std::cerr << "Running reader : " << i << std::endl;
		pthread_create(&threads_n[i - 1], NULL, OS::Reader::Run, (void*) i);
	}
	OS::Writer::Init(m);
	for (long long i = 1; i <= 2 * m; ++i) {
		std::cerr << "Running sentinel : " << i << " for file " << ((i + 1) / 2)
				<< std::endl;
		pthread_create(&threads_m[i - 1], NULL, OS::Writer::Sentinel,
				(void*) ((i + 1) / 2));
	}

	for (int i = 0; i < n; ++i)
		pthread_join(threads_n[i], NULL);

	while (!memInstance->isEmpty()) {
		cerr << "OPERATION IN PROGRESS, WAITING FOR THEM TO COMPLETE" << endl;
		sleep(1);
	}
	memInstance->memory[255] = 0;
	cerr << "KILLING SERVER" << endl;

	for (int i = 0; i < 2 * m; ++i)
		pthread_join(threads_m[i], NULL);

	cerr << "EXITING" << endl;
	return 0;
}
