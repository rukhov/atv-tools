/*
 * This file is a part of the analog-tv-tools project.
 * Copyright (c) 2025 Roman Ukhov <ukhov.roman@gmail.com>
 */

#include "raw_file_writer.h"

namespace
{

    class raw_file_writer : public processor<float>
    {
        uint64_t _total_written = 0;
        std::ofstream _o;

    public:
        raw_file_writer(std::filesystem::path const &path)
            : _o(path, std::ios::out | std::ios::binary)
        {
            std::clog << std::format("Opened file for write: {}", path.string());
        }

        ~raw_file_writer() {}
        // processor<float>
    private:
        processor<float>::out_span_t
        process(processor<float>::in_span_t const &buff) override
        {
            _o.write(reinterpret_cast<char const *>(buff.data()), buff.size() * sizeof(float));
            return {};
        }
    };
} // namespace

std::unique_ptr<processor<float>> make_raw_writer(std::filesystem::path const &path)
{
    return std::make_unique<raw_file_writer>(path);
}