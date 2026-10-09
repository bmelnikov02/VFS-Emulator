cmake_minimum_required(VERSION 3.19)
project(VPS LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Test)

qt_standard_project_setup()

qt_add_executable(VPS
    WIN32 MACOSX_BUNDLE
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/mainwindow.ui
    src/VFSnode.h src/VFSnode.cpp
    src/vfs.h src/vfs.cpp
)

target_link_libraries(VPS
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS VPS
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET VPS
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

add_executable(vfs_tests
    tests/test_vfs.cpp
    src/vfs.cpp
    src/vfsnode.cpp
)

target_include_directories(vfs_tests PRIVATE src)

target_link_libraries(vfs_tests PRIVATE
    Qt6::Test
    Qt6::Core
)

enable_testing()
add_test(NAME vfs_tests COMMAND vfs_tests)

target_compile_definitions(vfs_tests PRIVATE
    TEST_VFS_DIR="${CMAKE_SOURCE_DIR}/tests/vfs_files"
    TEST_VFS_DEEP_DIR="${CMAKE_SOURCE_DIR}/tests/vfs_deep"
)

