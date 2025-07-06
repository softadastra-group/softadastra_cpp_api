# ────────────────────────────────────────────────────────────────
# 🚀 Main Source Directory - CMake Configuration
# This file links all core submodules (utils, tools, catalogue, etc.)
# and compiles the final executable entry point: ${PROJECT_NAME}
# ────────────────────────────────────────────────────────────────

# ────────────────────────────────────────────────────────────────
# 📁 Add all core internal subdirectories (modular components)
# Each folder must have its own CMakeLists.txt to define a static lib.
# ────────────────────────────────────────────────────────────────
add_subdirectory(utils)
add_subdirectory(tools)
add_subdirectory(catalogue)
add_subdirectory(payments)
add_subdirectory(categories)

# ────────────────────────────────────────────────────────────────
# 📦 Collect all .cpp source files under this directory
# This can be used for global compilation logic if needed
# (Currently only used to include main.cpp manually below)
# ────────────────────────────────────────────────────────────────
file(GLOB_RECURSE SRC_FILES 
    "*.cpp"
    EXCLUDE "*test*_test.cpp" "*unittest*.cpp"
)

# ────────────────────────────────────────────────────────────────
# 🔧 Build the main application binary
# Only main.cpp is used here — all other logic lives in linked modules
# ────────────────────────────────────────────────────────────────
add_executable(${PROJECT_NAME} main.cpp)

# ────────────────────────────────────────────────────────────────
# 🔗 Link the application to all required modules and libraries
# Includes both internal modules and external dependencies
# ────────────────────────────────────────────────────────────────
target_link_libraries(${PROJECT_NAME} PRIVATE
    catalogue                        # Business logic for products and ECS
    utils                            # Logger, .env loader, etc.
    tools                            # Shared helpers
    payments                         # Payment gateway logic
    categories                       # Category management (routes, repo, service)

    OpenSSL::SSL                     # SSL support (e.g. token signing, encryption)
    OpenSSL::Crypto
    SQLite::SQLite3                  # Local DB support
    Threads::Threads                 # C++ multithreading support
    mysqlcppconn                     # MySQL C++ connector
    nlohmann_json::nlohmann_json    # JSON parsing
)

# ────────────────────────────────────────────────────────────────
# Optional: Link spdlog if available
# ────────────────────────────────────────────────────────────────
if(spdlog_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
endif()

# Optional: Link MySQL if separately found (redundant if mysqlcppconn is enough)
if(MySQL_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE MySQL::MySQL)
endif()
