cmake_minimum_required(VERSION 2.8)
project(PublicVision)
set(CMAKE_INCLUDE_PATH "/home/dean/dean.test/darknet/include")
set(CMAKE_LIBRARY_PATH "/home/dean/dean.test/darknet/libdarknet.so")
find_package(catkin REQUIRED COMPONENTS
        ezshell
        )
find_package(Boost REQUIRED COMPONENTS
        filesystem
        system
        thread)
find_package(OpenCV REQUIRED COMPONENTS
        )
find_package(CUDA REQUIRED)

if (NOT Boost_FOUND)
    message("未发现Boost")
endif ()

aux_source_directory(. srcs)

include_directories(${Boost_INCLUDE_DIR})

catkin_package(
        INCLUDE_DIRS Vision

        LIBRARIES PublicVision

        CATKIN_DEPENDS
        ezshell
)
### include TL package
include_directories(${catkin_INCLUDE_DIRS})
include_directories("${CUDA_INCLUDE_DIRS}")
message(----${CMAKE_LIBRARY_PATH})

option(Test "This is a option for Test, test the package" OFF)
ADD_DEFINITIONS(-DGPU -DCUDNN -DOPENCV)

set(SOURCES_DIRECTORIES
        camera
        capture
        Vision
        yolo
        opencv_no_thread
        #command
        )

foreach (DIRECTORY ${SOURCES_DIRECTORIES})
    message(STATUS "-- Sources: Adding ${DIRECTORY}/")
    include(${DIRECTORY}/source.cmake)
    set(PREFIXED_SOURCES)
    foreach (SOURCE ${Source})
        set(PREFIXED_SOURCES ${PREFIXED_SOURCES} ${DIRECTORY}/${SOURCE})
    endforeach (SOURCE)
    set(ALL_SOURCES ${ALL_SOURCES} ${PREFIXED_SOURCES})
endforeach (DIRECTORY)

foreach (SSSS ${ALL_SOURCES})
    message(STATUS "-- Sources: ${SSSS}")
endforeach (SSSS)

foreach (DIRECTORY ${SOURCES_DIRECTORIES})
    if (${Test} STREQUAL "ON")
        message(STATUS "-- Sources: Test ${DIRECTORY}/test.cpp")
        add_executable(${DIRECTORY} ${ALL_SOURCES} ${DIRECTORY}/test.cpp ${srcs})
        target_link_libraries(${DIRECTORY} ${catkin_LIBRARIES})
        target_link_libraries(${DIRECTORY} ${Boost_LIBRARIES} ${OpenCV_LIBS} ${CMAKE_LIBRARY_PATH})
    else ()
        add_library(${DIRECTORY} ${ALL_SOURCES})
        target_link_libraries(${DIRECTORY} ${catkin_LIBRARIES} ${Boost_LIBRARIES} ${OpenCV_LIBS} ${CMAKE_LIBRARY_PATH})
    endif ()
endforeach (DIRECTORY)

add_library(PublicVision SHARED ${ALL_SOURCES} )

target_link_libraries(PublicVision ${catkin_LIBRARIES} ${OpenCV_LIBS} ${Boost_LIBRARIES} ${CMAKE_LIBRARY_PATH})

