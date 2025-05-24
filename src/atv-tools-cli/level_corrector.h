/*
 * This file is a part of the analog-tv-tools project.
 * Copyright (c) 2025 Roman Ukhov <ukhov.roman@gmail.com>
 */

#pragma once

template <typename T>
class level_corrector
{
    T _state = 0;
    double _add;
    double _multiply;

public:
    level_corrector(double add, double multiply) : _add(add), _multiply(multiply) {}

    T state() const { return _state; }

    T process(T s)
    {
        _state = (s + _add) * _multiply;
        return _state;
    }

    void process(std::span<T> const &buff)
    {
        for (auto &e : buff)
        {
            e = process(e);
        }
    }
};
