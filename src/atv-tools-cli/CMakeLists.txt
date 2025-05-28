set(TARGET_NAME ${CMAKE_PROJECT_NAME}-cli)

set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS Off)

find_package(Boost REQUIRED COMPONENTS program_options)
find_package(SndFile REQUIRED)
find_package(iir CONFIG REQUIRED)
find_package(OpenCV REQUIRED)

find_package(lib-atv-tools CONFIG REQUIRED)

add_executable(${TARGET_NAME})

target_sources(${TARGET_NAME} PRIVATE
    main.cpp
    options.cpp
    snd_file_reader.cpp
    video_writer.cpp
    raw_file_writer.cpp
    raw_file_reader.cpp
)

target_precompile_headers(${TARGET_NAME} PRIVATE stdafx.h)

target_link_libraries(${TARGET_NAME} PRIVATE 
    Boost::program_options 
    lib-atv-tools::lib-atv-tools
    SndFile::sndfile 
    opencv_videoio
	  iir::iir
)

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${TARGET_NAME}> $<TARGET_FILE_DIR:${TARGET_NAME}>
  COMMAND_EXPAND_LISTS
) 