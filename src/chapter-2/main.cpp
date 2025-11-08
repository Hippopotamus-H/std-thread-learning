#include <iostream>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <gtest/gtest.h>


std::mutex mtx;
std::timed_mutex tmtx;

TEST(stdUniqueLock, constructor) {
    std::unique_lock<std::mutex> uniqueLock(mtx);
    EXPECT_TRUE(uniqueLock.owns_lock());
}


// 延迟锁定，比lock_guard更灵活
TEST(stdUniqueLock, defer_lock_constructor) {
    std::unique_lock<std::mutex> uniqueLock(mtx,std::defer_lock);
    EXPECT_FALSE(uniqueLock.owns_lock());

    uniqueLock.lock();
    EXPECT_TRUE(uniqueLock.owns_lock());

    uniqueLock.unlock();
    EXPECT_FALSE(uniqueLock.owns_lock());
}

// 时间约束的锁定尝试
//TEST(stdUniqueLock, time_constrained_constructor_timeOut) {
//
//    {
//        std::thread t([] {
//            std::lock_guard<std::timed_mutex> lock(tmtx);
//            std::this_thread::sleep_for(std::chrono::seconds(15));
//            });
//
//        t.detach();
//    }
//
//    // 睡眠5秒确保上面的线程首先执行
//    std::this_thread::sleep_for(std::chrono::seconds(5));
//
//    // 只等待5秒
//    std::unique_lock<std::timed_mutex> uniqueLock(tmtx, std::chrono::seconds(5));
//    EXPECT_FALSE(uniqueLock.owns_lock());
//}


const int N = 21;
int cur = 0;
std::condition_variable cv;
void printOdd()
{
    while (true)
    {
        std::unique_lock<std::mutex> uniqueLock(mtx);
        cv.wait(uniqueLock, [] {return cur % 2 == 1; });

        if (cur > N)
        {
            ++cur;
            cv.notify_one();
            break;
        }
        std::cout << std::this_thread::get_id() << " print: " << cur << std::endl;
        ++cur;
        cv.notify_one();
    }
}

void printEven()
{
    while (true)
    {
        std::unique_lock<std::mutex> uniqueLock(mtx);
        cv.wait(uniqueLock, [] {return cur % 2 == 0; });

        if (cur > N)
        {
            ++cur;
            cv.notify_one();
            break;
        }
        std::cout << std::this_thread::get_id() << " print: " << cur << std::endl;
        ++cur;
        cv.notify_one();
    }
}

// 两个线程交替打印奇偶数
TEST(stdConditionVariable, use) {
    cur = 0;
    std::thread oddThread(printOdd);
    std::thread evenThread(printEven);

    if (evenThread.joinable())
    {
        evenThread.join();
    }

    if (oddThread.joinable())
    {
        oddThread.join();
    }
}

// 简洁版本
void printNumbers(bool isOdd) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);

        // 等待：要么轮到我了，要么工作完成了
        cv.wait(lock, [isOdd] {
            return cur > N || (cur % 2 == (isOdd ? 1 : 0));
            });

        if (cur > N) {
            cv.notify_all();  // 通知所有线程退出
            break;
        }

        std::cout << std::this_thread::get_id()
            << " print " << (isOdd ? "odd" : "even")
            << ": " << cur << std::endl;
        ++cur;
        cv.notify_one();
    }
}

TEST(stdConditionVariable, useFun) {
    cur = 0;
    std::thread oddThread(printNumbers,true);
    std::thread evenThread(printNumbers,false);

    if (evenThread.joinable())
    {
        evenThread.join();
    }

    if (oddThread.joinable())
    {
        oddThread.join();
    }
}

int main(int argc, char** argv)
{

    // 初始化gtest
    ::testing::InitGoogleTest(&argc, argv);

    // 运行所有测试
    return RUN_ALL_TESTS();
	return 0;
}