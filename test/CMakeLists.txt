#find_package(GTest REQUIRED)

add_executable(
	test_cli
	test.c
 "test.h")


target_link_libraries(
	test_cli
	simpleCli
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

#add_test(
#	NAME	test_cli
#	COMMAND test_cli
#)