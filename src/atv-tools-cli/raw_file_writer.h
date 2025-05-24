/*
 * This file is a part of the analog-tv-tools project.
 * Copyright (c) 2025 Roman Ukhov <ukhov.roman@gmail.com>
 */

#pragma once

#include "processor.h"

std::unique_ptr<processor<float>> make_raw_writer(std::filesystem::path const &path);