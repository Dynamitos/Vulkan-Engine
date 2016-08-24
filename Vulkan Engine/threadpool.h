#include "utils.h"

class Thread
{
private:
	bool destroying = false;
	std::thread worker;
	std::queue<std::function<void()>> jobQueue;
	std::mutex queueMutex;
	std::condition_variable condition;
		// Loop through all remaining jobs
	void queueLoop();

public:
	Thread();
	~Thread();
	// Add a new job to the thread's queue
	void addJob(std::function<void()> function);
		// Wait until all work items have been finished
	void wait();
};

class ThreadPool
{
public:
	std::vector<std::unique_ptr<Thread>> threads;
		// Sets the number of threads to be allocted in this pool
	void setThreadCount(uint32_t count);

		// Wait until all threads have finished their work items
	void wait();
};
