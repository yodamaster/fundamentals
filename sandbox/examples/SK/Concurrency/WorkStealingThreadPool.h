#ifndef SK_CONCURRENCY_WORK_STEALING_THREAD_POOL_INC
#define SK_CONCURRENCY_WORK_STEALING_THREAD_POOL_INC

#pragma once

#include <functional>
#include <algorithm>
#include <vector>
#include <cassert>
#include "TinyThread/Tinythread.h"
#include "SK/Concurrency/Task.h"
#include "SK/Concurrency/ThreadSafeQueue.h"
#include "SK/Concurrency/WorkStealingQueue.h"

namespace SK {
  namespace Concurrency {
    class WorkStealingThreadPool {

      WorkStealingThreadPool(const WorkStealingThreadPool&);
      WorkStealingThreadPool& operator=(const WorkStealingThreadPool&);

    public:

      WorkStealingThreadPool() : m_done(false) {
        const unsigned threadCount = WorkStealingThreadPool::threadCount();
        try {
          for (unsigned i = 0; i < threadCount; ++i) {
            m_threads.push_back(
                new tthread::thread(&WorkStealingThreadPool::doWork, this));
            // set thread affinity
          }
        }
        catch (...) {
          destroy();
          throw;
        }
      }

      ~WorkStealingThreadPool() { destroy(); }

      template <class Func>
      void submit(const Func& task, unsigned core = 0) {
        m_workQueue.push(Task(task));
      }

      static unsigned threadCount() {
        return tthread::thread::hardware_concurrency();
      }

    private:

      static void doWork(void* data) {
        WorkStealingThreadPool* this_ =
            static_cast<WorkStealingThreadPool*>(data);
        while (!this_->m_done) {
          // Task task;
          // if (this_->m_workQueue.tryPop(task))
          //{
          //	task();
          //}
          // else if (this_->m_workQueue.trySteal(task))
          //{
          //	task();
          //}
          // else
          //{
          //	tthread::this_thread::yield();
          //}
        }
      }

      void destroy() {
        m_done = true;
        const unsigned threadCount = WorkStealingThreadPool::threadCount();
        for (unsigned i = 0; i < threadCount; ++i) {
          if (m_threads[i]->joinable()) {
            m_threads[i]->join();
          }
          delete m_threads[i];
        }
      }

      bool m_done;
      std::vector<WorkStealingQueue*> m_workQueues;
      std::vector<tthread::thread*> m_threads;

      static WorkStealingQueue* m_localWorkQueue;
      static Static unsigned index;
    };
  } // namespace Concurrency
} // namespace SK

#endif // SK_CONCURRENCY_WORK_STEALING_THREAD_POOL_INC
