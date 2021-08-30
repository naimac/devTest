#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
#include <queue>
#include <mutex>

#define interval 300

std::queue<int> nbQ;
std::mutex      mut;

// std::thread     th1([&]{read_list();});
// std::thread     th2([&]{write_list();});

void read_list()
{
    int i = 0;
    while (i++ < 7)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        std::lock_guard<std::mutex> guard(mut);
        std::cout << nbQ.front() << std::endl;
        nbQ.pop();
    }
}

void write_list()
{
    int i = 0;

    while (i++ < 7)
    {
        std::lock_guard<std::mutex> guard(mut);
        std::cout << "Push" << std::endl;
        nbQ.push(i);
    }
}

int main() 
{
    std::thread th1(read_list);
    std::thread th2(write_list);

    th1.join();
    th2.join();
}