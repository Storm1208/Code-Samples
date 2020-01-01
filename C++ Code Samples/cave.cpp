/*This program processes a sequence of instructions
from an input file (one per line) to track a user's
movement through a maze. The instructions can be
N,S,E, or W (for North, South, East, and West respectively)

Every "step" taken will cause the program to roll out a
bit of "thread"; and every retraced step will cause The
program to roll the "thread" back up. Upon completion,
the program will output the total length of the thread
to show how far into the cave the user traveled*/
#include <iostream>
#include <stack>
#include <fstream>

using namespace std;


int main(int argc, char* argv[]){

	if(argc < 2 || argc > 2)
	{
		cout << "Incorrect number of arguments entered.";
	}

	//we'll use a stack to track our actions, like a maze game!
	stack<char> directions;
	char temp;

	//opening file
	fstream input;
	input.open(argv[1]);

	/*looping through directions in file
	while simultaneously calculating units
	of spool*/
	while(input >> temp)
	{
		if(!directions.empty()){
			char top = directions.top();
			if((top == 'N' && temp != 'S') || (top == 'S' && temp != 'N') || (top == 'W' && temp != 'E')
			|| (top == 'E' && temp != 'W'))
			{
				directions.push(temp);
			}else{
				directions.pop();
			}
		}else if(directions.empty())
		{
			directions.push(temp);
		}
	}

	int length = directions.size();
	cout << length << endl;
}
