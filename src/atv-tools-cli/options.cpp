/*
 * This file is a part of the analog-tv-tools project.
 * Copyright (c) 2025 Roman Ukhov <ukhov.roman@gmail.com>
 */

#include "options.h"
#include <boost/program_options.hpp>

namespace po = boost::program_options;

namespace
{

    char const *INPUT_FILE_OPTION = "input-file";
    char const *INPUT_DATA_TYPE_OPTION = "input-data-type";
    char const *OUTPUT_FILE_OPTION = "output-file";
    char const *OUT_CVBS_RAW_FILE_OPTION = "out-cvbs-raw-file";
    char const *AMPLIFICATION_OPTION = "amplification";
    char const *DC_CORRECTION_OPTION = "dc-correction";
    char const *SAMPLE_RATE_OPTION = "sample-rate";
    char const *MAX_FRAME_NUMBER_OPTION = "max-frames";
    char const *INPUT_TYPE_OPTION = "input-type";
    char const *OUTPUT_TYPE_OPTION = "output-type";
    char const *STANDARD_OPTION = "standard";
    char const *BASEBAND_CARRIER_FREQUENCY_OPTION = "baseband-carrier-frequency";
    char const *BLACK_AND_WHITE_MODE_OPTION = "bw";

} // namespace

options read_options(int argc, char *argv[])
{
    options opts;
    // Declare the supported options.
    po::options_description desc("Allowed options");
    desc.add_options()                   //
        ("help", "produce help message") //
        (INPUT_TYPE_OPTION,
         po::value<std::string>(),
         "input file type (f32, i16, auto), default auto. f32 means 32-bit float, i16 "
         "means int16") //
        (INPUT_DATA_TYPE_OPTION,
         po::value<std::string>(),
         "input data type (cvbs, fm, am), default cvbs.") //
        (OUTPUT_TYPE_OPTION,
         po::value<std::string>(),
         "output file type (raw, avi), default avi")                                 //
        (INPUT_FILE_OPTION, po::value<std::string>(), "define input file name")      //
        (OUTPUT_FILE_OPTION, po::value<std::string>(), "define output file name")    //
        (OUT_CVBS_RAW_FILE_OPTION, po::value<std::string>(), "output cvbs RAW file") //
        (SAMPLE_RATE_OPTION, po::value<double>(), "input sample rate, Hz")           //
        (STANDARD_OPTION,
         po::value<std::string>(),
         "define TV signal standard (secam, ntsc, pal)")                       //
        (AMPLIFICATION_OPTION, po::value<double>(), "Amplification, ex. 0.5")  //
        (DC_CORRECTION_OPTION, po::value<double>(), "DC correction, ex. -1.5") //
        (MAX_FRAME_NUMBER_OPTION,
         po::value<uint64_t>(),
         "Maximum frames to process, then stop") //
        (BASEBAND_CARRIER_FREQUENCY_OPTION,
         po::value<double>(),
         "Baseband carrier frequency, Hz") //
        (BLACK_AND_WHITE_MODE_OPTION,
         po::value<bool>(),
         "Black&White mode, 0 or 1, default is 0") //
        ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help"))
    {
        std::cout << desc << "\n";
        return opts;
    }

    if (vm.count(INPUT_TYPE_OPTION))
    {
        auto it = vm[INPUT_TYPE_OPTION].as<std::string>();
        if (it == "f32")
            opts.input_type = options::in_type::F32;
        else if (it == "i16")
            opts.input_type = options::in_type::I16;
        else
            opts.input_type = options::in_type::AUTO;
        std::cout << std::format("input file type\t: '{}'\n", (int)opts.input_type);
    }

    if (vm.count(INPUT_DATA_TYPE_OPTION))
    {
        auto it = vm[INPUT_DATA_TYPE_OPTION].as<std::string>();
        if (it == "cvbs")
            opts.input_data_type = options::in_data_type::cvbs;
        else
            throw std::runtime_error(
                std::format("Data type <{}> is not supported.\n", it));

        std::cout << std::format("input data type\t: '{}'\n", it);
    }

    if (vm.count(OUTPUT_TYPE_OPTION))
    {
        auto it = vm[OUTPUT_TYPE_OPTION].as<std::string>();
        if (it == "raw")
            opts.output_type = options::out_type::RAW;
        else
            opts.output_type = options::out_type::AVI;
        std::cout << std::format("output file type\t: '{}'\n", (int)opts.output_type);
    }

    if (vm.count(STANDARD_OPTION))
    {
        auto st = vm[STANDARD_OPTION].as<std::string>();
        if (st == "pal")
            opts.standard = atv::standard_e::PAL;
        else if (st == "secam")
            opts.standard = atv::standard_e::SECAM;
        else
            opts.standard = atv::standard_e::NTSC;
        std::cout << std::format("Standard\t: {}\n", (int)opts.standard);
        if (opts.standard != atv::standard_e::SECAM)
            throw std::runtime_error(
                std::format("Standard <{}> is not supported yet.\n", st));
    }

    if (vm.count(INPUT_FILE_OPTION))
    {
        opts.input_file = vm[INPUT_FILE_OPTION].as<std::string>();
        std::cout << std::format("Input file\t: '{}'\n", opts.input_file.string());
    }

    if (vm.count(OUTPUT_FILE_OPTION))
    {
        opts.output_file = vm[OUTPUT_FILE_OPTION].as<std::string>();
        std::cout << std::format("Output file\t: '{}'\n", opts.output_file.string());
    }

    if (vm.count(OUT_CVBS_RAW_FILE_OPTION))
    {
        opts.out_cvbs_raw_file = vm[OUT_CVBS_RAW_FILE_OPTION].as<std::string>();
        std::cout << std::format("Output cvbs RAW file\t: '{}'\n",
                                 opts.out_cvbs_raw_file.string());
    }

    if (vm.count(AMPLIFICATION_OPTION))
    {
        opts.amplification = vm[AMPLIFICATION_OPTION].as<double>();
        std::cout << std::format("Amplification\t: {}\n", opts.amplification);
    }

    if (vm.count(DC_CORRECTION_OPTION))
    {
        opts.dc_correction = vm[DC_CORRECTION_OPTION].as<double>();
        std::cout << std::format("DC correction\t: {}\n", opts.dc_correction);
    }

    if (vm.count(SAMPLE_RATE_OPTION))
    {
        opts.input_sample_rate_hz = vm[SAMPLE_RATE_OPTION].as<double>();
        std::cout << std::format("Sample Rate\t: {}\n", opts.input_sample_rate_hz);
    }

    if (vm.count(BASEBAND_CARRIER_FREQUENCY_OPTION))
    {
        opts.carrier_frequency_hz = vm[BASEBAND_CARRIER_FREQUENCY_OPTION].as<double>();
        std::cout << std::format("Baseband carrier frequency\t: {}\n",
                                 opts.carrier_frequency_hz);
    }

    if (vm.count(MAX_FRAME_NUMBER_OPTION))
    {
        opts.max_frame_number = vm[MAX_FRAME_NUMBER_OPTION].as<uint64_t>();
        std::cout << std::format("Maximum frames\t: {}\n", opts.max_frame_number);
    }

    if (vm.count(BLACK_AND_WHITE_MODE_OPTION))
    {
        opts.balck_and_white = vm[BLACK_AND_WHITE_MODE_OPTION].as<bool>();
        std::cout << std::format("Black&White mode\t: {}\n", opts.balck_and_white);
    }

    return opts;
}