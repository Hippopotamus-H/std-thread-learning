#include "calculatepi.h"
#include <random>
#include <thread>
#include <vector>
#include <atomic>

CalculatePi::CalculatePi(uint64_t n, bool multiThread /* = false */, unsigned int threadCount /* = 5 */)
	: mTotalSamples(n), mbMultiThread(multiThread),mInCircleCounts(0)
{
	mThreadCount = std::max(std::thread::hardware_concurrency(), threadCount);
}


unsigned int CalculatePi::threadCount() const
{
	return mThreadCount;
}

void CalculatePi::setThreadCount(unsigned int n)
{
	mThreadCount = std::max(std::thread::hardware_concurrency(), n);
}

void CalculatePi::setMode(bool multiThread)
{
	mbMultiThread = multiThread;
}

double CalculatePi::run()
{
	mInCircleCounts = 0;
	if (mbMultiThread && mThreadCount > 1) {
		return multiThreadRun();
	}
	else {
		return singleThreadRun();
	}
}

double CalculatePi::singleThreadRun()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dis(0.0, 1.0);

	uint64_t inside_circle = 0;

	for (uint64_t i = 0; i < mTotalSamples; ++i) {
		double x = dis(gen);
		double y = dis(gen);

		if (x * x + y * y <= 1.0) {
			inside_circle++;
		}
	}

	return 4.0 * inside_circle / mTotalSamples;
}

double CalculatePi::multiThreadRun()
{
	std::vector<std::thread> threads;
	std::vector<uint64_t> results(mThreadCount, 0);

	uint64_t samplesPerThread = mTotalSamples / mThreadCount;
	uint64_t remainingSamples = mTotalSamples % mThreadCount;

	// 创建并启动所有线程
	for (unsigned int i = 0; i < mThreadCount; ++i) {
		uint64_t samples = samplesPerThread;
		if (i == 0) {
			samples += remainingSamples; // 第一个线程处理余数
		}

		threads.emplace_back(&CalculatePi::threadTask, this,
			samples, std::ref(results[i]));
	}

	// 等待所有线程完成
	for (auto& thread : threads) {
		thread.join();
	}

	// 汇总结果
	uint64_t totalInsideCircle = 0;
	for (auto count : results) {
		totalInsideCircle += count;
	}

	return 4.0 * totalInsideCircle / mTotalSamples;
}

void CalculatePi::threadTask(uint64_t samples, uint64_t& result)
{
	thread_local std::random_device rd;
	thread_local std::mt19937 gen(rd());
	thread_local std::uniform_real_distribution<double> dis(0.0, 1.0);

	uint64_t inside_circle = 0;

	for (uint64_t i = 0; i < samples; ++i) {
		double x = dis(gen);
		double y = dis(gen);

		if (x * x + y * y <= 1.0) {
			inside_circle++;
		}
	}

	result = inside_circle;
}