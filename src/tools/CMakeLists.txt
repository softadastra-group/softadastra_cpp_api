# ────────────────────────────────────────────────────────────────
# 🧰 Tools Module - CMake Configuration
# This file builds the 'tools' module as either:
# - an OBJECT library (when .cpp files exist), or
# - an INTERFACE library (when it's header-only).
#
# It also links OpenCV for image processing and utility functions.
# ────────────────────────────────────────────────────────────────

# Gather all .cpp source files in the tools directory
file(GLOB TOOLS_SOURCES *.cpp)

# Find and configure OpenCV (required dependency)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# ────────────────────────────────────────────────────────────────
# Case 1: .cpp source files exist → compile as an OBJECT library
# ────────────────────────────────────────────────────────────────
if(TOOLS_SOURCES)
    add_library(tools OBJECT ${TOOLS_SOURCES})

    target_include_directories(tools PUBLIC
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/include/tools
    )

    target_link_libraries(tools PUBLIC ${OpenCV_LIBS})

# ────────────────────────────────────────────────────────────────
# Case 2: No .cpp source files → fallback to INTERFACE library
# This allows headers to still be included in dependent modules.
# ────────────────────────────────────────────────────────────────
else()
    message(WARNING "No source files found in tools directory - creating empty INTERFACE target")
    
    add_library(tools INTERFACE)

    target_include_directories(tools INTERFACE
        ${CMAKE_SOURCE_DIR}/include/tools
    )
endif()
