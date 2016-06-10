#include "gl2d/include/radians.h"

#include <cmath>

namespace gl2d {

Radians::Radians(double radians) : radians_(radians) {}

Radians& Radians::Normalize() {
  const double twopi = Radians::TWOPI.radians_;

  while (util::cmpD(radians_, -twopi) < 0) radians_ += twopi;
  while (util::cmpD(radians_,  twopi) > 0) radians_ -= twopi;

  return *this;
}

Radians& Radians::operator*=(double k) {
  radians_ *= k;
  return *this;
}

Radians& Radians::operator+=(double k) {
  radians_ += k;
  return *this;
}

Radians& Radians::operator-=(double k) {
  radians_ -= k;
  return *this;
}

Radians& Radians::operator/=(double k) {
  radians_ /= k;
  return *this;
}

Radians& Radians::operator*=(const Radians& r) {
  radians_ *= r.radians_;
  return *this;
}

Radians& Radians::operator+=(const Radians& r) {
  radians_ += r.radians_;
  return *this;
}

Radians& Radians::operator-=(const Radians& r) {
  radians_ -= r.radians_;
  return *this;
}

Radians& Radians::operator/=(const Radians& r) {
  radians_ /= r.radians_;
  return *this;
}

Radians operator*(const Radians& r1, const Radians& r2) {
  Radians t = r1;
  t *= r2;
  return t;
}

Radians operator*(const Radians& radians, double k) {
  Radians t = radians;
  t *= k;
  return t;
}

Radians operator*(double k, const Radians& radians) {
  Radians t = radians;
  t *= k;
  return t;
}

Radians operator+(const Radians& r1, const Radians& r2) {
  Radians t = r1;
  t += r2;
  return t;
}

Radians operator+(const Radians& radians) {
  return radians;
}

Radians operator+(const Radians& radians, double k) {
  Radians t = radians;
  t += k;
  return t;
}

Radians operator+(double k, const Radians& radians) {
  Radians t = radians;
  t += k;
  return t;
}

Radians operator-(const Radians& r1, const Radians& r2) {
  Radians t = r1;
  t -= r2;
  return t;
}

Radians operator-(const Radians& radians) {
  Radians t = radians;
  t.radians_ = -t.radians_;
  return t;
}

Radians operator-(const Radians& radians, double k) {
  Radians t = radians;
  t -= k;
  return t;
}

Radians operator-(double k, const Radians& radians) {
  Radians t = -radians;
  t += k;
  return t;
}

Radians operator/(const Radians& r1, const Radians& r2) {
  Radians t = r1;
  t /= r2;
  return t;
}

Radians operator/(const Radians& radians, double k) {
  Radians t = radians;
  t /= k;
  return t;
}

Radians operator/(double k, const Radians& radians) {
  Radians t(k);
  t /= radians;
  return t;
}

Radians& Radians::operator=(double k) {
  radians_ = k;
  return *this;
}

bool Radians::operator==(const Radians& radians) const {
  return util::cmpD(radians_, radians.radians_) == 0;
}

bool Radians::operator!=(const Radians& radians) const {
  return !(*this == radians);
}

double Radians::Cos(const Radians& radians) {
  return cos(radians.radians_);
}

double Radians::Sin(const Radians& radians) {
  return sin(radians.radians_);
}

Radians Radians::Acos(double value) {
  Radians rad(acos(value));
  if (util::cmpD(rad.radians_, 0) < 0)
    rad += TWOPI;
  return rad;
}

Radians Radians::Asin(double value) {
  Radians rad(asin(value));
  if (util::cmpD(rad.radians_, 0) < 0)
    rad += TWOPI;
  return rad;
}

const Radians Radians::PI(3.14159265358979323846264338327950288419716939937510);
const Radians Radians::TWOPI(2 * Radians::PI);

}  // namespace gl2d
