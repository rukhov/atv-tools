/*
 * This file is a part of the analog-tv-tools project.
 * Copyright (c) 2025 Roman Ukhov <ukhov.roman@gmail.com>
 */

#include "video_writer.h"

#include <opencv2/core.hpp> // Basic OpenCV structures (cv::Mat)
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp> // Video write

using namespace cv;

namespace
{

    class video_writer_impl : public video_writer
    {
        VideoWriter _outputVideo; // Open the output
        Size _frame_size;

    public:
        video_writer_impl(std::filesystem::path const &file_path)
            : _frame_size(1280, 960) //_frame_size((int)standard.total_line_count * 4 / 3,
                                     //(int)standard.total_line_count)
        {
            _outputVideo.open(file_path.string().c_str(),
                              VideoWriter::fourcc('M', 'J', 'P', 'G'),
                              25,
                              _frame_size,
                              true);

            if (!_outputVideo.isOpened())
                throw std::runtime_error(
                    std::format("Cannot open output file <{}>", file_path.string()));
        }

    private:
        void process_frame(std::span<atv::decoder::RGB_color> const &src,
                           size_t visible_rect_x,
                           size_t visible_rect_y,
                           size_t visible_rect_width,
                           size_t visible_rect_height,
                           size_t total_width,
                           size_t total_height) override
        {
            Mat frame(Size{(int)visible_rect_width, (int)visible_rect_height},
                      CV_8UC3,
                      Scalar(0, 0, 0));

            for (auto y = 0; y < visible_rect_height; ++y)
            {
                for (auto x = 0; x < visible_rect_width; ++x)
                {
                    auto rgb = src[visible_rect_x + x + (visible_rect_y + y) * total_width];
                    frame.at<Vec3b>({x, y}) = Vec3b(rgb.b, rgb.g, rgb.r); // OpenCV uses BGR format
                }
            }

            Mat dst;
            cv::resize(frame, dst, _frame_size, 0, 0, cv::INTER_LINEAR);

            _outputVideo << dst;
        }
    };
} // namespace

std::unique_ptr<video_writer> video_writer::make(std::filesystem::path const &file_path)
{
    return std::make_unique<video_writer_impl>(file_path);
}