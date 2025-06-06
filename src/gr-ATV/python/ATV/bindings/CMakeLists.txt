# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# Check if there is C++ code at all
########################################################################
if(NOT ATV_sources)
    message(STATUS "No C++ sources... skipping python bindings")
    return()
endif(NOT ATV_sources)

########################################################################
# Check for pygccxml
########################################################################
gr_python_check_module_raw("pygccxml" "import pygccxml" PYGCCXML_FOUND)

include(GrPybind)

########################################################################
# Python Bindings
########################################################################

list(APPEND ATV_python_files
    TvDecoder_python.cc 
    python_bindings.cc
)

gr_pybind_make_oot(ATV ../../.. gr::ATV "${ATV_python_files}")

# copy bindings extension for use in QA test module
add_custom_command(
    TARGET ATV_python
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:ATV_python>
            ${PROJECT_BINARY_DIR}/test_modules/gnuradio/ATV/)

install(
    TARGETS ATV_python
    DESTINATION ${GR_PYTHON_DIR}/gnuradio/ATV
    COMPONENT pythonapi)
