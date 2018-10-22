#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using ip_pool_t = std::vector<std::vector<std::string>>;

template <typename... Args>
auto filter(const ip_pool_t &ip_pool, Args... args)
{
    const int a[] = {args...};

    ip_pool_t ipf;  // filtered
    for (auto ip : ip_pool)
    {
        bool rc = true;
        for (auto j : a)
        {
            if (ip[j] != std::to_string(a[j]))
            {
                rc = false;
                break;
            }
        }
        if (rc)
            ipf.push_back(ip);
    }

    return ipf;
}


// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
auto split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

void printIp(const std::vector<std::string> &ip)
{
    for(auto ip_part = ip.cbegin(); ip_part != ip.cend(); ++ip_part)
    {
        if (ip_part != ip.cbegin())
        {
            std::cout << ".";
        }
        std::cout << *ip_part;
    }
}

void printIpPool(const ip_pool_t &v)
{
    for(auto ip = v.cbegin(); ip != v.cend(); ++ip)
    {
        printIp(*ip);
        std::cout << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    (void) argc;    // suppress warnings
    (void) argv;    // suppress warnings

    ip_pool_t ip_pool;

    try
    {

        for(std::string line; std::getline(std::cin, line);)
        {
            auto v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

//        printIpPool(ip_pool);
        // TODO reverse lexicographically sort
        std::sort(ip_pool.rbegin(), ip_pool.rend());
        printIpPool(ip_pool);
        std::cout << "sort" << std::endl;

        auto ipfiltered = filter(ip_pool, 1);
        printIpPool(ipfiltered);
//        ipfiltered = filter(ip_pool, 46, 70);        // std::move implicitly
//        auto ip4670 = filter_any(ip_pool, 46);
//        printIpPool(ip_pool);               // std::move implicitly

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
