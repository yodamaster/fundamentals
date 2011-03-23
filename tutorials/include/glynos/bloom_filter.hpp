//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __GLYNOS_BLOOM_FILTER_INC__
# define __GLYNOS_BLOOM_FILTER_INC__


// http://en.literateprograms.org/Bloom_filter_(C)
namespace glynos {
template <
    class Key,
    class Value,
    class Hash
    >
class bloom_filter {
public:

    bool insert(const Key &key, const Value &value);
    std::shared_ptr<const Value> exists(const Key &key) const;
    template <
        class Func
        >
    void walk(const Func &func);

};
} // namespace glynos


#endif // __GLYNOS_BLOOM_FILTER_INC__
