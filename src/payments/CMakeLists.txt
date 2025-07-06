# ────────────────────────────────────────────────────────────────
# 💰 Payments Module - CMake Configuration
# This file builds the 'payments' static library, compiling all 
# related API handlers, services, controllers, models, and database
# logic. It also declares public include paths and links to the 
# required libraries (internal + external).
# ────────────────────────────────────────────────────────────────

# Recursively gather all .cpp source files from payments subdirectories
file(GLOB_RECURSE PAYMENTS_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/api/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/controllers/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/database/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/models/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/services/*.cpp
)

# Define the static library target for the payments module
add_library(payments STATIC ${PAYMENTS_SOURCES})

# Public include directories to expose this module’s headers to others
target_include_directories(payments PUBLIC
    ${CMAKE_SOURCE_DIR}/include/payments
)

# Link all required dependencies for this module
target_link_libraries(payments
    PUBLIC
        utils                              # Internal utilities (e.g., Logger, EnvLoader)
        tools                              # Internal shared helper functions
        OpenSSL::SSL                       # SSL for secure hashing, encryption
        OpenSSL::Crypto                    # OpenSSL cryptographic primitives
        SQLite::SQLite3                    # SQLite3 support (if used for embedded storage)
        Threads::Threads                   # Multithreading support
        MySQLCppConn::MySQLCppConn         # MySQL C++ Connector
        nlohmann_json::nlohmann_json       # JSON parsing and serialization
        crow                               # Crow framework for REST APIs
)
