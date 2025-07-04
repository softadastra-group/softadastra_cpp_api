file(GLOB_RECURSE LIB_SOURCES 
    "../src/utils/*.cpp"
)

add_library(softadastra_lib STATIC ${LIB_SOURCES})

target_include_directories(softadastra_lib PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/Crow/include
    ${CMAKE_SOURCE_DIR}/src/utils 
    ${MYSQL_INCLUDE_DIR}
)

target_link_libraries(softadastra_lib PRIVATE
    OpenSSL::SSL
    OpenSSL::Crypto
    SQLite::SQLite3
    Threads::Threads
)