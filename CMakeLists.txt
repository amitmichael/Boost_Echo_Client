cmake_minimum_required(VERSION 3.15)
project(StompBookClubClient)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

find_package(Boost 1.57.0 COMPONENTS system filesystem REQUIRED)

if(Boost_FOUND)

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})

endif()


add_executable(StompBookClubClient StompBookClubClient/src/ConnectionHandler.cpp StompBookClubClient/include/ConnectionHandler.h  StompBookClubClient/src/ClientKeyboard.cpp StompBookClubClient/include/ClientKeyboard.h StompBookClubClient/src/ClientSocket.cpp StompBookClubClient/include/ClientSocket.h StompBookClubClient/src/Inventory.cpp StompBookClubClient/include/Inventory.h StompBookClubClient/src/Book.cpp StompBookClubClient/include/Book.h StompBookClubClient/src/StompEncoderDecoder.cpp StompBookClubClient/include/StompEncoderDecoder.h StompBookClubClient/src/Message.cpp StompBookClubClient/include/Message.h StompBookClubClient/src/User.cpp StompBookClubClient/include/User.h StompBookClubClient/src/MsgInfo.cpp StompBookClubClient/include/MsgInfo.h StompBookClubClient/src/StompBookClubClient.cpp)


if(Boost_FOUND)

    target_link_libraries(StompBookClubClient ${Boost_LIBRARIES})

endif()

