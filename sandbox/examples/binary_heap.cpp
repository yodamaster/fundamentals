#include <algorithm>
#include <vector>
#include <numeric>
#include <iostream>


namespace sandbox {
template <class T>
class binary_heap {

public:

  typedef typename std::vector<T>::iterator iterator;


  template <class Range>
  binary_heap(const Range &list)
    : heap_(std::begin(list), std::end(list)) {
    build();
  }

  void push(T value) {
    heap_.push_back(value);
    percolate_up();
  }

  T top() {
    assert(!heap_.empty());
    return *heap_.begin();
  }

  void pop() {
    percolate_down();
    heap_.pop_back();
  }

  iterator begin() { return heap_.begin(); }
  iterator end() { return heap_.end(); }

  void build() {
    std::make_heap(std::begin(heap_), std::end(heap_));
  }

  void percolate_up() {
    std::push_heap(std::begin(heap_), std::end(heap_));
  }

  void percolate_down() {
    std::pop_heap(std::begin(heap_), std::end(heap_));
  }

private:

  std::vector<T> heap_;

};
} // namespace sandbox


template <class Range>
void print_range(Range &range) {
  std::cout << "[";
  std::for_each(std::begin(range), std::end(range), [] (int value) {
      std::cout << value << ", ";
    });
  std::cout << "]" << std::endl;
}


int main(int argc, char *argv[]) {

  std::vector<int> ints(10);
  std::iota(std::begin(ints), std::end(ints), 0);
  std::random_shuffle(std::begin(ints), std::end(ints));
  sandbox::binary_heap<int> heap(ints);
  print_range(heap);
  std::cout << "=====" << std::endl;

  std::make_heap(std::begin(ints), std::end(ints));
  print_range(heap);
  std::cout << "=====" << std::endl;

  heap.push(-1);
  print_range(heap);
  std::cout << "=====" << std::endl;

  heap.pop();
  print_range(heap);
  std::cout << "=====" << std::endl;
}
