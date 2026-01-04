cmake_minimum_required(VERSION 3.1)

project(zenux-legacy-components LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(PROJECT_VERSION_MAJOR "0")
set(PROJECT_VERSION_MINOR "0")
set(PROJECT_VERSION_PATCH "1")
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

include(FeatureSummary)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(GenerateExportHeader)

set(QT_MAJOR_VER "5" CACHE STRING "Qt major version")
set(QTX "Qt${QT_MAJOR_VER}")

find_package(${QTX} COMPONENTS Core Network Test CONFIG REQUIRED)
find_package(VeinFramework REQUIRED)
find_package(SCPI REQUIRED)
find_package(ZenuxCore REQUIRED)

enable_testing()

# Inspired by
# https://github.com/KDAB/kdabtv/blob/master/Qt-Widgets-and-more/UnitTests/Tests/CMakeLists.txt
function(SETUP_TESTS)
    foreach(_testname ${ARGN})
        add_test(NAME ${_testname} COMMAND ${_testname})
        add_executable(${_testname} ${_testname}.h ${_testname}.cpp)
        target_include_directories(${_testname}
            PRIVATE
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
            ${PROJECT_SOURCE_DIR}/src
            )
        target_link_libraries(${_testname}
            PUBLIC
            ${QTX}::Test
            Zera::zera-timers-testlib
            Zera::tasks-base-testlib
            resman-test-helpers
            zera-xmlconfig
            xml-config-test-data
            )
    endforeach()
endfunction()

write_basic_package_version_file(
    ZenuxLegacyComponentsConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY SameMajorVersion
    )
configure_file(ZenuxLegacyComponentsConfig.cmake.in ZenuxLegacyComponentsConfig.cmake @ONLY)
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/ZenuxLegacyComponentsConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/ZenuxLegacyComponentsConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ZenuxLegacyComponents
    )

install(EXPORT ZenuxLegacyComponentsExport
    FILE ZenuxLegacyComponentsTargets.cmake
    NAMESPACE Zera::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ZenuxLegacyComponents
    )

add_subdirectory(resman-lib)
add_subdirectory(zera-math)
add_subdirectory(zera-xmlconfig)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
