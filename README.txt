HyperFractal – the three-dimensional fractal animation generator.

All fractal parameters are located in fractal.cpp:
  Fractal::func – an iteration fractal function;
  Fractal::nextFrame – a function that changes parameters for the next frame;
  Fractal::color – a fractal color function;
  MAX_RADIUS – limit of fractal size (empty parts aren't handled);
  MAX_FRAMES – a count of frames.


Default names of frames are /tmp/img000.bmp, /tmp/img001.bmp, ...
Image parameters that are located in main.cpp:
  SIZE  – a half of image size;
  LIMIT – iterations limit;
  THREAD_COUNT - count of generation threads.

Note: libpthread-stubs0-dev and freeglut3-dev must be installed.