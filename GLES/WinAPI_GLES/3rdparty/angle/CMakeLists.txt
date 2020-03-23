cmake_minimum_required(VERSION 3.7)
project(angle)

if(WIN32)
    if(MINGW)
        set(AVM_TARGET_COMPILER "mingw")
        execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpmachine
                OUTPUT_VARIABLE AVM_TARGET_ARCH
                OUTPUT_STRIP_TRAILING_WHITESPACE)
        if(AVM_TARGET_ARCH MATCHES "amd64|x86_64|AMD64")
            set(AVM_TARGET_ARCH "x64")
        else()
            set(AVM_TARGET_ARCH "x86")
        endif()

    elseif(MSVC)
        set(AVM_TARGET_COMPILER "msvc")
        if(CMAKE_CL_64)
            set(AVM_TARGET_ARCH "x64")
        else()
            set(AVM_TARGET_ARCH "x86")
        endif()
    endif()

else()
    message(FATAL_ERROR "Angle EGL is only for WIN32!!")
endif()

set(CONF_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
configure_file(ANGLEConfig.cmake.in ANGLEConfig.cmake @ONLY)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/ANGLEConfig.cmake DESTINATION CMake)

install(FILES
        lib/windows-${AVM_TARGET_ARCH}/libEGL.lib
        lib/windows-${AVM_TARGET_ARCH}/libGLESv2.lib
        DESTINATION lib)

install(FILES
        bin/windows-${AVM_TARGET_ARCH}/d3dcompiler_47.dll
        bin/windows-${AVM_TARGET_ARCH}/libEGL.dll
        bin/windows-${AVM_TARGET_ARCH}/libGLESv2.dll
        DESTINATION bin)

install(DIRECTORY include DESTINATION .)
