#include <iostream>
#include <functional>
#include "SK/Concurrency/ThreadPool.h"


tthread::mutex coutMonitor;


void countTo(unsigned count)
{
	for (unsigned i = 1; i <= count; ++i)
	{
		//tthread::lock_guard<tthread::mutex> lock(coutMonitor);
		std::cout << i << std::endl; 
	}
}


int
main(int argc, char *argv[]) {

	SK::Concurrency::ThreadPool threadPool;
	const unsigned threadCount = threadPool.threadCount();
	std::cout << "Running tasks in " << threadCount << " threads." << std::endl;
	for (unsigned i = 0; i < threadCount; ++i)
	{
		threadPool.submit(std::bind(&countTo, 10), i);
	}
	return 0;
}
