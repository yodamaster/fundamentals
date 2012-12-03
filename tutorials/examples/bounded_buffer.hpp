//            Copyright (c) Glyn Matthews 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __GLYNOS_BOUNDED_BUFFER_INC__
# define __GLYNOS_BOUNDED_BUFFER_INC__

# include <vector>
# include <mutex>

namespace glynos {
template <
	typename T
	>
class bounded_buffer {

public:

	typedef std::vector<T> buffer_type;
	typedef typename buffer_type::value_type value_type;
	typedef typename buffer_type::size_type size_type;

	bounded_buffer(size_type size)
		: buffer_(size)
		, first_(0)
		, last_(0)
		, buffered_(0) {

	}

	void consume(const T &value) {
		std::mutex::lock lock(monitor_);
		while (buffered_ == buffer_.size()) {
			buffer_not_full_.wait(lock);
		}

		buffer_[last_] = value;
		last_ = (last_ + 1) % buffer_.size();
		++buffered_;
		buffer_not_empty_.notify_one();
	}

	T produce() const {
		std::mutex::lock lock(monitor_);
		while (buffered_ == 0) {
			buffer_not_empty_.wait(lock);
		}

		T value = std::move(buffer_[first_]);
		first_ = (first_ + 1) % buffer_.size();
		--buffered_;
		buffer_not_full_.notify_one();
		return std::move(value);
	}

private:

	std::condition_variable buffer_not_full_, buffer_not_empty_;
	std::mutex monitor_;

	buffer_type buffer_;
	size_type first_, last_, buffered_;

};
} // namespace glynos


#endif // __GLYNOS_BOUNDED_BUFFER_INC__
