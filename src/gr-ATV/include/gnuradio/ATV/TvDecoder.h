/* -*- c++ -*- */
/*
 * Copyright 2025 Roman Ukhov <ukhov.roman@gmail.com>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ATV_TVDECODER_H
#define INCLUDED_ATV_TVDECODER_H

#include <gnuradio/ATV/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace ATV {

/*!
 * \brief <+description of block+>
 * \ingroup ATV
 *
 */
class ATV_API TvDecoder : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<TvDecoder> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of ATV::TvDecoder.
     *
     * To avoid accidental use of raw pointers, ATV::TvDecoder's
     * constructor is in a private implementation
     * class. ATV::TvDecoder::make is the public interface for
     * creating new instances.
     */
    static sptr
    make(double samp_rate, int standard, unsigned short port, const std::string& path);
};

} // namespace ATV
} // namespace gr

#endif /* INCLUDED_ATV_TVDECODER_H */
