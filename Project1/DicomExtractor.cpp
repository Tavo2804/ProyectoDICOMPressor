#include "DicomExtractor.h"

#include <fstream>

using namespace std;
using namespace cv;

DicomExtractor::DicomExtractor()
{
}


DicomExtractor::~DicomExtractor()
{
}

DicomFileStructure DicomExtractor::extractDICOM(char * path)
{
	DicomFileStructure dicomStructure;

	ifstream file (path, ios::in | ios::binary);

	file.seekg(0, ios::end);
	streampos size = file.tellg();
	file.seekg(128, ios::beg);
	char * bytes = new char[(int)size - 128];
	file.read(bytes, (int)size - 128);
	file.close();

	//busqueda por inicio de pixeles
	int i = 4;
	while (bytes[i]!=0x28||bytes[i+1]!=0x00|| bytes[i + 2] != 0x10|| bytes[i + 3] != 0x00) {
		i++;
	}
	short rows = 0;
	for (int j = 9; j > 7; j--) {
		rows = (rows << 8) + (bytes[i + j] & 0x000000ff);
	}
	i += 10;
	short cols = 0;
	for (int j = 9; j > 7; j--) {
		cols = (cols << 8) + (bytes[i + j] & 0x000000ff);
	}
	
	while (bytes[i] != 0xffffffe0 || bytes[i + 1] != 0x7f || bytes[i + 2] != 0x10 || bytes[i + 3] != 0x00) {
		i++;
	}

	char* header = new char[i];
	cout << i << endl;
	for (int a = 0; a < i; a++) {
		header[a] = bytes[a];
	}
	cout << header << endl;
	int headerSize = i;
	
	i += 12;
	Mat image = Mat(rows,cols,CV_8UC3);
	int a, b;
	for (a = 0; a < rows; a++) {
		Vec3b* imageRow = image.ptr<Vec3b>(a);
		for (b = 0; b < cols; b++) {
			imageRow[b][2] = (uchar)bytes[i];
			imageRow[b][1] = (uchar)bytes[i+1];
			imageRow[b][0] = (uchar)bytes[i+2];
			i+=3;
		}
	}

	dicomStructure.setHeader(header);
	dicomStructure.setHeaderSize(headerSize);
	dicomStructure.setPixelData(image);
	dicomStructure.setPath(path);
	dicomStructure.setSize(size);

	return dicomStructure;
}
