#include <string>
#include <iostream>
#include <boost/locale.hpp>
#include <boost/algorithm/string/case_conv.hpp>


int
main(int argc, char *argv[]) {
#if defined(_WIN32)
  boost::locale::generator gen;
  std::locale::global(gen(""));
  try {
    std::wstring grussen = L"grüßEN!";
    std::wcout << boost::algorithm::to_upper_copy(grussen) << " "
               << boost::locale::to_upper(grussen) << std::endl;
  }
  catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }
#endif // defined(_WIN32)
  return 0;
}
