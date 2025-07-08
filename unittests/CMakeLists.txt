# unittests/CMakeLists.txt
# ────────────────────────────────────────────────────────────────
# 🔬 Unit Test Runner - Catch2 or GoogleTest
# Compiles all *_test.cpp files in this folder as test executables
# and links them to required internal modules.
# ────────────────────────────────────────────────────────────────

# 🧪 Récupère tous les fichiers de test du dossier actuel
file(GLOB_RECURSE UNITTEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

# 📦 Pour chaque fichier test
foreach(test_file ${UNITTEST_SOURCES})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name} ${test_file})

    # 🔗 Lier aux bibliothèques internes + dépendances
    target_link_libraries(${test_name} PRIVATE
        product
        categories
        payments
        utils
        tools
        nlohmann_json::nlohmann_json
        Catch2::Catch2WithMain
    )
    # 📁 Ajouter les headers globaux (si utilisés dans les tests)
    target_include_directories(${test_name} PRIVATE
        ${CMAKE_SOURCE_DIR}/include
    )

    # 📌 Enregistrer le test avec CTest
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
