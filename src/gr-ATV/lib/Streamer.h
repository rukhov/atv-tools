#pragma once

#include <lib-atv-tools/decoder.h>

namespace gr::AnalogTV {
class Streamer
{
public:
    virtual ~Streamer() = default;

    virtual void on_frame(std::span<atv::decoder::RGB_color> const&,
                          size_t visible_rect_x,
                          size_t visible_rect_y,
                          size_t visible_rect_width,
                          size_t visible_rect_height,
                          size_t total_width,
                          size_t total_height) = 0;
};

} // namespace gr::AnalogTV