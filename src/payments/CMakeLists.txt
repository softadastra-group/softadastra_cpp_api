# Ajout des sous-répertoires (si tu veux faire un CMake séparé par dossier interne plus tard)
# Sinon on compile tout d’un coup ici
file(GLOB_RECURSE PAYMENTS_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/api/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/controllers/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/database/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/models/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/services/*.cpp
)

add_library(payments STATIC ${PAYMENTS_SOURCES})

target_include_directories(payments PUBLIC
    ${CMAKE_SOURCE_DIR}/include/payments
)

target_link_libraries(payments
    PUBLIC
        OpenSSL::SSL
        OpenSSL::Crypto
        SQLite::SQLite3
        Threads::Threads
        MySQLCppConn::MySQLCppConn
        nlohmann_json::nlohmann_json
)
