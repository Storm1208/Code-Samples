/*This program reads in a text file and will
output its characters in reverse to the terminal.
The name of the file is fed in as a command line
parameter.*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

int main(int argc,char* argv[])
{
	 if(argc != 2)
	 {
	 	cout << "Incorrect number of arguments entered.\n";
	 	return 0;
	 }


	 int num_char = 0;

	 //opening file and reading in number of characters
	 ifstream myFile;//if stream for reading IN, ofstream for OUT
	 myFile.open(argv[1]);

	 string temp;


	 getline(myFile,temp);
	 stringstream numgrab(temp);
	 numgrab << temp;
	 numgrab >> num_char;

	 /*grabbing all words in file and placing them
	 in a stringstream*/
	 getline(myFile,temp);
	 stringstream parser(temp);
	 parser << temp;

	 //dynamically allocated word array
	 char *words = NULL;
	 words = new char[num_char];
	 char temp2;

	 for(int i = 0; i < num_char; i++)
	 {
	 	parser.get(temp2);
	 	words[i] = temp2;
	 }


	 for(int j = num_char - 1; j > -1; j--)
	 {
	 	cout << words[j];
	 }

	 cout << endl;

	 delete[] words;




	 return 1;
}
