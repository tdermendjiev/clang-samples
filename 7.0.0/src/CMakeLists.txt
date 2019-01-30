
set(GENERATOR_SOURCES
    main.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${LIBXML2_INCLUDE_DIR})

add_executable(objc-metadata-generator ${GENERATOR_SOURCES})
target_link_libraries(objc-metadata-generator
    ${LLVM_LINKER_FLAGS}
    clangFrontend
    clangSerialization
    clangDriver
    clangParse
    clangSema
    clangAnalysis
    clangAST
    clangBasic
    clangEdit
    clangLex
    clangTooling
)

set_target_properties(objc-metadata-generator PROPERTIES
    COMPILE_FLAGS "-fvisibility=hidden -Werror -Wall -Wextra -Wno-unused-parameter"
)

