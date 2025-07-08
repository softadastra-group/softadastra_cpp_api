# ────────────────────────────────────────────────────────────────
# 🛍️ Product Module - CMake Configuration
# This file builds the 'product' static library by collecting
# all source files related to product models, services, and routes.
# ────────────────────────────────────────────────────────────────

# Collect all source files (.cpp) for the product module
file(GLOB_RECURSE PRODUCT_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/api/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/services/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/models/*.cpp
)

# Créer une bibliothèque statique 'product'
add_library(product STATIC ${PRODUCT_SRC})

# Include dirs pour les headers de ce module
target_include_directories(product PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/products
    ${CMAKE_SOURCE_DIR}/include/products/api
    ${CMAKE_SOURCE_DIR}/include/products/services
    ${CMAKE_SOURCE_DIR}/include/products/models
)

# Lier dépendances nécessaires
target_link_libraries(product
    PUBLIC
        utils                              # Logging, EnvLoader, etc.
        tools                              # outils généraux
        nlohmann_json::nlohmann_json       # JSON
        crow                               # Crow framework
)
