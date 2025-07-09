
cmake_minimum_required(VERSION 3.14)

# ────────────────────────────────────────────────────────────────
# 🛠️  Project Metadata
# ────────────────────────────────────────────────────────────────
project(Softadastra 
    VERSION 0.1 
    LANGUAGES CXX
    DESCRIPTION "Softadastra C++ backend project"
)

# ────────────────────────────────────────────────────────────────
# 🧱 C++ Standard and Compiler Flags
# ────────────────────────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Common compile-time warnings and debug info
add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -g
)

# Optional: enable high-level optimization
option(ENABLE_OPTIMIZATION "Enable -O3 optimization" OFF)
if(ENABLE_OPTIMIZATION)
    add_compile_options(-O3)
endif()

# Optional: enable runtime sanitizers
option(ENABLE_SANITIZERS "Enable address and undefined behavior sanitizers" ON)
if(ENABLE_SANITIZERS)
    add_compile_options(-fsanitize=address,undefined)
    add_link_options(-fsanitize=address,undefined)
endif()

# ────────────────────────────────────────────────────────────────
# 📁 Output Directories for Build Artifacts
# ────────────────────────────────────────────────────────────────
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ────────────────────────────────────────────────────────────────
# 🔍 External Dependencies
# ────────────────────────────────────────────────────────────────
find_package(OpenSSL REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(Threads REQUIRED)

# ─── MySQL Connector C++ Detection
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
    message(STATUS "✅ Found MySQL C++ Connector:")
    message(STATUS "  - Includes: ${MYSQLCPPCONN_INCLUDE_DIR}")
    message(STATUS "  - Library: ${MYSQLCPPCONN_LIBRARY}")
    
    add_library(MySQLCppConn::MySQLCppConn UNKNOWN IMPORTED)
    set_target_properties(MySQLCppConn::MySQLCppConn PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${MYSQLCPPCONN_INCLUDE_DIR}"
        IMPORTED_LOCATION "${MYSQLCPPCONN_LIBRARY}"
    )
else()
    message(FATAL_ERROR "❌ MySQL C++ Connector not found!")
endif()

# ────────────────────────────────────────────────────────────────
# 📦 Third-Party Libraries via FetchContent
# ────────────────────────────────────────────────────────────────
include(FetchContent)

# JSON library (nlohmann/json)
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(nlohmann_json)

# ────────────────────────────────────────────────────────────────
# 🧪 Catch2 (v3) - Modern C++ Testing Framework
#
# Utilisé pour les tests unitaires de tous les modules (products, categories, payments...).
# Cette version inclut "Catch2::Catch2WithMain" qui génère automatiquement le point d'entrée
# pour les binaires de test (pas besoin de définir un main()).
#
# 🧩 Site officiel : https://github.com/catchorg/Catch2
# 📌 Avantage : Compatible C++17, simple, header-only
# ────────────────────────────────────────────────────────────────
FetchContent_Declare(
    catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.4
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(catch2)

# GoogleTest (optional)
option(BUILD_TESTS "Enable unit tests" ON)
if(BUILD_TESTS)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
        GIT_SHALLOW TRUE
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    enable_testing()
endif()

# ────────────────────────────────────────────────────────────────
# 🧱 Crow Framework (as interface library)
# ────────────────────────────────────────────────────────────────
add_library(crow INTERFACE)
target_include_directories(crow INTERFACE ${CMAKE_SOURCE_DIR}/Crow/include)

# ────────────────────────────────────────────────────────────────
# 📂 Subdirectories
# ────────────────────────────────────────────────────────────────
add_subdirectory(lib)
add_subdirectory(src)

# ────────────────────────────────────────────────────────────────
# 📥 Global Include Directories
# ────────────────────────────────────────────────────────────────
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/Crow/include
)

# ────────────────────────────────────────────────────────────────
# 🧪 Tests (optional)
# ────────────────────────────────────────────────────────────────
if(BUILD_TESTS)
    if(EXISTS ${CMAKE_SOURCE_DIR}/test/CMakeLists.txt)
        add_subdirectory(test)
    endif()
    if(EXISTS ${CMAKE_SOURCE_DIR}/unittests/CMakeLists.txt)
        add_subdirectory(unittests)
    endif()
endif()

# ────────────────────────────────────────────────────────────────
# 🚀 Installation Configuration
# ────────────────────────────────────────────────────────────────
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(DIRECTORY include/ DESTINATION include)
