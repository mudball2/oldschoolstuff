////////////////////////////////////////////////////////////////////////////////////////////////
// File :			main.cpp
// Author :			Rodney Stoeffler
// Created :		03.24.08
// Last Modified :	10.29.09
// Purpose :		The main driver for the memory game
// Notes :			Property of Full Sail University, Data Structures Course.
////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////
// INCLUDES
////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>				// needed for drawing the screen
#include <conio.h>				// needed for _kbhit and _getch.
#include "MemoryFunctions.h"	// interface for drawing the screen and delay function
#include "DynArray.h"           // include DynArray for AI behavior. 
using namespace std;


////////////////////////////////////////////////////////////////////////////////////////////////
// Function : splash
// Parameters : none.
// Return : none.
// Notes : Displays the title and waits for the user to hit 'any key to continue.'
////////////////////////////////////////////////////////////////////////////////////////////////
void Splash(void);


////////////////////////////////////////////////////////////////////////////////////////////////
// Function :	main
// Parameters : argc - the number of command line arguments
//				argv - the array of command line arguments
// return :		int - 0 for success
////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char ** argv)
{

	//Seed the RNG
	srand((unsigned int)time(0));
	rand();
	
	bool input = false; //A boolean to display AI pattern.
	
	int pat = 4;
	int num;
	DynArray<int> pattern; //Declaring a pattern array. 
	DynArray<int> player; //Declaring a player array.
	int timesPressed = 0; //Check how many buttons were pressed.
	int doubleCheck = 0; //Check if all buttons were correct.
	int score = 0; //Score variable.
	int round = 1; //Round variable.

	Splash(); //Show splash screen.
   empty(); //Empty screen.

   while(true) //Begin game loop.
   {
	   if( input == false )
	   {
		   for(int i = 0; i < pat; i++)
		   {
			   num = rand()%4+1-1;
			   pattern.append(num);
		   

			   if(num == 1)
			   {
				   drawUp();
				   delay(150);
				   empty();
			   } else if (num == 2) {
				   drawDown();
				   delay(150);
				   empty();
			   } else if (num == 3) {
				   drawLeft();
				   delay(150);
				   empty();
			   } else {
				   drawRight();
				   delay(150);
				   empty();
			   }
		   }
		   input = true;
	   }


      if(_kbhit())
      {
         char ch = _getch();
         switch(tolower(ch))
         {
            // show stuff for each specific move
            case 'w':   
            {
               drawUp();
               delay(150);
               empty();
			   player.append(1);
			   timesPressed++;
            } 
            break;

            case 's':   
            {
               drawDown();
               delay(150);
               empty();
			   player.append(2);
			   timesPressed++;
            } 
            break;

            case 'a':   
            {
               drawLeft();
               delay(150);
               empty();
			   player.append(3);
			   timesPressed++;
            } 
            break;

            case 'd':   
            {
               drawRight();
               delay(150);
               empty();
			   player.append(0);
			   timesPressed++;
            } 
            break;
         }

		 if(timesPressed == pat) //If the player pressed is equal to array size.
		 {
			 for(int i = 0; i < pat; i++) //Loop through.
			 {
				 if(pattern.operator[](i) == player.operator[](i))
					 doubleCheck++;//Increment doubleCheck.
				 else 
				 {
				 }
			 }

			if(doubleCheck == pat) //if doubleCheck is equal to array size.
				score += 100; //Give the player 100 points.
			else
				score += 50; //Reward the player anyhow.

			//Reset everything.
			timesPressed = 0;
			doubleCheck = 0;
			round++;
			pat++;
			input = false;
			 
			cout << "Score: " << score << "\t Round :" << round << endl; //Display score and round.
			delay(3000);//Delay for a bit.
		 }
	

         // exiting test on the 'q' key
         if(ch == 'q')
			break;
      }
   }
   // complete.
   return 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////
// Function : splash
// Parameters : none.
// Return : none.
// Notes : Displays the title and waits.
////////////////////////////////////////////////////////////////////////////////////////////////
void Splash(void)
{
	//Display the text. 
	cout << "          _______. __  .___  ___.   ______   .__   __. \n"
		 <<	"	 /       ||  | |   \\/   |  /  __  \\  |  \\ |  | \n"
		 <<	"	|   (----`|  | |  \\  /  | |  |  |  | |   \\|  | \n"
		 <<	"	 \\   \\    |  | |  |\\/|  | |  |  |  | |  . `  | \n"
		 <<	"     .----)   |   |  | |  |  |  | |  `--'  | |  |\\   | \n"
		 <<	"     |_______/    |__| |__|  |__|  \\______/  |__| \\__| \n";
	delay(5000);
}