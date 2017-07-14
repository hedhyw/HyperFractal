/*
 * The MIT License
 *
 * Copyright 2016 Maxim Krivchun.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/* 
 * File:   Fractal.cpp
 * Author: hedhyw
 * 
 * Created on October 30, 2016, 9:33 AM
 */

#include "Fractal.h"

Fractal::Fractal(int ITERATION_LIMIT)
: MAX_RADIUS(2.0), MAX_FRAMES(80), LIMIT(ITERATION_LIMIT) {
    C = triplexNumber(1.2, -0.34, +1.24);
}

void Fractal::nextFrame() {
    static float rot = 0;
    rot += 
    frame_index++;
    C = triplexNumber::sphere(1.0, rot / 90.0f * 40 / M_PI, rot / 180.0f+0.5f);
}

void Fractal::func(triplexNumber &t, double x, double y, double z) {
    t = t.pow(3) + C;
}

uint8_t Fractal::color(int i, int i2, int x, int y, int z) {
    const int MIN_COLOR = 5;
    // i2 - product of absolute values of complex numbers
    // i - count of iterations
    i = ((int) (i * 5 * 0xFF) / LIMIT) % 0xFF;
    return (uint8_t) (i < MIN_COLOR ? 0 : (int) (i2) % 0xFF);
}

bool Fractal::hasNextFrame() {
    return (frame_index < MAX_FRAMES);
}

int Fractal::getFrameIndex() {
    return frame_index;
}

Fractal::~Fractal() {
    
}
