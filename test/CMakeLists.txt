
# requires CMake 2.6.3 or later
ENABLE_TESTING()

SET(ENGINE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/rts")


FIND_PACKAGE(Boost 1.35.0 COMPONENTS unit_test_framework REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

FIND_PACKAGE(SDL REQUIRED)
INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIR})

#INCLUDE_DIRECTORIES(BEFORE lib/lua/include)
INCLUDE_DIRECTORIES(${ENGINE_SOURCE_DIR})
INCLUDE_DIRECTORIES(${ENGINE_SOURCE_DIR}/System/)

AUX_SOURCE_DIRECTORY("${ENGINE_SOURCE_DIR}/System/Net/" test_UDPListener_src)
list(APPEND test_UDPListener_src "${ENGINE_SOURCE_DIR}/System/Net/UDPListener.cpp")
list(APPEND test_UDPListener_src "${ENGINE_SOURCE_DIR}/System/Net/RawPacket.cpp")
list(APPEND test_UDPListener_src "${ENGINE_SOURCE_DIR}/System/Net/PackPacket.cpp")
list(APPEND test_UDPListener_src "${ENGINE_SOURCE_DIR}/System/Net/UDPConnection.cpp")
list(APPEND test_UDPListener_src "${ENGINE_SOURCE_DIR}/System/Net/Connection.cpp")
list(APPEND test_UDPListener_src "${ENGINE_SOURCE_DIR}/System/Net/Socket.cpp")
list(APPEND test_UDPListener_src "${CMAKE_CURRENT_SOURCE_DIR}/engine/System/NullLogOutput.cpp")
list(APPEND test_UDPListener_src "${CMAKE_CURRENT_SOURCE_DIR}/engine/System/NullGlobalConfig.cpp")
list(APPEND test_UDPListener_src "${CMAKE_CURRENT_SOURCE_DIR}/engine/System/Nullerrorhandler.cpp")
#AUX_SOURCE_DIRECTORY("${ENGINE_SOURCE_DIR}/System/FileSystem/" test_UDPListener_src)
#AUX_SOURCE_DIRECTORY("${ENGINE_SOURCE_DIR}/System/" test_UDPListener_src)
#list(APPEND test_UDPListener_src "${ENGINE_SOURCE_DIR}/System/LogOutput.cpp")
#list(APPEND test_UDPListener_src "${ENGINE_SOURCE_DIR}/System/Util.cpp")
#list(APPEND test_UDPListener_src "${ENGINE_SOURCE_DIR}/Game/GameVersion.cpp")

list(APPEND test_UDPListener_src "${CMAKE_CURRENT_SOURCE_DIR}/engine/System/Net/TestUDPListener.cpp")

add_definitions(-DBOOST_TEST_DYN_LINK)

ADD_EXECUTABLE(test_UDPListener ${test_UDPListener_src})
TARGET_LINK_LIBRARIES(test_UDPListener ${SDL_LIBRARY})
TARGET_LINK_LIBRARIES(test_UDPListener ${Boost_REGEX_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_PROGRAM_OPTIONS_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_SIGNALS_LIBRARY} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

list(APPEND test_bitops_src "${CMAKE_CURRENT_SOURCE_DIR}/engine/System/Testbitops.cpp")
ADD_EXECUTABLE(test_bitops ${test_bitops_src})
TARGET_LINK_LIBRARIES(test_bitops ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

ADD_TEST(NAME testUDPListener COMMAND test_UDPListener)
ADD_TEST(NAME testbitops COMMAND test_bitops)
