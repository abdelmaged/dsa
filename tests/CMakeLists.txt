include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/b514bdc898e2951020cbdca1304b75f5950d1f59.zip
  DOWNLOAD_EXTRACT_TIMESTAMP ON
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(sort_test sort_test.cpp)
target_link_libraries(sort_test PRIVATE GTest::gtest_main sorting)

add_executable(data_structure_test data_structure_test.cpp)
target_link_libraries(data_structure_test PRIVATE GTest::gtest_main data_structure)

add_executable(graph_test graph_test.cpp)
target_link_libraries(graph_test PRIVATE GTest::gtest_main graph)

add_executable(algo_test algo_test.cpp)
target_link_libraries(algo_test PRIVATE GTest::gtest_main algo)

include(GoogleTest)
gtest_discover_tests(sort_test)
gtest_discover_tests(data_structure_test)
gtest_discover_tests(graph_test)
gtest_discover_tests(algo_test)
