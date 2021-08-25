// AUTOR: Dana Belén Choque Zárate
// FECHA: 26/03/2021
// EMAIL: alu01013283482ull.edu.es
// VERSION: 1.0
// ASIGNATURA: Algoritmos y Estructuras de Datos
// PRÁCTICA Nº: 3
// ESTILO: Google C++ Style Guide
// COMPILACIÓN: g++ -g main_polynomial.cc -o main_polynomial
// EJECUCIÓN: ./main_polynomial < data_polynomial.txt
// COMENTARIOS:
// 

#ifndef POLYNOMIAL_H_
#define POLYNOMIAL_H_

#include <iostream>
#include <math.h>  // fabs, pow

#include "vector_t.h"
#include "sparse_vector_t.h"

// Clase para polinomios basados en vectores densos de doubles
class Polynomial : public vector_t<double> {
 public:
  // constructores
  Polynomial(const int n = 0) : vector_t<double>(n) {};
  Polynomial(const Polynomial &pol)
      : vector_t<double>(pol) {}; // constructor de copia

  // destructor
  ~Polynomial() {};

  // E/S
  void Write(std::ostream & = std::cout, const double eps = EPS) const;

  // operaciones
  double Eval(const double) const;                                // FASE III
  bool IsEqual(const Polynomial &, const double = EPS) const;     // FASE IV
};

// Clase para polinomios basados en vectores dispersos
class SparsePolynomial : public sparse_vector_t {
 public:
  // constructores
  SparsePolynomial(const int n = 0) : sparse_vector_t(n) {};
  SparsePolynomial(const Polynomial &pol) : sparse_vector_t(pol) {};
  SparsePolynomial(const SparsePolynomial &);  // constructor de copia

  // destructor
  ~SparsePolynomial() {};

  // E/S
  void Write(std::ostream & = std::cout) const;

  // operaciones
  double Eval(const double) const;                                      // FASE III
  bool IsEqual(const SparsePolynomial &, const double = EPS) const;     // FASE IV
  bool IsEqual(const Polynomial &, const double = EPS) const;           // FASE IV

  // 
  void OrdenarVector(const SparsePolynomial &, const double = EPS) const;
};

// E/S
void Polynomial::Write(std::ostream &os, const double eps) const {
  os << get_size() << ": [ ";
  bool first{true};
  for (int i{0}; i < get_size(); i++)
    if (IsNotZero(at(i), eps)) {
      os << (!first ? " + " : "") << at(i)
         << (i > 1 ? " x^" : (i == 1) ? " x" : "");
      if (i > 1)
        os << i;
      first = false;
    }
  os << " ]" << std::endl;
}


std::ostream &operator<<(std::ostream &os, const Polynomial &p) {
  p.Write(os);
  return os;
}

// FASE III
double Polynomial::Eval(const double x) const {
  double result{0.0};

  for (int i = 0; i < get_size(); i++) 
    result += get_val(i) * pow(x, i);

  return result;
}

// FASE IV
bool Polynomial::IsEqual(const Polynomial &pol, const double eps) const {
  bool differents = false;
  
  
  for (int i = 0; i < get_size(); i++) {
    if (IsNotZero(at(i), eps))
      if(at(i) != pol.at(i)) 
        differents = true;
  }
  return !differents;
}

// constructor de copia
SparsePolynomial::SparsePolynomial(const SparsePolynomial &spol) {
  *this = spol;   // se invoca directamente al operator=
}

// E/S
void SparsePolynomial::Write(std::ostream &os) const {
  os << get_n() << "(" << get_nz() << "): [ ";
  bool first{true};
  for (int i{0}; i < get_nz(); i++) {
    int inx{at(i).get_inx()};
    os << (!first ? " + " : "") << at(i).get_val()
       << (inx > 1 ? " x^" : (inx == 1) ? " x" : "");
    if (inx > 1)
      os << inx;
    first = false;
  }
  os << " ]" << std::endl;
}

std::ostream &operator<<(std::ostream &os, const SparsePolynomial &p) {
  p.Write(os);
  return os;
}

// FASE III
// Operaciones con polinomios
double SparsePolynomial::Eval(const double x) const {
  double result{0.0};

  for (int i = 0; i < get_nz(); i++)
    result += at(i).get_val() * pow(x, at(i).get_inx());

  return result;
}

// FASE IV
bool SparsePolynomial::IsEqual(const SparsePolynomial &spol, const double eps) const {
  bool differents = false;

  if (get_nz() == spol.get_nz()) {
    for (int i = 0; i < get_nz(); i++) {
      if (IsNotZero(at(i).get_val() - spol.at(i).get_val(), eps))
        differents = true;
    }
  } else { differents = true; }

  return !differents;
}

// FASE IV
bool SparsePolynomial::IsEqual(const Polynomial &spol, const double eps) const {
  bool differents = false;

  for (int i = 0; i < get_nz(); i++) {
    if (IsNotZero(spol.get_val(i), eps)) 
      if (at(i).get_val() != spol.get_val(i))
        differents = true;
  }

  return !differents;
}

// modificación
void SparsePolynomial::OrdenarVector(const SparsePolynomial &spol, const double eps) const {
  double min = INFINITY;
  vector_t<double> vector;
  vector.resize(spol.get_nz());
  double auxUno , aux;

  for (int i = 0; i < spol.get_nz(); i++) {
    aux = spol.at(i).get_val();
    for (int  j = 0; j < get_nz(); j++) {
      auxUno = spol.at(j).get_val();
      if(auxUno < aux) {
        vector.at(i) = auxUno;
        aux = auxUno;
        auxUno = min;
        std::cout << aux << " ";
      }
    }
  }

}


#endif  // POLYNOMIAL_H_
