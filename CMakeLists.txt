cmake_minimum_required(VERSION 3.14)
project(Softadastra 
    VERSION 0.1 
    LANGUAGES CXX
    DESCRIPTION "Projet Softadastra"
)

# Configuration de base
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Options de compilation
add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -g
)

# Optimisation
option(ENABLE_OPTIMIZATION "Activer l'optimisation O3" OFF)
if(ENABLE_OPTIMIZATION)
    add_compile_options(-O3)
endif()

# Sanitizers optionnels
option(ENABLE_SANITIZERS "Activer les sanitizers (Address, Undefined)" ON)
if(ENABLE_SANITIZERS)
    add_compile_options(-fsanitize=address,undefined)
    add_link_options(-fsanitize=address,undefined)
endif()

# Structure de sortie
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Dependencies
find_package(OpenSSL REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(Threads REQUIRED)
# Configuration pour MySQL C++ Connector
find_path(MYSQLCPPCONN_INCLUDE_DIR mysql_connection.h
    PATHS /usr/include/cppconn
          /usr/include/mysql-cppconn-8
          /usr/include/mysql
          /usr/local/include
    REQUIRED
)

find_library(MYSQLCPPCONN_LIBRARY
    NAMES mysqlcppconn mysqlcppconn8
    PATHS /usr/lib
          /usr/lib/x86_64-linux-gnu
          /usr/local/lib
    REQUIRED
)

if(MYSQLCPPCONN_INCLUDE_DIR AND MYSQLCPPCONN_LIBRARY)
    message(STATUS "Found MySQL C++ Connector:")
    message(STATUS "  - Includes: ${MYSQLCPPCONN_INCLUDE_DIR}")
    message(STATUS "  - Library: ${MYSQLCPPCONN_LIBRARY}")
    
    add_library(MySQLCppConn::MySQLCppConn UNKNOWN IMPORTED)
    set_target_properties(MySQLCppConn::MySQLCppConn PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${MYSQLCPPCONN_INCLUDE_DIR}"
        IMPORTED_LOCATION "${MYSQLCPPCONN_LIBRARY}"
    )
else()
    message(FATAL_ERROR "MySQL C++ Connector not found!")
endif()

# Configuration GoogleTest
option(BUILD_TESTS "Construire les tests" ON)

# Partie unique pour inclure FetchContent
include(FetchContent)

# nlohmann/json (toujours utile)
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
    GIT_SHALLOW TRUE
)
# FetchContent_Declare(
#     nlohmann_json
#     SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/json
# )

# GoogleTest (optionnel)
if(BUILD_TESTS)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
        GIT_SHALLOW TRUE
    )
endif()

# Téléchargement et mise à disposition
FetchContent_MakeAvailable(nlohmann_json)

if(BUILD_TESTS)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    enable_testing()
endif()


# Configuration des sous-répertoires
add_subdirectory(lib)
add_subdirectory(src)

# Inclusions globales (après création de la cible dans src/)
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/Crow/include
)

# Tests optionnels (seulement si les dossiers existent)
if(BUILD_TESTS)
    if(EXISTS ${CMAKE_SOURCE_DIR}/test/CMakeLists.txt)
        add_subdirectory(test)
    endif()
    if(EXISTS ${CMAKE_SOURCE_DIR}/unittests/CMakeLists.txt)
        add_subdirectory(unittests)
    endif()
endif()

# Installation
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(DIRECTORY include/ DESTINATION include)