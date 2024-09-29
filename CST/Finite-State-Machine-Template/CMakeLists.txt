cmake_minimum_required(VERSION 3.22)

project(fsm
        VERSION 0.0.1
        HOMEPAGE_URL "https://github.com/bcitcstdatacomm/libdc_fsm"
        DESCRIPTION ""
        LANGUAGES C)

set(CMAKE_C_STANDARD ${CMAKE_LANGUAGE_VERSION})

add_compile_definitions(_POSIX_C_SOURCE=200809L _XOPEN_SOURCE=700)

if(APPLE)
    add_definitions(-D_DARWIN_C_SOURCE)
endif()

find_program(LINT "clang-tidy")
IF(LINT)
    set(CMAKE_C_CLANG_TIDY "clang-tidy;-checks=*,-llvmlibc-restrict-system-libc-headers,-cppcoreguidelines-init-variables,-clang-analyzer-security.insecureAPI.strcpy,-concurrency-mt-unsafe,-android-cloexec-accept,-android-cloexec-dup,-google-readability-todo,-cppcoreguidelines-avoid-magic-numbers,-readability-magic-numbers,-cert-dcl03-c,-hicpp-static-assert,-misc-static-assert,-altera-struct-pack-align,-clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling;--quiet")
ENDIF()

set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(SOURCE_LIST "${SOURCE_DIR}/fsm.c"
                "${SOURCE_DIR}/main.c")
set(HEADER_LIST "${INCLUDE_DIR}/fsm.h")

set(SANITIZE TRUE)


include_directories(${INCLUDE_DIR})
add_compile_options("-Wall"
        "-Wextra"
        "-Wpedantic"
        "-Wshadow"
        "-Wstrict-overflow=4"
        "-Wswitch-default"
        "-Wswitch-enum"
        "-Wunused"
        "-Wunused-macros"
        "-Wdate-time"
        "-Winvalid-pch"
        "-Wmissing-declarations"
        "-Wmissing-include-dirs"
        "-Wmissing-prototypes"
        "-Wstrict-prototypes"
        "-Wundef"
        "-Wnull-dereference"
        "-Wstack-protector"
        "-Wdouble-promotion"
        "-Wvla"
        "-Walloca"
        "-Woverlength-strings"
        "-Wdisabled-optimization"
        "-Winline"
        "-Wcast-qual"
        "-Wfloat-equal"
        "-Wformat=2"
        "-Wfree-nonheap-object"
        "-Wshift-overflow"
        "-Wwrite-strings")

if (${SANITIZE})
    add_compile_options("-fsanitize=address"
            "-fsanitize=undefined"
            "-fsanitize-address-use-after-scope"
            "-fstack-protector-all"
            "-fdelete-null-pointer-checks"
            "-fno-omit-frame-pointer")

    if (NOT APPLE)
        add_compile_options("-fsanitize=leak")
    endif()

    add_link_options("-fsanitize=address"
            "-fsanitize=bounds")
endif ()

if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    #    add_compile_options("-O2")
    add_compile_options("-Wcast-align"
            "-Wunsuffixed-float-constants"
            "-Warith-conversion"
            "-Wcast-align=strict"
            "-Wunsafe-loop-optimizations"
            "-Wvector-operation-performance"
            "-Walloc-zero"
            "-Wtrampolines"
            "-Wtsan"
            "-Wformat-overflow=2"
            "-Wformat-signedness"
            "-Wjump-misses-init"
            "-Wformat-truncation=2")
elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
endif ()

find_package(Doxygen
        REQUIRED
        REQUIRED dot
        OPTIONAL_COMPONENTS mscgen dia)

set(DOXYGEN_ALWAYS_DETAILED_SEC YES)
set(DOXYGEN_REPEAT_BRIEF YES)
set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_JAVADOC_AUTOBRIEF YES)
set(DOXYGEN_OPTIMIZE_OUTPUT_FOR_C YES)
set(DOXYGEN_GENERATE_HTML YES)
set(DOXYGEN_WARNINGS YES)
set(DOXYGEN_QUIET YES)

doxygen_add_docs(doxygen
        ${HEADER_LIST}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMENT "Generating Doxygen documentation for open")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CLANG_TIDY_CHECKS "*")
set(CLANG_TIDY_CHECKS "${CLANG_TIDY_CHECKS},-llvmlibc-restrict-system-libc-headers")
set(CLANG_TIDY_CHECKS "${CLANG_TIDY_CHECKS},-misc-unused-parameters")
set(CLANG_TIDY_CHECKS "${CLANG_TIDY_CHECKS},-clang-diagnostic-unused-parameter")
set(CLANG_TIDY_CHECKS "${CLANG_TIDY_CHECKS},-clang-diagnostic-unused-variable")
set(CLANG_TIDY_CHECKS "${CLANG_TIDY_CHECKS},-cppcoreguidelines-init-variables")
set(CLANG_TIDY_CHECKS "${CLANG_TIDY_CHECKS},-readability-identifier-length")
set(CLANG_TIDY_CHECKS "${CLANG_TIDY_CHECKS},-clang-diagnostic-unused-but-set-variable")
set(CLANG_TIDY_CHECKS "${CLANG_TIDY_CHECKS},-clang-analyzer-deadcode.DeadStores")
set(CLANG_TIDY_CHECKS "${CLANG_TIDY_CHECKS},-altera-id-dependent-backward-branch")
set(CLANG_TIDY_CHECKS "${CLANG_TIDY_CHECKS},-cert-dcl03-c")
set(CLANG_TIDY_CHECKS "${CLANG_TIDY_CHECKS},-hicpp-static-assert")
set(CLANG_TIDY_CHECKS "${CLANG_TIDY_CHECKS},-misc-static-assert")
set(CLANG_TIDY_CHECKS "${CLANG_TIDY_CHECKS},-altera-unroll-loops")
set(CLANG_TIDY_CHECKS "${CLANG_TIDY_CHECKS},-altera-struct-pack-align")
set(CLANG_TIDY_CHECKS "${CLANG_TIDY_CHECKS},-clang-analyzer-security.insecureAPI.strcpy")
set(CMAKE_C_CLANG_TIDY clang-tidy -checks=${CLANG_TIDY_CHECKS},--quiet)


add_executable(${PROJECT_NAME} ${SOURCE_LIST})
add_dependencies(${PROJECT_NAME} doxygen)

find_library(LIBDC_ERROR dc_error REQUIRED)
find_library(LIBDC_POSIX dc_posix REQUIRED)
target_link_libraries(${PROJECT_NAME} ${LIBDC_ERROR})
target_link_libraries(${PROJECT_NAME} ${LIBDC_POSIX})
target_include_directories(${PROJECT_NAME} PRIVATE ../include/fsm)
target_include_directories(${PROJECT_NAME} PRIVATE /usr/include)
target_include_directories(${PROJECT_NAME} PRIVATE /usr/local/include)
target_link_directories(${PROJECT_NAME} PRIVATE /usr/local/lib)
