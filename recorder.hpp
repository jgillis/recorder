#ifndef Recorder_H_
#define Recorder_H_

#include <iostream>

//#if defined _WIN32
//#if defined (MAKEDLL)
//    #define DLL_EXPORT __declspec(dllexport)
//#else
//    #define DLL_EXPORT __declspec(dllimport)
//#endif // defined MAKEDLL
//#else
//    #define DLL_EXPORT
//#endif // defined _WIN32

class Recorder {
public:
  Recorder();
  Recorder(double value);
  void operator<<=(double value);
  void operator>>=(double& value);
  explicit operator bool() const;
  friend
    std::ostream& operator<<(std::ostream &stream, const Recorder& obj);
  static void start_recording();
  static void stop_recording();

  /* Assignments */
  double getValue() const;
  inline double value() const {return getValue();}
  Recorder& operator = ( double arg) { return operator=(Recorder(arg)); }
  //Recorder& operator = ( const Recorder& );

  /* IO friends */
  friend  std::istream& operator >> (std::istream& is, const Recorder& a);

  /* Operation + Assignment */
  inline Recorder& operator += ( double value ) { return operator+=(Recorder(value)); }
  inline Recorder& operator += ( const Recorder& value) { return operator=(*this+value); }
  inline Recorder& operator -= ( double value ) { return operator-=(Recorder(value)); }
  inline Recorder& operator -= ( const Recorder& value) { return operator=(*this-value); }
  inline Recorder& operator *= ( double value)  { return operator*=(Recorder(value)); }
  inline Recorder& operator *= ( const Recorder& value) { return operator=(*this*value); }
  inline Recorder& operator /= ( double value)  { return operator/=(Recorder(value)); }
  inline Recorder& operator /= ( const Recorder& value) { return operator=(*this/value); }

  /* Comparison (friends) */
  friend     bool operator != ( const Recorder&, const Recorder& );
  friend     bool operator == ( const Recorder&, const Recorder& );
  friend     bool operator <= ( const Recorder&, const Recorder& );
  friend     bool operator >= ( const Recorder&, const Recorder& );
  friend     bool operator >  ( const Recorder&, const Recorder& );
  friend     bool operator <  ( const Recorder&, const Recorder& );
  inline friend    bool operator != ( double lhs, const Recorder& rhs) { return Recorder(lhs)!=rhs; }
  inline friend    bool operator == ( double lhs, const Recorder& rhs) { return Recorder(lhs)==rhs; }
  inline friend    bool operator <= ( double lhs, const Recorder& rhs) { return Recorder(lhs)<=rhs; }
  inline friend    bool operator >= ( double lhs, const Recorder& rhs) { return Recorder(lhs)>=rhs; }
  inline friend    bool operator >  ( double lhs, const Recorder& rhs) { return Recorder(lhs)>rhs; }
  inline friend    bool operator <  ( double lhs, const Recorder& rhs) { return Recorder(lhs)<rhs; }

  /* sign operators (friends) */
  inline friend Recorder operator + ( const Recorder& x ) { return x; }
  friend Recorder operator - ( const Recorder& x );

  /* binary operators (friends) */
  friend Recorder operator + ( const Recorder&, const Recorder& );
  inline friend Recorder operator + ( double lhs, const Recorder& rhs) { return Recorder(lhs)+rhs; }
  inline friend Recorder operator + ( const Recorder& lhs, double rhs)  { return lhs+Recorder(rhs); }
  friend Recorder operator - ( const Recorder&, const Recorder& );
  inline friend Recorder operator - ( const Recorder& lhs, double rhs ) { return lhs-Recorder(rhs); }
  inline friend Recorder operator - ( double lhs, const Recorder& rhs )  { return Recorder(lhs)-rhs; }
  friend Recorder operator * ( const Recorder&, const Recorder& );
  inline friend Recorder operator * ( double lhs, const Recorder& rhs)  { return Recorder(lhs)*rhs; }
  inline friend Recorder operator * ( const Recorder& lhs, double rhs) { return lhs*Recorder(rhs); }
  inline friend Recorder operator / ( const Recorder& lhs, double rhs) { return lhs/Recorder(rhs); }
  friend Recorder operator / ( const Recorder&, const Recorder& );
  friend Recorder operator / ( double lhs, const Recorder& rhs )  { return Recorder(lhs)/rhs; }

  /* unary operators (friends) */
  friend Recorder exp  ( const Recorder& );
  friend Recorder log  ( const Recorder& );
  friend Recorder sqrt ( const Recorder& );
  friend Recorder sin  ( const Recorder& );
  friend Recorder cos  ( const Recorder& );
  friend Recorder tan  ( const Recorder& );
  friend Recorder asin ( const Recorder& );
  friend Recorder acos ( const Recorder& );
  friend Recorder atan ( const Recorder& );

  /* special operators (friends) */
  /* no internal use of condassign: */
  inline friend Recorder    pow   ( const Recorder& lhs, double rhs) { return pow(lhs, Recorder(rhs)); }
  friend Recorder    log10 ( const Recorder& );

  /* Additional ANSI C standard Math functions Added by DWJ on 8/6/90 */
  friend Recorder sinh  ( const Recorder& );
  friend Recorder cosh  ( const Recorder& );
  friend Recorder tanh  ( const Recorder& );
  friend Recorder asinh ( const Recorder& );
  friend Recorder acosh ( const Recorder& );
  friend Recorder atanh ( const Recorder& );
  friend Recorder erf   ( const Recorder& );
  friend Recorder fabs  ( const Recorder& );
  friend Recorder ceil  ( const Recorder& );
  friend Recorder floor ( const Recorder& );
  friend Recorder fmax ( const Recorder&, const Recorder& );
  inline friend Recorder fmax ( double lhs, const Recorder& rhs) { return fmax(Recorder(lhs), rhs); }
  inline friend Recorder fmax ( const Recorder& lhs, double rhs) { return fmax(lhs, Recorder(rhs)); }
  friend Recorder fmin ( const Recorder&, const Recorder& );
  inline friend Recorder fmin ( double lhs, const Recorder& rhs) { return fmin(Recorder(lhs), rhs); }
  inline friend Recorder fmin ( const Recorder& lhs, double rhs) { return fmin(lhs, Recorder(rhs)); }

  friend Recorder ldexp ( const Recorder&, int );
  friend Recorder frexp ( const Recorder&, int* );
  /* special operators (friends) */
  friend Recorder atan2 ( const Recorder&, const Recorder& );
  /* uses condassign internally */
  friend Recorder pow   ( const Recorder&, const Recorder& );
  inline friend Recorder pow   ( double lhs, const Recorder& rhs) { return pow(Recorder(lhs), rhs); }
  /* User defined version of logarithm to test extend_quad macro */
  friend Recorder myquad( const Recorder& );

protected:
  void disp(std::ostream &stream) const;
  static double get_id();
  bool is_symbol() const;
  std::string repr() const;
  static Recorder from_binary(const Recorder& lhs, const Recorder& rhs, double res, const std::string& op);
  static Recorder from_unary(const Recorder& arg, double res, const std::string& op);

  static std::ofstream& stream();
  explicit Recorder(double value, int id);
  double value_;
  int id_;

  static int counter;
  static int counter_input;
  static int counter_output;
  static std::ofstream* stream_;
};

#endif
