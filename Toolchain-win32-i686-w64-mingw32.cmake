# the name of the target operating system
SET(CMAKE_SYSTEM_NAME Windows)

# here is the target environment located
SET(CMAKE_FIND_ROOT_PATH /opt/mingw-w32)

# which compilers to use for C and C++
SET(CMAKE_C_COMPILER ${CMAKE_FIND_ROOT_PATH}/bin/i686-w64-mingw32-gcc)
SET(CMAKE_CXX_COMPILER ${CMAKE_FIND_ROOT_PATH}/bin/i686-w64-mingw32-g++)
SET(CMAKE_RC_COMPILER ${CMAKE_FIND_ROOT_PATH}/bin/i686-w64-mingw32-windres)

# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search 
# programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
