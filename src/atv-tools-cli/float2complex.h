/*
 * This file is a part of the analog-tv-tools project.
 * Copyright (c) 2025 Roman Ukhov <ukhov.roman@gmail.com>
 */

#pragma once

#include <lib-dsp/processor.h>

class float2complex : public dsp::processor<float, std::complex<float>>
{
    std::vector<std::complex<float>> _buffer;

public:
    out_span_t process(in_span_t const& in) override
    {
        if (_buffer.size() < in.size() / 2)
            _buffer.resize(in.size() / 2);

        for (size_t i = 0; i < in.size() / 2; ++i) {
            _buffer[i].real(in[i * 2]);
            _buffer[i].imag(in[i * 2 + 1]);
        }

        return { reinterpret_cast<std::complex<float>*>(_buffer.data()), in.size() / 2 };
    }
};