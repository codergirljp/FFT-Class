#include <iostream>
#include "FFT.h"
#include "FileData.h"

using namespace std;

// Test using the File Data Class
void TestFileData()
{
	FileData fd;
	fd.LoadFileData("64Data.txt", 64);

	for(int i=0; i<fd.DataSize; i++)
	{
		cout << fd.Data[i] << endl;	
	}
	
	cout << "DataSize = " << fd.DataSize << endl;
}

//Test using the FFT Class
// expects FileData object to be preloaded with data
void TestFFT(FileData fd)
{
	FFT fft;
	fft.SetRawData(fd.Data, fd.DataSize);
	fft.PrintFFT();
	fft.CalculateFFT();
	cout << endl;
	fft.PrintFFT();
}

// Run all the Tests
void RunTests()
{
	TestFileData();

	FileData fd;
	fd.LoadFileData("64Data.txt", 64);
	TestFFT(fd);

	cout << "Tested True\n";
}

int main()
{
	FileData fd;
	fd.LoadFileData("64Data.txt", 64);
	
	FFT fft;
	fft.SetRawData(fd.Data, fd.DataSize);
	fft.CalculateFFT();
	fd.ExportFFTData("FFT64Data.txt", fft.m_FFTData, fft.m_FFTDataLength);

	fft.PrintFFT();

	getchar();
	return 0;
}
