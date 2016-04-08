#include "gl2d/include/vector.h"

#include <cmath>

#include "gl2d/include/point.h"
#include "gl2d/include/util.h"

namespace gl2d {

Vector::Vector(double x, double y) : dest_(x, y) {}
Vector::Vector(const ::gl2d::Point& dest) : dest_(dest) {}
Vector::Vector(const ::gl2d::Point& orig, const ::gl2d::Point& dest) :
    dest_(dest - orig) {}

const ::gl2d::Point& Vector::Point() const {
    return dest_;
}

void Vector::Point(const ::gl2d::Point& dest) {
    dest_ = dest;
}

double Vector::x() const {
    return dest_.x();
}

void Vector::x(double x) {
    dest_.x(x);
}

void Vector::y(double y) {
    dest_.y(y);
}

double Vector::y() const {
    return dest_.y();
}

double Vector::Magnitude() const {
  return sqrt(dest_.x() * dest_.x() + dest_.y() * dest_.y());
}

Vector& Vector::Normalize() {
  *this /= Magnitude();
  return *this;
}

Radians Vector::Angle() const {
  Radians angle(acos(dest_.x() / Magnitude()));
  if (util::cmpD(dest_.y(), 0) < 0)
    angle = 2 * Radians::PI - angle;
  return angle;
}

Vector& Vector::Rotate(const Radians& angle) {
  double x = dest_.x() * cos(angle) - dest_.y() * sin(angle);
  double y = dest_.x() * sin(angle) + dest_.y() * cos(angle);
  dest_.x(x);
  dest_.y(y);
  return *this;
}

Vector& Vector::operator+=(const Vector& v) {
  dest_ += v.Point();
  return *this;
}

Vector& Vector::operator-=(const Vector& v) {
  dest_ -= v.Point();
  return *this;
}

Vector& Vector::operator*=(double k) {
  dest_ *= k;
  return *this;
}

Vector& Vector::operator/=(double k) {
  dest_ /= k;
  return *this;
}

Vector operator+(const Vector& v, const Vector& w) {
  Vector t = v;
  t += w;
  return t;
}

Vector operator-(const Vector& v, const Vector& w) {
  Vector t = v;
  t -= w;
  return t;
}

Vector operator-(const Vector& v) {
  return Vector(-v.Point());
}

Vector operator*(const Vector& v, double k) {
  Vector t = v;
  t *= k;
  return t;
}

Vector operator*(double k, const Vector& v) {
  Vector t = v;
  t *= k;
  return t;
}

Vector operator/(const Vector& v, double k) {
  Vector t = v;
  t /= k;
  return t;
}

bool Vector::operator==(const Vector& v) const {
  return dest_ == v.Point();
}

bool Vector::operator!=(const Vector& v) const {
  return !(*this == v);
}

const Vector Vector::i = Vector(1, 0);
const Vector Vector::j = Vector(0, 1);

}  // namespace gl2d

