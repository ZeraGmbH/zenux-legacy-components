file(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/async-notifications/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/scpi-interfaces/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/scpi-protobuf/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/settings/*.cpp
    )

file(GLOB HEADER
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/async-notifications/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/scpi-interfaces/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/scpi-protobuf/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/settings/*.h
    )

add_library(service-common-code SHARED
    ${SOURCES}
    ${HEADER}
    )

target_link_libraries(service-common-code
    PUBLIC
    Qt5::Core
    Zera::xiqnet
    Zera::SCPI
    Zera::zera-xmlconfig
    zera-math
    Zera::zera-timers
    # ask linker to help us finding unresolved symbols
    "-Wl,--no-undefined"
    )

target_include_directories(service-common-code
    PUBLIC
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/service-common-code>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/async-notifications>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/resources>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/scpi-interfaces>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/scpi-protobuf>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/settings>
    )

set_target_properties(service-common-code PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(service-common-code PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

generate_export_header(service-common-code)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/service-common-code_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/service-common-code
    )

export(TARGETS service-common-code NAMESPACE Zera:: FILE ZenuxLegacyComponentsTargets.cmake)
install(TARGETS service-common-code
    EXPORT ZenuxLegacyComponentsExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

install(
    FILES ${HEADER}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/service-common-code
    )
