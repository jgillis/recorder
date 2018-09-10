

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

double Recorder::getValue() const {return value_;}

Recorder operator+(const Recorder& lhs, const Recorder& rhs) {
  return Recorder::from_binary(lhs, rhs, lhs.value_ + rhs.value_, "plus");
}
Recorder operator*(const Recorder& lhs, const Recorder& rhs) {
  return Recorder::from_binary(lhs, rhs, lhs.value_ * rhs.value_, "times");
}
Recorder operator-(const Recorder& lhs, const Recorder& rhs) {
  return Recorder::from_binary(lhs, rhs, lhs.value_ - rhs.value_, "minus");
}
Recorder operator/(const Recorder& lhs, const Recorder& rhs) {
  return Recorder::from_binary(lhs, rhs, lhs.value_ / rhs.value_, "ldivide");
}
bool operator>=(const Recorder& lhs, const Recorder& rhs) {
  return static_cast<bool>(Recorder::from_binary(lhs, rhs, lhs.value_ >= rhs.value_, "ge"));
}
Recorder operator<=(const Recorder& lhs, const Recorder& rhs) {
  return Recorder::from_binary(lhs, rhs, lhs.value_ <= rhs.value_, "le");
}
Recorder operator>(const Recorder& lhs, const Recorder& rhs) {
  return Recorder::from_binary(lhs, rhs, lhs.value_ > rhs.value_, "gt");
}
Recorder operator<(const Recorder& lhs, const Recorder& rhs) {
  return Recorder::from_binary(lhs, rhs, lhs.value_ < rhs.value_, "lt");
}
Recorder operator!=(const Recorder& lhs, const Recorder& rhs) {
  return Recorder::from_binary(lhs, rhs, lhs.value_ != rhs.value_, "ne");
}
Recorder operator==(const Recorder& lhs, const Recorder& rhs) {
  return Recorder::from_binary(lhs, rhs, lhs.value_ == rhs.value_, "eq");
}

Recorder operator-(const Recorder& arg) {
    return Recorder::from_unary(arg, -arg.value_, "uminus");
}

Recorder pow( const Recorder&lhs, const Recorder& rhs) {
    Recorder::from_binary(lhs, rhs, pow(lhs.value_,rhs.value_), "power");
}

Recorder fmax ( const Recorder&lhs, const Recorder& rhs) {
  Recorder::from_binary(lhs, rhs, fmax(lhs.value_,rhs.value_), "fmax");
}
Recorder fmin ( const Recorder&lhs, const Recorder& rhs) {
  Recorder::from_binary(lhs, rhs, fmin(lhs.value_,rhs.value_), "fmin");
}
Recorder atan2 ( const Recorder&lhs, const Recorder& rhs) {
  Recorder::from_binary(lhs, rhs, atan2(lhs.value_,rhs.value_), "atan2");
}

Recorder exp(const Recorder& arg) {
    return Recorder::from_unary(arg, exp(arg.value_), "exp");
}
Recorder log(const Recorder& arg) {
    return Recorder::from_unary(arg, log(arg.value_), "log");
}
Recorder sqrt(const Recorder& arg) {
    return Recorder::from_unary(arg, sqrt(arg.value_), "sqrt");
}
Recorder sin(const Recorder& arg) {
    return Recorder::from_unary(arg, sin(arg.value_), "sin");
}
Recorder cos(const Recorder& arg) {
    return Recorder::from_unary(arg, cos(arg.value_), "cos");
}
Recorder tan(const Recorder& arg) {
    return Recorder::from_unary(arg, tan(arg.value_), "tan");
}
Recorder asin(const Recorder& arg) {
    return Recorder::from_unary(arg, asin(arg.value_), "asin");
}
Recorder acos(const Recorder& arg) {
    return Recorder::from_unary(arg, acos(arg.value_), "acos");
}
Recorder atan(const Recorder& arg) {
    return Recorder::from_unary(arg, atan(arg.value_), "atan");
}

Recorder log10(const Recorder& arg) {
    return Recorder::from_unary(arg, log10(arg.value_), "log10");
}
Recorder sinh(const Recorder& arg) {
    return Recorder::from_unary(arg, sinh(arg.value_), "sinh");
}
Recorder cosh(const Recorder& arg) {
    return Recorder::from_unary(arg, cosh(arg.value_), "cosh");
}
Recorder tanh(const Recorder& arg) {
    return Recorder::from_unary(arg, tanh(arg.value_), "tanh");
}
Recorder asinh(const Recorder& arg) {
    return Recorder::from_unary(arg, asinh(arg.value_), "asinh");
}
Recorder acosh(const Recorder& arg) {
    return Recorder::from_unary(arg, acosh(arg.value_), "acosh");
}
Recorder atanh(const Recorder& arg) {
    return Recorder::from_unary(arg, atanh(arg.value_), "atanh");
}
Recorder erf(const Recorder& arg) {
    return Recorder::from_unary(arg, erf(arg.value_), "erf");
}
Recorder fabs(const Recorder& arg) {
    return Recorder::from_unary(arg, fabs(arg.value_), "fabs");
}
Recorder ceil(const Recorder& arg) {
    return Recorder::from_unary(arg, ceil(arg.value_), "ceil");
}
Recorder floor(const Recorder& arg) {
    return Recorder::from_unary(arg, floor(arg.value_), "floor");
}

Recorder::operator bool() const {
  stream() << "if ~nom" << std::endl;
  stream() << "assert(" << repr() << "==" << value_ << ", 'branch error');" << std::endl;
  bool ret = value_;
  stream() << "end" << std::endl;
  return ret;
}
std::ostream& operator<<(std::ostream &stream, const Recorder& obj) {
  obj.disp(stream);
  return stream;
}

std::istream& operator >> (std::istream& is, const Recorder& a) {
  throw std::runtime_error("No way!");
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
    stream() << "a" << id << " = " << op << "(" << arg.repr() << std::endl;
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

