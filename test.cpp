#include "recorder.hpp"


static Recorder bar;

int main(){

  double p = 7;

  Recorder x;
  Recorder y;
  Recorder t;

  x <<= 1;
  y <<= 2;
  t <<= 3;
  bar <<= 32;

  Recorder z = x*3;

  if (z>=0) {
    z+=y*bar;
  }

  double r;
  z >>= r;

  Recorder::stop_recording();
  return 0;
}
