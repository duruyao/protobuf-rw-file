cmake_minimum_required(VERSION 3.5)
project(pb_rw_file)
set(CMAKE_CXX_STANDARD 11)
find_package(Protobuf REQUIRED)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
add_custom_target(proto_to_cc ALL
        COMMAND ${Protobuf_PROTOC_EXECUTABLE} --proto_path=${SRC_DIR} --cpp_out=${SRC_DIR} pb_rw_file.proto
        DEPENDS pb_rw_file.proto)
add_executable(pb_rw_file)
add_dependencies(pb_rw_file proto_to_cc)
aux_source_directory(${SRC_DIR} ALL_SRC)
target_sources(pb_rw_file PRIVATE ${ALL_SRC})
target_link_libraries(pb_rw_file PRIVATE ${Protobuf_LIBRARIES})
install(TARGETS pb_rw_file RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})
