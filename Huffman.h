#ifndef HUFFMAN_H
#define HUFFMAN_H
#include "HuffmanCode.h"
#include "Node.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Huffman
{
public:
	Huffman(); //Default constructor
	virtual ~Huffman(); //Default destructor
	bool isFinalNode(Node* headNode); //Checks the tree if its the final node
	bool SearchForChar(Node* ptrNode, char Char); //Checks the Node to see if the char is in that node
	void CountCharOccur(); //Takes the lines from the file and counts all the chars
	void DecodeFile(); //Decodes an already encoded file
	void EncodeChar(Node* ptrNode, char Char); //Finds the Huffman code for each char
	void EncodeFile(); //Encodes the inputed file
	void EncodeToFile(); //Makes the encoded file and a file with the codes
	void FileName(string Name); //Reads in the name of the file from the command line
	void FillInCode(char Char, string CharCode); //Fills in my table with their Huffman code
	void InputLine(string Line, string Function); //Takes the lines from the file and saves them
	void PrintInfo(); //Prints how many bits the message would had taken and how much the compress massage took
protected:
private:
    	double BitsOfComp; //Number of bits for the compressed file
    	double BitsOfFile; //Number of bits for the uncompressed file
	string NameOfFile; //Holds the name of the file
	string HuffCode; //Holds the Huffman code for a character
	vector<HuffmanCode*> HuffmanCharCode; //Holds the encoding table
	vector<string> FileToDecode; //Holds the lines from the file to decode
	vector<string> FileToEncode; //Holds the lines from the file to encode
	vector<Node*> HuffmanTree; //Holds my Huffman tree for encoding
};
#endif // HUFFMAN_H
