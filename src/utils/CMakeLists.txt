# Fichiers sources
file(GLOB UTILS_SOURCES *.cpp)

# Création de la bibliothèque utils
add_library(utils OBJECT ${UTILS_SOURCES})

# Inclusions
target_include_directories(utils PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/utils
)

# Options spécifiques
target_compile_options(utils PRIVATE -Wno-deprecated-declarations)