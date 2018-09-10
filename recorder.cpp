

#include <iostream>
#include <fstream>
#include <ctime>

using namespace casadi;
using namespace std;

class Recorder {
public:
  Recorder() : id_(counter++) {}
  Recorder(double value) : id_(-1), value_(value) {}
  void operator<<=(double value) {
    if (!is_symbol()) throw runtime_error("Needs to be symbolic");
    stream() << "if nom" << std::endl;
    stream() << "  " << repr() << " = " << value << ";" << std::endl;
    stream() << "else" << std::endl;
    stream() << "  " << repr() << " = x(" << counter_input+1 << ");" << std::endl;
    stream() << "end" << std::endl;
    counter_input++;
    value_ = value;
  }
  void operator>>=(double& value) {
    if (!is_symbol()) throw runtime_error("Needs to be symbolic");
    stream() << "if ~nom" << std::endl;
    stream() << "y{" << counter_output+1 << "} = " << repr() << ";"  << std::endl;
    stream() << "end" << std::endl;    
    counter_output++;
    value = value_;
  }
  Recorder operator+(const Recorder& rhs) const {
    return from_binary(*this, rhs, value_ + rhs.value_, "plus");
  }
  Recorder operator*(const Recorder& rhs) const {
    return from_binary(*this, rhs, value_ * rhs.value_, "times");
  }
  Recorder operator>=(const Recorder& rhs) const {
    return from_binary(*this, rhs, value_ >= rhs.value_, "ge");
  }
  explicit operator bool() const {
    stream() << "if ~nom" << std::endl;
    stream() << "assert(" << repr() << "==" << value_ << ", 'branch error');" << std::endl;
    bool ret = value_;
    stream() << "end" << std::endl;    
  }
  inline friend
    std::ostream& operator<<(std::ostream &stream, const Recorder& obj) {
    obj.disp(stream);
    return stream;
  }
  static void start_recording() {
    stream_ = new ofstream("foo.m");
    stream() << std::setprecision(16);
    stream() << "function y=foo(x)" << std::endl;
    stream() << "nom = nargin==0;" << std::endl;
    counter = 0;
  }
  static void stop_recording() {
    stream() << "if ~nom, y = vertcat(y{:}); end;" << std::endl;
    delete stream_;
    stream_ = nullptr;
  }
protected:
  void disp(std::ostream &stream) const {
    if (is_symbol()) {
      stream << "[#" << id_ << "|" << value_ << "]";
    } else {
      stream << "(" << value_ << ")";
    }
  }
  static double get_id() {
    counter++;
    return counter;
  }
  bool is_symbol() const {
    return id_>=0;
  }
  std::string repr() const {
    if (is_symbol()) {
      return "a" + str(id_);
    } else {
      std::stringstream ss;
      ss << std::setprecision(16);
      ss << value_;
      return ss.str();
    }
  }
  static Recorder from_binary(const Recorder& lhs, const Recorder& rhs, double res, const std::string& op) {
    if (lhs.is_symbol() || rhs.is_symbol()) {
      int id = get_id();
      stream() << "a" << id << " = " << op << "(" << lhs.repr() <<  "," <<   rhs.repr() << ");" << std::endl;
      stream() << "if nom, assert(" << "a" << id << "==" << res << "); end;" << std::endl;
      return Recorder(res, id);
    } else {
      return Recorder(res);
    }
  }

  static std::ofstream& stream() {
    if (stream_==nullptr) throw runtime_error("Stream is not opened");
    return *stream_;
  };
  explicit Recorder(double value, int id) {
    id_ = id;
    value_ = value;
  }
  double value_;
  int id_;

  static int counter;
  static int counter_input;
  static int counter_output;
  static std::ofstream* stream_;
};


int Recorder::counter = 0;
int Recorder::counter_input = 0;
int Recorder::counter_output = 0;
std::ofstream* Recorder::stream_ = nullptr;

