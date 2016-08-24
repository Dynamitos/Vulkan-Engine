#include "utils.h"

struct ThreadData
{
    VkCommandPool cmdPool;
    std::vector<VkCommandBuffer> cmdBuffers;
    volatile int workload;
}

class ThreadPool
{
public:
    ThreadPool(uint32_t numThreads);
    ThreadPool();
    ~ThreadPool();
    void addJob(VkDevice device, VkPipeline pipeline, VkBuffer vertBuffer, VkBuffer indices);
private:
    std::vector<ThreadData> threadData;
};
