#pragma once

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using ip_t = std::vector<uint8_t>;
using ip_pool_t = std::vector<ip_t>;

ip_pool_t filter_any(const ip_pool_t &ip_pool, unsigned char num)
{
    ip_pool_t ipf;  // filtered
    for (auto ip : ip_pool)
    {
        if (std::any_of(ip.cbegin(), ip.cend(), [num](unsigned char s)
                    { return s == num; } ))
        {
            ipf.push_back(ip);
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
        bool rc = true;
        int b = 0;
        for (auto j : a)
        {
            if (ip[b] != j)
            {
                rc = false;
                break;
            }
            ++b;
        }
        if (rc)
            ipf.push_back(ip);
    }

    return ipf;
}

