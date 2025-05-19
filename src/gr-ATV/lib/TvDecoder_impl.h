/* -*- c++ -*- */
/*
 * Copyright 2025 Roman Ukhov <ukhov.roman@gmail.com>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ATV_TVDECODER_IMPL_H
#define INCLUDED_ATV_TVDECODER_IMPL_H

#include <gnuradio/ATV/TvDecoder.h>

namespace gr {
namespace ATV {

class TvDecoder_impl : public TvDecoder
{
private:
    // Nothing to declare in this block.

public:
    TvDecoder_impl(double samp_rate);
    ~TvDecoder_impl();

    // Where all the action really happens
    void forecast(int noutput_items, gr_vector_int& ninput_items_required);

    int general_work(int noutput_items,
                     gr_vector_int& ninput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items);
};

} // namespace ATV
} // namespace gr

#endif /* INCLUDED_ATV_TVDECODER_IMPL_H */
