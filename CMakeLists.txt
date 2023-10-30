cmake_minimum_required (VERSION 3.8)

project ("simpleCli" LANGUAGES C)

include(GNUInstallDirs)
message(STATUS "Project will be build at: ${PROJECT_BINARY_DIR}")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})   #设置静态库输出路径
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})   #设置动态库输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})	  #设置可执行文件输出路径
message(STATUS "lib: ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
message(STATUS "dll: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
message(STATUS "exe: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")


set (CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/install)
message(STATUS "Project will be installed at: ${CMAKE_INSTALL_PREFIX}")

set(INSTALL_LIBDIR ${CMAKE_INSTALL_PREFIX}/lib)           #设置静态库安装路径
set(INSTALL_BINDIR ${CMAKE_INSTALL_PREFIX}/bin)           #设置动态库安装路径
set(INSTALL_INCLUDEDIR ${CMAKE_INSTALL_PREFIX}/include)   #设置头文件安装路径

# to build dll
add_subdirectory(src)

# to test
#enable_testing()
add_subdirectory(test)
