#include <iostream>


using namespace std;

// https://campusingenieriaytecnologia.ull.es/mod/page/view.php?id=289786

// problema 1
int devolver(int n) {
	if (n == 0)
		return 0;
	else return 1 + devolver(n/10);
}
// sol:
int digit(const int number) {
	return number ? 1+ digit(number / 10) : 0;
}

// problema 2
int suma (int number) {
	if (number == 0)
		return 0;
	else return number % 10 + suma(number / 10);
}
// sol:
int sum_digit(const int number) {
	return number ? number % 10 + sum_digit(number / 10) : 0;
}


// problema 3
int convert_to_binary(const int number) {
	if (number <= 1) return number;
	if (number > 1) return convert_to_binary(number / 2) * 10 + (number % 2);
}


// problema 4
int collatz(const int number) {
	if (number == 1) return 1;
	if (number % 2 == 0) return 1 + collatz(number / 2);
	else return 1 + collatz(3 * number + 1);
}


// problema 5
bool primo(const int divisor /* = 2*/, const int number) {
	if ( number == divisor) return true;
	if (number % divisor == 0) return false;
	return primo(number, divisor + 1);
}

// problema 6:  Calcular el Máximo Común Divisor de dos números enteros positivos.
int mcd(const int a, const int b,const int divisor = 2) {
	if (a < divisor || b < divisor) return 1;
	else if(a % divisor == 0 && b % divisor == 0)
		return divisor * mcd(a / divisor, b / divisor, divisor);
	else
		return mcd(a, b, divisor + 1);
}

// problema 7: Calcular el Mínimo Común Múltiplo de dos números enteros positivos.
int mcm(const int a, const int b,const int divisor = 2) {
  if (a < divisor || b < divisor) return a * b;
	else if(a % divisor == 0 && b % divisor != 0)
		return divisor * mcm(a / divisor, b, divisor);
	else if(a % divisor != 0 && b % divisor == 0)
    return divisor * mcm(a, b / divisor, divisor);
  else
		return mcd(a, b, divisor + 1);
}

// sol:
int mcm(const int a, const int b,const int divisor = 2) {
  if (a < divisor || b < divisor) return a * b;
	if(a % divisor && b % divisor)
		return mcd(a, b, divisor + 1);
  int x = a % divisor ? a : a / divisor;
  int y = b % divisor? b : b / divisor;
  return mcd(x, y, divisor);
}

// problema 9
template <class T>
T det(const matrix_t<T> &mat) {
  if(mat.get_m() == 1) return (1, 1);
  float sum = 0;
  matrix_t<T> submat(mat.get_m() - 1, mat.get_n() - 1);
  for (int col = 1; col <= mat.get_m(); col++) {
    for (int i = 1; i < submat.get_m(); i++) {
      for (int j = 1; j < submat.get_n(); j++) {
        submat(i, j) = mat (i + 1, j < col ? j : j +1);
      }
    }
  sum += (col % 2 ? mat(1, col) : -mat(1, col)) * det(submat);
  }
  return sum;
}




int main() {
	// problema 3
  int number{0};
	number = 19;
	int fin;
	fin = convert_to_binary(number);
	cout << fin << endl;

	// problema 4
	int idk{0};
	idk = collatz(27);
	cout << idk << endl;

	// problema 5
	bool idk2;
	idk2 = primo(2, 13);
	cout << idk2 << endl;

  // problema 6
  int nose;
  nose = mcd(1, 2, 3);
  cout << nose << endl;

  // problema 7
  int nose2;
  nose2 = mcm(1, 2, 3);
  cout << nose2 << endl;

  return 1;
}