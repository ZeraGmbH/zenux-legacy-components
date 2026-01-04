file(GLOB SOURCES
    resmanrunfacade.cpp
    resourcemanager.cpp
    rmprotobufwrapper.cpp
    resource/*.cpp
    server/*.cpp
    scpi/*.cpp
    )

file(GLOB HEADER
    *.h
    resource/*.h
    server/*.h
    scpi/*.h
    )

add_library(resman-lib STATIC
    ${SOURCES}
    ${HEADER}
    )

target_link_libraries(resman-lib
    PUBLIC
    ${QTX}::Core
    ${QTX}::Network
    Zera::xiqnet
    Zera::zeraprotobuf
    Zera::SCPI
    )

target_include_directories(resman-lib
    PUBLIC
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/resman-lib>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/resource>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/scpi>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/server>
    )

set_target_properties(resman-lib PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(resman-lib PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

export(TARGETS resman-lib NAMESPACE Zera:: FILE ZenuxLegacyComponentsTargets.cmake)
install(TARGETS resman-lib
    EXPORT ZenuxLegacyComponentsExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

install(
    FILES ${HEADER}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/resman-lib
    )

add_subdirectory(tests)
