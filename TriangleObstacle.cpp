/**
 * @author Daniel Escoz Solana
 */
#include "TriangleObstacle.hpp"
#include <iostream>

void TriangleObstacle::draw () {
  glColor3f(.6f, .8f, .6f);
  glBegin(GL_POLYGON);
  for (auto it = _points.begin(); it != _points.end(); ++it) {
    glVertex2f(it->x(), it->y());
  }
  glEnd();

  glColor3f(.4f, .6f, .4f);
  glBegin(GL_LINE_LOOP);
  for (auto it = _points.begin(); it != _points.end(); ++it) {
    glVertex2f(it->x(), it->y());
  }
  glEnd();
}

bool TriangleObstacle::collide (
  Vect pos, Vect::Component rad, Vect spd, float delta,
  Vect& outPos, Vect& outSpd, float& outDelta
) {
  std::array<Vect::Component, 3> dists, projs;
  std::array<int, 3> signs;

  auto nspd = spd.normalized();

  // Compute the above arrays
  for (auto i = 0; i < 3; i++) {
    auto w = _points[i] - pos;

    dists[i] = w.dot(nspd.perp_left_z0());
    projs[i] = w.dot(nspd);
    signs[i] = (dists[i] > 0) ? 1 : (dists[i] < 0) ? -1 : 0;
  }

  if (abs(signs[0] + signs[1] + signs[2]) >= 3) {
    // fast discard
    return false;
  }

  std::vector<Vect::Component> thits;
  std::vector<Vect> normals;

  for (auto i = 0; i < 3; i++) {
    auto j = (i + 1) % 3;

    if (signs[i] * signs[j] < 0) {
      auto num = (projs[i] * dists[j]) - (dists[i] * projs[j]);
      auto den = dists[j] - dists[i];

      thits.push_back(num / den);
      normals.push_back((_points[i] - _points[j]).perp_left_z0().normalized());
    }
  }

  if (thits.size() == 0) {
    return false;
  }

  size_t iMin = 0;
  auto norm = normals[0];
  auto tMin = thits[0];
  auto tMax = tMin;

  for (auto i = 0; i < thits.size(); i++) {
    if (thits[i] < tMin) {
      tMin = thits[i];
      norm = normals[i];
      iMin = i;
    }
    if (thits[i] > tMax) {
      tMax = thits[i];
    }
  }

  auto spdmod = spd.mod();
  auto when = (tMin / spdmod) - 0.001f;

  if (tMin < 0 || tMin > spdmod * delta) {
    if (tMin < 0 && tMax > 0) {
      // Inside!!
      outPos = pos + spd * when;
      outDelta = delta - 0.001f;
      outSpd = spd;

      return true;

    } else {
      return false;
    }
  }

  outPos = pos + spd * when;
  outDelta = delta - when;
  outSpd = spd - norm.project(spd) * 2;

  return true;
}