project(third_party)
cmake_minimum_required(VERSION 3.5)

#########
# options

###########
# libraries

include(ExternalProject)

if(AVM_TARGET_PLATFORM_WIN32)
    ExternalProject_Add(angle
            SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/angle
            CMAKE_ARGS
            )
endif()

if(AVM_TARGET_PLATFORM_WIN32)
    add_dependencies(exg angle)
endif()