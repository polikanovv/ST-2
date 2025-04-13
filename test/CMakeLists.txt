
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()


add_executable(${PROJECT_NAME}.test
  AllTests.cpp
  tests.cpp
)

target_link_libraries(${PROJECT_NAME}.test
  ${PROJECT_NAME}
  gtest
  gtest_main
  pthread
)

target_compile_definitions(${PROJECT_NAME}.test 
  PRIVATE TEST_DIR="${CMAKE_CURRENT_LIST_DIR}/test")

install(TARGETS ${PROJECT_NAME}.test
        DESTINATION "${tool_dest}")