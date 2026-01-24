project(WinAPI_EGL)
cmake_minimum_required(VERSION 3.5)

set(SOURCE_DIR "src")

# If WIN32 is given the property WIN32_EXECUTABLE will be set on the target created
# https://cmake.org/cmake/help/v3.0/command/add_executable.html
# When this property is set to true the executable when linked on Windows will be created with a WinMain() entry point instead of just main()
add_executable(WinAPI_EGL WIN32 ${SOURCE_DIR}/main.cpp)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/angle/include")
target_link_libraries(WinAPI_EGL "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/angle/lib/windows-x64/libEGL.lib")
target_link_libraries(WinAPI_EGL "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/angle/lib/windows-x64/libGLESv2.lib")