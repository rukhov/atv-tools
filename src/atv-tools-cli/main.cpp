/*
 * This file is a part of the analog-tv-tools project.
 * Copyright (c) 2025 Roman Ukhov <ukhov.roman@gmail.com>
 */

#include <iostream>

#include <lib-atv-tools/decoder.h>

#include "options.h"
#include "raw_file_reader.h"
#include "raw_file_writer.h"
#include "snd_file_reader.h"
#include "timer.h"
#include "video_writer.h"
#include "level_corrector.h"

int main(int argc, char *argv[])
{
    timer::clock_t::duration decode_duration = {};
    timer::clock_t::duration video_encode_duration = {};

    try
    {
        std::cout << std::format(
            "Analogue TV decoding tools.\nCopyright (C) Roman Ukhov 2025.\n\n");

        options opts = read_options(argc, argv);

        std::unique_ptr<processor<float>> reader;
        std::unique_ptr<video_writer> writer;

        if (opts.input_type == options::in_type::F32)
        {
            reader = make_raw_reader(opts.input_file, DaraType::F32);
        }
        else if (opts.input_type == options::in_type::I16)
        {
            reader = make_raw_reader(opts.input_file, DaraType::I16);
        }
        else
        {
            reader = make_snd_reader(opts.input_file);
        }

        std::unique_ptr<processor<float>> raw_writer;
        if (opts.output_type == options::out_type::RAW)
        {
            raw_writer = make_raw_writer(opts.out_cvbs_raw_file);
        }
        else
        {
            try
            {
                writer = video_writer::make(opts.output_file);
            }
            catch (std::exception const &e)
            {
                std::cerr << std::format("Failed to create video writer: {}\n", e.what());
                return -1;
            }
        }

        bool b_Stop = false;
        size_t frameNum = 0;
        auto frame_cb = [&](std::span<atv::decoder::RGB_color> const &frame,
                            size_t visible_rect_x,
                            size_t visible_rect_y,
                            size_t visible_rect_width,
                            size_t visible_rect_height,
                            size_t total_width,
                            size_t total_height)
        {
            std::cout << std::format("Frame: {}\r", frameNum) << std::flush;

            if constexpr (1)
            {
                timer timer;
                if (writer)
                {
                    writer->process_frame(frame,
                                          visible_rect_x,
                                          visible_rect_y,
                                          visible_rect_width,
                                          visible_rect_height,
                                          total_width,
                                          total_height);
                }
                video_encode_duration += timer.duration();
            }

            ++frameNum;

            if (opts.max_frame_number > 0 && frameNum == opts.max_frame_number)
                b_Stop = true;
        };

        std::vector<float> in_buffer(1024 * 4);
        level_corrector<float> level_corrector(opts.dc_correction,
                                               opts.amplification);

        auto decoder = atv::decoder::make(atv::standard_e::SECAM, frame_cb);

        std::cout << std::format("Start processing.\n");

        for (;;)
        {

            auto data = reader->process({in_buffer.data(), in_buffer.size()});

            if (data.size() == 0)
                break;

            if (b_Stop == true)
                break;

            level_corrector.process(data);

            timer timer;

            if (raw_writer)
            {
                raw_writer->process(data);
                continue;
            }

            decoder->process(data.size(), data.data());

            decode_duration += timer.duration();
        }

        {
            timer timer;
            decoder->process_outstanding_tasks();
            decode_duration += timer.duration();
        }

        std::cout << std::format(
            "Done. ==================\nTotal frame number: {}\nProductivity: "
            "{:0.2f} FPS.\n",
            frameNum,
            frameNum > 0 ? (1. * 1000 /
                            std::chrono::duration_cast<std::chrono::milliseconds>(
                                (decode_duration - video_encode_duration) / frameNum)
                                .count())
                         : (0.));
    }
    catch (std::exception const &e)
    {
        std::cerr << std::format("Unhandled exception: {}\n", e.what());
    }

    return 0;
}