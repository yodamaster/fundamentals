#ifndef SK_THREAD_SAFE_QUEUE_INC
#define SK_THREAD_SAFE_QUEUE_INC

#include <memory>

namespace SK {
	template <typename T>
	class ThreadSafeQueue {

		Queue(const Queue&);
		Queue& operator = (const Queue&);

	public:

		ThreadSafeQueue() 
			: head(new Node), tail(head.get()) {

		}

		

	private:

		struct Node {
			T* data;
			T* next;
		};

		Node* head;
		Node* tail;

	};
} // namespace SK

#endif // SK_THREAD_SAFE_QUEUE_INC
