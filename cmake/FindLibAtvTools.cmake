include(FetchContent)

FetchContent_Declare(
  lib-atv-tools-package
  URL file://$ENV{HOME}/projects/analog-tv-tools/lib-atv-tools.zip
)

FetchContent_MakeAvailable(lib-atv-tools-package)

list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR}/_deps/lib-atv-tools-package-src/cmake)
