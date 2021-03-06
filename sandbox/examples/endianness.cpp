#include <iostream>
#include <cstdint>
#include <cassert>

#if defined(_WIN32)
#include <windows.h>

int main(int argc, char* argv[]) {
  std::cout << std::hex << 0x0A0B << std::endl;
  {
    uint32_t net_ulong = _byteswap_ulong(0xDEADBEEF);
    std::cout << std::hex << net_ulong << std::endl;
    assert(0xEFBEADDE == net_ulong);
  }

  {
    uint32_t net_ulong = _byteswap_ulong(0x00000A0B);
    std::cout << std::hex << net_ulong << std::endl;
    assert(0x0B0A0000 == net_ulong);
  }

  {
    uint16_t net_ushort = _byteswap_ushort(0x0A0B);
    std::cout << std::hex << net_ushort << std::endl;
    assert(0x0B0A == net_ushort);
  }
}
#else

#include <netinet/in.h>

int main(int argc, char *argv[]) {
  {
    uint32_t net_ulong = htonl(0xDEADBEEF);
    std::cout << std::hex << net_ulong << std::endl;
    assert(0xEFBEADDE == net_ulong);
  }
}


#endif // defined(_WIN32)
