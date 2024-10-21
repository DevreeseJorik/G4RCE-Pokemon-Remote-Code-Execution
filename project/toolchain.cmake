set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_CROSSCOMPILING TRUE)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(CMAKE_C_COMPILER_WORKS 1)

set(CMAKE_C_COMPILER "arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "arm-none-eabi-g++")
set(CMAKE_ASM_COMPILER "arm-none-eabi-as")

set(CMAKE_C_FLAGS "-mcpu=arm946e-s -mtune=arm946e-s -mthumb -march=armv5te -Os -nostartfiles -nodefaultlibs -fno-builtin -ffunction-sections --data-sections -Wl,--gc-sections -fno-unroll-loops -fomit-frame-pointer" )

set(DEFAULT_LINKING_DIR ${CMAKE_CURRENT_SOURCE_DIR}/linking)
set(DEFAULT_C_LINKERFILE ${DEFAULT_LINKING_DIR}/c_linker.ld)
set(DEFAULT_ASM_LINKERFILE ${DEFAULT_LINKING_DIR}/asm_linker.ld)
set(DEFAULT_SYMBOLFILE ${DEFAULT_LINKING_DIR}/symbols.sym)

set(CMAKE_FIND_ROOT_PATH ${CMAKE_SYSROOT})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
