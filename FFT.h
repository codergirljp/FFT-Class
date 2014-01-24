#pragma once

// The following line must be defined before including math.h to correctly define M_PI
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PI	M_PI	/* pi to machine precision, defined in math.h */
#define TWOPI	(2.0*PI)


/************************************************
* FFT  class 
* Contains code from the book Numerical Recipes in C *
* Visit www.nr.com for the licence.             *
************************************************/
class FFT
{
private:
	// raw Data array and length
	int m_rawDataLength;
    double *m_rawData;

	// calculates the fft
	void four1(double data[], int nn, int isign);

public:
    // FFT Data array and length
	int m_FFTDataLength;
	double *m_FFTData;

	//default constructor 
	FFT(void);

	void SetRawData(double rawData[], int rawDataLength);
	void CalculateFFT();
	void CalculateIFFT();
	void PrintFFT();

	// destructor for FFT class
	virtual ~FFT(void);
};

