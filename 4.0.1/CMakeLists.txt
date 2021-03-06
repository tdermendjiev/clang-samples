project(MetadataGenerator)
cmake_minimum_required(VERSION 2.8)


find_program(LLVM_CONFIG_EXE ${CMAKE_CURRENT_SOURCE_DIR}/clang+llvm-4.0.1-x86_64-apple-macosx10.9.0/bin/llvm-config
			 HINTS ENV LLVM_CONFIG_PATH)
if (NOT EXISTS ${LLVM_CONFIG_EXE})
    message(FATAL_ERROR "llvm-config not found")
endif ()
macro(llvm_config option var)
    execute_process(
        COMMAND ${LLVM_CONFIG_EXE} --${option}
        OUTPUT_VARIABLE ${var}
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
endmacro()


set(CMAKE_OSX_DEPLOYMENT_TARGET 10.12)

llvm_config(system-libs LLVM_SYSTEM_LIBS)
llvm_config(cppflags LLVM_PREPROCESSOR_FLAGS)
llvm_config(libs LLVM_LIBS)
llvm_config(ldflags LLVM_LINKER_FLAGS)
llvm_config(libdir LLVM_LIBDIR)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti ${LLVM_PREPROCESSOR_FLAGS}")
set(LLVM_LINKER_FLAGS "${LLVM_LINKER_FLAGS} ${LLVM_SYSTEM_LIBS} ${LLVM_LIBS}")
message(${LLVM_LINKER_FLAGS})

add_subdirectory(src)
