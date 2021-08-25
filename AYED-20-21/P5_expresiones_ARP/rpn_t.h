// AUTOR: Dana Belén Choque Zárate
// FECHA: 30/04/2021
// EMAIL: alu01013283482ull.edu.es
// VERSION: 2.0
// ASIGNATURA: Algoritmos y Estructuras de Datos
// PRÁCTICA Nº: 5
// ESTILO: Google C++ Style Guide
// COMENTARIOS: Clase RPN (Reverse Polish Notation)

#ifndef RPNT_H_
#define RPNT_H_

#include <iostream>
#include <cctype>
#include <cmath>
//#include <cstdlib>

#include "queue_l_t.h"

// Clase RPN (Reverse Polish Notation)
template <class T> class rpn_t {
 public:
  // constructor
 rpn_t(void) : stack_() {}

  // destructor
  ~rpn_t() {}

  // operaciones
  const int evaluate(queue_l_t<char>&);
  int opera4 (const char, int, int);

 private:
  T stack_;
  void operate_(const char operador);
};


// operaciones
template<class T> const int rpn_t<T>::evaluate(queue_l_t<char>& q) {
  while (!q.empty()) 	{
    char c = q.front();
    q.pop();
    std::cout << "Sacamos de la cola un carácter: " << c;

    if (isdigit(c)) {
      int i = c - '0';
      std::cout << " (es un dígito) " << std::endl
		<< "   Lo metemos en la pila..." << std::endl;
      stack_.push(i);
    } else {
      std::cout << " (es un operador)" << std::endl;
      operate_(c);
    }
  }
  return stack_.top();
}


template<class T> void rpn_t<T>::operate_(const char c) {
  assert(c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == 'r' || c == 'l' || c == 'c');

  int result{0};
  int firstOperate{0}, secondOperate{0};
  firstOperate = stack_.top();
  std::cout << "   Sacamos de la pila un operando: " << firstOperate << std::endl;
  stack_.pop();
  if ( c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
    secondOperate = stack_.top();
    std::cout << "   Sacamos de la pila otro operando: " << secondOperate << std::endl;
    stack_.pop();
  }

  switch (c) {
    case '+':
      result = secondOperate + firstOperate;
      break;
    case '-':
      result = secondOperate - firstOperate;
      break;
    case '*':
      result = secondOperate * firstOperate;
      break;
    case '/':
      result = secondOperate / firstOperate;
      break;
    case '^':
      result = std::pow(secondOperate, firstOperate);
      break;
    case 'r':
      result = std::sqrt(firstOperate);
      break;
    case 'l':
      result = std::log2(firstOperate);
      break;
    case 'c':
      result = std::pow(firstOperate, 2);
      break;
  }
  
  std::cout << "   Metemos en la pila el resultado: " << result << std::endl;
  stack_.push(result);
}

// modificación
template<class T> int rpn_t<T>::opera4(const char c, int firstOperate, int secondOperate) {
  assert(c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == 'r' || c == 'l' || c == 'c' || c == '%');

  int result{0};
  switch (c) {
    case '+':
      result = secondOperate + firstOperate;
      break;
    case '-':
      result = secondOperate - firstOperate;
      break;
    case '*':
      result = secondOperate * firstOperate;
      break;
    case '/':
      result = secondOperate / firstOperate;
      break;
    case '^':
      result = std::pow(secondOperate, firstOperate);
      break;
    case 'r':
      result = std::sqrt(firstOperate);
      break;
    case 'l':
      result = std::log2(firstOperate);
      break;
    case 'c':
      result = std::pow(firstOperate, 2);
      break;
    case '%':
      result = (secondOperate * firstOperate) / 100;
      break;
  }

  return result;
}


#endif  // RPNT_H_
