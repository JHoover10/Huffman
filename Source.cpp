#include "Huffman.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[]){
	Huffman Solver;
	ifstream myFile(argv[2]); //Reads from the file inputed from the command line
	string Line;

	Solver.FileName(argv[2]); //Takes the name of the file from the command line

    //Reads in the data from the file
	while (getline(myFile, Line))
	{
		Solver.InputLine(Line, argv[1]);
	}

    //If-else statements to choose which function to use
	if (strcmp(argv[1], "-e") == 0)
	{
		Solver.EncodeFile();
	}
	else if(strcmp(argv[1], "-d") == 0)
	{
		Solver.DecodeFile();
	}

	return 1;
}
