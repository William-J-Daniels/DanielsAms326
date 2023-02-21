#ifndef PC_THREADPOOL_H
#define PC_THREADPOOL_H

#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <future>
#include <memory>

namespace pc {

//auto total_threads = std::thread::hardware_concurrency();

class ThreadPool
{
public:
    // just like for std::thread, no move or copy
    ThreadPool(const ThreadPool &) = delete;
    ThreadPool(ThreadPool &&)      = delete;
    ThreadPool &operator= (const ThreadPool &) = delete;
    ThreadPool &operator= (ThreadPool &&)      = delete;

    ThreadPool(std::size_t init_threads);
    virtual ~ThreadPool();

    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args)
        -> std::future<typename std::result_of<F(Args...)>::type>;

private:
    std::vector<std::thread> Threads;
    std::queue<std::function<void()>> Jobs;

    // ownership management
    std::mutex Mtx;
    std::condition_variable Condition;
    bool stop = false;
};

}

#endif // PC_THREADPOOL_H
