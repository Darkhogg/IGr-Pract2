/**
 * @author Daniel Escoz Solana
 */
#include "PolygonObstacle.hpp"

void PolygonObstacle::draw () {
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
}

bool PolygonObstacle::collide (
  Vect pos, Vect::Component rad, Vect spd, float delta,
  Vect& outPos, Vect& outSpd, float& outDelta
) {
  

  return false;
}