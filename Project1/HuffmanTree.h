#include <opencv2/core/utility.hpp>

using namespace cv;
using namespace std;

#pragma once
typedef struct dictionaryPair {
	uchar element;
	string code;
} dictionaryPair_t;

class FrequencyNode
{
public:
	FrequencyNode(uchar elementValue, FrequencyNode* nextNode = NULL);
	FrequencyNode(FrequencyNode* leftNode, FrequencyNode* rightNode, FrequencyNode* nextNode = NULL);
	void incrementFrequency();
	bool hasToShift();
	void fillDictionary(string dict[], string &code);
	

private:
	uchar element;
	long frequency;
	FrequencyNode *next;
	FrequencyNode *left;
	FrequencyNode *right;

	friend class HuffmanTree;
};

class HuffmanTree
{
public:
	HuffmanTree();
	~HuffmanTree();
	bool isEmpty();
	/*
	Metodo que inserta un nodo de elemento
	*/
	void insert(uchar element);
	/*
	Metodo que inserta un nodo de frecuencia
	*/
	void insert(FrequencyNode* left, FrequencyNode* right);
	FrequencyNode* search(uchar element);
	/*
	Metodo para recorrer un elemento a la siguiente posici�n
	*/
	void shiftElement(uchar element);
	void shiftElement(FrequencyNode* node);
	void print();
	/*
	Metodo para obtener y eliminar el primer elemento
	*/
	FrequencyNode* pop();
	long getLength();
	FrequencyNode* getFirst();
	double getEntropy(long numberOfElements);
	void fillFrequencyArray(uchar* array);

protected:
	FrequencyNode *first;
	long length;
};
