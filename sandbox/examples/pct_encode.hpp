#ifndef __GLYNOS_FUNDAMENTALS_SANDBOX_EXAMPLES_PCT_ENCODE_INC__
#define __GLYNOS_FUNDAMENTALS_SANDBOX_EXAMPLES_PCT_ENCODE_INC__


#include <iterator>
#include <cassert>


namespace glynos {
namespace detail {
template <
	typename CharT
	>
inline
CharT hex_to_letter(CharT in) {
	switch (in) {
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
        return in + '0';
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	default:
        return in - 10 + 'A';
	}
	return CharT();
}

template <
	typename CharT,
	class OutputIterator
	>
void encode_char(CharT in, OutputIterator &out) {
	switch (in)
	{
	case 'a':
	case 'A':
	case 'b':
	case 'B':
	case 'c':
	case 'C':
	case 'd':
	case 'D':
	case 'e':
	case 'E':
	case 'f':
	case 'F':
	case 'g':
	case 'G':
	case 'h':
	case 'H':
	case 'i':
	case 'I':
	case 'j':
	case 'J':
	case 'k':
	case 'K':
	case 'l':
	case 'L':
	case 'm':
	case 'M':
	case 'n':
	case 'N':
	case 'o':
	case 'O':
	case 'p':
	case 'P':
	case 'q':
	case 'Q':
	case 'r':
	case 'R':
	case 's':
	case 'S':
	case 't':
	case 'T':
	case 'u':
	case 'U':
	case 'v':
	case 'V':
	case 'w':
	case 'W':
	case 'x':
	case 'X':
	case 'y':
	case 'Y':
	case 'z':
	case 'Z':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case '-':
	case '.':
	case '_':
	case '~':
	case '/':
		out++ = in;
		break;
	default:
		out++ = '%';
		out++ = hex_to_letter(in >> 4);
		out++ = hex_to_letter(in & 0x0f);
		;
	}
}
} // namespace detail

template <
    typename InputIterator,
    typename OutputIterator
    >
OutputIterator encode(InputIterator first,
					  InputIterator last,
					  OutputIterator out) {
    auto it = first;
    while (it != last) {
		detail::encode_char(*it, out);
		++it;
    }
    return out;
}

template <
    class InputIterator,
    class OutputIterator
    >
OutputIterator encode(const InputIterator &in_begin,
					  const InputIterator &in_end,
					  const OutputIterator &out_begin) {
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    InputIterator it = in_begin;
    OutputIterator out = out_begin;
    while (it != in_end) {
		detail::encode_char(*it, out);
		++it;
    }
    return out;
}

template <class String>
String encode_user_info(const String &user_info) {
	String encoded;
	encode_user_info(std::begin(user_info), std::end(user_info),
					 std::back_inserter(encoded));
	return std::move(encoded);
}
} // namespace glynos


#endif // __GLYNOS_FUNDAMENTALS_SANDBOX_EXAMPLES_PCT_ENCODE_INC__
