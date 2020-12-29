#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;
int N = 0;
double** D = NULL, ** E = NULL;


int generate(int n) { // код генератора входных данных

	int n0 = n;
	srand(time(NULL));

	while (n && !(n & (n - 1)) != 1) {
		n++;
	}

	n0 = n - n0;

	D = new double* [n];
	E = new double* [n];

	for (int i = 0; i < n; i++) {
		D[i] = new double[n];
		E[i] = new double[n];
	}

	for (int i = 0; i < n - n0; i++) {
		for (int j = 0; j < n - n0; j++) {
			D[i][j] = rand() % 10;
			E[i][j] = rand() % 10;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = (i >= n - n0 ? 0 : n - n0); j < n; j++) {
			D[i][j] = 0.0;
			E[i][j] = 0.0;
		}
	}

	return n;
}

void printArr(double** A, int n) { //печать матрицы

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << "\t" << A[i][j] << "\t";
		cout << endl;
	}
	cout << endl;
}

void multip(double** A, double** B, double** C, int n) { //функция перемножения

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			C[i][j] = 0;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++) {
				C[i][j] += A[i][k] * B[k][j];
				N ++;
			}
}

double** subtraction (double** A, double** B, int n) { //вычитание матриц

	double** C = new double* [n];

	for (int i = 0; i < n; i++)
		C[i] = new double[n];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			C[i][j] = A[i][j] - B[i][j];
		
		}
	return C;
}


double** addition (double** A, double** B, int n) { //сложение матриц

	double** C = new double* [n];

	for (int i = 0; i < n; i++) 
		C[i] = new double[n];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			C[i][j] = A[i][j] + B[i][j];
		
		}

	return C;
}

void shtrassen(double** A, double** B, double** C, int n) { // Алгоритм Штрассена перемножения матриц A и B 

	if (n <= 32) { 
		multip(A, B, C, n);
	}
	else {
		double** A11 = new double* [n];
		double** A12 = new double* [n];
		double** A21 = new double* [n];
		double** A22 = new double* [n];

		double** B11 = new double* [n];
		double** B12 = new double* [n];
		double** B21 = new double* [n];
		double** B22 = new double* [n];

		double** C11 = new double* [n];
		double** C12 = new double* [n];
		double** C21 = new double* [n];
		double** C22 = new double* [n];

		double** P1 = new double* [n];
        double** P2 = new double* [n];
        double** P3 = new double* [n];
        double** P4 = new double* [n];
        double** P5 = new double* [n];
        double** P6 = new double* [n];
        double** P7 = new double* [n];

    for (int i = 0; i < n; i++) {

	 A11[i] = new double[n];
	 A12[i] = new double[n];
	 A21[i] = new double[n];
	 A22[i] = new double[n];

	 B11[i] = new double[n];
	 B12[i] = new double[n];
	 B21[i] = new double[n];
	 B22[i] = new double[n];

	 C11[i] = new double[n];
	 C12[i] = new double[n];
	 C21[i] = new double[n];
	 C22[i] = new double[n];

	 P1[i] = new double[n];
	 P2[i] = new double[n];
	 P3[i] = new double[n];
	 P4[i] = new double[n];
	 P5[i] = new double[n];
	 P6[i] = new double[n];
	 P7[i] = new double[n];

}

for (int i = 0; i < n / 2; i++)
{
	for (int j = 0; j < n / 2; j++)
	{
		A11[i][j] = A[i][j];
		A12[i][j] = A[i][j + n / 2];
		A21[i][j] = A[i + n / 2][j];
		A22[i][j] = A[i + n / 2][j + n / 2];

		B11[i][j] = B[i][j];
		B12[i][j] = B[i][j + n / 2];
		B21[i][j] = B[i + n / 2][j];
		B22[i][j] = B[i + n / 2][j + n / 2];

	}
}


shtrassen(addition(A11, A22, n / 2), addition(B11, B22, n / 2), P1, n / 2); 

shtrassen(addition(A21, A22, n / 2), B11, P2, n / 2);

shtrassen(A11, subtraction(B12, B22, n / 2), P3, n / 2);

shtrassen(A22, subtraction(B21, B11, n / 2), P4, n / 2);

shtrassen(addition(A11, A12, n / 2), B22, P5, n / 2);

shtrassen(subtraction(A21, A11, n / 2), addition(B11, B12, n / 2), P6, n / 2);

shtrassen(subtraction(A12, A22, n / 2), addition(B21, B22, n / 2), P7, n / 2);


C11 = subtraction(addition(addition(P1, P4, n / 2), P7, n / 2), P5, n / 2);
C12 = addition(P3, P5, n / 2);
C21 = addition(P2, P4, n / 2);
C22 = subtraction(addition(addition(P1, P3, n / 2), P6, n / 2), P2, n / 2);

for (int i = 0; i < n / 2; i++) //склейка результирующей матрицы
{
	for (int j = 0; j < n / 2; j++)
	{
		C[i][j] = C11[i][j];
		C[i][j + n / 2] = C12[i][j];
		C[i + n / 2][j] = C21[i][j];
		C[i + n / 2][j + n / 2] = C22[i][j];
	}
}
	}


}


int main()
{
	int n, n1, n0 = 0;
	cout << "N = ";
	cin >> n;
	double** C;
	n1 = n;

	n = generate(n);
	C = new double* [n];

	for (int i = 0; i < n; i++) {
		C[i] = new double[n];
	}

	unsigned int start_time = clock();
	shtrassen(D, E, C, n);


	unsigned int end_time = clock();
	cout << endl <<"time: " << (end_time - start_time) / 1000.0; 
}
