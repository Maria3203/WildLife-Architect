cmake_minimum_required(VERSION 3.26)

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing executable name in this file
# for now, the project name is used as the executable name
set(MAIN_PROJECT_NAME "oop")
set(MAIN_EXECUTABLE_NAME "${MAIN_PROJECT_NAME}")

project(${MAIN_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/Options.cmake)
include(cmake/CompilerFlags.cmake)
include(cmake/CopyHelper.cmake)

###############################################################################
# (Secțiunea de FetchContent și find_package rămâne comentată așa cum era)
###############################################################################

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing name here
# AICI AM MODIFICAT: Am lăsat STRICT fișierele .cpp din TEMA_2. Tema 1 este complet izolată!
add_executable(${MAIN_EXECUTABLE_NAME}
        "TEMA_2/main.cpp"
        "TEMA_2/src/Entitate.cpp"
        "TEMA_2/src/Animal.cpp"
        "TEMA_2/src/Pradator.cpp"
        "TEMA_2/src/Prada.cpp"
        "TEMA_2/src/Planta.cpp"
        "TEMA_2/src/Ecosistem.cpp"
)

# NOTE: Add all defined targets (e.g. executables, libraries, etc. )
set_compiler_flags(RUN_SANITIZERS ${USE_ASAN} TARGET_NAMES ${MAIN_EXECUTABLE_NAME})

###############################################################################

# use SYSTEM so cppcheck and clang-tidy do not report warnings from these directories
# AICI AM MODIFICAT: Îi spunem compilatorului unde sunt headerele noastre noi (.hpp)
target_include_directories(${MAIN_EXECUTABLE_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/TEMA_2/include>
)
target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE
        ext
)

###############################################################################

# copy binaries to "bin" folder; these are uploaded as artifacts on each release
install(TARGETS ${MAIN_EXECUTABLE_NAME} DESTINATION ${DESTINATION_DIR})
if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()

copy_files(FILES tastatura.txt DIRECTORY assets COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})