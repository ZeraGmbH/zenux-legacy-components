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
    ${QTX}::Core
    Zera::zera-timers-testlib
    resman-lib
    )

SETUP_TESTS(
    test_scpi
    test_connect_disconnect_free_all_mem
)
