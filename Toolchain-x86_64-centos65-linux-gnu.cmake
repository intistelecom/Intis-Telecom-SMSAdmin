# edit this file to find right compiler and root path
# the name of the target operating system
set(CMAKE_VERBOSE_MAKEFILE FALSE)
set(CMAKE_SYSTEM_NAME Linux)

# here is the target environment located
set(CMAKE_FIND_ROOT_PATH /opt/x86_64-centos65-linux-gnu)

# which compilers to use for C and C++
set(CMAKE_C_COMPILER   ${CMAKE_FIND_ROOT_PATH}/bin/gcc)
set(CMAKE_CXX_COMPILER ${CMAKE_FIND_ROOT_PATH}/bin/g++)

# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search
# programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_CXX_LINK_FLAGS "-Wl,--warn-unresolved-symbols,--allow-shlib-undefined")
