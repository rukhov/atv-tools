find_program(PYTEST "pytest")

#message("=================== atv-tools-cli dir: " ${CMAKE_BINARY_DIR})

set(ASSETS_DIR \ ${CMAKE_BINARY_DIR} )
if(UNIX)
  set(EXECUTABLES_DIR \ ${CMAKE_BINARY_DIR}/bin )
elseif(WIN32)
  set(EXECUTABLES_DIR \ ${CMAKE_BINARY_DIR}/bin/$<CONFIG> )
endif()

set(PROJECTS_DIR \ ${CMAKE_SOURCE_DIR} )

add_test (NAME test_decode_secam_color_bars.py
  COMMAND pytest 
    --verbosity=1
    --log-cli-level=30
    --projectPath ${PROJECTS_DIR}
    --assetsPath ${ASSETS_DIR}
    --executablesPath ${EXECUTABLES_DIR}
    test_decode_secam_color_bars.py
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_test (NAME test_decode_secam_cartoon_4.py
  COMMAND pytest 
    --verbosity=1
    --log-cli-level=30
    --projectPath ${PROJECTS_DIR}
    --assetsPath ${ASSETS_DIR}
    --executablesPath ${EXECUTABLES_DIR}
    test_decode_secam_cartoon_4.py
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_test (NAME test_bw_secam_productivity.py
  COMMAND pytest 
    --verbosity=1
    --log-cli-level=30
    --projectPath ${PROJECTS_DIR}
    --assetsPath ${ASSETS_DIR}
    --executablesPath ${EXECUTABLES_DIR}
    test_bw_secam_productivity.py
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)