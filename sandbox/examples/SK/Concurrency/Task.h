#ifndef SK_CONCURRENCY_TASK_INC
#define SK_CONCURRENCY_TASK_INC

#include <functional>

namespace SK
{
	namespace Concurrency
	{
		namespace Detail
		{
			class TaskBase
			{
				TaskBase(const TaskBase&);
				TaskBase& operator=(const TaskBase&);

			public:

				TaskBase()
				{
				}

				virtual ~TaskBase()
				{
				}

				virtual void operator()() = 0;

				virtual TaskBase* clone() = 0;
			};

			template <class Func>
			class TaskWrapper : public TaskBase
			{
				TaskWrapper(const TaskWrapper&);
				TaskWrapper operator=(const TaskWrapper&);

			public:

				TaskWrapper(const Func& func) : m_func(func)
				{
				}

				virtual ~TaskWrapper()
				{
				}

				virtual void operator()()
				{
					m_func();
				}

				virtual TaskWrapper* clone()
				{
					return new TaskWrapper(m_func);
				}

			private:

				Func m_func;
			};
		} // namespace Detail

		class Task
		{
		public:

			Task() : m_task(0)
			{
			}

			template <class Func>
			Task(const Func& func)
				: m_task(new Detail::TaskWrapper<Func>(func))
			{
			}

			Task(const Task& other) : m_task(other.m_task->clone())
			{
			}

			Task& operator=(const Task& other)
			{
				Task(other).swap(*this);
				return *this;
			}

			virtual ~Task()
			{
				delete m_task;
			}

			void swap(Task& other) throw()
			{
				std::swap(m_task, other.m_task);
			}

			void operator()()
			{
				assert(m_task && "Uncallable task.");
				(*m_task)();
			}

		private:

			Detail::TaskBase* m_task;
		};

	} // namespace Concurrency
} // namespace SK

#endif // SK_CONCURRENCY_TASK_INC
