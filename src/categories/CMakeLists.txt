# ────────────────────────────────────────────────────────────────
# 📦 Category Module - CMake Configuration
# This file builds the 'categories' static library, including all
# category-related source files, headers, and linked dependencies.
# ────────────────────────────────────────────────────────────────

# Collect all relevant source files in the categories module
file(GLOB_RECURSE CATEGORY_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/api/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/services/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/models/*.cpp
)

# Define the static library target
add_library(categories STATIC ${CATEGORY_SOURCES})

# Expose public headers to consumers
target_include_directories(categories PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/categories
    ${CMAKE_SOURCE_DIR}/include/categories/api
    ${CMAKE_SOURCE_DIR}/include/categories/services
    ${CMAKE_SOURCE_DIR}/include/categories/models
)

# Link with internal and external dependencies
target_link_libraries(categories
    utils                           # Logging, EnvLoader, etc.
    tools                           # Shared utilities
    crow                            # HTTP routing
    nlohmann_json::nlohmann_json   # JSON
)
