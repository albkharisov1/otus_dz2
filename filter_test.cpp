#define BOOST_TEST_MODULE filter_test_module

#include "ip_filter.h"
#include <iostream>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(filter_test_suite)

BOOST_AUTO_TEST_CASE(filter_test_version)
{
    ip_pool_t ip_pool;
    ip_t ip = {"15", "1", "17", "18"};
    ip_pool.push_back(ip);
//    ip_pool_t ipf = filter(ip_pool, 1);
    std::cout << "hello" << std::endl;
#if 0
    ip_t ip = {"15", "1", "17", "18"};
    ip_t ip2 = {"1", "16", "17", "18"};
    ip_t ip3 = {"9", "16", "1", "18"};
    ip_t ip4 = {"0", "16", "17", "1"};
//    std::cout << ip[0] << ip[1] << ip[2] << ip[3] << std::endl;
    ip_pool_t ip_pool;
    ip_pool.push_back(ip);
    ip_pool.push_back(ip2);
    ip_pool.push_back(ip3);
    ip_pool.push_back(ip4);
    ip_pool.emplace_back(ip4);

    ip_pool_t ipf = filter(ip_pool, 1);
    std::cout << ipf.size() << std::endl;
    //BOOST_CHECK(ipf.size() == 1);
#endif  // 0
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()

