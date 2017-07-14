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
 * File:   triplexNumber.cpp
 * Author: hedhyw
 * 
 * Created on October 24, 2016, 10:40 AM
 */

#include "triplexNumber.h"
#include "math.h"

triplexNumber::triplexNumber(double X, double Y, double Z)
: x(X), y(Y), z(Z) {
    init();
}



triplexNumber triplexNumber::sphere(double fi, double theta, double r){
    return triplexNumber(r * std::cos(fi) * std::sin(theta),
            r * std::sin(fi) * std::sin(theta),
            r * std::cos(theta));
}

triplexNumber::triplexNumber()
: x(0), y(0), z(0) {
    init();
}

triplexNumber::triplexNumber(const triplexNumber& orig)
: x(orig.x), y(orig.y), z(orig.z) {
    init();
}

triplexNumber::~triplexNumber() {
}

void triplexNumber::init(){
    r = std::sqrt(x * x + y * y + z * z);
    fi = (x == 0 ? M_PI / 2.0 : std::atan(y/x));
    theta = (r == 0 ? 0 : std::acos(z / r)); // if r == 0 : error!
}

double triplexNumber::getFi() {
    return this->fi;
}

double triplexNumber::getTheta() {
    return this->theta;
}

double triplexNumber::getX() {
    return this->x;
}

double triplexNumber::getY() {
    return this->y;
}

double triplexNumber::getZ() {
    return this->z;
}

double triplexNumber::getAbs() {
    return this->r;
}

bool triplexNumber::operator==(const triplexNumber& t) {
    return (x == t.x && y == t.y && z == t.z);
}

void triplexNumber::operator=(const triplexNumber& t) {
    x = t.x; y = t.y; z = t.z;
    init();
}

triplexNumber triplexNumber::operator+(const triplexNumber& t) {
    return triplexNumber(
            x + t.x,
            y + t.y,
            z + t.z
            );
}

triplexNumber triplexNumber::operator*(const double& n){
    return triplexNumber(x*n, y*n, z*n);
}

triplexNumber triplexNumber::operator-(const triplexNumber& t) {
    return triplexNumber(
            x - t.x,
            y - t.y,
            z - t.z
            );
}

void triplexNumber::operator+=(const triplexNumber& t) {
    x += t.x;
    y += t.y;
    z += t.z;
    init();
}

void triplexNumber::operator-=(const triplexNumber& t) {
    x -= t.x;
    y -= t.y;
    z -= t.z;
    init();
}

void triplexNumber::operator*=(const double& n) {
    x *= n;
    y *= n;
    z *= n;
    init();
}

triplexNumber triplexNumber::pow(double N) {
    double rn = std::pow(r, N), ntheta = N*theta, nfi = N*fi;
    return triplexNumber(
            rn * std::cos(nfi) * std::sin(ntheta),
            rn * std::sin(nfi) * std::sin(ntheta),
            rn * std::cos(ntheta)
            );
}