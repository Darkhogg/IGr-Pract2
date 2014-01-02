#include "Matr.hpp"

Matr Matr::operator+= (const Matr& other) {
  for (size_t i = 0; i < MATR_SIZE_2; ++i) {
    data[i] += other.data[i];
  }
}

Matr Matr::operator-= (const Matr& other) {
  for (size_t i = 0; i < MATR_SIZE_2; ++i) {
    data[i] -= other.data[i];
  }
}


Matr operator* (const Matr& m1, const Matr& m2) {
  Matr mr;

  for (size_t i = 0; i < Matr::MATR_SIZE; ++i) {
    for (size_t j = 0; j < Matr::MATR_SIZE; ++j) {
      Vect::Component p = 0;

      for (size_t k = 0; k < Matr::MATR_SIZE; ++k) {
        p += m1.data[i*Matr::MATR_SIZE + k] * m2.data[k*Matr::MATR_SIZE + j];
      }

      mr.data[i*Matr::MATR_SIZE + j] = p;
    }
  }

  return mr;
}


Vect operator* (const Matr& m, const Vect& v) {
  std::array<Vect::Component, 3> va = {v.x(), v.y(), v.w()};
  std::array<Vect::Component, 3> a;

  for (size_t i = 0; i < 3; ++i) {
    a[i] = 0;
    for (size_t k = 0; k < 3; ++k) {
      a[i] += m.data[i*Matr::MATR_SIZE + k] * va[k];
    }
  }

  return Vect{a[0], a[1], a[2]};
}


Vect operator* (const Vect& v, const Matr& m) {
  return m*v;
  /*
  std::array<Vect::Component, 3> va = {v.x(), v.y(), v.w()};
  std::array<Vect::Component, 3> a;

  for (size_t j = 0; j < 3; ++j) {
    a[j] = 0;
    for (size_t k = 0; k < 3; ++k) {
      a[j] += va[k] * m.data[k*Matr::MATR_SIZE + j];
    }
  }

  return Vect{a[0], a[1], a[2]};
  */
}


Matr operator+ (Matr m1, const Matr& m2) {
  m1 += m2;
  return m1;
}

Matr operator- (Matr m1, const Matr& m2) {
  m1 -= m2;
  return m1;
}

Matr Matr::scale (Vect::Component sx, Vect::Component sy) {
  return {
     sx, 0.f, 0.f,
    0.f,  sy, 0.f,
    0.f, 0.f, 1.f
  };
}

Matr Matr::rotate (Vect::Component ang) {
  auto c = cos(ang);
  auto s = sin(ang);

  return {
      c,   s, 0.f,
     -s,   c, 0.f,
    0.f, 0.f, 1.f
  };
}

Matr Matr::translate (Vect::Component tx, Vect::Component ty) {
  return {
    1.f, 0.f,  tx,
    0.f, 1.f,  ty,
    0.f, 0.f, 1.f
  };
}

Matr Matr::transposed () {
  return {
    data[0], data[3], data[6],
    data[1], data[4], data[7],
    data[2], data[5], data[8] 
  };
}