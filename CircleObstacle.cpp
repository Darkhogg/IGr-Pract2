/**
 * @author Daniel Escoz Solana
 */
#include "CircleObstacle.hpp"

#include <iostream>

void CircleObstacle::draw () {
  Obstacle::draw();
  
  auto radius = _rad;
  int points = std::max(6, (int)(radius * 3));
  auto step = 2 * M_PI / points;

  glLineWidth(1);
  glColor3f(.6f, .6f, .8f);
  glBegin(GL_POLYGON);
  for (int i = 0; i < points; i++) {
    glVertex2f(
      _center.x() + (radius * cos(i * step)),
      _center.y() + (radius * sin(i * step))
    );
  }
  glEnd();

  glColor3f(.4f, .4f, .6f);
  glBegin(GL_LINE_LOOP);
  for (int i = 0; i < points; i++) {
    glVertex2f(
      _center.x() + (radius * cos(i * step)),
      _center.y() + (radius * sin(i * step))
    );
  }
  glEnd();
}

bool CircleObstacle::performCollide (
  Vect pos, Vect::Component rad, Vect spd, float delta,
  Vect& outPos, Vect& outSpd, float& outDelta
) {
  auto mrad = rad + _rad;
  auto dist = (_center - pos).mod();

  if (dist < mrad) {
    outDelta = 0;
    outPos = _center + (outPos - _center).normalized() * (mrad+1);

    auto norm = (outPos - _center).normalized(); // Normalized normal
    outSpd = spd - norm.project(spd) * 1.5;

    return true;
  }

  // Destination point of this step
  auto dest = pos + spd * delta;

  
  auto d = spd * delta;
  auto f = pos - _center;

  auto a = d.dot(d);
  auto b = 2 * f.dot(d);
  auto c = f.dot(f) - mrad * mrad;

  auto disc = b*b - 4*a*c;

  if (disc < 0.0f) {
    return false; // Something went horribly wrong earlier
  }

  auto sqrtDisc = sqrt(disc);
  auto inv2A = 1.0f / (2 * a);

  auto t1 = (-b - sqrtDisc) * inv2A;
  auto t2 = (-b + sqrtDisc) * inv2A;

  if (t1 >= 0 && t1 <= 1) {
    outPos = pos + d * t1;

  } else if (t2 >= 0 && t2 <= 1) {
    outPos = pos + d * t2;

  } else {
    return false;
  }

  outDelta = (1 - ((outPos - pos).mod()) / spd.mod()) * delta;
  outPos = _center + (outPos - _center).normalized() * (mrad + 0.001);

  auto norm = (outPos - _center).normalized(); // Normalized normal
  outSpd = spd - norm.project(spd) * 2;

  return true;
}