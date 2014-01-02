#ifndef __MATR__H__
#define __MATR__H__

#include "skel/skel.h"

#include <array>

class Matr {

	private:
    static const size_t MATR_SIZE = 3;
    static const size_t MATR_SIZE_2 = MATR_SIZE*MATR_SIZE;

		std::array<Vect::Component, MATR_SIZE_2> data;

  public:
    Matr () : data({
      1.f, 0.f, 0.f,
      0.f, 1.f, 0.f,
      0.f, 0.f, 1.f
    }) {}

    Matr (std::initializer_list<Vect::Component> comps) {
      std::copy(comps.begin(), comps.end(), data.begin());
    }

    Matr operator+= (const Matr& other);
    Matr operator-= (const Matr& other);
    Matr operator*= (const Matr& other);
    //Matr operator+= (const Matr& other);

    static Matr scale (Vect::Component sx, Vect::Component sy);
    static Matr rotate (Vect::Component ang);
    static Matr translate (Vect::Component tx, Vect::Component ty);

    Matr transposed ();

    friend Matr operator* (const Matr& m1, const Matr& m2);

    friend Vect operator* (const Matr& m, const Vect& v);
    friend Vect operator* (const Vect& v, const Matr& m);

    friend std::ostream& operator<<(std::ostream& os, const Matr& m);
};

Matr operator+ (Matr m1, const Matr& m2);
Matr operator- (Matr m1, const Matr& m2);


inline std::ostream& operator<<(std::ostream& os, const Matr& m) {
    os << "[ ";
    for (size_t i = 0; i < Matr::MATR_SIZE_2; ++i) {
      if (i != 0) {
        os << ", ";
      }
      if (i != 0 && i%Matr::MATR_SIZE == 0) {
        os << std::endl << "  ";
      }
      os << m.data[i];
    }
    os << "] " << std::endl;
    return os;
}

#endif