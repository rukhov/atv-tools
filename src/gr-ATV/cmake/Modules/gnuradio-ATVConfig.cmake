find_package(PkgConfig)

PKG_CHECK_MODULES(PC_GR_ATV gnuradio-ATV)

FIND_PATH(
    GR_ATV_INCLUDE_DIRS
    NAMES gnuradio/ATV/api.h
    HINTS $ENV{ATV_DIR}/include
        ${PC_ATV_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GR_ATV_LIBRARIES
    NAMES gnuradio-ATV
    HINTS $ENV{ATV_DIR}/lib
        ${PC_ATV_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/gnuradio-ATVTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GR_ATV DEFAULT_MSG GR_ATV_LIBRARIES GR_ATV_INCLUDE_DIRS)
MARK_AS_ADVANCED(GR_ATV_LIBRARIES GR_ATV_INCLUDE_DIRS)
