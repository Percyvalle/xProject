#pragma once

#include "xProjectHeaders_common.hpp"

namespace Xp {

	template<typename T>
	class Queue {
	private:
		std::mutex m_mutexQueue;
		std::mutex m_blockingQueue;
		std::deque<T> m_dequeQueue;
		std::condition_variable m_cvQueue;

	public:
		Queue() = default;
		Queue(const Queue<T>&) = delete;
		~Queue() { clear(); };

		void push_back(const T& _value)
		{
			std::lock_guard<std::mutex> lock(m_mutexQueue);
			m_dequeQueue.emplace_back(_value);

			std::unique_lock<std::mutex> unique_lock(m_blockingQueue);
			m_cvQueue.notify_one();
		}
		void push_front(const T& _value)
		{
			std::lock_guard<std::mutex> lock(m_mutexQueue);
			m_dequeQueue.emplace_front(_value);

			std::unique_lock<std::mutex> unique_lock(m_blockingQueue);
			m_cvQueue.notify_one();
		}

		T pop_back()
		{
			std::lock_guard<std::mutex> lock(m_mutexQueue);
			T temp = m_dequeQueue.back();
			m_dequeQueue.pop_back();

			return temp;
		}

		T pop_front()
		{
			std::lock_guard<std::mutex> lock(m_mutexQueue);
			T temp = m_dequeQueue.front();
			m_dequeQueue.pop_front();

			return temp;
		}

		T& front() 
		{
			std::lock_guard<std::mutex> lock(m_mutexQueue);
			return m_dequeQueue.front(); 
		}
		T& back() 
		{
			std::lock_guard<std::mutex> lock(m_mutexQueue);
			return m_dequeQueue.back(); 
		}

		bool empty() 
		{
			std::lock_guard<std::mutex> lock(m_mutexQueue);
			return m_dequeQueue.empty(); 
		}

		void clear() 
		{
			std::lock_guard<std::mutex> lock(m_mutexQueue);
			m_dequeQueue.clear(); 
		}
		size_t count() 
		{
			std::lock_guard<std::mutex> lock(m_mutexQueue);
			return m_dequeQueue.size(); 
		}

		void wait() {
			while (empty()) {
				std::unique_lock<std::mutex> lock(m_blockingQueue);
				m_cvQueue.wait(lock);
			}
		}
	};

}