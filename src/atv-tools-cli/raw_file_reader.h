/*
 * This file is a part of the analog-tv-tools project.
 * Copyright (c) 2025 Roman Ukhov <ukhov.roman@gmail.com>
 */

#pragma once

#include "processor.h"

enum class DaraType
{
    F32,
    I16
};

std::unique_ptr<processor<float>> make_raw_reader(std::filesystem::path const &path,
                                                  DaraType type = DaraType::F32);