/* -*- c++ -*- */
/*
 * Copyright 2025 Roman Ukhov <ukhov.roman@gmail.com>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <gnuradio/ATV/TvDecoder.h>
#include <gnuradio/io_signature.h>

#include <lib-atv-tools/decoder.h>

#include "RTSPServer.h"

namespace gr {
namespace ATV {

using namespace gr::AnalogTV;

using input_type = float;
using output_type = float;

class TvDecoder_impl : public TvDecoder
{
private:
    std::unique_ptr<atv::decoder> _decoder;
    uint16_t _port;
    std::string _path;
    std::unique_ptr<Streamer> _streamer;

public:
    /*
     * The private constructor
     */
    TvDecoder_impl(double samp_rate, int, unsigned short port, const std::string& path)
        : gr::sync_block("TvDecoder",
                         gr::io_signature::make(
                             1 /* min inputs */, 1 /* max inputs */, sizeof(input_type)),
                         gr::io_signature::make(0 /* min outputs */,
                                                0 /*max outputs */,
                                                sizeof(output_type))),
          _decoder(atv::decoder::make(atv::standard_e::SECAM,
                                      samp_rate,
                                      [this](std::span<atv::decoder::RGB> const& frame,
                                             size_t visible_rect_x,
                                             size_t visible_rect_y,
                                             size_t visible_rect_width,
                                             size_t visible_rect_height,
                                             size_t total_width,
                                             size_t total_height) {
                                          on_frame_ready(frame,
                                                         visible_rect_x,
                                                         visible_rect_y,
                                                         visible_rect_width,
                                                         visible_rect_height,
                                                         total_width,
                                                         total_height);
                                      })),
          _port(port),
          _path("/" + path)
    {
    }
    /*
     * Our virtual destructor.
     */
    ~TvDecoder_impl() {}

    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items) override
    {
        auto const in = static_cast<const float*>(input_items[0]);

        _decoder->process(noutput_items, in);

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

private:
    void on_frame_ready(std::span<atv::decoder::RGB> const& frame,
                        size_t visible_rect_x,
                        size_t visible_rect_y,
                        size_t visible_rect_width,
                        size_t visible_rect_height,
                        size_t total_width,
                        size_t total_height)
    {
        if (!_streamer) {
            _streamer = make_rtsp_server(
                _port, _path.c_str(), visible_rect_width, visible_rect_height, 8000);
        }

        _streamer->on_frame(frame,
                            visible_rect_x,
                            visible_rect_y,
                            visible_rect_width,
                            visible_rect_height,
                            total_width,
                            total_height);
    }
};

TvDecoder::sptr TvDecoder::make(double samp_rate,
                                int standard,
                                unsigned short port,
                                const std::string& path)
{
    return gnuradio::make_block_sptr<TvDecoder_impl>(samp_rate, standard, port, path);
}

} /* namespace ATV */
} /* namespace gr */
