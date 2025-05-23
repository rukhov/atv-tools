include(FetchContent)

FetchContent_Declare(
  lib-atv-tools-package
  URL ${CMAKE_CURRENT_SOURCE_DIR}/resources/lib-atv-tools-windows-x64.zip
)

FetchContent_MakeAvailable(lib-atv-tools-package)

list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR}/_deps/lib-atv-tools-package-src/cmake)
