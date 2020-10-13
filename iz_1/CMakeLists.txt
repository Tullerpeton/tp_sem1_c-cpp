cmake_minimum_required(VERSION 3.17)
set(PROJECT iz_1)
project(${PROJECT})

set(CMAKE_CXX_STANDARD 14)

# Using files
set (HEADERS
        Task_manager/task_manager.h
        Errors/error_message.h
        Geometry/point3D.h
        Geometry/tetrahedron.h
        Geometry/geometry_operations.h
        Errors/error_code.h)

set (SOURCES
        Task_manager/task_manager.c
        Errors/error_message.c
        Geometry/tetrahedron.c
        Geometry/point3D.c
        Geometry/geometry_operations.c)


# Release flags
set(RELEASE_CXX_FLAGS "-std=c++14 -Wall -Werror -pedantic")
set(RELEASE_C_FLAGS "-std=c99 -Wall -Werror -pedantic")
# Debug flags
set(DEBUG_CXX_FLAGS "-std=c++14 -Wall -pedantic -g3")
set(DEBUG_C_FLAGS "-std=c99 -Wall -pedantic -g3")


# Choice target
message("BUILD_TYPE -- ${CMAKE_BUILD_TYPE}")
if (CMAKE_BUILD_TYPE MATCHES Debug)

    # Set flags
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DEBUG_CXX_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${DEBUG_C_FLAGS}")

    add_executable (${PROJECT}
            main.c
            ${SOURCES}
            )

elseif (CMAKE_BUILD_TYPE MATCHES Test)
    # Add gtest
    add_subdirectory(googletest)
    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

    # Set flags
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${RELEASE_CXX_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${RELEASE_C_FLAGS}")


    add_executable(${PROJECT}
            Tests/test.cpp
            Tests/unit_tests.cpp
            ${SOURCES}
            )
    target_link_libraries(${PROJECT}
            gtest
            gtest_main
            )

    add_test(run_tests run_tests)

elseif (CMAKE_BUILD_TYPE MATCHES Release)
    # Set flags
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${RELEASE_CXX_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${RELEASE_C_FLAGS}")

    add_executable (${PROJECT}
            main.c
            ${SOURCES}
            )
endif ()

# Include project directories
target_include_directories(${PROJECT} PRIVATE "${PROJECT_SOURCE_DIR}")

