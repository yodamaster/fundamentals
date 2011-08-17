#ifndef ___LIST_IO_INC__
# define ___LIST_IO_INC__

# include <glynos/list.hpp>
# include <ostream>


template <
    class T
    >
std::ostream &operator << (std::ostream &os, const glynos::list<T> &list) {
    std::shared_ptr<const typename glynos::list<T>::node_type> node;
    for (node = list.head(); node; node = node->next) {
        os << *node->value << ", ";
    }
    return os;
}


#endif // ___LIST_IO_INC__
