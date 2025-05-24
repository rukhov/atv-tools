/*
 * This file is a part of the analog-tv-tools project.
 * Copyright (c) 2025 Roman Ukhov <ukhov.roman@gmail.com>
 */

#pragma once

class timer
{
public:
    using clock_t = std::chrono::steady_clock;

    timer() : _start(clock_t::now()) {}

    clock_t::duration duration() const { return clock_t::now() - _start; }

private:
    const clock_t::time_point _start;
};