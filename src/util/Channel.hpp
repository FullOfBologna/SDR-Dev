#include <thread>
#include <condition_variable>
#include <mutex>

template<typename T>
class Channel
{

public:
    Channel();
    ~Channel();

    //Attempt to allow Channel to push whenever. It's possible this will lock indefinitely if either it's unable to acquire the lock, or 
    void put(std::array<T,MAXIMUM_BUFFER_SIZE>& dataBuffer, size_t bufferSize){
        std::unique_lock<std::mutex> lock(m_mutex);
//      m_cond.wait(lock, [&](){return data_ready});
        //type of auto = std::array<T,MAXIMUM_BUFFER_SIZE>::iterator 
        for(auto it = dataBuffer.begin(); it != dataBuffer.end(); ++it)
        {
            if(it > (dataBuffer.begin() + bufferSize))
            {
                break;
            }
            auto data = *it;
            m_buffer.push(data);
        }
        m_cond.notify_one();
    }

private:
    std::condition_variable m_condVar;
    std::mutex m_mutex;
    std::queue<T> m_buffer; //Decision Point between using a queue and using an array
                            
}
