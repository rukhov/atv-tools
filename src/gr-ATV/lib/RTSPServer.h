#pragma once

#include "Streamer.h"

#include <string>

namespace gr::AnalogTV {
std::unique_ptr<Streamer> make_rtsp_server(uint16_t port,
                                           std::string const& mount_point,
                                           size_t width,
                                           size_t height,
                                           uint32_t bitrate = 2000);

} // namespace gr::AnalogTV