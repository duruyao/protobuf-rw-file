# Protocol Buffers Example of Saving/Loading Files

## 1. Prerequisites

- [CMake](https://cmake.org/)
- [Protocol Buffers](https://github.com/protocolbuffers/protobuf)

## 2. Unix Builds

Use CMake to build targets.

```shell
cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="${PWD}"
cmake --build build --target all -- --jobs=4
cmake --build build --target install
```

## 3. Usage

Read a file into protobuf messages and write protobuf messages to another file.

```shell
$ ./pb_rw_file photo.jpg photo-copy.jpg
```
