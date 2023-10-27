# Inspired by
# https://github.com/KDAB/kdabtv/blob/master/Qt-Widgets-and-more/UnitTests/Tests/CMakeLists.txt

add_library(resman-test-helpers STATIC
    clientmultitontest.cpp
    clientmultitontest.h
    )

target_include_directories(resman-test-helpers
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    )

target_link_libraries(resman-test-helpers
    PUBLIC
    Qt5::Core
    resman-lib
    )

SETUP_TESTS(
    test_scpi
)
