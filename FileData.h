#pragma once

// includes for getting data from text file
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>     /* strtod */

using namespace std;

class FileData
{
public:
	double *Data;  // Pointer to file data array
	int DataSize;  // number of data values in the file (one per a line)
	FileData(void);
	void LoadFileData(string fileName, int dataSize);
	void ExportFFTData(string fileName, double FFTData[], int FFTDataSize);
	virtual ~FileData(void);
};

