include(FetchContent)

FetchContent_Declare(
  rtsp_server_template 
  GIT_REPOSITORY https://github.com/rukhov/rtsp_server_template.git
  GIT_TAG        origin/main
)
set(BUILD_EXAMPLES OFF)
FetchContent_MakeAvailable( rtsp_server_template )