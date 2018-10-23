#pragma once

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using ip_t = std::vector<std::string>;
using ip_pool_t = std::vector<ip_t>;

#define IPV4_PARTS      4

ip_pool_t filter_any(const ip_pool_t &ip_pool, unsigned char num)
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
ip_pool_t filter(const ip_pool_t &ip_pool, Args... args)
{
    const int a[] = {args...};
    static_assert(sizeof...(Args) <= 4, "filter gets 4 parameters max + ip_pool");

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

