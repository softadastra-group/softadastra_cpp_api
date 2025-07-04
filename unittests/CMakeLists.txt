if(TARGET gtest)
    file(GLOB UNITTEST_SOURCES *.cpp)
    foreach(test_file ${UNITTEST_SOURCES})
        get_filename_component(test_name ${test_file} NAME_WE)
        add_executable(${test_name} ${test_file})
        target_link_libraries(${test_name} PRIVATE
            ${PROJECT_NAME}
            gtest
        )
        add_test(NAME ${test_name} COMMAND ${test_name})
    endforeach()
endif()