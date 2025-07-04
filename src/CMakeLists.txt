# Déclaration des sous-répertoires
add_subdirectory(utils)
add_subdirectory(tools)
add_subdirectory(catalogue) 

# Fichiers sources principaux
file(GLOB_RECURSE SRC_FILES 
    "*.cpp"
    EXCLUDE "*test*_test.cpp" "*unittest*.cpp"
)

# Création de l'exécutable principal
add_executable(${PROJECT_NAME} main.cpp)

# Liaisons des bibliothèques et dépendances
target_link_libraries(${PROJECT_NAME} PRIVATE
    catalogue    
    utils
    tools
    OpenSSL::SSL
    OpenSSL::Crypto
    SQLite::SQLite3
    Threads::Threads
    mysqlcppconn
    nlohmann_json::nlohmann_json
)

if(spdlog_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
endif()

if(MySQL_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE MySQL::MySQL)
endif()
