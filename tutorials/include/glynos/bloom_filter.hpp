//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __GLYNOS_BLOOM_FILTER_INC__
# define __GLYNOS_BLOOM_FILTER_INC__


# include <functional>
# include <algorithm>
# include <cstring>
# include <climits>


// http://en.literateprograms.org/Bloom_filter_(C)
// http://code.google.com/p/java-bloomfilter/
// http://code.google.com/p/bloom/
namespace glynos {
template <
    class Key,
    class Value,
    class Hash
    >
class bloom_filter {
public:

    explicit bloom_filter(unsigned int size = 1000)
        : data_(new char[((size + CHAR_BIT - 1) / CHAR_BIT)]),
          size_(size) {

    }

    bloom_filter(const bloom_filter &other)
        : data_(new char[((other.size_ + CHAR_BIT - 1) / CHAR_BIT)]),
          size_(other.size_) {
        std::memcpy(data_, other.data_, ((size_ + CHAR_BIT - 1) / CHAR_BIT));
    }

    bloom_filter(bloom_filter &&other)
        : data_(new char[other.size_]),
          size_(other.size_) {
        std::memcpy(data_, other.data_, ((size_ + CHAR_BIT - 1) / CHAR_BIT));
        other.data_ = 0;
        other.size_ = 0;
    }

    bloom_filter &operator = (const bloom_filter &other) {
        bloom_filter(other).swap(*this);
        return *this;
    }

    bloom_filter &&operator = (bloom_filter &&other) {
        bloom_filter(other).swap(*this);
        return *this;
    }

    ~bloom_filter() {
        delete [] data_;
    }

    void swap(bloom_filter &other) {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
    }

    void insert(const Key &key, const Value &value) {
        for (unsigned int i = 0; function_count_; ++i)
        {
            // setbit
        }
    }

    bool exists(const Key &key) const {
        for (unsigned int i = 0; function_count_; ++i)
        {
            // getbit
        }
        return false;
    }

private:

    char *data_;
    unsigned int size_;
    unsigned int function_count_;

};
} // namespace glynos


#endif // __GLYNOS_BLOOM_FILTER_INC__
