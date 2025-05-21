#include "RTSPServer.h"

#include <rtsp_streamer/RtspStreamer.h>

namespace {

using namespace gr::AnalogTV;

class RTSPServer_impl : public Streamer, public rtsp_streamer::FrameSource

{
#pragma pack(push, 1)
    struct _RGB {

        uint8_t r, g, b;
    };
#pragma pack(pop)

    size_t _frame_counter = 0;
    std::vector<uint8_t> _frame;

    uint16_t _port;
    std::string _path;
    std::unique_ptr<rtsp_streamer::RtspStreamer> _streamer;
    GstVideoInfo _format = {};

public:
    RTSPServer_impl(uint16_t port,
                    std::string const& path,
                    size_t width,
                    size_t height,
                    uint32_t bitrate)
        : _port(port), _path(path)
    {
        _format.width = width;
        _format.height = height;

        if (_format.height % 2)
            _format.height++;

        _streamer = rtsp_streamer::make_streamer(_port, _path, *this, bitrate);
    }

private:
    void on_frame(std::span<atv::decoder::RGB> const& src,
                  size_t visible_rect_x,
                  size_t visible_rect_y,
                  size_t visible_rect_width,
                  size_t visible_rect_height,
                  size_t total_width,
                  size_t total_height) override
    {
        if (!stride())
            return;

        for (int x = 0; x < _format.width; ++x) {
            for (int y = 0; y < _format.height; ++y) {

                auto rgb = src[(x + visible_rect_x) + (y + visible_rect_y) * total_width];

                *(atv::decoder::RGB*)(&(
                    _frame[x * sizeof(atv::decoder::RGB) + y * stride()])) = rgb;
            }
        }
    }
    // FrameSource
private:
    void set_format(GstVideoInfo const& format) override
    {
        _format = format;
        _frame.resize(stride() * format.height);
        ++_frame_counter;
    }

    std::tuple<size_t /*width*/, size_t /*height*/> get_frame_size() const override
    {
        return { _format.width, _format.height };
    }
    double /* width / heigth */ get_pixel_ratio() const override { return 1.0; }
    size_t stride() const override { return _format.stride[0]; }
    bool is_eof() const override { return false; }
    std::span<uint8_t> get_next_frame() override
    {
        return { (uint8_t*)_frame.data(), stride() * _format.height };
    }
};

} // namespace

namespace gr::AnalogTV {
std::unique_ptr<Streamer> make_rtsp_server(
    uint16_t port, std::string const& path, size_t width, size_t height, uint32_t bitrate)
{
    rtsp_streamer::init(0, nullptr);

    return std::make_unique<RTSPServer_impl>(port, path, width, height, bitrate);
}
} // namespace gr::AnalogTV