//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __GLYNOS_ALGORITHMS_QUICK_SORT_INC__
# define __GLYNOS_ALGORITHMS_QUICK_SORT_INC__


# include <algorithm>
# include <iterator>


namespace glynos {
  namespace algorithms {
    template <
      class Iter,
      class Pred
      >
    void quick_sort(Iter first, Iter last, const Pred &pred) {
      if (first != last) {
        Iter left = first, right = last;
        Iter pivot = left++;

        while(left != right) {
	  if (pred(*left, *pivot)) {
	    ++left;
	  }
	  else {
	    while((left != right) && pred(*pivot, *right)) {
	      --right;
	    }
	    std::iter_swap(left, right);
	  }
        }

        quick_sort(first, left, pred);
        quick_sort(right, last, pred);
      }
    }


    template <
      class Seq,
      class Pred
      >
    void quick_sort(Seq &seq, const Pred &pred) {
      quick_sort(std::begin(seq), std::end(seq), pred);
    }
  } // namespace algorithms
} // namespace glynos


#endif // __GLYNOS_ALGORITHMS_QUICK_SORT_INC__
