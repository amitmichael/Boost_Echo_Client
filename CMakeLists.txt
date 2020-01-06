cmake_minimum_required(VERSION 3.15)
project(Boost_Echo_Client)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost 1.57.0 COMPONENTS system filesystem REQUIRED)

if(Boost_FOUND)

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})

endif()

add_executable(Boost_Echo_Client Boost_Echo_Client/src/ConnectionHandler.cpp Boost_Echo_Client/include/ConnectionHandler.h Boost_Echo_Client/src/echoClient.cpp Boost_Echo_Client/src/ClientKeyboard.cpp Boost_Echo_Client/include/ClientKeyboard.h Boost_Echo_Client/src/ClientSocket.cpp Boost_Echo_Client/include/ClientSocket.h Boost_Echo_Client/src/Frame.cpp Boost_Echo_Client/include/Frame.h Boost_Echo_Client/src/Inventory.cpp Boost_Echo_Client/include/Inventory.h Boost_Echo_Client/src/Book.cpp Boost_Echo_Client/include/Book.h)

if(Boost_FOUND)

    target_link_libraries(Boost_Echo_Client ${Boost_LIBRARIES})

endif()

