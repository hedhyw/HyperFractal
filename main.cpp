/*
 * The MIT License
 *
 * Copyright 2016 hedhyw.
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
#include "math.h"
#include "GL/glut.h"
#include "GL/glu.h"
#include "triplexNumber.h"
#include "box.h"
#include <algorithm>
#include <vector>
#include "bitmapCore.hpp"
#include <mutex>
#include <thread>
#include <chrono>
using namespace std;

const int SIZE = 150;
const int DELTA = SIZE / 2.0;
const int LIMIT = 30;
const int MIN_COLOR = 5;
const int THREAD_COUNT = 2;
const double FRACTAL_RADIUS = 2.0;
const string FRAMES_PATH_PREFIX = "/tmp/img";
triplexNumber C(1.2, -0.34, +1.24);
//const triplexNumber C(-1.2, -1.34, +1.24);
uint8_t *** arr;
float rot = 0.0f;
int i = 0; // frameindex

const int Z_COUNTER_STOP_VALUE = -1;
volatile int z_counter = SIZE + 1;
std::mutex mtx;

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
                //r = 0.25*r;
                //g = 0.5*g;
                if (i == 0) continue;
                if (X > 0 && Y > 0 && Z > 0 &&
                        X < SIZE - 1 && Y < SIZE - 1 && Z < SIZE - 1) {
                    if (arr[X][Y][Z - 1] != 0 && arr[X][Y][Z + 1] != 0 &&
                            arr[X - 1][Y][Z] != 0 && arr[X + 1][Y][Z] != 0 &&
                            arr[X][Y - 1][Z] != 0 && arr[X][Y + 1][Z] != 0) continue;
                }
                //++count;
                glPushMatrix();
                glColor3f(r / 255.0f, g / 255.0f, b / 255.0f);
                float color[] = {r / 255.0f, g / 255.0f, b / 255.0f};
                //float emission[] = {0.01f,0.01f,0.01f};
                glColor3f(r / 255.0f, g / 255.0f, b / 255.0f);
                //glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
                //glMaterialfv(GL_FRONT, GL_EMISSION, emission);
                glTranslatef((X - DELTA) / (float) SIZE*FRACTAL_RADIUS,
                        (Y - DELTA) / (float) SIZE*FRACTAL_RADIUS,
                        (Z - DELTA) / (float) SIZE * FRACTAL_RADIUS);
                glScalef(FRACTAL_RADIUS / (float) SIZE,
                        FRACTAL_RADIUS / (float) SIZE,
                        FRACTAL_RADIUS / (float) SIZE);
                //draw_box();
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
    //init_fractal();
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
    //glRotatef(2*rot, 1.0f, 1.0f, 1.0f);
    draw_fractal();
    glDisable(GL_LIGHT0); // light0 off
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

    cout << "generating finished." << endl;
}

void idle() {
    //triplexNumber b(0, 0.02, -0.01);
    //C += b;
    //
    //C = triplexNumber(0.2,cos(rot/90.0f*M_PI*0.5)*80/M_PI,1,true);
    //C = triplexNumber(0.2, rot / 90.0f * 40 / M_PI, 1, true);
    C = triplexNumber::sphere(1.0, rot / 90.0f * 40 / M_PI, rot / 180.0f+0.5f);
    rot += 1.0f;

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
                double x = FRACTAL_RADIUS * (X - DELTA) / (double) SIZE,
                        y = FRACTAL_RADIUS * (Y - DELTA) / (double) SIZE,
                        z = FRACTAL_RADIUS * (Z - DELTA) / (double) SIZE;
                //triplexNumber t(cos(x),sin(y),cos(z)*sin(z));
                triplexNumber t(x, y, z);
                int i, i2 = 1;
                for (i = 0; i < LIMIT; ++i) {
                    //t = t.pow(3.1) + C;
                    t = t.pow(3) + C;
                    i2 *= t.getAbs();
                    if (t.getAbs() > FRACTAL_RADIUS) break;
                }
                i = ((int) (i * 5 * 0xFF) / LIMIT) % 0xFF;
                //if (i > MIN_COLOR) i = (int)(t.getAbs()*13495) %0xFF;
                arr[Z][Y][X] = (uint8_t) (i < MIN_COLOR ? 0 : (int) (i2) % 0xFF);
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

