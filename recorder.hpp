
#include <iostream>


class Recorder {
public:
  Recorder();
  Recorder(double value);
  void operator<<=(double value);
  void operator>>=(double& value);
  Recorder operator+(const Recorder& rhs) const;
  Recorder operator*(const Recorder& rhs) const;
  Recorder operator>=(const Recorder& rhs) const;
  explicit operator bool() const;
  inline friend
    std::ostream& operator<<(std::ostream &stream, const Recorder& obj);
  static void start_recording();
  static void stop_recording();
  
  /* Assignments */
  double getValue() const;
  inline double value() const;
  Recorder& operator = ( double );
  Recorder& operator = ( const Recorder& );
  
  /* IO friends */
  inline friend 
    std::istream& operator >> (std::istream& is, const Recorder& a);
	
  /* Operation + Assignment */
  Recorder& operator += ( double );
  Recorder& operator += ( const Recorder& );
  Recorder& operator -= ( double y );
  Recorder& operator -= ( const Recorder& );
  Recorder& operator *= ( double );
  Recorder& operator *= ( const Recorder& );
  Recorder& operator /= ( double );
  Recorder& operator /= ( const Recorder& );
  
  /* Comparison (friends) */
  friend 
    Recorder operator != ( const Recorder&, const Recorder& );
  friend 
    Recorder operator == ( const Recorder&, const Recorder& );
  friend 
    Recorder operator <= ( const Recorder&, const Recorder& );
  friend 
    Recorder operator >= ( const Recorder&, const Recorder& );
  friend 
    Recorder operator >  ( const Recorder&, const Recorder& );
  friend 
    Recorder operator <  ( const Recorder&, const Recorder& );
  inline friend 
    Recorder operator != (double lhs, const Recorder& rhs) { return Recorder(lhs)!=rhs; }
  inline friend 
    Recorder operator == ( double lhs, const Recorder& rhs) { return Recorder(lhs)==rhs; }
  inline friend 
    Recorder operator <= ( double lhs, const Recorder& rhs) { return Recorder(lhs)<=rhs; }
  inline friend 
    Recorder operator >= ( double lhs, const Recorder& rhs) { return Recorder(lhs)>=rhs; }
  inline friend 
    Recorder operator >  ( double lhs, const Recorder& rhs) { return Recorder(lhs)>rhs; }
  inline friend 
    Recorder operator <  ( double lhs, const Recorder& rhs) { return Recorder(lhs)<rhs; }
	
  /* sign operators (friends) */
  inline friend Recorder operator + ( const Recorder& x ) { return x; }
  friend Recorder operator - ( const Recorder& x );
  
  /* binary operators (friends) */
  friend Recorder operator + ( const Recorder&, const Recorder& );
  inline friend Recorder operator + ( double lhs, const Recorder& rhs) { return Recorder(lhs)+rhs; }
  inline friend Recorder operator + ( const Recorder& lhs, double rhs)  { return lhs+Recorder(rhs); }
  friend Recorder operator - ( const Recorder&, const Recorder& );
  inline friend Recorder operator - ( const Recorder&, double ) { return lhs-Recorder(rhs); }
  inline friend Recorder operator - ( double, const Recorder& )  { return Recorder(lhs)-rhs; }
  friend Recorder operator * ( const Recorder&, const Recorder& );
  inline friend Recorder operator * ( double lhs, const Recorder& rhs)  { return Recorder(lhs)*rhs; }
  inline friend Recorder operator * ( const Recorder& lhs, double rhs) { return lhs*Recorder(rhs); }
  inline friend Recorder operator / ( const Recorder& lhs, double rhs) { return lhs/Recorder(rhs); }
  friend Recorder operator / ( const Recorder&, const Recorder& );
  friend Recorder operator / ( double, const Recorder& )  { return Recorder(lhs)/rhs; }
	
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
  friend Recorder    pow   ( const Recorder&, double );
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
  friend Recorder fmax ( double, const Recorder& );
  friend Recorder fmax ( const Recorder&, double );
  friend Recorder fmin ( const Recorder&, const Recorder& );
  friend Recorder fmin ( double, const Recorder& );
  friend Recorder fmin ( const Recorder&, double );

  friend Recorder ldexp ( const Recorder&, int );
  friend Recorder frexp ( const Recorder&, int* );
  /* special operators (friends) */
  friend Recorder atan2 ( const Recorder&, const Recorder& );
  /* uses condassign internally */
  friend Recorder pow   ( const Recorder&, const Recorder& );
  friend Recorder pow   ( double, const Recorder& );
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
