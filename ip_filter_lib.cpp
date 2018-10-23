#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "ip_filter.h"

auto filter_any(const ip_pool_t &ip_pool, unsigned char num)
{
    ip_pool_t ipf;  // filtered
    for (auto ip : ip_pool)
    {
        for (int i = 0 ; i < IPV4_PARTS ; ++i)
        {
            if (ip[i] == std::to_string(num))
            {
                ipf.push_back(ip);
                break;
            }
        }
    }
    return ipf;
}

template <typename... Args>
auto filter(const ip_pool_t &ip_pool, Args... args)
{
    const int a[] = {args...};

    ip_pool_t ipf;  // filtered
    for (auto ip : ip_pool)
    {
//        std::cout << "ip:" << ip[0] << "." << ip[1] << "." << ip[2] << "." << ip[3] << std::endl;
        bool rc = true;
        int b = 0;
        for (auto j : a)
        {
//            std::cout << "    ip[j]:" << ip[b] << " | " << std::to_string(j) << std::endl;
//            if (ip[b] != std::to_string(j))
            if (std::stoi(ip[b]) != j)
            {
                rc = false;
                break;
            }
            if (++b > IPV4_PARTS)
                break;
        }
        if (rc)
            ipf.push_back(ip);
    }

    return ipf;
}

