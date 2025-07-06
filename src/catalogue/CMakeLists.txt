# ────────────────────────────────────────────────────────────────
# 📦 Catalogue Module - CMake Configuration
# This file builds the 'catalogue' static library by collecting
# all source files related to ECS components, systems, services,
# and REST routes. It also declares public include paths and links
# necessary internal and external libraries.
# ────────────────────────────────────────────────────────────────

# Recursively gather all .cpp files from the catalogue module structure
file(GLOB_RECURSE CATALOGUE_SRC
    components/*.cpp
    ecs/*.cpp
    entities/*.cpp
    routes/*.cpp
    services/*.cpp
    systems/*.cpp
)

# Define the static library target for the catalogue domain
add_library(catalogue STATIC ${CATALOGUE_SRC})

# Public include directories to expose this module’s headers
target_include_directories(catalogue PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/catalogue
    ${CMAKE_SOURCE_DIR}/include/catalogue/components
    ${CMAKE_SOURCE_DIR}/include/catalogue/ecs
    ${CMAKE_SOURCE_DIR}/include/catalogue/entities
    ${CMAKE_SOURCE_DIR}/include/catalogue/routes
    ${CMAKE_SOURCE_DIR}/include/catalogue/services
    ${CMAKE_SOURCE_DIR}/include/catalogue/systems
)

# Link dependencies required by the catalogue module
target_link_libraries(catalogue
    PUBLIC
        utils                              # Internal utilities (logging, env, etc.)
        tools                              # Internal shared tools/helpers
        nlohmann_json::nlohmann_json       # External JSON library
        crow                               # Crow HTTP framework for REST API routes
)
