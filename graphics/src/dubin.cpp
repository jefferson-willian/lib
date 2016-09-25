#include "graphics/include/dubin.h"

#include "gl2d/include/circle.h"
#include "gl2d/include/line_segment.h"
#include "gl2d/include/point.h"
#include "gl2d/include/arc.h"
#include "gl2d/include/radians.h"
#include "gl2d/include/distance.h"
#include "gl2d/include/vector.h"
#include "gl2d/include/tangent.h"

#include <vector>

namespace dubin {

namespace {

std::pair<gl2d::Circle, gl2d::Circle> TangentCircles(const gl2d::Point& orig,
    gl2d::Vector dir, double radius) {
  dir.Normalize();
  dir *= radius;

  dir.Rotate(gl2d::Radians::PI / 2);
  gl2d::Circle c1(orig + dir.Point(), radius);

  dir.Rotate(-gl2d::Radians::PI);
  gl2d::Circle c2(orig + dir.Point(), radius);

  return {c1, c2};
}

gl2d::Arc GetArc(const gl2d::Circle& c, const gl2d::Point& p1, const gl2d::Point& p2) {
  return gl2d::Arc(c, gl2d::Vector(c.Center(), p1).Angle(),
      gl2d::Vector(c.Center(), p2).Angle());
}

gl2d::Point GetPoint(const gl2d::Circle& c, const gl2d::Point& p) {
  gl2d::Vector v(c.Center(), p);
  v.Normalize();
  v *= c.Radius();

  return v.Point() + c.Center();
}

}  // namespace

std::vector<Path> Path::GetAllPaths(const gl2d::Point& a, const gl2d::Vector& d1,
    const gl2d::Point& b, const gl2d::Vector& d2, double curvature) {
  std::vector<Path> paths;

  if (a == b && d1 == d2)
    return paths;

  auto ca = TangentCircles(a, d1, curvature);
  auto cb = TangentCircles(b, d2, curvature);

  std::vector<gl2d::LineSegment> lines;

  // Curves permutation. RR, LL, RR, RL, LR.
  int ca_i[] = {1, 0, 1, 0};
  int cb_i[] = {1, 0, 0, 1};

  // Get CSC.
  for (int i = 0; i < 4; ++i) {
    const gl2d::Circle& cai = ca_i[i] == 0 ? ca.first : ca.second;
    const gl2d::Circle& cbi = cb_i[i] == 0 ? cb.first : cb.second;

    lines = gl2d::Tangent(cai, cbi);

    if (lines.size() > i) {
      const gl2d::LineSegment& line = gl2d::LineSegment(lines[i]);

      const gl2d::Point& p1 = ca_i[i] == 0 ? a : line.a();
      const gl2d::Point& p2 = ca_i[i] == 0 ? line.a() : a;
      const gl2d::Point& p3 = cb_i[i] == 0 ? line.b() : b;
      const gl2d::Point& p4 = cb_i[i] == 0 ? b : line.b();

      Path p;
      p.line_segment_ = line;
      p.out_ = gl2d::Arc(cai, p1, p2);
      p.in_  = gl2d::Arc(cbi, p3, p4);
      p.is_csc_ = true;

      paths.emplace_back(p);
    }
  }

  for (int i = 0; i < 2; ++i) {
    auto c1 = i == 0 ? ca.first : ca.second;
    auto c2 = i == 0 ? cb.first : cb.second;

    if (c1 == c2)
      continue;

    double dist = gl2d::Distance(c1.Center(), c2.Center());

    if (gl2d::util::cmpD(dist, c1.Radius() * 4) > 0)
      continue;

    gl2d::Vector v(c1.Center(), c2.Center());
    v.Magnitude(2 * c1.Radius());
    auto rotation = gl2d::Radians::Acos((dist / 2) / v.Magnitude());
    v.Rotate(i == 0 ? rotation : -rotation);

    gl2d::Circle c3(c1.Center() + v.Point(), c1.Radius());

    gl2d::Arc rad1 = i == 0 ? gl2d::Arc(c1, a, c3.Center()) : gl2d::Arc(c1, c3.Center(), a);
    gl2d::Arc rad2 = i == 0 ? gl2d::Arc(c3, c2.Center(), c1.Center()) : gl2d::Arc(c3, c1.Center(), c2.Center());
    gl2d::Arc rad3 = i == 0 ? gl2d::Arc(c2, c3.Center(), b) : gl2d::Arc(c2, b, c3.Center());

    Path p_;
    p_.out_ = rad1;
    p_.in_ = rad3;
    p_.mid_circle_ = rad2;
    p_.is_csc_ = false;

    paths.emplace_back(p_);
  }

  return paths;
}

Path* Path::ShortestPath(const gl2d::Point& a, const gl2d::Vector& d1,
    const gl2d::Point& b, const gl2d::Vector& d2, double curvature) {
  const std::vector<Path>& paths = GetAllPaths(a, d1, b, d2, curvature);

  if (paths.empty())
    return nullptr;

  int id = 0;
  double best = paths[0].Length();
  for (int i = 1; i < paths.size(); ++i) {
    const Path& path = paths[i];
    if (gl2d::util::cmpD(path.Length(), best) < 0) {
      id = i;
      best = path.Length();
    }
  }

  return new Path(paths[id]);
}

}  // namespace dubin