add_library(lib cmd_bulk.cpp bulk_processor.cpp)

target_include_directories(lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(lib PUBLIC cxx_std_14)
