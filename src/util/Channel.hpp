#ifndef CHANNEL_H_
#define CHANNEL_H_

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
    void put(std::array<T,MAXIMUM_BUFFER_SIZE>& dataBuffer, size_t bufferSize)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cond.wait(lock, [&](){return data_ready});
        //type of auto = std::array<T,MAXIMUM_BUFFER_SIZE>::iterator 
        m_currentBufferSize = bufferSize;

        if(m_currentBufferSize < MAXIMUM_BUFFER_SIZE)
        {
            m_currentBufferSize = bufferSize;
        }else{
            m_currentBufferSize = (size_t)MAXIMUM_BUFFER_SIZE;
        }

        std::copy(dataBuffer.begin(), dataBuffer.begin() + m_currentBufferSize, m_buffer.begin());
        m_condVar.notify_one();
    }


    //Transferring buffer to outgoing buffer by reference instead of transferring ivia return, for performance sake, to avoid any unnecessary calls to copy constructors.
    void receive(std::array<T, MAXIMUM_BUFFER_SIZE>& outputBuffer, size_t& outBufferSize)
    {
        // Needs to be a way to handle communicating the buffer size between the two classes. 
        std::unique_lock<std::mutex> lock(m_mutex);
        // Setup the wait handler
        m_condVar.wait(lock, [&](){return !data_ready});

        outBufferSize = m_currentBufferSize;

        // Rely on put() to handle setting the current          
        std::copy(m_buffer.begin(), m_buffer.begin()+m_currentBufferSize, outputBuffer.begin());

        m_condVar.notify_one();
    }

    void close()
    {
        std::scoped_lock lock(m_mutex);
        m_closed = true;
        cond.notify_all();
    }


private:

    //Need some kind of unit testing perhaps spin up two basic threads at the start to make sure Channel is configured properly? 

    bool m_closed = false;
    std::condition_variable m_condVar;
    std::mutex m_mutex;
    std::array<T,MAXIMUM_BUFFER_SIZE> m_buffer; //Decision Point between using a queue and using an array
    size_t m_currentBufferSize;                                                
}

#endif
