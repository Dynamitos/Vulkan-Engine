#include "threadpool.h"



Thread::Thread()
{
	worker = std::thread(&Thread::queueLoop, this);
}
Thread::~Thread()
{
	if (worker.joinable())
	{
		wait();
		queueMutex.lock();
    	destroying = true;
    	condition.notify_one();
		queueMutex.unlock();
		worker.join();
	}
}

void Thread::queueLoop()
{
	while (true)
	{
		std::function<void()> job;
		{
			std::unique_lock<std::mutex> lock(queueMutex);
			condition.wait(lock, [this] { return !jobQueue.empty() || destroying; });
			if (destroying)
			{
				break;
			}
			job = jobQueue.front();
		}
		job();
		{
			std::lock_guard<std::mutex> lock(queueMutex);
			jobQueue.pop();
			condition.notify_one();
		}
	}
}

void ThreadPool::addJob(std::function<void()> function)
{
	std::lock_guard<std::mutex> lock(queueMutex);
	jobQueue.push(std::move(function));
	condition.notify_one();
}

void ThreadPool::wait()
{
	std::unique_lock<std::mutex> lock(queueMutex);
	condition.wait(lock, [this]() { return jobQueue.empty(); });
}

void ThreadPool::setThreadCount(uint32_t count)
{
	threads.clear();
	for (auto i = 0; i < count; i++)
    {
		threads.push_back(std::make_unique<Thread>());
	}
}
void ThreadPool::wait()
{
	for (auto &thread : threads)
	{
		thread->wait();
	}
}
