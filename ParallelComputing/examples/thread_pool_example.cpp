#include <iostream>
#include <vector>
#include <chrono>

#include <threadpool.h>

int main()
{

    pc::ThreadPool pool(4);
    std::vector< std::future<int> > results;

    auto result = pool.enqueue([](int answer){return answer;},42);

    return 0;
}
