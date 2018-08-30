cmake_minimum_required(VERSION 2.8)

PROJECT(COCMobile${MYVER})
set (CMAKE_BUILD_TYPE DEBUG)
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../../binRun/server)
#set(CMAKE_CXX_FLAGS "-D_CONSOLE -g -Wall -O2 -D_FILE_OFFSET_BITS=64 -D_LARGE_FILE -pipe -Wno-invalid-offsetof -fcheck-new  -D_POSIX_THREADS -D_POSIX_THREAD_SAFE_FUNCTIONS -D_REENTRANT")
set(CMAKE_CXX_FLAGS "-D_CONSOLE -g -Wall -O2 -D_LARGE_FILE -pipe -Wno-invalid-offsetof -fcheck-new  -D_POSIX_THREADS -D_POSIX_THREAD_SAFE_FUNCTIONS -D_REENTRANT")
ADD_LIBRARY(cocgame  STATIC CocGameComm.cpp TcpPacket.cpp)
#ADD_EXECUTABLE(COCMobile testmain.cpp)

link_directories(${PROJECT_BINARY_DIR}/../../binRun/server ${PROJECT_SOURCE_DIR}/../../common/lib /usr/local/lib)
link_libraries(cocgame${MYVER} libjson_linux-gcc-4.1.2_libmt common glib-2.0 curl pthread libtcpChatComm libtlcrypto)  

include_directories(usr/local/inlcude ${PROJECT_SOURCE_DIR}/ ${PROJECT_SOURCE_DIR}/../ ${PROJECT_SOURCE_DIR}/../include ${PROJECT_SOURCE_DIR}/../tcpChatComm ${PROJECT_SOURCE_DIR}/../../opensource/jsoncpp/include)

