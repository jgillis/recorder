

#include <iostream>
#include <fstream>
#include <ctime>

using namespace casadi;
using namespace std;

class Recorder {
public:
  Recorder() : id_(counter++) {}
  Recorder(double value) : id_(-1), value_(value) {}
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
  inline friend 
    int operator != ( const Recorder&, const Recorder& );
  inline friend 
    int operator == ( const Recorder&, const Recorder& );
  inline friend 
    int operator <= ( const Recorder&, const Recorder& );
  inline friend 
    int operator >= ( const Recorder&, const Recorder& );
  inline friend 
    int operator >  ( const Recorder&, const Recorder& );
  inline friend 
    int operator <  ( const Recorder&, const Recorder& );
  inline friend 
    int operator != (double, const Recorder& rhs);
  inline friend 
    int operator == ( double, const Recorder& rhs);
  inline friend 
    int operator <= ( double, const Recorder& rhs);
  inline friend 
    int operator >= ( double, const Recorder& rhs);
  inline friend 
    int operator >  ( double, const Recorder& rhs);
  inline friend 
    int operator <  ( double, const Recorder& rhs);
	
  /* sign operators (friends) */
  friend Recorder operator + ( const Recorder& x );
  friend Recorder operator - ( const Recorder& x );
  
  /* binary operators (friends) */
    friend Recorder operator + ( const Recorder&, const Recorder& );
    friend Recorder operator + ( double, const Recorder& );
    friend Recorder operator + ( const Recorder&, double );
    friend Recorder operator - ( const Recorder&, const Recorder& );
    inline friend Recorder operator - ( const Recorder&, double );
    friend Recorder operator - ( double, const Recorder& );
    friend Recorder operator * ( const Recorder&, const Recorder& );
    friend Recorder operator * ( double, const Recorder& );
    inline friend Recorder operator * ( const Recorder&, double );
    inline friend Recorder operator / ( const Recorder&, double );
    friend Recorder operator / ( const Recorder&, const Recorder& );
    friend Recorder operator / ( double, const Recorder& );
	
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
	
  
   
protected:
  void disp(std::ostream &stream) const;
  static double get_id();
  bool is_symbol() const;
  std::string repr() const;
  static Recorder from_binary(const Recorder& lhs, const Recorder& rhs, double res, const std::string& op);

  static std::ofstream& stream();
  explicit Recorder(double value, int id);
  double value_;
  int id_;

  static int counter;
  static int counter_input;
  static int counter_output;
  static std::ofstream* stream_;
};