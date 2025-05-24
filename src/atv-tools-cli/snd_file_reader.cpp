/*
 * This file is a part of the analog-tv-tools project.
 * Copyright (c) 2025 Roman Ukhov <ukhov.roman@gmail.com>
 */

#include "snd_file_reader.h"

namespace
{

    class snd_file_reader_impl : public processor<float>
    {
        SNDFILE *_file = nullptr;
        uint64_t _total_read = 0;
        SF_INFO _info = {};
        std::vector<float> _buffer;

    public:
        snd_file_reader_impl(std::filesystem::path const &path)
        {
            _file = sf_open(path.string().c_str(), SFM_READ, &_info);

            if (!_file)
                throw std::runtime_error(
                    std::format("Cannot open sound file: {}", path.string()));

            if (_info.channels > 2)
                throw std::runtime_error(
                    std::format("Unexpected channels number: {}", _info.channels));

            std::clog << std::format(
                "Opened file (fmt:{:x}): {}", _info.format, path.string());
        }

        ~snd_file_reader_impl() { sf_close(_file); }
        // processor<float>
    private:
        processor<float>::out_span_t
        process(processor<float>::in_span_t const &buff) override
        {
            if (_buffer.size() < buff.size())
                _buffer.resize(buff.size());

            size_t readCount =
                sf_readf_float(_file, _buffer.data(), buff.size() / _info.channels);
            readCount *= _info.channels;
            _total_read += readCount;
            return {_buffer.data(), readCount};
        }
    };
} // namespace

std::unique_ptr<processor<float>> make_snd_reader(std::filesystem::path const &path)
{
    return std::make_unique<snd_file_reader_impl>(path);
}