# Unit tests for config-management

set(TEST_SOURCES
    test_configmanager.h
    test_configmanager.cpp
)

add_executable(run_tests ${TEST_SOURCES})

target_link_libraries(run_tests PRIVATE
    Qt5::Core
    Qt5::Test
)

# Copy config files to test directory
file(COPY ${CMAKE_SOURCE_DIR}/config/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/config/)

add_test(NAME run_tests COMMAND run_tests)
