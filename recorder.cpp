

#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <stdexcept>
#include <iomanip>
#include "recorder.hpp"


Recorder::Recorder() : id_(counter++) {}
Recorder::Recorder(double value) : id_(-1), value_(value) {}
void Recorder::operator<<=(double value) {
  if (!is_symbol()) throw std::runtime_error("Needs to be symbolic");
  stream() << "if nom" << std::endl;
  stream() << "  " << repr() << " = " << value << ";" << std::endl;
  stream() << "else" << std::endl;
  stream() << "  " << repr() << " = x(" << counter_input+1 << ");" << std::endl;
  stream() << "end" << std::endl;
  counter_input++;
  value_ = value;
}
void Recorder::operator>>=(double& value) {
  if (!is_symbol()) throw std::runtime_error("Needs to be symbolic");
  stream() << "if ~nom" << std::endl;
  stream() << "y{" << counter_output+1 << "} = " << repr() << ";"  << std::endl;
  stream() << "end" << std::endl;    
  counter_output++;
  value = value_;
}
Recorder Recorder::operator+(const Recorder& rhs) const {
  return from_binary(*this, rhs, value_ + rhs.value_, "plus");
}
Recorder Recorder::operator*(const Recorder& rhs) const {
  return from_binary(*this, rhs, value_ * rhs.value_, "times");
}
Recorder Recorder::operator>=(const Recorder& rhs) const {
  return from_binary(*this, rhs, value_ >= rhs.value_, "ge");
}
Recorder Recorder::operator<=(const Recorder& rhs) const {
  return from_binary(*this, rhs, value_ <= rhs.value_, "le");
}
Recorder Recorder::operator>(const Recorder& rhs) const {
  return from_binary(*this, rhs, value_ > rhs.value_, "gt");
}
Recorder Recorder::operator<(const Recorder& rhs) const {
  return from_binary(*this, rhs, value_ < rhs.value_, "lt");
}
Recorder Recorder::operator!=(const Recorder& rhs) const {
  return from_binary(*this, rhs, value_ != rhs.value_, "ne");
}
Recorder Recorder::operator==(const Recorder& rhs) const {
  return from_binary(*this, rhs, value_ == rhs.value_, "eq");
}




Recorder::operator bool() const {
  stream() << "if ~nom" << std::endl;
  stream() << "assert(" << repr() << "==" << value_ << ", 'branch error');" << std::endl;
  bool ret = value_;
  stream() << "end" << std::endl;
  return ret;
}
inline std::ostream& operator<<(std::ostream &stream, const Recorder& obj) {
  obj.disp(stream);
  return stream;
}
void Recorder::start_recording() {
  stream_ = new std::ofstream("foo.m");
  stream() << std::setprecision(16);
  stream() << "function y=foo(x)" << std::endl;
  stream() << "nom = nargin==0;" << std::endl;
  counter = 0;
}
void Recorder::stop_recording() {
  stream() << "if ~nom, y = vertcat(y{:}); end;" << std::endl;
  delete stream_;
  stream_ = nullptr;
}
void Recorder::disp(std::ostream &stream) const {
  if (is_symbol()) {
    stream << "[#" << id_ << "|" << value_ << "]";
  } else {
    stream << "(" << value_ << ")";
  }
}
double Recorder::get_id() {
  counter++;
  return counter;
}
bool Recorder::is_symbol() const {
  return id_>=0;
}
std::string Recorder::repr() const {
  if (is_symbol()) {
    return "a" + std::to_string(id_);
  } else {
    std::stringstream ss;
    ss << std::setprecision(16);
    ss << value_;
    return ss.str();
  }
}
Recorder Recorder::from_binary(const Recorder& lhs, const Recorder& rhs, double res, const std::string& op) {
  if (lhs.is_symbol() || rhs.is_symbol()) {
    int id = get_id();
    stream() << "a" << id << " = " << op << "(" << lhs.repr() <<  "," <<   rhs.repr() << ");" << std::endl;
    stream() << "if nom, assert(" << "a" << id << "==" << res << "); end;" << std::endl;
    return Recorder(res, id);
  } else {
    return Recorder(res);
  }
}
Recorder Recorder::from_unary(const Recorder& arg, double res, const std::string& op) {
  if (arg.is_symbol()) {
    int id = get_id();
    stream() << "a" << id << " = " << op << "(" << arg.repr());" << std::endl;
    stream() << "if nom, assert(" << "a" << id << "==" << res << "); end;" << std::endl;
    return Recorder(res, id);
  } else {
    return Recorder(res);
  }
}
std::ofstream& Recorder::stream() {
  if (stream_==nullptr) throw std::runtime_error("Stream is not opened");
  return *stream_;
};
Recorder::Recorder(double value, int id) {
  id_ = id;
  value_ = value;
}

int Recorder::counter = 0;
int Recorder::counter_input = 0;
int Recorder::counter_output = 0;
std::ofstream* Recorder::stream_ = nullptr;

