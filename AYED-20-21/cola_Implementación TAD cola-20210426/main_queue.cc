// AUTOR: 
// FECHA: 
// EMAIL: 
// VERSION: 1.0
// ASIGNATURA: Algoritmos y Estructuras de Datos
// COMENTARIOS: programa de prueba del TAD cola
// Se compila con:
// g++ main_queue.cpp -o main_queue

//#include <cstdio>
#include "queue_v_t.h"
#include "queue_l_t.h"

// ejercicio 5: respuesta
template <class T>
T fusion(T& cola1, T& cola2) {
  T colaFusion;
  while (!cola1.empty() || !cola2.empty()) {
    if (!cola1.empty()) {
      colaFusion.push(cola1.front());
      cola1.pop();
    }

    if(!cola2.empty()) {
      colaFusion.push(cola2.front());
      cola2.pop();
    }
  }
  return colaFusion;
}

// ejercico 6: solución
template <class T>
void deleteLetter(T& cola) {
  T aux;
  while (!cola.empty()) {
    if (!aux.contains(cola.front()))
      aux.push(cola.front());
    cola.pop();
  }
  cola.copy(aux),
}

// extra / nota: Es posible declarar una plantilla de una clase que a su vez contenga una plantilla.
// por ejemplo, para el ejercico 3:
template <template<class> class C, class T>
void reverse(C<T>& src) {
  const int n = src.size();
  T stack[n];
  for (int i = 0; i < n; i++) {
    stack[i] = src.front();
    src.pop();
  }
  for (int i = n - 1; i >= 0; i--)
    src.push(stack[i]);
}


int main(void)
{
	queue_v_t<char> cola_vector;

	for (int i = 0; i < 10; i++)
	{
		cola_vector.push('a' + i);
		cout << cola_vector;
	}

	cout << endl;

	while (!cola_vector.empty())
	{
		cola_vector.pop();
		cout << cola_vector;
	}


	queue_l_t<char> cola_lista;

	for (int i = 0; i < 10; i++)
	{
		cola_lista.push('a' + i);
		cout << cola_lista;
	}

	cout << endl;

	std::cout << "encontrado: "<< cola_lista.check('c') << std::endl;



	return 0;
}

