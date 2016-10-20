#include "Huffman.h"

Huffman::Huffman() : BitsOfComp(0), BitsOfFile(0)
{
	//ctor
}

Huffman::~Huffman()
{
	//dtor
}


bool Huffman::isFinalNode(Node* headNode)
{
	bool isSame = false; //Test for if char is in the node
	string testStr; //Holds the string of chars inside the node

	testStr = headNode->Chars;

    //Searches the node to check if every char from my encoding table
    //is in that node
	for (int i = 0; i < HuffmanCharCode.size(); i++)
	{
		isSame = false;

		for (int j = 0; j < testStr.length(); j++)
		{
			if (HuffmanCharCode.at(i)->Char == testStr[j])
			{
				isSame = true;
			}
		}

		if (isSame == false)
		{
			return 0;
		}
	}

	return 1;
}


bool Huffman::SearchForChar(Node* ptrNode, char Char)
{
    //Searches for a char in a node
	for (int i = 0; i < ptrNode->Chars.length(); i++)
	{
		if (ptrNode->Chars.at(i) == Char)
		{
			return 1;
		}
	}

	return 0;
}


void Huffman::CountCharOccur()
{
	bool CharExist = false; //Checks for if the char already exist in the list
	HuffmanCode *tempNode; //Node for creating my Huffman table and sorting it
	int key; //The key is for sorting
	string tempStr; //Holds the strings from the file to count all the chars

    //Loop to read each line from the file to encode. It reads each line
    //and checks each character against the list if it's already in there
    //it increments it or if not makes a new one.
	for (int i = 0; i < FileToEncode.size(); i++)
	{
		tempStr = FileToEncode.at(i);

		for (int j = 0; j < tempStr.length(); j++)
		{
			CharExist = false;

			for (int k = 0; k < HuffmanCharCode.size(); k++)
			{
				if (tempStr[j] == HuffmanCharCode.at(k)->Char)
				{
					CharExist = true;
					HuffmanCharCode.at(k)->NumOfOcc++;
					BitsOfFile++;
				}
			}

			if (CharExist == false)
			{
				tempNode = new HuffmanCode;
				tempNode->Char = tempStr[j];
				tempNode->NumOfOcc = 1;
				tempNode->Code = "0";
				HuffmanCharCode.push_back(tempNode);
				BitsOfFile++;
			}
		}
	}

    //Sorts the Huffman code table
	tempNode = new HuffmanCode;
	for (int i = 0; i < HuffmanCharCode.size(); i++)
	{
		key = i;

		while (key > 0 && HuffmanCharCode.at(key)->NumOfOcc >
			HuffmanCharCode.at(key - 1)->NumOfOcc)
		{
			tempNode = HuffmanCharCode.at(key);
			HuffmanCharCode.at(key) = HuffmanCharCode.at(key - 1);
			HuffmanCharCode.at(key - 1) = tempNode;
			key--;
		}
	}
}


void Huffman::DecodeFile()
{
    	HuffmanCode* tempNode; //Temp node for reading in the Huffman code table
    	NameOfFile.erase(NameOfFile.end() - 4, NameOfFile.end()); //Finds the files holding the codes
	NameOfFile.append(".codes");
    	ifstream myCodes(NameOfFile.c_str());
	int tempCount = 0;
	NameOfFile.erase(NameOfFile.end() - 6, NameOfFile.end()); //Creates the file to output the decoded code
	NameOfFile.append(".dec");
	ofstream myFile(NameOfFile.c_str());
	string Line, testString, tempString; //Strings for decoding the file

   	//Reads in the codes from the file
    	while (getline(myCodes, Line))
	{
		tempNode = new HuffmanCode;
		tempNode->Char = Line[6];
		tempNode->NumOfOcc = 0;
		tempCount = 0;
		for (int i = 0; i < Line.length(); i++)
		{
			if (Line[i] == ':')
			{
				tempCount++;
			}
			else if (tempCount == 3)
			{
				tempCount = i + 1;
			}
		}
		Line.erase(0, tempCount);
		tempNode->Code = Line;
		HuffmanCharCode.push_back(tempNode);
	}

    	//Decodes the message using the codes and the encoded file.
	for (int i = 0; i < FileToDecode.size(); i++)
	{
		testString = FileToDecode.at(i);

		for (int j = 0; j < testString.length(); j++)
		{
			tempString.push_back(testString[j]);

			for (int k = 0; k < HuffmanCharCode.size(); k++)
			{
				if (tempString == HuffmanCharCode.at(k)->Code)
				{
					myFile << HuffmanCharCode.at(k)->Char;
					tempString.clear();
				}
			}
		}
		myFile << endl;
	}
}


void Huffman::EncodeChar(Node* ptrNode, char Char)
{
    //Finds the char in the Huffman tree and creates the
    //code for it
	if (ptrNode->NodeL == NULL && ptrNode->NodeR == NULL)
	{
		FillInCode(Char, HuffCode);
		HuffCode.clear();
	}
	else if (SearchForChar(ptrNode->NodeL, Char))
	{
		HuffCode.push_back('0');
		EncodeChar(ptrNode->NodeL, Char);
	}
	else if (SearchForChar(ptrNode->NodeR, Char))
	{
		HuffCode.push_back('1');
		EncodeChar(ptrNode->NodeR, Char);
	}
}


void Huffman::EncodeFile()
{
	int key = 1; //Key for creating the tree
	Node* headNode; //Holds the top node for the tree
	Node* tempNode; //For creating a new node for the tree

	CountCharOccur();

    //Takes the info from my Huffman table and creates nodes
    //for them to create a tree
	for (int i = 0; i < HuffmanCharCode.size(); i++)
	{
		tempNode = new Node;
		tempNode->Chars.push_back(HuffmanCharCode.at(i)->Char);
		tempNode->NumOfOcc = HuffmanCharCode.at(i)->NumOfOcc;
		tempNode->NodeL = NULL;
		tempNode->NodeR = NULL;
		HuffmanTree.push_back(tempNode);
	}

	do
	{
	    //Create a new node for the tree
		tempNode = new Node;
		tempNode->Chars = "0";
		tempNode->NumOfOcc = 0;
		tempNode->NodeL = NULL;
		tempNode->NodeR = NULL;
		headNode = tempNode;

        //Assigns the right side of the node
		key = 1;
		do
		{
			for (int it = HuffmanTree.size() - 1; it >= 0; it--)
			{
				if (HuffmanTree.at(it)->NumOfOcc == key)
				{
					tempNode->NodeR = HuffmanTree.at(it);
					tempNode->Chars = HuffmanTree.at(it)->Chars;
					tempNode->NumOfOcc += HuffmanTree.at(it)->NumOfOcc;
					HuffmanTree.erase(HuffmanTree.begin() + it);
					break;
				}
			}

			key++;
		} while (tempNode->NodeR == NULL);

        //Assigns the left side of the node
		key = 1;
		do
		{
			for (int it = HuffmanTree.size() - 1; it >= 0; it--)
			{
				if (HuffmanTree.at(it)->NumOfOcc == key)
				{
					tempNode->NodeL = HuffmanTree.at(it);
					tempNode->Chars += HuffmanTree.at(it)->Chars;
					tempNode->NumOfOcc += HuffmanTree.at(it)->NumOfOcc;
					HuffmanTree.insert(HuffmanTree.begin() + it, tempNode);
					HuffmanTree.erase(HuffmanTree.begin() + it + 1);
					break;
				}
			}

			key++;
		} while (tempNode->NodeL == NULL);
	} while (!isFinalNode(headNode));

    //Finds the encoded code for each char
	for (int i = 0; i < HuffmanCharCode.size(); i++)
	{
		EncodeChar(headNode, HuffmanCharCode.at(i)->Char);
	}

	EncodeToFile();

	PrintInfo();
}


void Huffman::EncodeToFile()
{
	NameOfFile.erase(NameOfFile.end() - 4, NameOfFile.end()); //Creates the file for the encoded mission
	NameOfFile.append(".enc");
	ofstream myFile(NameOfFile.c_str());

    //Sends the data for the encoded message
	for (int i = 0; i < FileToEncode.size(); i++)
	{
		for (int j = 0; j < FileToEncode.at(i).size(); j++)
		{
			for (int k = 0; k < HuffmanCharCode.size(); k++)
			{
				if (FileToEncode.at(i)[j] == HuffmanCharCode.at(k)->Char)
				{
					myFile << HuffmanCharCode.at(k)->Code;
					BitsOfComp += HuffmanCharCode.at(k)->Code.length();
				}
			}
		}
		myFile << endl;
	}

	NameOfFile.erase(NameOfFile.end() - 4, NameOfFile.end()); //Creates the file to hold the encoding table
	NameOfFile.append(".codes");
	ofstream myFile2(NameOfFile.c_str());

    //Sends the encoding table to the file
	for (int i = 0; i < HuffmanCharCode.size(); i++)
	{
		myFile2 << "Char: " << HuffmanCharCode.at(i)->Char << " "
            << "NumOfOcc: " << HuffmanCharCode.at(i)->NumOfOcc << " "
            << "Code: " << HuffmanCharCode.at(i)->Code << endl;
	}

}


void Huffman::FileName(string Name)
{
	NameOfFile = Name; //Sets the file name
}


void Huffman::FillInCode(char Char, string CharCode)
{
    //Sets the Huffman code value to each char
	for (int i = 0; i < HuffmanCharCode.size(); i++)
	{
		if (HuffmanCharCode.at(i)->Char == Char)
		{
			HuffmanCharCode.at(i)->Code = CharCode;
		}
	}
}


void Huffman::InputLine(string Line, string Function)
{
    //Based on which command is entered this chooses which vector
    //to save the information to
	if (Function == "-e")
	{
		FileToEncode.push_back(Line);
	}
	else if (Function == "-d")
	{
		FileToDecode.push_back(Line);
	}
}


void Huffman::PrintInfo()
{
    BitsOfFile *= 8;

    //Prints the number of bits required for uncompressed and compressed
    cout << "The number of bits for the uncompressed file: " << BitsOfFile << endl
        << "The number of bits for the compressed file: " << BitsOfComp << endl
	<< "The compressio ratio: " << (1 - (BitsOfComp / BitsOfFile)) * 100 << "%" << endl;
}
