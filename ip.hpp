#ifndef NEXTLIB_IP_HPP
#define NEXTLIB_IP_HPP

#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32")
#else
#include <arpa/inet.h>
#include <netdb.h>
#endif

#include <string>

namespace Next
{
    namespace IP
    {
        int GetByURL(std::string url, std::string &ip) {
            ip = "";
            #ifdef _WIN32
            WSADATA d;
            WORD VER = MAKEWORD(2, 2);
            if ((WSAStartup(VER, &d) != 0) || (VER != d.wVersion)) {
                WSACleanup();
                return 1;
            }

            hostent *h;
            in_addr **addr_list;
            if ((h = gethostbyname(url.c_str())) == NULL) {
                return 1;
            }
            
            addr_list = (in_addr **) h->h_addr_list;

            for (int i = 0; addr_list[i] != NULL; i++) {
                ip += inet_ntoa(*addr_list[i]);
                return 0;
            }

            return 1;
            #else
            struct hostent *he;
            struct in_addr **addr_list;

            if ((he = gethostbyname(url.c_str())) == NULL) {
                return 1;
            }

            addr_list = (struct in_addr **) he->h_addr_list;

            for (int i = 0; addr_list[i] != NULL; i++) {
                ip += inet_ntoa(*addr_list[i]);
                return 0;
            }

            return 1;
            #endif
        }
    }
}

#endif // NEXTLIB_IP_HPP