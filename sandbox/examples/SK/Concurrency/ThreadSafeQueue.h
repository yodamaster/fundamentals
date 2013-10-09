#ifndef SK_THREAD_SAFE_QUEUE_INC
#define SK_THREAD_SAFE_QUEUE_INC

#pragma once

#include <memory>
#include "TinyThread/Tinythread.h"

template <typename T>
class Foo;

namespace SK {
  namespace Concurrency {
    template <typename T>
    class ThreadSafeQueue {

      ThreadSafeQueue(const ThreadSafeQueue&);
      ThreadSafeQueue& operator=(const ThreadSafeQueue&);

    public:

      ThreadSafeQueue() : m_head(new Node), m_tail(m_head) {}

      bool tryPop(T& value) {
        Node* old_head = tryPopHead(value);
        bool popped = old_head != 0;
        delete old_head;
        return popped;
      }

      void push(const T& value) {
        T* data = new T(value);
        Node* node = new Node;
        {
          tthread::lock_guard<tthread::mutex> lock(m_tailMutex);
          m_tail->data = data;
          Node* new_tail = node;
          m_tail->next = node;
          m_tail = new_tail;
        }
        m_dataCond.notify_one();
      }

      bool empty() const {
        tthread::lock_guard<tthread::mutex> lock(m_headMutex);
        return m_head == getTail();
      }

    private:

      struct Node {
        T* data;
        Node* next;
      };

      Node* popHead() {
        Node* old_head = m_head;
        m_head = old_head->next;
        return old_head;
      }

      Node* getTail() {
        tthread::lock_guard<tthread::mutex> lock(m_tailMutex);
        return m_tail;
      }

      Node* tryPopHead(T& value) {
        tthread::lock_guard<tthread::mutex> lock(m_headMutex);
        if (m_head != getTail()) {
          value = *m_head->data;
          return popHead();
        }
        return 0;
      }

      tthread::mutex m_headMutex;
      Node* m_head;
      tthread::mutex m_tailMutex;
      Node* m_tail;
      tthread::condition_variable m_dataCond;
    };
  } // namespace Concurrency
} // namespace SK

#endif // SK_THREAD_SAFE_QUEUE_INC
