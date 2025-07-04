if(TARGET gtest_main AND TARGET catalogue)
    file(GLOB_RECURSE TEST_SOURCES
        "${CMAKE_SOURCE_DIR}/test/*.cpp"
    )

    if(TEST_SOURCES)
        add_executable(tests ${TEST_SOURCES})

        target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

        target_link_libraries(tests PRIVATE
            catalogue
            gtest_main
        )

        add_test(NAME tests COMMAND tests)
    else()
        message(WARNING "No test sources found - skipping test build")
    endif()
endif()
