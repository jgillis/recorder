
int main(){

  double p = 7;

  Recorder::start_recording();

  Recorder x;
  Recorder y;
  Recorder t;

  x <<= 2;
  y <<= 5.5;
  t <<= 6+1.0/3;

  uout() << "t:" << t << std::endl;
  t = 5;
  uout() << "t:" << t << std::endl;
  t = t+3;
  uout() << "t:" << t << std::endl;

  uout() << "x:" << x << std::endl;
  x = x+3;
  uout() << "x:" << x << std::endl;
  x = x+3;
  uout() << "x:" << x << std::endl;
  x = x+t;
  uout() << "x:" << x << std::endl;

  t = x;
  uout() << "t:" << t << std::endl;
  t = 99;
  uout() << "t:" << t << std::endl;
  Recorder z = x+y;

  if (z>=20) {
    z = z+50;
  } else {
    z = z+3;
  }


  z = z*(x>=0);

  uout() << "z:" << z << std::endl;

  double znum;
  z >>= znum;

 Recorder::stop_recording();

  uout() << znum << std::endl;

  return 0;
}
