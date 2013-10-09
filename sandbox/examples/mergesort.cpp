#include <vector>
#include <iterator>
#include <iostream>

namespace sandbox
{
template <class Sequence>
Sequence merge(Sequence left, Sequence right)
{
	Sequence result;
	unsigned left_i = 0, right_i = 0;
	while (left_i < left.size() || right_i < right.size())
	{
		if (left_i < left.size() && right_i < right.size())
		{
			if (left[left_i] < right[right_i])
			{
				result.push_back(std::move(left[left_i]));
				++left_i;
			}
			else
			{
				result.push_back(std::move(right[right_i]));
				++right_i;
			}
		}
		else if (left_i < left.size())
		{
			result.push_back(std::move(left[left_i]));
			++left_i;
		}
		else
		{
			result.push_back(std::move(right[right_i]));
			++right_i;
		}
	}
	return result;
}

template <class Sequence>
Sequence mergesort(const Sequence &input)
{
	if (input.size() <= 1)
	{
		return input;
	}

	unsigned middle_i = input.size() / 2;
	auto middle = std::begin(input);
	std::advance(middle, middle_i);
	Sequence unsorted_left, unsorted_right;
	std::copy(std::begin(input), middle, std::back_inserter(unsorted_left));
	std::copy(middle, std::end(input), std::back_inserter(unsorted_right));
	return merge(mergesort(unsorted_left), mergesort(unsorted_right));
}

//template <class Sequence>
//Sequence mergesort(const Sequence &input)
//{
//	if (input.size() <= 1)
//	{
//		return input;
//	}
//
//	typename Sequence::difference_type j = 0;
//	for (auto value : input)
//	{
//		for (decltype (j) n = 1; *(n <= j) && (j % (n * 2)) == 0); n *= 2)
//		{
//			//merge(
//		}
//	}
//}

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
	auto sorted = sandbox::mergesort(sequence);
	for (auto value : sorted)
	{
		std::cout << value << ", ";
	}
	std::cout << std::endl;
	return 0;
}
