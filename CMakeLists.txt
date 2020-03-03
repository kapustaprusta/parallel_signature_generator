project(parallel_signature_generator)
cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

if (UNIX)
    find_package (Threads)
endif()

if(WIN32)
    set(BOOST_ROOT "C://local//boost_1_72_0")
endif()

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.72.0 REQUIRED COMPONENTS program_options)

include_directories(${Boost_INCLUDE_DIRS})

set(SOURCES
    psg.cpp

    src/defs/defs.h

    src/reader/reader.h

    src/reader/file_reader/file_reader.h
    src/reader/file_reader/file_reader.cpp

    src/writer/writer.h

    src/writer/file_writer/file_writer.h
    src/writer/file_writer/file_writer.cpp

    src/hash_calculator/hash_calculator.h

    src/hash_calculator/md5_hash_calculator/md5_hash_calculator.h
    src/hash_calculator/md5_hash_calculator/md5_hash_calculator.cpp

    src/task/task.h

    src/task/hash_task/hash_task.h
    src/task/hash_task/hash_task.cpp

    src/threadpool/threadpool.h
    src/threadpool/threadpool.cpp

    src/cli_parser/cli_parser.h
    src/cli_parser/cli_parser.cpp
)

add_executable(parallel_signature_generator ${SOURCES})

if (WIN32)
    target_link_libraries(parallel_signature_generator PUBLIC ${Boost_LIBRARIES})
endif()

if (UNIX)
    target_link_libraries (parallel_signature_generator PUBLIC ${CMAKE_THREAD_LIBS_INIT}
                                                        PUBLIC ${Boost_LIBRARIES}
    )
endif()
