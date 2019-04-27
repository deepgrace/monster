#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include <mutex>
#include <queue>
#include <future>
#include <memory>
#include <thread>
#include <vector>
#include <functional>
#include <type_traits>
#include <condition_variable>

namespace monster
{
    class thread_pool
    {
        public:
            thread_pool(size_t size);

            template <typename F, typename... Args>
            auto post(F&& f, Args&&... args);

            ~thread_pool();

        private:
            bool stop = false;
            std::mutex mutex;
            std::condition_variable cond;
            std::vector<std::thread> workers;
            std::queue<std::function<void()>> tasks;
    };

    thread_pool::thread_pool(size_t size)
    {
        for (size_t i = 0; i != size; ++i)
             workers.emplace_back([this]
             {
                 while (true)
                 {
                     std::function<void()> task;
                     {
                         std::unique_lock<std::mutex> lock(mutex);
                         cond.wait(lock, [this]{ return stop || !tasks.empty(); });
                         if (stop && tasks.empty())
                             return;
                         task = std::move(tasks.front());
                         tasks.pop();
                     }
                     task();
                 }
             });
    }

    template <typename F, typename... Args>
    auto thread_pool::post(F&& f, Args&&... args)
    {
        using task_type = std::packaged_task<std::invoke_result_t<F, Args...>()>;
        auto task = std::make_shared<task_type>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        auto fut = task->get_future();
        {
            std::unique_lock<std::mutex> lock(mutex);
            tasks.emplace([task]{ (*task)(); });
        }
        cond.notify_one();
        return fut;
    }

    thread_pool::~thread_pool()
    {
        {
            std::unique_lock<std::mutex> lock(mutex);
            stop = true;
        }
        cond.notify_all();
        for (auto& worker: workers)
             worker.join();
    }
}

#endif
