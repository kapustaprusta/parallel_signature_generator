project(parallel_signature_generator)
cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

if(WIN32)
    set(BOOST_ROOT "C://local//boost_1_72_0")
endif()

find_package(Boost 1.72.0 REQUIRED COMPONENTS)

include_directories(${Boost_INCLUDE_DIRS})

set(SOURCES
    psg.cpp

    src/reader/reader.h

    src/reader/file_reader/file_reader.h
    src/reader/file_reader/file_reader.cpp

    src/writer/writer.h

    src/writer/file_writer/file_writer.h
    src/writer/file_writer/file_writer.cpp

    src/hash_calculator/hash_calculator.h

    src/hash_calculator/md5_hash_calculator/md5_hash_calculator.h
    src/hash_calculator/md5_hash_calculator/md5_hash_calculator.cpp

    src/data_structures/shared_queue/shared_queue.h

    src/task/task.h

    src/task/reader_task/reader_task.h
    src/task/reader_task/reader_task.cpp

    src/task/writer_task/writer_task.h
    src/task/writer_task/writer_task.cpp
)

add_executable(parallel_signature_generator ${SOURCES})
target_link_libraries(parallel_signature_generator PUBLIC ${Boost_LIBRARIES})