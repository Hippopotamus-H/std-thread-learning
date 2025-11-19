#ifndef CALCULATEPI_H
#define CALCULATEPI_H

#include <random>
#include <chrono>
#include <thread>
#include <mutex>
class CalculatePi {
public:
	CalculatePi(uint64_t n, bool multiThread = false, unsigned int threadCount = 5);
	~CalculatePi() = default;
	double run();
	unsigned int threadCount() const;
	void setThreadCount(unsigned int n);
	void setMode(bool multiThread);
private:
	void CalculatePi::threadTask(uint64_t samples, uint64_t& result);
	double CalculatePi::multiThreadRun();
	double CalculatePi::singleThreadRun();
private:
	uint64_t mTotalSamples;
	uint64_t mInCircleCounts;
	std::mutex mMutex;
	bool mbMultiThread;
	uint16_t mThreadCount;
};

#endif // CALCULATEPI_H
