#ifndef GL2D_INCLUDE_TANGENT_H_
#define GL2D_INCLUDE_TANGENT_H_

#include <vector>

#include "gl2d/circle.h"
#include "gl2d/line_segment.h"
#include "gl2d/point.h"

namespace gl2d {

std::vector<LineSegment> Tangent(const Point& p, const Circle& c);

std::vector<LineSegment> Tangent(const Circle& c1, const Circle& c2);

}  // namespace gl2d

#endif  // GL2D_INCLUDE_TANGENT_H_
