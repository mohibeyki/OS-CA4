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
	pthread_t threads_m[m];
	for (long long i = 1; i <= n; ++i) {
		std::cout << "Running reader : " << i << std::endl;
		pthread_create(&threads_n[i], NULL, OS::Reader::run, (void*) i);
	}
	sleep(3);
	OS::Writer::init(m);
	for (long long i = 1; i <= m; ++i) {
		cout << "DEBUG" << endl;
		for (int j = 0; j < 100; j++)
			cout << "MEM: " << j << ' ' << (int) memInstance->memory[j] << endl;
		cout << "ENDDEBUG" << endl;

		std::cout << "Running writer : " << i << std::endl;
		pthread_create(&threads_m[i], NULL, OS::Writer::Sentinel, (void*) i);
		sleep(5);
	}

	for (int i = 0; i < n; ++i)
		pthread_join(threads_n[i], NULL);

	while (!memInstance->isEmpty())
		sleep(1);
	memInstance->memory[255] = 0;

	for (int i = 0; i < m; ++i)
		pthread_join(threads_m[i], NULL);

	return 0;
}
