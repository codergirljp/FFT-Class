
#include "FileData.h"

// constructor for FileData class
FileData::FileData(void)
	:DataSize(0)
{
}

/*  Load a 1 dimensional array of data from a file 
   - data is expected to be one value per a line  */
void FileData::LoadFileData(string fileName, int dataSize)
{
	
		DataSize = dataSize;  // Make the DataSize available to others

		// initialize data array size and values
		Data = (double *) malloc(DataSize * sizeof(double));

		// open text file
		string line;
		ifstream file (fileName);
	 
		int inx = 0;

		if (file.is_open())
		{
			while ( getline (file,line) )
			{
				std::string::size_type sz;     // alias of size_t
				double val = std::stod (line,&sz);
				Data[inx] = val;
				inx++;
			}

		   file.close();
		}
		else
		{
			cout << "File " << fileName << " not found." << endl;
		}
}

/* Exports FFT Data to a space deliminated file from FFT data array created with real + complex parts by FFT class*/
void FileData::ExportFFTData(string fileName, double fftData[], int fftDataSize)
{
    ofstream outfile;
    outfile.open (fileName);
 
	for(int i=0; i<fftDataSize; i++) 
	{
		 outfile <<  i << " " << fftData[2*i+1] << " " << fftData[2*i+2] << "\n";
	}

	outfile.close();
}

// Destructor for FileData class
FileData::~FileData(void)
{
}
