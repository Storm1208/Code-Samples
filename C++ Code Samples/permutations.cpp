/*This program takes in a string and outputs all
possible permutations of the string one line at a time
to the terminal. The program utilizes recursion to
find all permutations of the string.*/
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void permutations_helper(std::string in, int first_char, int second_char)
{

  if(first_char == second_char)
  {
    cout << in << endl;
    return;
  }

  for(int i = first_char; i < second_char; i++){
    char temp = in[first_char];
    in[first_char] = in[i];
    in[i] = temp;
    permutations_helper(in,first_char + 1,second_char);
    temp = in[first_char];
    in[first_char] = in[i];
    in[i] = temp;
  }

}

void permutations(std::string in)
{
  int num = (in.length());
  permutations_helper(in,0,num);

}
