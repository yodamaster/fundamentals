#ifndef SK_THREAD_POOL_INC
#define SK_THREAD_POOL_INC

#include <thread>
#include <functional>

namespace SK {
	class ThreadPool {


	public:

		ThreadPool();

		~ThreadPool();

		void submit(std::function<void ()> job);

	private:

		void doWork();

		bool m_done;

	};
} // namespace SK

#endif // SK_THREAD_POOL_INC
