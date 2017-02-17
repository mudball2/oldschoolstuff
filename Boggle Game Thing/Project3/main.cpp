#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <conio.h>
#include "CommonFile.h"

using namespace std;

const unsigned int BUCK = 501;

unsigned int hashFunction(const string& v)
{
	unsigned int value = 0;
	for(unsigned int i = 0; i < v.size(); i++)
	{
		value = (11 * value) + ( v[i] - 97 + 7);
	}
	
	return value % BUCK;

}

struct DTSTimer
{
	unsigned int startTime;
public:
	DTSTimer()
	{
		reset();
	}

	void reset()
	{
		startTime = clock();
	}

	unsigned int getElapsedTime()
	{
		return(clock()-startTime);
	}

	static void delay(unsigned int milli)
	{
		unsigned int ST = clock();
		while(clock()-ST < milli){}
	}

};


int main(int argc, char ** argv)
{

	srand((unsigned int)time(0));
	rand();

	int RANDOM = 0;
	int NOT_RANDOM = 1;
	DTSTimer time;
	string userInput;
	string word;
	int score = 0;
#if 1
	char grid[4][4] = {{ 'a', 'r', 'l', 'w'},
					   { 'i', 't', 'o', 's'},
					   { 'e', 'n', 's', 't'},
					   { 'w', 'p', 'k', 'j'}};
#elif 0
	//Will be used for the random grids.
	char grid[4][4] = {{ rand() % (122-97) + 97, rand() % (122-97) + 97, rand() % (122-97) + 97, rand() % (122-97) + 97},
	                   { rand() % (122-97) + 97, rand() % (122-97) + 97, rand() % (122-97) + 97, rand() % (122-97) + 97},
	                   { rand() % (122-97) + 97, rand() % (122-97) + 97, rand() % (122-97) + 97, rand() % (122-97) + 97},
	                   { rand() % (122-97) + 97, rand() % (122-97) + 97, rand() % (122-97) + 97, rand() % (122-97) + 97}};
#endif

	ifstream dict;
	HTable<string> hTable(BUCK, hashFunction);
	BST<string> bst;
	Graph<char> graph;

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			graph.addVertex(grid[i][j]);
		}
	}

	dict.open("engldict.txt");

	if(!dict.is_open())
		cerr << "Could not open file!" << endl; 

	if(dict.is_open())
	{
		while(!dict.eof())
		{
			dict >> word; //Read in the word.
		
			hTable.insert(word); //Insert into the hash table. 
		}
	}

	cout << "MUDBALL GAMES PRESENTS:" << endl;
	cout << endl; 
	cout << " '||'''|,                       '||`        \n"
         << "  ||   ||                        ||         \n"
         <<"  ||;;;;   .|''|, .|''|, .|''|,  ||  .|''|, \n"
         <<"  ||   ||  ||  || ||  || ||  ||  ||  ||..|| \n"
         <<" .||...|'  `|..|' `|..|| `|..|| .||. `|...  \n"
         <<"                      ||     ||             \n"
         <<"                   `..|'  `..|'  \n";
	time.delay(5000);

	time.reset();
	while(time.getElapsedTime() < 60000)
	{
	// input
	
		// if the user pressed a key
		if(_kbhit())
		{
			char ch = _getch();
			
			// if it's a special ky...disregard
			if(-32 == ch)
				_getch();
			
			// if it's a valid letter, add it to the string
			else if(isalpha(ch))
			{
				userInput += tolower(ch);
			}

			// enter
			if(static_cast<int>(ch) == '\r')
			{
				
				if(bst.find(userInput) == true)
					score += 0;
				else
				{
					hTable.find(userInput);
					if(hTable.find(userInput) != -1 )
					{
						for( int i = 0; i < 16; i++)
						{
							if(graph[i].element == userInput[userInput.size()-1])
							{
								bst.insert(userInput); //Add input to the BST.
								score += 50;//Update score.
							}
						}
					}
				}

				userInput = ""; //Reset userInput.
				//userInput = nullptr;
			}
			// backspace
			if('\b' == static_cast<int>(ch))
			{
				//userInput[userInput.size()-1] = '\b';
				userInput = "";
			}
		}

	// update

	// render
		system("cls");
		cout << "Time left: " << 60 - (time.getElapsedTime() / 1000) <<"\t\tScore: " << score << "\t\t\t" 
			<< "Your answers:\n\n";
		cout << "\t\t\t\t\t\t\t";
		bst.printInOrder();
		cout << endl << endl << endl;
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				cout << "| " << grid[i][j] << " |" << "\t";
			}
			cout << endl << endl;
		}
		cout << userInput;
	}
	dict.close();
	return 0;
}