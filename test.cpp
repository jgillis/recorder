#include "recorder.hpp"

int main(){

  Recorder a;
  Recorder b;

  a <<= 2;
  b <<= 3;

  Recorder z = a*b;
  Recorder y1 = cos(a)-z;

  double y1num;
  y1 >>= y1num;

 Recorder::stop_recording();

  return 0;
}

//#include "recorder.hpp"
//
//int main(){
//
//  double p = 7;
//
//  Recorder x;
//  Recorder y;
//  Recorder t;
//
//  x <<= 2;
//  y <<= 5.5;
//  t <<= 6+1.0/3;
//
//  std::cout << "t:" << t << std::endl;
//  t = 5;
//  std::cout << "t:" << t << std::endl;
//  t = t+3;
//  std::cout << "t:" << t << std::endl;
//
//  std::cout << "x:" << x << std::endl;
//  x = x+3;
//  std::cout << "x:" << x << std::endl;
//  x = x+3;
//  std::cout << "x:" << x << std::endl;
//  x = x+t;
//  std::cout << "x:" << x << std::endl;
//
//  t = x;
//  std::cout << "t:" << t << std::endl;
//  t = 99;
//  std::cout << "t:" << t << std::endl;
//  Recorder z = x+y;
//
//  if (z>=20) {
//    z = z+50;
//  } else {
//    z = z+3;
//  }
//
//
//  z = z*(x>=0);
//  z = sin(z);
//  std::cout << "z:" << z << std::endl;
//
//  double znum;
//  z >>= znum;
//
// Recorder::stop_recording();
//
//  std::cout << znum << std::endl;
//
//  return 0;
//}
