file(GLOB_RECURSE CATALOGUE_SRC
    components/*.cpp
    ecs/*.cpp
    entities/*.cpp
    routes/*.cpp
    services/*.cpp
    systems/*.cpp
)

add_library(catalogue STATIC ${CATALOGUE_SRC})

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
