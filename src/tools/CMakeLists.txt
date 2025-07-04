file(GLOB TOOLS_SOURCES *.cpp)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

if(TOOLS_SOURCES)
    add_library(tools OBJECT ${TOOLS_SOURCES})

    target_include_directories(tools PUBLIC
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/include/tools
    )

    target_link_libraries(tools PUBLIC ${OpenCV_LIBS}) 
else()
    message(WARNING "No source files found in tools directory - creating empty target")
    add_library(tools INTERFACE)

    target_include_directories(tools INTERFACE
        ${CMAKE_SOURCE_DIR}/include/tools
    )
endif()
