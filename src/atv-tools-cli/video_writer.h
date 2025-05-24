/*
 * This file is a part of the analog-tv-tools project.
 * Copyright (c) 2025 Roman Ukhov <ukhov.roman@gmail.com>
 */

#pragma once

#include <lib-atv-tools/decoder.h>

class video_writer
{
public:
    virtual ~video_writer() = default;
    virtual void process_frame(std::span<atv::decoder::RGB_color> const &,
                               size_t visible_rect_x,
                               size_t visible_rect_y,
                               size_t visible_rect_width,
                               size_t visible_rect_height,
                               size_t total_width,
                               size_t total_height) = 0;

    static std::unique_ptr<video_writer> make(std::filesystem::path const &file_path);
};
