﻿#define _USE_MATH_DEFINES // jeśli nie dam tego na początek do nie zadziała z cmath (wtedy musiałoby być math.h)
#include <iostream>
#include <complex>
#include<cmath>


using namespace std;

// Zakładam, że N zawsze jest potęgą 2 -> N=2^x

// D F T - dyskretna transformata Fouriera 
complex<double>* DFT(double* f, unsigned int size) {
	complex<double>* C = new complex<double>[size]{0};

	for (int k = 0; k < size; k++) {
		for (int n = 0; n < size; n++) {
			complex<double> w = exp(complex<double>(0, -2 * M_PI * k * n/size));
			//complex<double> w = polar(1.0, -2 * M_PI * k * n / size);
			C[k] += f[n] * w;
		}
	}

	return C;
}

// wyniki DFT i FFT moga się między sobą nieznacznie różnić

// F F T - szybka transformata Fouriera
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
	delete[] odd_tmp;
	complex<double>* even = FFT(even_tmp, size / 2);
	delete[] even_tmp;

	for (int k = 0; k < size / 2; k++) {
		//complex<double> w = polar(1.0, - 2 * M_PI * k / size) * odd[k]; // robi to samo
		complex<double> w = exp(complex<double>(0, -2 * M_PI * k / size)) * odd[k];
		C[k] = even[k] + w;
		C[k + size / 2] = even[k] - w;
	}

	delete[] odd;
	delete[] even;

	return C;
}

int main()
{

	double f[]{ 1.0, 2.0, 1.0, -1.0, 1.5 };



	complex<double>* C = DFT(f, 5);

	for (int i = 0; i < 5; i++)
		cout << C[i] << '\n';

}


