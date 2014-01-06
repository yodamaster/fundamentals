
#include <utility>
#include <stack>
#include <vector>
#include <iostream>

namespace sandbox
{
  template <typename Sequence>
  std::pair<Sequence, Sequence> partition(const Sequence& sequence, const typename Sequence::value_type& pivot)
  {
    std::pair<Sequence, Sequence> result;
    for (auto item : sequence) {
      if (item < pivot) {
        result.first.push_back(item);
      }
      else {
        result.second.push_back(item);
      }
    }
    return result;
  }

  template <typename Sequence>
  Sequence quicksort(const Sequence& input) {
    std::stack<Sequence> sequences;
    sequences.push(input);
    Sequence output;

    while (!sequences.empty()) {
      Sequence tmp = sequences.top();
      sequences.pop();

      if (tmp.size() == 1) {
        output.push_back(tmp[0]);
        continue;
      }

      auto pivot = tmp.back();
      tmp.pop_back();
      auto left_right = partition(tmp, pivot);

      if (!left_right.second.empty()) {
        sequences.push(left_right.second);
      }
      Sequence pivot_seq;
      pivot_seq.push_back(pivot);
      sequences.push(pivot_seq);
      if (!left_right.first.empty()) {
        sequences.push(left_right.first);
      }
    }
    return output;
  }
} // namespace sandbox

int main(int argc, char* argv[])
{
  std::vector<int> sequence;
  sequence.push_back(5);
  sequence.push_back(4);
  sequence.push_back(2);
  sequence.push_back(0);
  sequence.push_back(9);
  sequence.push_back(2);
  sequence.push_back(3);
  sequence.push_back(7);
  auto sorted = sandbox::quicksort(sequence);
  for (auto value : sorted)
    {
      std::cout << value << ", ";
    }
  std::cout << std::endl;
  return 0;
}
