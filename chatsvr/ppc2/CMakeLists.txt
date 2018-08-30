cmake_minimum_required(VERSION 2.8)

PROJECT(ppc_new${MYVER})
set (CMAKE_BUILD_TYPE DEBUG)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../../binRun/server)

link_directories(${PROJECT_BINARY_DIR}/../../binRun/server ${PROJECT_SOURCE_DIR}/../../common/lib /usr/local/lib)
link_libraries(ppc_new${MYVER} dbclient_new common utility ACE glib-2.0
    tlcrypto BeanstalkClient curl libevent.a libevent_core.a libevent_extra.a
    libevent_pthreads.a pthread libthrift.a libiconv.a libFilter.a
    librdkafka.a libjson_linux-gcc-4.1.2_libmt.a)
include_directories(${PROJECT_SOURCE_DIR}/../../common
${PROJECT_SOURCE_DIR}/../../common/include
${PROJECT_SOURCE_DIR}/../../common/ACE_wrappers
${PROJECT_SOURCE_DIR}/../../opensource/jsoncpp/include)
set(CMAKE_CXX_FLAGS "-D_CONSOLE -g -Wall -O2 -D_CONSOLE -pipe -Wno-invalid-offsetof -fcheck-new -D_ACE_SOCK -D_POSIX_THREADS -D_POSIX_THREAD_SAFE_FUNCTIONS -D_REENTRANT")
add_executable(ppc_new${MYVER} ../tools/kafkaProducter.cpp kafkalog.cpp ../roomcomm/RoomPacketRecv.cpp BigRoomd.cpp  ../tools/common.cpp ../tools/performance.cpp AwardBase.cpp BigRoomServer.cpp beanstalkMsg.cpp   Room.cpp  User.cpp UserManager.cpp dbAccess.cpp)
#zz_CPPFLAGS=-I ../../common -I ../../common/include -Wall -O2 -D_CONSOLE -pipe -Wno-invalid-offsetof -fcheck-new -g -D_ACE_SOCK -D_POSIX_THREADS -D_POSIX_THREAD_SAFE_FUNCTIONS -D_REENTRANT
