/**
 * @author Daniel Escoz Solana
 */
#include "PolygonObstacle.hpp"

#include <iostream>
#include <cfloat>

bool d = false;

void PolygonObstacle::draw () {
  Obstacle::draw();
  
  glLineWidth(1);
  glColor3f(.8f, .6f, .6f);
  glBegin(GL_POLYGON);
  for (auto it = _points.begin(); it != _points.end(); ++it) {
    glVertex2f(it->x(), it->y());
  }
  glEnd();

  glColor3f(.6f, .4f, .4f);
  glBegin(GL_LINE_LOOP);
  for (auto it = _points.begin(); it != _points.end(); ++it) {
    glVertex2f(it->x(), it->y());
  }
  glEnd();

  if (!d) {
    d = true;
    //inflate(10).draw();
    d = false;
  }
}

bool PolygonObstacle::performCollide (
  Vect pos, Vect::Component rad, Vect spd, float delta,
  Vect& outPos, Vect& outSpd, float& outDelta, Vect& norm
) {
  if (rad >= Ball::MIN_PARTICLE_RADIUS) {
    return inflate(rad).performCollide(pos, 0, spd, delta, outPos, outSpd, outDelta, norm);
  }

  Vect::Component tin = -DBL_MAX;
  Vect::Component tout = spd.mod();

  auto nspd = spd.normalized();

  Vect normt;

  for (size_t i = 0; i < _points.size(); i++) {
    size_t j = (i + 1) % _points.size();

    auto wi = _points[i] - pos;
    auto wj = _points[j] - pos;

    auto dist_i = wi.dot(nspd.perp_left_z0());
    auto proj_i = wi.dot(nspd);
    auto dist_j = wj.dot(nspd.perp_left_z0());
    auto proj_j = wj.dot(nspd);

    auto num = (proj_i * dist_j) - (dist_i * proj_j);
    auto den = dist_j - dist_i;

    auto thit = num / den;
    auto normal = (_points[i] - _points[j]).perp_left_z0().normalized();

    auto vn = nspd.dot(normal);
    if (vn < 0) {
      if (thit > tin) {
        tin = thit;
        normt = normal;
      }
    } else if (vn > 0) {
      tout = std::min(tout, thit);
    }

    if (tin >= tout) {
      // "Fast" discard
      return false;
    }
  }

  auto when = (tin / spd.mod()) - 0.001f;

  if (tin >= spd.mod() * delta) {
    return false;
  }
  if (tin <= 0) {
    return false;
    outPos = pos + spd * when;
    outDelta = delta - 0.0001f;
    outSpd = spd - normt.project(spd) * 2;

    return true;
  }

  outPos = pos + spd * when;
  outDelta = delta - when;
  outSpd = spd - normt.project(spd) * 2;

  return true;
}

PolygonObstacle PolygonObstacle::inflate (Vect::Component size) {
  std::vector<Vect> pts;

  for (int i = 0; i < _points.size(); i++) {
    auto j = (i + 1) % _points.size();
    auto k = (j + 1) % _points.size();

    auto n = (_points[i] - _points[j]).perp_left_z0().normalized();
    auto nn = (_points[j] - _points[k]).perp_left_z0().normalized();

    // Inflated edge
    pts.push_back(_points[i] + n * size);
    pts.push_back(_points[j] + n * size);

    // Inflated pseudo-arc
    auto angFrom = n.yaw();
    auto angTo = nn.yaw();
    auto points = 16;

    if (angTo < angFrom) {
      angTo += 2 * M_PI;
    }

    auto step = (angTo - angFrom) / (points - 1);
    for (int p = 1; p < points - 1; p++) {
      auto ang = angFrom + step * p;
      pts.push_back(_points[j] + Vect(size * cos(ang), size * sin(ang), 1.f));
    }
  }

  return PolygonObstacle(pts);
}