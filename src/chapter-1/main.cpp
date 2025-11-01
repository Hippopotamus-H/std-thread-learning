#include <iostream>
#include <thread>
#include <functional>
#include <gtest/gtest.h>

TEST(stdThread, default_constructor) {
    std::thread t;
    EXPECT_FALSE(t.joinable());
}


TEST(stdThread, move_constructor) {

    std::thread t([]() {
        std::cout << "move_test" << std::endl; });

    EXPECT_TRUE(t.joinable());

    std::thread mt = std::move(t);

    EXPECT_FALSE(t.joinable());
    EXPECT_TRUE(mt.joinable());

    if (mt.joinable())
    {
        mt.join();
    }
    EXPECT_FALSE(mt.joinable());
}

// 调用普通函数
int custom_f(int a, int b)
{
    std::cout << "custom_f run" << std::endl;
    return a + b;
}
TEST(stdThread, custom_function) {

    std::thread t(&custom_f, 2, 3);
    EXPECT_TRUE(t.joinable());
    if (t.joinable())
    {
        t.detach();
    }
    EXPECT_FALSE(t.joinable());
}

// 调用类成员函数
class custom_cls {
public:
    int test_mem(int a, int b) {
        std::cout << "member_f run" << std::endl;
        return a + b;
    }
};
TEST(stdThread, member_function) {
    custom_cls cls;
    std::thread t(&custom_cls::test_mem,&cls, 2, 3);
    EXPECT_TRUE(t.joinable());
    if (t.joinable())
    {
        t.detach();
    }
    EXPECT_FALSE(t.joinable());
}

// 传递引用
int ref_f(int& a, int b)
{
    std::cout << "ref_f run" << std::endl;
    a = a + b;
    return a;
}
TEST(stdThread, ref_parmeter) {
    int a = 2;
    std::thread t(ref_f,std::ref(a), 3);
    EXPECT_TRUE(t.joinable());
    if (t.joinable())
    {
        t.join();
    }
    EXPECT_FALSE(t.joinable());
    EXPECT_TRUE(a == 5);
}

TEST(stdThread, detach) {
    int a = 2;
    std::thread t(ref_f, std::ref(a), 3);
    EXPECT_TRUE(t.joinable());
    if (t.joinable())
    {
        t.detach();
    }
    // 睡眠 2 秒
    std::this_thread::sleep_for(std::chrono::seconds(2));
    EXPECT_FALSE(t.joinable());

    // 这里只有执行线程执行完毕后，再执行才会true，所以当前线程sleep 2秒
    EXPECT_TRUE(a == 5);
}


TEST(stdThread, get_id) {
    int a = 2;
    std::thread t(ref_f, std::ref(a), 3);
    EXPECT_TRUE(t.joinable());
    std::cout << "run t thread id " << t.get_id() << std::endl;
    if (t.joinable())
    {
        t.join();
    }
    EXPECT_FALSE(t.joinable());

    std::thread::id id= t.get_id();
    std::thread::id curId = std::this_thread::get_id();
    std::cout << "runed t thread id " << id << std::endl;
    std::cout << "cur thread id " << curId << std::endl;
    EXPECT_FALSE(id== curId);
}

TEST(stdThread, hardware_concurrency) {
    int a = std::thread::hardware_concurrency();
    std::cout << "hardware_concurrency count " << a << std::endl;
    EXPECT_TRUE(a >= 0);
}

int main(int argc, char** argv)
{

    // 初始化gtest
    ::testing::InitGoogleTest(&argc, argv);

    // 运行所有测试
    return RUN_ALL_TESTS();
	return 0;
}