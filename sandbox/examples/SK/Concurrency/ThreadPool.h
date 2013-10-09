#ifndef SK_CONCURRENCY_THREAD_POOL_INC
#define SK_CONCURRENCY_THREAD_POOL_INC

#pragma once

#include <functional>
#include <algorithm>
#include <vector>
#include <cassert>
#include "TinyThread/Tinythread.h"
#include "SK/Concurrency/Task.h"
#include "SK/Concurrency/ThreadSafeQueue.h"

namespace SK
{
	namespace Concurrency
	{
		class ThreadPool {

			ThreadPool(const ThreadPool&);
			ThreadPool& operator = (const ThreadPool&);

		public:

			ThreadPool()
				: m_done(false)
			{
				const unsigned threadCount = ThreadPool::threadCount();
				try
				{
					for (unsigned i = 0; i < threadCount; ++i)
					{
						m_threads.push_back(new tthread::thread(&ThreadPool::doWork, this));
						// set thread affinity
					}
				}
				catch (...)
				{
					destroy();
					throw;
				}
			}

			~ThreadPool()
			{
				destroy();
			}

			template <class Func>
			void submit(const Func& task, unsigned core = 0)
			{
				m_workQueue.push(Task(task));
			}

			static unsigned threadCount()
			{
				return tthread::thread::hardware_concurrency();
			}

		private:

			static void doWork(void *data)
			{
				ThreadPool *this_ = static_cast<ThreadPool *>(data);
				while (!this_->m_done)
				{
					Task task;
					if (this_->m_workQueue.tryPop(task))
					{
						task();
					}
					else
					{
						tthread::this_thread::yield();
					}
				}
			}

			void destroy()
			{
				m_done = true;
				const unsigned threadCount = ThreadPool::threadCount();
				for (unsigned i = 0; i < threadCount; ++i)
				{
					if (m_threads[i]->joinable())
					{
						m_threads[i]->join();
					}
					delete m_threads[i];
				}
			}

			bool m_done;
			ThreadSafeQueue<Task> m_workQueue;
			std::vector<tthread::thread*> m_threads;

		};
	} // namespace Concurrency
} // namespace SK

#endif // SK_CONCURRENCY_THREAD_POOL_INC
