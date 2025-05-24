/*
 * This file is a part of the analog-tv-tools project.
 * Copyright (c) 2025 Roman Ukhov <ukhov.roman@gmail.com>
 */

#include "raw_file_reader.h"

namespace
{

    class raw_file_reader : public processor<float>
    {
        uint64_t _total_written = 0;
        std::ifstream _i;
        std::vector<uint8_t> _buffer;
        std::vector<float> _out_buffer;
        DaraType _type;

        size_t itemSize() const
        {
            if (_type == DaraType::F32)
                return sizeof(float);
            else
                return sizeof(int16_t);
        }

        size_t bufferLength() const { return _buffer.size() / itemSize(); }
        void bufferResize(size_t length) { _buffer.resize(length * itemSize()); }

    public:
        raw_file_reader(std::filesystem::path const &path, DaraType type)
            : _i(path, std::ios::in | std::ios::binary), _type(type)
        {
            std::clog << std::format("Opened file for read: {}", path.string());
        }

        ~raw_file_reader() {}
        // processor<float>
    private:
        processor<float>::out_span_t
        process(processor<float>::in_span_t const &buff) override
        {
            if (bufferLength() < buff.size())
                bufferResize(buff.size());

            if (_out_buffer.size() < buff.size())
                _out_buffer.resize(buff.size());

            size_t itemsRead = 0;

            _i.read(reinterpret_cast<char *>(_buffer.data()), buff.size() * itemSize());

            itemsRead = _i.gcount() / itemSize();

            if (_type == DaraType::F32)
            {
                auto src = reinterpret_cast<float *>(_buffer.data());
                for (size_t i = 0; i < itemsRead; ++i)
                {
                    _out_buffer[i] = src[i];
                }
            }
            else if (_type == DaraType::I16)
            {
                auto src = reinterpret_cast<int16_t *>(_buffer.data());
                for (size_t i = 0; i < itemsRead; ++i)
                {
                    _out_buffer[i] = src[i] / double(1 << 15);
                }
            }
            else
                throw std::runtime_error("Unsipported data type");

            return {_out_buffer.data(), itemsRead};
        }
    };
} // namespace

std::unique_ptr<processor<float>> make_raw_reader(std::filesystem::path const &path,
                                                  DaraType type)
{
    return std::make_unique<raw_file_reader>(path, type);
}