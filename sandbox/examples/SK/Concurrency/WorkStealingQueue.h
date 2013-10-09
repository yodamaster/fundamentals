#ifndef SK_CONCURRENCY_WORK_STEALING_QUEUE_INC
#define SK_CONCURRENCY_WORK_STEALING_QUEUE_INC

#pragma once

#include <deque>
#include "Tinythread/Tinythread.h"
#include "SK/Concurrency/Task.h"

namespace SK {
  namespace Concurrency {
    template <typename T>
    class WorkStealingQueue {
    private:

      WorkStealingQueue(const WorkStealingQueue&);
      WorkStealingQueue& operator=(const WorkStealingQueue&);

    public:

      WorkStealingQueue() {}

      void push(const T& data) {
        tthread::lock_guard<tthread::mutex> lock(m_taskMonitor);
        m_tasks.push_front(data);
      }

      bool tryPop(T& value) {
        tthread::lock_guard<tthread::mutex> lock(m_taskMonitor);
        bool hasTasks = !m_tasks.empty();
        if (hasTasks) {
          value = m_tasks.front();
          m_tasks.pop_front();
        }
        return hasTasks;
      }

      bool trySteal(T& value) {
        tthread::lock_guard<tthread::mutex> lock(m_taskMonitor);
        bool hasTasks = !m_tasks.empty();
        if (hasTasks) {
          value = m_tasks.back();
          m_tasks.pop_back();
        }
        return hasTasks;
      }

    private:

      mutable tthread::mutex m_taskMonitor;
      std::deque<T> m_tasks;
    };
  } // namespace Concurrency
} // namespace SK

// endif // SK_CONCURRENCY_WORK_STEALING_QUEUE_INC
