
#include "System/Net/UDPListener.h"

#define BOOST_TEST_MODULE UDPListener
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(TryBindSocketTestCases)
{
	netcode::SocketPtr socket;
	BOOST_CHECK(netcode::UDPListener::TryBindSocket(11111, &socket, "127.0.0.1"));
	BOOST_CHECK(netcode::UDPListener::TryBindSocket(11111, &socket, "::1"));
	BOOST_CHECK(netcode::UDPListener::TryBindSocket(11111, &socket, "fe80::224:1dff:fecf:df44"));
	BOOST_CHECK(netcode::UDPListener::TryBindSocket(11111, &socket, "::"));
	BOOST_CHECK(netcode::UDPListener::TryBindSocket(11111, &socket, "0.0.0.0"));
}
