# ────────────────────────────────────────────────────────────────
# 🛠️ Utils Module - CMake Configuration
# This module provides utility functions used across the entire 
# application (e.g., logging, environment loading, string helpers).
# It is compiled as a static library and included by other modules.
# ────────────────────────────────────────────────────────────────

# Gather all .cpp source files in the utils directory
file(GLOB UTILS_SOURCES CONFIGURE_DEPENDS *.cpp)

# Define the static library target for utils
add_library(utils STATIC ${UTILS_SOURCES})

# Public include paths to expose utils headers to other modules
target_include_directories(utils PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/utils
)

# Suppress specific compiler warnings for deprecated APIs
target_compile_options(utils PRIVATE -Wno-deprecated-declarations)
