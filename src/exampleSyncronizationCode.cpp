#include <cassert>
#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <optional>
#include <condition_variable>

template<typename T>
class Channel {
    static constexpr std::size_t default_max_length = 10;
  public:
    using value_type = T;

    explicit Channel(std::size_t max_length = default_max_length)
      : max_length_(max_length) {}

    std::optional<value_type> next() {
        std::unique_lock locker(mtx_);
        cond_.wait(locker, [this]() {
            return !buffer_.empty() || closed_; 
        });
        
        if (buffer_.empty()) {
          assert(closed_);
          return std::nullopt;
        }
        
        value_type val = buffer_.front();
        buffer_.pop();
        cond_.notify_one();
        return val;
    }
    
    void put(value_type val) {
        std::unique_lock locker(mtx_);
        cond_.wait(locker, [this]() {
            return buffer_.size() < max_length_;
        });

        buffer_.push(std::move(val));
        cond_.notify_one();
    }

    void close() {
        std::scoped_lock locker(mtx_);
        closed_ = true;
        cond_.notify_all();
    }

  private:
    std::size_t max_length_;  
    std::queue<value_type> buffer_;
    bool closed_ = false;    

    std::mutex mtx_;
    std::condition_variable cond_; 
};

void producer_main(Channel<int>& chan, int val) {
    // Don't use while(true), it's Undefined Behavior
    while (val >= 0) {
        chan.put(val);
        std::cout << "Produced " << val << std::endl;
        val--;
    }
}

void consumer_main(Channel<int>& chan) {
    bool running = true;
    while (running) {
        auto val = chan.next();
        if (!val) {
            running = false;
            continue;
        }

        std::cout << "Consumed " << *val << std::endl;
    };
}

int main()
{
    // You are responsible for ensuring the channel outlives both threads.
    Channel<int> channel;

    std::thread producer_thread(producer_main, std::ref(channel), 13);
    std::thread consumer_thread(consumer_main, std::ref(channel));
    
    producer_thread.join();
    channel.close();

    consumer_thread.join();

    return 0;
}
