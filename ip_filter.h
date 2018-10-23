#pragma once

//#include <cassert>
//#include <cstdlib>
//#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using ip_t = std::vector<std::string>;
using ip_pool_t = std::vector<ip_t>;

#define IPV4_PARTS      4

ip_pool_t filter_any(const ip_pool_t &ip_pool, unsigned char num);

template <typename... Args>
ip_pool_t filter(const ip_pool_t &ip_pool, Args... args);

