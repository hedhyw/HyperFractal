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
 * File:   triplexNumber.h
 * Author: hedhyw
 *
 * Created on October 24, 2016, 10:39 AM
 */

#ifndef TRIPLEXNUMBER_H
#define TRIPLEXNUMBER_H

class triplexNumber {
public:
    triplexNumber();
    triplexNumber(double, double, double);
    triplexNumber(const triplexNumber&);
    static triplexNumber sphere(double, double, double);
    virtual ~triplexNumber();
    double getX();
    double getY();
    double getZ();
    double getFi();
    double getTheta();
    double getAbs();
    
    triplexNumber pow(double);
    void operator=(const triplexNumber&);
    triplexNumber operator+(const triplexNumber&);
    triplexNumber operator-(const triplexNumber&);
    triplexNumber operator*(const double&);
    void operator*=(const double&);
    void operator+=(const triplexNumber&);
    void operator-=(const triplexNumber&);
    bool operator==(const triplexNumber&);
    
private:
    double x, y, z;
    double theta, fi, r;
    void init();
};

#endif /* TRIPLEXNUMBER_H */

