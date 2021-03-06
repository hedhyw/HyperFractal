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
 * File:   main.cpp
 * Author: hedhyw
 *
 * Created on October 24, 2016, 10:38 AM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <vector>
#include <mutex>
#include <thread>
#include <chrono>
#include "GL/glut.h"
#include "GL/glu.h"
#include "box.h"
#include "bitmapCore.hpp"
#include "Fractal.h"
#include "triplexNumber.h"

using namespace std;

const int SIZE = 150;
const int DELTA = SIZE / 2.0;
const int LIMIT = 30;
const int THREAD_COUNT = 2;
const string FRAMES_PATH_PREFIX = "/tmp/img";
triplexNumber C(1.2, -0.34, +1.24);
uint8_t *** arr;
float rot = 0.0f;
int i = 0; // frameindex

const int Z_COUNTER_STOP_VALUE = -1;
volatile int z_counter = SIZE + 1;
std::mutex mtx;
Fractal fractal(LIMIT);

void draw_fractal() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertexBuf);
    for (int Z = 0; Z < SIZE; ++Z) {
        for (int Y = 0; Y < SIZE; ++Y) {
            for (int X = 0; X < SIZE; ++X) {
                uint8_t i = arr[Z][Y][X];
                uint8_t r = (sin(3 * 0.8 + i) + 1)*128;
                uint8_t g = (sin(3 * 0.84 + i) + 1)*128;
                uint8_t b = (sin(3 * 0.901 + i) + 1)*128;
                if (i == 0) continue;
                if (X > 0 && Y > 0 && Z > 0 &&
                        X < SIZE - 1 && Y < SIZE - 1 && Z < SIZE - 1) {
                    if (arr[X][Y][Z - 1] != 0 && arr[X][Y][Z + 1] != 0 &&
                            arr[X - 1][Y][Z] != 0 && arr[X + 1][Y][Z] != 0 &&
                            arr[X][Y - 1][Z] != 0 && arr[X][Y + 1][Z] != 0) continue;
                }
                glPushMatrix();
                glColor3f(r / 255.0f, g / 255.0f, b / 255.0f);
                float color[] = {r / 255.0f, g / 255.0f, b / 255.0f};
                glColor3f(r / 255.0f, g / 255.0f, b / 255.0f);
                glTranslatef((X - DELTA) / (float) SIZE*fractal.MAX_RADIUS,
                        (Y - DELTA) / (float) SIZE*fractal.MAX_RADIUS,
                        (Z - DELTA) / (float) SIZE * fractal.MAX_RADIUS);
                glScalef(fractal.MAX_RADIUS / (float) SIZE,
                        fractal.MAX_RADIUS / (float) SIZE,
                        fractal.MAX_RADIUS / (float) SIZE);
                glDrawArrays(GL_QUADS, 0, VERTEX_BUFFER_SIZE);
                glPopMatrix();
            }
        }
    }
    glDisableClientState(GL_VERTEX_ARRAY);
}

void init() {
    glClearColor(0.34, 0.34, 0.34, 1);
    glEnable(GL_CULL_FACE);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
}

void light0_on() {
    float diffuse[] = {0.8, 0.8, 1, 1};
    float ambient[] = {0.2, 0.3, 0.4, 1};
    float position[] = {2.0, 2.0, 0, 1.0};
    GLfloat specular[] = {0.0, 0.0, 0.0, 1.0};
    float spot_direction[] = {-position[0], -position[1], -position[2]};
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    //glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 60);
    //glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
    //glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    glLoadIdentity();
    gluLookAt(3, 3, 0.5,
            0, 0, 0,
            0, 0, 1);
    light0_on();
    draw_fractal();
    glDisable(GL_LIGHT0);
    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double) width / (double) height, 0.5, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void genFractal() {
    cout << "start generating..." << endl;
    cout << "Frame #" << i << endl;
    cout << fixed << setprecision(5);
    cout << setw(10) << "X:" << C.getX();
    cout << setw(10) <<  "Y:" << C.getY();
    cout << setw(10) <<  "Z:" << C.getZ() << endl;
    cout << setw(10) <<  "R:" << C.getAbs();
    cout << setw(10) <<  "FI:" << C.getFi();
    cout << setw(10) <<  "THETA:" << C.getTheta() << endl;

    z_counter = 0;
    while (z_counter < SIZE) {
        cout << '\r' << ((z_counter + 1) * 100 / SIZE) << '%';
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(200));
    }
    cout << "\r100%" << endl;

    cout << "generation finished." << endl;
}

void idle() {
    if (!fractal.hasNextFrame()) {
        exit(0);
    }
    fractal.nextFrame();

    genFractal();

    display();
    const int W = SIZE * 2, H = W;
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    GLubyte * pixels = new GLubyte[W * H * 3];

    glReadPixels(0, 0, W, H, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    stringstream ss; ss << FRAMES_PATH_PREFIX;
    ss << setfill('0') << setw(5) << i++ << ".bmp";
    string file_name = ss.str();
    cout << file_name << endl << endl;
    ofstream ofs(file_name, ios_base::trunc);
    bitmapCore bmp(&ofs);
    bitmapCore::pixel* pxls = new bitmapCore::pixel[W];
    bmp.writeHeader(W, H);
    for (int Y = 0; Y < H; ++Y) {
        for (int X = 0; X < W; ++X) {
            int i = (X + Y * W)*3;
            pxls[X] = {pixels[i + 2], pixels[i + 1], pixels[i]};
        }
        bmp.writeLine(pxls);
        bmp.endLine();
    }
    delete [] pixels;
    ofs.close();

}

void gen() {
    while (z_counter != Z_COUNTER_STOP_VALUE) {
        mtx.lock();
        if (z_counter >= SIZE) {
            mtx.unlock();
            this_thread::yield();
            continue;
        }
        volatile int Z = z_counter++;
        mtx.unlock();
        for (int Y = 0; Y < SIZE; ++Y) {
            for (int X = 0; X < SIZE; ++X) {
                double x = fractal.MAX_RADIUS * (X - DELTA) / (double) SIZE,
                        y = fractal.MAX_RADIUS * (Y - DELTA) / (double) SIZE,
                        z = fractal.MAX_RADIUS * (Z - DELTA) / (double) SIZE;
                triplexNumber t(x, y, z);
                int i, i2 = 1;
                for (i = 0; i < LIMIT; ++i) {
                    fractal.func(t, x, y, z);
                    i2 *= t.getAbs();
                    if (t.getAbs() > fractal.MAX_RADIUS) break;
                }
                arr[Z][Y][X] = fractal.color(i, i2, x, y, z);
            }
        }
    }
}

int main(int argc, char** argv) {
    triplexNumber p = triplexNumber(0.1, 0.2, 0.5), k;

    cout << "start initialization..." << endl;
    cout << "Array size:      " << (long)pow(SIZE, 3) << " bytes" << endl;
    cout << "Iteration limit: " << LIMIT << endl;
    cout << "Threads count:   " << THREAD_COUNT << endl;

    arr = new uint8_t**[SIZE];
    for (int Z = 0; Z < SIZE; Z++) {
        arr[Z] = new uint8_t*[SIZE];
        for (int Y = 0; Y < SIZE; Y++) {
            arr[Z][Y] = new uint8_t[SIZE];
        }
    }

    thread * threads = new thread[THREAD_COUNT];
    for (int i = 0; i < THREAD_COUNT; i++)
        threads[i] = thread(gen);

    cout << "initialization finished." << endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(50, 25);
    glutInitWindowSize(SIZE * 2, SIZE * 2);
    glutCreateWindow("Hyper Fractal");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutMainLoop();

    z_counter = Z_COUNTER_STOP_VALUE;
    for (int i = 0; i < THREAD_COUNT; i++)
        threads[i].join();
    delete [] threads;
    delete [] arr;

    return 0;
}

