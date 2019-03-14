cmake_minimum_required(VERSION 2.8)
project(ezshell)
set(CMAKE_INCLUDE_PATH "/usr/include")
set(CMAKE_LIBRARY_PATH "/usr/lib/x86_64-linux-gnu/libncurses.so")
find_package(catkin REQUIRED COMPONENTS
        ZeroMQ
        )
find_package(Boost REQUIRED COMPONENTS
        filesystem
        system
        thread)

if (NOT Boost_FOUND)
    message("未发现Boost")
endif ()

aux_source_directory(. srcs)

include_directories(${Boost_INCLUDE_DIR})

catkin_package(
        CATKIN_DEPENDS
        ZeroMQ
)
### include TL package
include_directories(${catkin_INCLUDE_DIRS})


option(Test "This is a option for Test, test the package" OFF)

set(SOURCES_DIRECTORIES
        EZIO
        EZCommand
        EZTools
        EZServer
        EZClient
        EZInput
        EZOutput
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
        target_link_libraries(${DIRECTORY} ${Boost_LIBRARIES} ${CMAKE_LIBRARY_PATH})
    else ()
        add_library(${DIRECTORY} ${ALL_SOURCES})
        target_link_libraries(${DIRECTORY} ${catkin_LIBRARIES} ${Boost_LIBRARIES} ${CMAKE_LIBRARY_PATH})
    endif ()
endforeach (DIRECTORY)


#target_link_libraries(ezshell ${catkin_LIBRARIES})

