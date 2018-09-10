
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
