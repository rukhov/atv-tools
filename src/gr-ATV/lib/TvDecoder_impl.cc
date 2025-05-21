/* -*- c++ -*- */
/*
 * Copyright 2025 Roman Ukhov <ukhov.roman@gmail.com>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <gnuradio/ATV/TvDecoder.h>

#include <gnuradio/io_signature.h>

#include <vector>

#include <lib-atv-tools/decoder.h>

namespace gr {
namespace ATV {

using input_type = float;
using output_type = float;

class TvDecoder_impl : public TvDecoder
{
private:
    std::unique_ptr<atv::decoder> _decoder;

public:
    /*
     * The private constructor
     */
    TvDecoder_impl(double samp_rate)
        : gr::sync_block("TvDecoder",
                         gr::io_signature::make(
                             1 /* min inputs */, 1 /* max inputs */, sizeof(input_type)),
                         gr::io_signature::make(0 /* min outputs */,
                                                0 /*max outputs */,
                                                sizeof(output_type))),
          _decoder(atv::decoder::make(atv::standard_e::SECAM, samp_rate, {}))
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
        // auto in = static_cast<const input_type*>(input_items[0]);
        // auto out = static_cast<output_type*>(output_items[0]);

        // #pragma message("Implement the signal processing in your block and remove this
        // warning")
        //  Do <+signal processing+>
        //  Tell runtime system how many input items we consumed on
        //  each input stream.
        consume_each(noutput_items);

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }
};

TvDecoder::sptr TvDecoder::make(double samp_rate,
                                int standard,
                                unsigned short port,
                                const std::string& path)
{
    return gnuradio::make_block_sptr<TvDecoder_impl>(samp_rate);
}

} /* namespace ATV */
} /* namespace gr */
