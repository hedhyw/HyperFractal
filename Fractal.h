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
 * File:   Fractal.h
 * Author: hedhyw
 *
 * Created on October 30, 2016, 9:33 AM
 */

#ifndef FRACTAL_H
#define FRACTAL_H

#include <cmath>
#include <cstdint>
#include "triplexNumber.h"

class Fractal {
public:
    Fractal(int ITERATION_LIMIT);
    virtual ~Fractal();
    void func(triplexNumber &t, double x, double y, double z);
    void nextFrame();
    uint8_t color(int i, int i2, int x, int y, int z);
    bool hasNextFrame();
    const float MAX_RADIUS;
    const int MAX_FRAMES;
    const int LIMIT;
    int getFrameIndex();
protected:
    int frame_index = 0;
    triplexNumber C;
};

#endif /* FRACTAL_H */

