/**
 * @author Daniel Escoz Solana
 */
#include "Ball.hpp"

#include <cmath>
#include <iostream>

Ball Ball::withRandSpeed (Vect pos, int rad) {
  auto dir = (rand() / (double) RAND_MAX) * M_PI * 2;
  auto mod = (rand() / (double) RAND_MAX) * 150 + 50;
  return Ball(pos, Vect(mod*cos(dir), mod*sin(dir), 0.f), rad);
}

void Ball::update (float delta) {
  _pos += _dir * delta;
  _dir += _acc * delta;

  _ang += _angspd * delta;
}

void Ball::draw () const {
  auto radius = std::max((double) MIN_PARTICLE_RADIUS, _rad);
  int points = std::max(6, (int)(radius * 2));
  auto step = 2 * M_PI / points;

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  glLoadIdentity();
  glTranslated(_pos.x(), _pos.y(), 0);
  glScaled(radius, radius, 1);
  glRotated(_ang, 0, 0, 1);

  glColor3f(1, 1 ,1);
  glBegin(GL_POLYGON);
  for (int i = 0; i < points; i++) {
    glVertex2f(cos(i * step), sin(i * step));
  }
  glEnd();

  glColor3f(1, 0, 0);
  glLineWidth(2.f);
  glBegin(GL_LINES);
  glVertex2f(0, 0);
  glVertex2f(1, 0);
  glEnd();

  glPopMatrix();
}