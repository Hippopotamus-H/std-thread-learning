#include "calculatepi.h"
#include <iostream>

int main(int argc, char* argv[]) {

	uint64_t sample;
	std::cin >> sample;
    CalculatePi c(sample);

	{
		auto start = std::chrono::high_resolution_clock::now();
		c.setMode(true);
		c.setThreadCount(5);
		double ret = c.run();
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
		std::cout << " 多线程线程数：" << c.threadCount() << " samples: " << sample << " 执行时间 : " << duration.count() << " 秒" << std::endl;
		std::cout << " 结果: " << ret << std::endl;
	}
	
	{
		auto start = std::chrono::high_resolution_clock::now();
		c.setMode(false);
		double ret = c.run();
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
		std::cout << " 单线程 samples: " << sample << " 执行时间: " << duration.count() << " 秒" << std::endl;
		std::cout << " 结果: " << ret << std::endl;
	}

	std::cout << "计算完成" << std::endl;
	int a;
	std::cin >> a;
}