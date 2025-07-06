# ────────────────────────────────────────────────────────────────
# 📦 Category Module - CMake Configuration
# This file builds the 'categories' static library, including all
# category-related source files, headers, and linked dependencies.
# ────────────────────────────────────────────────────────────────

# Automatically collect all .cpp files in this folder
file(GLOB CATEGORY_SOURCES CONFIGURE_DEPENDS *.cpp)

# Define a static library target called 'categories'
add_library(categories STATIC ${CATEGORY_SOURCES})

# Include paths so other modules can access headers
target_include_directories(categories PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# Link the category module with internal and external dependencies
target_link_libraries(categories
    utils                           # Internal utility library (e.g., EnvLoader, Logger)
    tools                           # Internal tools shared across modules
    crow                            # Crow framework for HTTP routing
    nlohmann_json::nlohmann_json   # JSON parsing and serialization
)
