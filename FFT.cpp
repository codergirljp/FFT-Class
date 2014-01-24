#include <iostream>
#include "FFT.h"

// Constructor for FFT class.
FFT::FFT(void)
{
};

/* Sets the Raw Data to the input data
   - generates the FFTData array with zero padding and complex numbers */
void FFT::SetRawData(double rawData[], int rawDataLength)
{
	// for efficiency, loop through the raw data only one time
	//  setting both the raw data array and the m_FFTData array data here
	
	// initialize lengths of raw data and FFT Data array
	m_rawDataLength = rawDataLength;
	m_FFTDataLength = (int)pow(2.0, ceil(log((double)m_rawDataLength)/log(2.0)));

	// allocate memory for rawData
	m_rawData = (double *) malloc(m_rawDataLength * sizeof(double));

	/* allocate memory for FFTData real + complex numbers (note the +1) */
	m_FFTData = (double *) malloc((2* m_FFTDataLength + 1) * sizeof(double));
	
	for(int i=0; i < rawDataLength; i++)
	{
		// set m_rawData values
		m_rawData[i] = rawData[i];

		/* set m_FFTData real and complex values
		   Storing rawData[i] in a complex array to make it work with four1. 
	       This is needed even if rawData[i] is purely real. */
		m_FFTData[2*i+1] = m_rawData[i];
		m_FFTData[2*i+2] = 0.0;
	}

    /* Zero pad the remainder of the m_FFTData array with (0 + 0 j) */
	for(int i=m_rawDataLength; i<m_FFTDataLength; i++)
	{
		m_FFTData[2*i+1] = 0.0;
		m_FFTData[2*i+2] = 0.0;
	}
}

/* calculate FFT 
   - overwrites the m_FFTData with FFT of m_FFTData */
void FFT::CalculateFFT()
{
	four1(m_FFTData, m_FFTDataLength, 1);
}

/* calculate Inverse FFT 
   - overwrites the m_FFTData to normalized InverseFFT of m_FFTData */
void FFT::CalculateIFFT()
{
	// calculate Inverse FFT
	four1(m_FFTData, m_FFTDataLength, -1);

	/* normalize the IFFT */
	for(int i=0; i<m_FFTDataLength; i++)
	{
		m_FFTData[2*i+1] /= m_FFTDataLength;
		m_FFTData[2*i+2] /= m_FFTDataLength;
	}
}

void FFT::PrintFFT()
{
	for(int i=0; i<m_FFTDataLength; i++)
	{
		printf("FFTData[%d] = (%.2f + j %.2f)\n", i, m_FFTData[2*i+1], m_FFTData[2*i+2]);
	}
}

/*
 FFT/IFFT routine. (see pages 507-508 of Numerical Recipes in C)

 Inputs:
	data[] : array of complex* data points of size 2*NFFT+1.
		data[0] is unused,
		* the n'th complex number x(n), for 0 <= n <= length(x)-1, is stored as:
			data[2*n+1] = real(x(n))
			data[2*n+2] = imag(x(n))
		if length(Nx) < NFFT, the remainder of the array must be padded with zeros

	nn : FFT order NFFT. This MUST be a power of 2 and >= length(x).
	isign:  if set to 1, 
				computes the forward FFT
			if set to -1, 
				computes Inverse FFT - in this case the output values have
				to be manually normalized by multiplying with 1/NFFT.
 Outputs:
	data[] : The FFT or IFFT results are stored in data, overwriting the input.
*/
void FFT::four1(double data[], int nn, int isign)
{
    int n, mmax, m, j, istep, i;
    double wtemp, wr, wpr, wpi, wi, theta;
    double tempr, tempi;
    
    n = nn << 1;
    j = 1;
    for (i = 1; i < n; i += 2) {
	if (j > i) {
	    tempr = data[j];     data[j] = data[i];     data[i] = tempr;
	    tempr = data[j+1]; data[j+1] = data[i+1]; data[i+1] = tempr;
	}
	m = n >> 1;
	while (m >= 2 && j > m) {
	    j -= m;
	    m >>= 1;
	}
	j += m;
    }
    mmax = 2;
    while (n > mmax) {
	istep = 2*mmax;
	theta = TWOPI/(isign*mmax);
	wtemp = sin(0.5*theta);
	wpr = -2.0*wtemp*wtemp;
	wpi = sin(theta);
	wr = 1.0;
	wi = 0.0;
	for (m = 1; m < mmax; m += 2) {
	    for (i = m; i <= n; i += istep) {
		j =i + mmax;
		tempr = wr*data[j]   - wi*data[j+1];
		tempi = wr*data[j+1] + wi*data[j];
		data[j]   = data[i]   - tempr;
		data[j+1] = data[i+1] - tempi;
		data[i] += tempr;
		data[i+1] += tempi;
	    }
	    wr = (wtemp = wr)*wpr - wi*wpi + wr;
	    wi = wi*wpr + wtemp*wpi + wi;
	}
	mmax = istep;
    }
}

// Destructor for FFT class.
FFT::~FFT(void)
{
}
