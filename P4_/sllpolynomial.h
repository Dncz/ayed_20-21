// AUTOR: 
// FECHA: 
// EMAIL: 
// VERSION: 2.0
// ASIGNATURA: Algoritmos y Estructuras de Datos
// PRÁCTICA Nº: 4
// ESTILO: Google C++ Style Guide
// COMENTARIOS:
// 

#ifndef SLLPOLYNOMIAL_H_
#define SLLPOLYNOMIAL_H_

#include <iostream>
#include <math.h>  // fabs, pow

#include "pair_t.h"
#include "sll_t.h"
#include "vector_t.h"

#define EPS 1.0e-6

typedef pair_t<double> pair_double_t;  // Campo data_ de SllPolynomial
typedef sll_node_t<pair_double_t> SllPolyNode;  // Nodos de SllPolynomial

// Clase para polinomios basados en listas simples de pares
class SllPolynomial : public sll_t<pair_double_t> {
 public:
  // constructores
  SllPolynomial(void) : sll_t() {};
  SllPolynomial(const vector_t<double>&, const double = EPS);

  // destructor
  ~SllPolynomial() {};

  // E/S
  void Write(std::ostream& = std::cout) const;
  
  // operaciones
  double Eval(const double) const;
  bool IsEqual(const SllPolynomial&, const double = EPS) const;
  void Sum(const SllPolynomial&, SllPolynomial&, const double = EPS);
};


bool IsNotZero(const double val, const double eps = EPS) {
  return fabs(val) > eps;
}

// FASE II
// constructor
SllPolynomial::SllPolynomial(const vector_t<double>& v, const double eps) {
  // poner el código aquí
  SllPolyNode sll; // nodos
  pair_double_t sv; // datos, sparseVector
  for (int i = v.get_size() - 1; i >= 0; i--)
    if(IsNotZero(v.at(i), eps)) {
      sv.set(v.at(i), i);  // se establece como dato el valor del vector != 0
      SllPolyNode* aux = new SllPolyNode(sv);  // con un puntero apunto al valor guardado en sv
      assert (aux != NULL);  // comprobar que el nodo no sea nulo
      push_front(aux);  // insertar el nodo a la lista invocante
    }
  // para ver cuál es la cabeza...
  // std::cout << get_head()->get_data() << " " << std::endl;
}


// E/S
void SllPolynomial::Write(std::ostream& os) const {
  os << "[ ";
  bool first{true};
  SllPolyNode* aux{get_head()};
  while (aux != NULL) {
    int inx{aux->get_data().get_inx()};
    double val{aux->get_data().get_val()};
    if (val > 0)
      os << (!first ? " + " : "") << val;
    else
      os << (!first ? " - " : "-") << fabs(val);
    os << (inx > 1 ? " x^" : (inx == 1) ? " x" : "");
    if (inx > 1)
      os << inx;
    first = false;
    aux = aux->get_next();
  }
  os << " ]" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const SllPolynomial& p) {
  p.Write(os);
  return os;
}


// Operaciones con polinomios

// FASE III
// Evaluación de un polinomio representado por lista simple
double SllPolynomial::Eval(const double x) const {
  double result{0.0};
  // poner el código aquí
  SllPolyNode* nodo = get_head();  // nodo apunta a la cabeza
  // double paraElevar{0}; // recogemos el valor del valor que apunta el nodo
  while (nodo != NULL) {
    // paraElevar = nodo->get_data().get_val();
    result += nodo->get_data().get_val() * pow(x, nodo->get_data().get_inx());
    nodo = nodo->get_next();  // nodo apunta al siguiente
  }
  
  return result;
}
// HAY QUE USAR EL EPS
// Comparación si son iguales dos polinomios representados por listas simples
bool SllPolynomial::IsEqual(const SllPolynomial& sllpol,
			    const double eps) const {
  bool differents = false;

  SllPolyNode* nodo = get_head();
  SllPolyNode* polnodo = sllpol.get_head();

  while (nodo != NULL && polnodo != NULL) {
    if(nodo->get_data().get_val() != polnodo->get_data().get_val())
      differents = true;

    nodo = nodo->get_next();
    polnodo = polnodo->get_next();
  }

  return !differents;
}
// hay que usar el EPS porque si se suman dos cosas es 0 y no entra en suma...
// FASE IV
// Generar nuevo polinomio suma del polinomio invocante mas otro polinomio
void SllPolynomial::Sum(const SllPolynomial& sllpol,
			SllPolynomial& sllpolsum,
			const double eps) {
  // poner el código aquí
  // se guarda en sllpolsum el resultado
  SllPolyNode* nodo = get_head();
  SllPolyNode* polnodo = sllpol.get_head();
  pair_double_t resultado;

  while (nodo != NULL && polnodo != NULL) {
    // como cojo las x...
    // if(nodo->get_data().get_inx() == polnodo->get_data().get_inx()) {
    //   resultado.set(nodo->get_data().get_val() + polnodo->get_data().get_val(), nodo->get_data().get_inx());
    //   SllPolyNode* aux = new SllPolyNode(resultado);
    //   sllpolsum.push_front(aux);

    //   nodo = nodo->get_next();
    //   polnodo = polnodo->get_next();
    // }
    std::cout << nodo->get_data().get_inx() << " " << polnodo->get_data().get_inx() << std::endl;
    if (nodo->get_data().get_inx() > polnodo->get_data().get_inx()) {
      // resultado.set(nodo->get_data().get_val(), nodo->get_data().get_inx());
      polnodo = polnodo->get_next();
    } 
    
    if(nodo->get_data().get_inx() < polnodo->get_data().get_inx()) {
      // resultado.set(polnodo->get_data().get_inx(), polnodo->get_data().get_inx());
      nodo = nodo->get_next();
    } //else {
    //   resultado.set(nodo->get_data().get_val() + polnodo->get_data().get_val(), nodo->get_data().get_inx());
    // }
    
    if(nodo->get_data().get_inx() == polnodo->get_data().get_inx()) {
      resultado.set(nodo->get_data().get_val() + polnodo->get_data().get_val(), nodo->get_data().get_inx());
      SllPolyNode* aux = new SllPolyNode(resultado);
      sllpolsum.push_front(aux);

      nodo = nodo->get_next();
      polnodo = polnodo->get_next();
    }

    std::cout << nodo->get_data().get_inx() << "...." << polnodo->get_data().get_inx() << std::endl;
    // SllPolyNode* aux = new SllPolyNode(resultado);
    // sllpolsum.push_front(aux);

    // nodo = nodo->get_next();
    // polnodo = polnodo->get_next();
  }


}


#endif  // SLLPOLYNOMIAL_H_
