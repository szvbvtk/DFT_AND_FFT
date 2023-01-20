#define _USE_MATH_DEFINES // jeśli nie dam tego na początek do nie zadziała z cmath (wtedy musiałoby być math.h)
#include <iostream>
#include <complex>
#include<cmath>


using namespace std;

complex<double>* FFT(double* f, unsigned int size) {
	if (size == 1) {
		complex<double>* c0 = new complex<double>(f[0]);

		return c0;
	}

	complex<double>* C = new complex<double>[size];
	double* odd_tmp = new double[size / 2];
	double* even_tmp = new double[size / 2];

	for (int i = 0, j = 0; i < size; i+=2, j++) {
		odd_tmp[j] = f[i + 1];
		even_tmp[j] = f[i];
	}

	complex<double>* odd = FFT(odd_tmp, size / 2);
	complex<double>* even = FFT(even_tmp, size / 2);


	for (int k = 0; k < size / 2; k++) {
		//complex<double> w = polar(1.0, - 2 * M_PI * k / size) * odd[k]; // robi to samo
		complex<double> w = exp(complex<double>(0, -2 * M_PI * k / size)) * odd[k];
		C[k] = even[k] + w;
		C[k + size / 2] = even[k] - w;
	}

	delete[] odd_tmp;
	delete[] odd;
	delete[] even_tmp;
	delete[] even;

	return C;
}

int main()
{

	double f[4]{1, 2, 3, 4};



	complex<double>* C = FFT(f, 4);

	for (int i = 0; i < 4; i++)
		cout << C[i] << '\n';

}


