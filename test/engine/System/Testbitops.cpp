#include "System/bitops.h"

#define BOOST_TEST_MODULE bitops
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(CountBitsTestCases)
{

  BOOST_CHECK(count_bits_set(0) == 0);
  BOOST_CHECK(count_bits_set(1) == 1);
  BOOST_CHECK(count_bits_set(4294967295u) == 32);
  BOOST_CHECK(count_bits_set(16843216u) == 6);

}

BOOST_AUTO_TEST_CASE(NextPowerOfTwoTestCase) {

  BOOST_CHECK(next_power_of_2(0) == 0);
  BOOST_CHECK(next_power_of_2(1) == 1);
  BOOST_CHECK(next_power_of_2(3) == 4);
  BOOST_CHECK(next_power_of_2(536870000u) == 536870912);

}
