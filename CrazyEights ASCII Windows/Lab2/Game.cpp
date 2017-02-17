	#include "Game.h"
	//Include some header files 
	#include "Human.h"
	#include "Computer.h"
	#include "Card.h"
	#include "Deck.h"
	//Including this one to try the upcasting thing 
	#include "Player.h" //We may not need it because it is now an ABC and objects can only be created through 
						//maybe upcasting....? 
	//Now include the thing for the color 
	#include "Color.h"

	//Now I'm including stuff for the saving the high scores and such... 
	#include <fstream> //Yeap, the fstream does some cool stuff that might be nifty...

	//Now including stuff for music 
	#pragma comment(lib, "fmodex_vc.lib")
	#include <fmod.hpp>
	#include <fmod.h>

FMOD::System* sys;
FMOD_RESULT  result = FMOD::System_Create(&sys);


Game::Game()
{
	m_state = GAME_INIT;
}

void Game::Run()
{
	// Bool to control whether the game should continue to run.
	bool run = true;
	
	//Create the class objects and stuff here...
	CHuman hum;
	CDeck deck;
	CComputer com;

	//Creating the "byte" type varaible here...
	typedef unsigned char byte;

	// load sound
	FMOD::Sound* sound;
	sys->setOutput(FMOD_OUTPUTTYPE_DSOUND );
	sys->init(32, FMOD_INIT_NORMAL, 0); 
	result = sys->createSound("song.wav", FMOD_LOOP_NORMAL,NULL, &sound);

	//Initialize channel
	FMOD::Channel* channel = 0;
	
	CCard* humHand = new CCard[8]; // for human
	CCard* compHand = new CCard[8]; // for computer
	//Have something for current amount of cards
	int currentAmt = 5; 
	int currAmt = 5; //This is for the computer

	//Creating a stack for the discard pile
	CStack<CCard> discard;
	CCard topCard; //For simplicity(?) purposes... 

	
	byte cheatNumber = 0; //Initializing our "byte" variable.
	int cheat; //Declaring variable for player choice to toggle a cheat.
	//Names of cheats so it can show what is activated.
	const char* cheatNames[3] = { "All Cards LEGAL!", "Two Turns in a Row!", "No Wild Cards"};
	int cheatOn[3] = { 0, 0, 0};

	bool legalCard = true; //Initialize to true 

	//Some functions (if they'll work..)
	void MakeChoice(void); 
	void MakeMove(void); 

	//An in-game varaible that keeps score of the player and such.
	int playerScore = 0;
	
	//Will create the data file here.
	ofstream outfile;
	outfile.open("SavedScores.txt", ios::app); //Creates/opens the file
	if (outfile.fail()) {
		cout << "Didn't work..." << endl; 
	}// endif

	// Loop while our bool remains true.
	while(run)
	{
		switch(m_state)
		{
		case GAME_INIT:
			// Insert initialization code here.

			m_state = GAME_PLAY; //Set the state to gameplay...
			break;
		case GAME_PLAY:
			// Insert game play code here.
			//Initial game beep
			Beep(1000, 100);

			// play sound
			result = sys->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
			sys->update();

			hum.Ask();
			if(strcmp(hum.GetName(), "CHEAT") == 0)
			{
				Beep( 2000, 200); //Adding a beep
				for(;;)
				{
					for(;;)
					{
						cout << "Enter cheat # to toggle (cheat numbers 1-3): ";
						cout << "\n\tType \"0 0\" (with space) to leave\n"; 
						if(cin >> cheat && cheat >= 1 && cheat <= 3)
						{
							cin.ignore(INT_MAX, '\n');
							break;
						} else if( cin >> cheat && cheat == 0 ){
							break;
						}
						cin.clear();
						cin.ignore(INT_MAX, '\n');
						/*
						if(GetAsyncKeyState(VK_ESCAPE))
						{
							break; 
						}\*/
					}

					// Using the ^XOR operator and <<LEFTSHIFT operator to toggle the cheat items.
					cheatNumber ^= 1<<(cheat-1);
					//cout << cheatNumber; //No longer needed. 

					for(int i = 0; i < 3; ++i)
					{
						cout << i+1 << ": ";
						if(cheatNumber & (1<<i))
						{
							cout << cheatNames[i];
							cheatOn[i] = 1;
						}
						cout << '\n';
					}
					if(cheat == 0)
						break;
					/*
					if(GetAsyncKeyState(VK_ESCAPE))
					{
						break; 
					}
					*/
				}//end main for loop here...
				system("pause");
				system("cls");
			}
			
#if 0 //ALL OF THIS WILL NOW UPDATE IN-GAME
			hum.Show();
			deck.Shuffle();
			//Building an acutal hand that will be used to compare values and/or discard. (Will use the indicies with 
			//the choices for the if statements below that decide the logic and such.
			for( int i = 0; i < currentAmt; i++)
			{
				//hum.AddCard(deck.Draw()); //Maybe won't need this...?
				humHand[i] = deck.Draw(); 
				humHand[i].Show();
			}
			cout << endl;
			//com.SetName("compName"); //Try again later...
			com.SetScore(200);
			com.Show();
			//Building an acutal hand that will be used to compare values and/or discard. (Will use the indicies with 
			//the choices for the if statements below that decide the logic and such.
			for( int i = 0; i < currentAmt; i++)
			{
				//com.AddCard(deck.Draw()); 
				compHand[i] = deck.Draw(); 
				compHand[i].Show(); 
			}
#elif 0
			//This was simply to test the Draw() function and such. Our "straight forward" solution.
			deck.Draw(); // 0
			deck.Draw(); // 1 
			deck.Draw(); // 2 
			deck.Draw(); // 3 
			deck.Draw(); // 4 
			deck.Draw(); // 5
			deck.Draw(); // 6 
			deck.Draw(); // 7
#endif
			
			//topCard = deck.Draw(); //Moving the initialization of the discard pile here. 
			//Double checking the stack...

			//Main gameplay should start and loop here until the end. 
			//It should end until the deck is empty and when either hand is empty. 

			//Shuffle the deck...
			deck.Shuffle(); 
			//Set up the original hands and such..
			for(int i = 0; i < currentAmt; i++)
				humHand[i] = deck.Draw(); 

			for(int i = 0; i < currAmt; i++)
				compHand[i] = deck.Draw(); 

			for(;;) //Making an actual infinite for loop and will end the game based on an "if" check at the end of the loop.
			{
				//Show both the computer's and the player's hand.... 

				
				cout << FS::Green << endl;
				hum.Show();
				for( int i = 0; i < currentAmt; i++)
				{
					//hum.AddCard(deck.Draw()); //Maybe won't need this...?
					humHand[i].Show();
				}
				cout << FS::Default << endl; 

				cout << FS::Blue << endl; 
				//com.SetScore(200); //It's probably not entirely necessary for the computer to even have score. 
				com.Show();
				for( int i = 0; i < currAmt; i++)
				{
					//com.AddCard(deck.Draw());
					compHand[i].Show(); 
				}
				cout << FS::Default << endl; 
				//Now set up a "Discard" pile.
				cout << endl; 
				cout << "Discard Pile:"; 
				topCard = deck.Draw(); // A cloned card of the one removed? Into another variable for comparison?  
				discard.Push(topCard); // Pushing a primary card onto the discard stack. (No longer needed). 
				topCard.Show(); 

				//Before doing anything else, check to see if the player has any legal cards. If not, have them draw a card.
#if 0 //WILL THIS FINALLY BE THE END OF THE FORCE DRAW....? YES!!
				for( int i = 0; i < currentAmt; i++)
				{
					legalCard = true; 
					cout << /*humHand[i] <<*/ endl; 
					if(humHand[i].GetSuit() != topCard.GetSuit() || humHand[i].GetValue() != topCard.GetValue())
					{
						/*
						humHand[currentAmt+1] = deck.Draw(); 
						cout << "You have been forced to draw a card..." << endl;
						*/ 
						legalCard = false; 
					} else if(currentAmt >= 7){
						legalCard = true;
						break;
					}//endif
				}//New end point for the for loop 

				//If the legal card is false, then set everything up, set it to true and check again.
				if (legalCard == false)
				{
					//currentAmt++; 
					humHand[currentAmt+1] = deck.Draw(); 
					cout << "You have been forced to draw a card..." << endl; 
					legalCard = true; 
					for(int i = 0; i < currentAmt; i++)
						humHand[i].Show(); 
				}//end if 
				//} //end for loop
#endif

	//USING: #pragma region on this code because.....it's an eyesore...			
#pragma region playerAction
				//Temp variables for actions and choices
				int action, move;
				MakeMove();
				
				if( cin >> move && (move == 1 || move == 2))
				{
					if (move == 1 )
					{
						//Do nothing...should move on...
					} else if (move == 2 ) {
						currentAmt += 1; 
						humHand[currentAmt] = deck.Draw(); 
						for( int i = 0; i < currentAmt; i++)
							humHand[i].Show(); 
					} // end if 

				} else {
					MakeMove(); 
					cin >> move; 
				} // end if 

				MakeChoice(); 
				if( cin >> action && (action == 1 || action == 2 || action == 3 || action == 4 || action == 5 || action == 6 || action == 7 || action == 8 ))
				{

					//Now check the card chosen with the discard pile....
			
					if(action == 1 )
					{
						//Checks to see if the card is legal first.. 
						if(humHand[0].GetSuit() == topCard.GetSuit() || humHand[0].GetValue() == topCard.GetValue() || (cheatOn[0] == 1))
						{
							//Now we will remove that card from the hand, and then we will add it to the top of the discard stack.
							//On top of that, we will update what is seen.
							currentAmt--;
							topCard = humHand[0]; 
							cout << discard.Push(topCard) << endl; 
							cout << currentAmt << endl;
							swap(humHand[0], humHand[currentAmt]);
							for( int i = 0; i < currentAmt; i++)
								humHand[i].Show(); 
							system("pause");
						} else { 
							//Ask again and/or use the upcoming Update() function... 
							system("cls");
							MakeChoice(); 
							cin >> action;
						}//endif  

					}
					if(action == 2 )
					{
						//Checks to see if the card is legal first.. 
						if(humHand[1].GetSuit() == topCard.GetSuit() || humHand[1].GetValue() == topCard.GetValue() || (cheatOn[0] == 1))
						{
							//Now we will remove that card from the hand, and then we will add it to the top of the discard stack.
							//On top of that, we will update what is seen. 
							currentAmt--;
							topCard = humHand[1]; 
							cout << discard.Push(topCard) << endl; 
							cout << currentAmt << endl;
							swap(humHand[1], humHand[currentAmt]);
							for( int i = 0; i < currentAmt; i++)
								humHand[i].Show(); 
							system("pause");
						} else { 
							//Ask again and/or use the upcoming Update() function... 
							system("cls");
							MakeChoice(); 
							cin >> action;
						}//endif  

					}
					if(action == 3 )
					{
						//Checks to see if the card is legal first.. 
						if(humHand[2].GetSuit() == topCard.GetSuit() || humHand[2].GetValue() == topCard.GetValue() || (cheatOn[0] == 1))
						{
							//Now we will remove that card from the hand, and then we will add it to the top of the discard stack.
							//On top of that, we will update what is seen. 
							currentAmt--;
							topCard = humHand[2]; 
							cout << discard.Push(topCard) << endl; 
							cout << currentAmt << endl;
							swap(humHand[2], humHand[currentAmt]);
							for( int i = 0; i < currentAmt; i++)
								humHand[i].Show(); 
							system("pause");
						} else { 
							//Ask again and/or use the upcoming Update() function... 
							system("cls");
							MakeChoice(); 
							cin >> action;
						}//endif  

					}
					if(action == 4 )
					{
						//Checks to see if the card is legal first.. 
						if(humHand[3].GetSuit() == topCard.GetSuit() || humHand[3].GetValue() == topCard.GetValue() || (cheatOn[0] == 1))
						{
							//Now we will remove that card from the hand, and then we will add it to the top of the discard stack.
							//On top of that, we will update what is seen. 
							currentAmt--;
							topCard = humHand[3]; 
							cout << discard.Push(topCard) << endl; 
							cout << currentAmt << endl;
							swap(humHand[3], humHand[currentAmt]);
							for( int i = 0; i < currentAmt; i++)
								humHand[i].Show(); 
							system("pause");
						} else { 
							//Ask again and/or use the upcoming Update() function... 
							system("cls");
							MakeChoice(); 
							cin >> action;
						}//endif  

					}
					if(action == 5 )
					{
						//Checks to see if the card is legal first.. 
						if(humHand[4].GetSuit() == topCard.GetSuit() || humHand[4].GetValue() == topCard.GetValue() || (cheatOn[0] == 1))
						{
							//Now we will remove that card from the hand, and then we will add it to the top of the discard stack.
							//On top of that, we will update what is seen. 
							currentAmt--;
							topCard = humHand[4]; 
							cout << discard.Push(topCard) << endl; 
							cout << currentAmt << endl;
							swap(humHand[4], humHand[currentAmt]);
							for( int i = 0; i < currentAmt; i++)
								humHand[i].Show(); 
							system("pause");
						} else { 
							//Ask again and/or use the upcoming Update() function... 
							system("cls");
							MakeChoice(); 
							cin >> action;
						}//endif  

					}
					if(action == 6 )
					{
						//Checks to see if the card is legal first.. 
						if(humHand[5].GetSuit() == topCard.GetSuit() || humHand[5].GetValue() == topCard.GetValue() || (cheatOn[0] == 1))
						{
							//Now we will remove that card from the hand, and then we will add it to the top of the discard stack.
							//On top of that, we will update what is seen. 
							currentAmt--;
							topCard = humHand[5]; 
							cout << discard.Push(topCard) << endl; 
							cout << currentAmt << endl;
							swap(humHand[5], humHand[currentAmt]);
							for( int i = 0; i < currentAmt; i++)
								humHand[i].Show(); 
							system("pause");
						} else { 
							//Ask again and/or use the upcoming Update() function... 
							system("cls");
							MakeChoice(); 
							cin >> action;
						}//endif  

					}
					if(action == 7 )
					{
						//Checks to see if the card is legal first.. 
						if(humHand[6].GetSuit() == topCard.GetSuit() || humHand[6].GetValue() == topCard.GetValue() || (cheatOn[0] == 1))
						{
							//Now we will remove that card from the hand, and then we will add it to the top of the discard stack.
							//On top of that, we will update what is seen. 
							currentAmt--;
							topCard = humHand[6]; 
							cout << discard.Push(topCard) << endl; 
							cout << currentAmt << endl;
							swap(humHand[6], humHand[currentAmt]);
							for( int i = 0; i < currentAmt; i++)
								humHand[i].Show(); 
							system("pause");
						} else { 
							//Ask again and/or use the upcoming Update() function... 
							system("cls");
							MakeChoice(); 
							cin >> action;
						}//endif  

					}
					if(action == 8 )
					{
						//Checks to see if the card is legal first.. 
						if(humHand[7].GetSuit() == topCard.GetSuit() || humHand[7].GetValue() == topCard.GetValue() || (cheatOn[0] == 1))
						{
							//Now we will remove that card from the hand, and then we will add it to the top of the discard stack.
							//On top of that, we will update what is seen. 
							currentAmt--;
							topCard = humHand[7]; 
							cout << discard.Push(topCard) << endl; 
							cout << currentAmt << endl;
							swap(humHand[7], humHand[currentAmt]);
							for( int i = 0; i < currentAmt; i++)
								humHand[i].Show(); 
							system("pause");
						} else { 
							//Ask again and/or use the upcoming Update() function... 
							system("cls");
							MakeChoice(); 
							cin >> action;
						}//endif  

					}//endif
				} else {
					//Ask again and stuff....
					system("cls");
					MakeChoice(); 
				}//endif
				if( cheatOn[1] == 1 )
				{
					MakeMove();
				
					if( cin >> move && (move == 1 || move == 2))
					{
						if (move == 1 )
						{
							//Do nothing...should move on...
						} else if (move == 2 ) {
							currentAmt += 1; 
							humHand[currentAmt] = deck.Draw(); 
							for( int i = 0; i < currentAmt; i++)
								humHand[i].Show(); 
						} // end if 

					} else {
						MakeMove(); 
						cin >> move; 
					} // end if 

					MakeChoice(); 
					if( cin >> action && (action == 1 || action == 2 || action == 3 || action == 4 || action == 5 || action == 6 || action == 7 || action == 8 ))
					{

						//Now check the card chosen with the discard pile....
			
						if(action == 1 )
						{
							//Checks to see if the card is legal first.. 
							if(humHand[0].GetSuit() == topCard.GetSuit() || humHand[0].GetValue() == topCard.GetValue() || (cheatOn[0] == 1))
							{
								//Now we will remove that card from the hand, and then we will add it to the top of the discard stack.
								//On top of that, we will update what is seen.
								currentAmt--;
								topCard = humHand[0]; 
								cout << discard.Push(topCard) << endl; 
								cout << currentAmt << endl;
								swap(humHand[0], humHand[currentAmt]);
								for( int i = 0; i < currentAmt; i++)
									humHand[i].Show(); 
								system("pause");
							} else { 
								//Ask again and/or use the upcoming Update() function... 
								system("cls");
								MakeChoice(); 
								cin >> action;
							}//endif  

						}
						if(action == 2 )
						{
							//Checks to see if the card is legal first.. 
							if(humHand[1].GetSuit() == topCard.GetSuit() || humHand[1].GetValue() == topCard.GetValue() || (cheatOn[0] == 1))
							{
								//Now we will remove that card from the hand, and then we will add it to the top of the discard stack.
								//On top of that, we will update what is seen. 
								currentAmt--;
								topCard = humHand[1]; 
								cout << discard.Push(topCard) << endl; 
								cout << currentAmt << endl;
								swap(humHand[1], humHand[currentAmt]);
								for( int i = 0; i < currentAmt; i++)
									humHand[i].Show(); 
								system("pause");
							} else { 
								//Ask again and/or use the upcoming Update() function... 
								system("cls");
								MakeChoice(); 
								cin >> action;
							}//endif  

						}
						if(action == 3 )
						{
							//Checks to see if the card is legal first.. 
							if(humHand[2].GetSuit() == topCard.GetSuit() || humHand[2].GetValue() == topCard.GetValue() || (cheatOn[0] == 1))
							{
								//Now we will remove that card from the hand, and then we will add it to the top of the discard stack.
								//On top of that, we will update what is seen. 
								currentAmt--;
								topCard = humHand[2]; 
								cout << discard.Push(topCard) << endl; 
								cout << currentAmt << endl;
								swap(humHand[2], humHand[currentAmt]);
								for( int i = 0; i < currentAmt; i++)
									humHand[i].Show(); 
								system("pause");
							} else { 
								//Ask again and/or use the upcoming Update() function... 
								system("cls");
								MakeChoice(); 
								cin >> action;
							}//endif  

						}
						if(action == 4 )
						{
							//Checks to see if the card is legal first.. 
							if(humHand[3].GetSuit() == topCard.GetSuit() || humHand[3].GetValue() == topCard.GetValue() || (cheatOn[0] == 1))
							{
								//Now we will remove that card from the hand, and then we will add it to the top of the discard stack.
								//On top of that, we will update what is seen. 
								currentAmt--;
								topCard = humHand[3]; 
								cout << discard.Push(topCard) << endl; 
								cout << currentAmt << endl;
								swap(humHand[3], humHand[currentAmt]);
								for( int i = 0; i < currentAmt; i++)
									humHand[i].Show(); 
								system("pause");
							} else { 
								//Ask again and/or use the upcoming Update() function... 
								system("cls");
								MakeChoice(); 
								cin >> action;
							}//endif  

						}
						if(action == 5 )
						{
							//Checks to see if the card is legal first.. 
							if(humHand[4].GetSuit() == topCard.GetSuit() || humHand[4].GetValue() == topCard.GetValue() || (cheatOn[0] == 1))
							{
								//Now we will remove that card from the hand, and then we will add it to the top of the discard stack.
								//On top of that, we will update what is seen. 
								currentAmt--;
								topCard = humHand[4]; 
								cout << discard.Push(topCard) << endl; 
								cout << currentAmt << endl;
								swap(humHand[4], humHand[currentAmt]);
								for( int i = 0; i < currentAmt; i++)
									humHand[i].Show(); 
								system("pause");
							} else { 
								//Ask again and/or use the upcoming Update() function... 
								system("cls");
								MakeChoice(); 
								cin >> action;
							}//endif  

						}
						if(action == 6 )
						{
							//Checks to see if the card is legal first.. 
							if(humHand[5].GetSuit() == topCard.GetSuit() || humHand[5].GetValue() == topCard.GetValue() || (cheatOn[0] == 1))
							{
								//Now we will remove that card from the hand, and then we will add it to the top of the discard stack.
								//On top of that, we will update what is seen. 
								currentAmt--;
								topCard = humHand[5]; 
								cout << discard.Push(topCard) << endl; 
								cout << currentAmt << endl;
								swap(humHand[5], humHand[currentAmt]);
								for( int i = 0; i < currentAmt; i++)
									humHand[i].Show(); 
								system("pause");
							} else { 
								//Ask again and/or use the upcoming Update() function... 
								system("cls");
								MakeChoice(); 
								cin >> action;
							}//endif  

						}
						if(action == 7 )
						{
							//Checks to see if the card is legal first.. 
							if(humHand[6].GetSuit() == topCard.GetSuit() || humHand[6].GetValue() == topCard.GetValue() || (cheatOn[0] == 1))
							{
								//Now we will remove that card from the hand, and then we will add it to the top of the discard stack.
								//On top of that, we will update what is seen. 
								currentAmt--;
								topCard = humHand[6]; 
								cout << discard.Push(topCard) << endl; 
								cout << currentAmt << endl;
								swap(humHand[6], humHand[currentAmt]);
								for( int i = 0; i < currentAmt; i++)
									humHand[i].Show(); 
								system("pause");
							} else { 
								//Ask again and/or use the upcoming Update() function... 
								system("cls");
								MakeChoice(); 
								cin >> action;
							}//endif  

						}
						if(action == 8 )
						{
							//Checks to see if the card is legal first.. 
							if(humHand[7].GetSuit() == topCard.GetSuit() || humHand[7].GetValue() == topCard.GetValue() || (cheatOn[0] == 1))
							{
								//Now we will remove that card from the hand, and then we will add it to the top of the discard stack.
								//On top of that, we will update what is seen. 
								currentAmt--;
								topCard = humHand[7]; 
								cout << discard.Push(topCard) << endl; 
								cout << currentAmt << endl;
								swap(humHand[7], humHand[currentAmt]);
								for( int i = 0; i < currentAmt; i++)
									humHand[i].Show(); 
								system("pause");
							} else { 
								//Ask again and/or use the upcoming Update() function... 
								system("cls");
								MakeChoice(); 
								cin >> action;
							}//endif  

						}//endif
					} else {
						//Ask again and stuff....
						system("cls");
						MakeChoice(); 
					}//endif
				
				}
#pragma endregion

#pragma region computerAction
				//NOW it's the computer's turn. 
				for(int i = 0; i < currAmt; i++)
				{
					legalCard = true;
					if(compHand[i].GetSuit() != topCard.GetSuit() && compHand[i].GetValue() != topCard.GetValue())
					{
						legalCard = false; 
					} else if( currAmt > 8 ){
						legalCard = true;
					}//endif
				} // new end for the for loop here...just to see if it works better. 
					if (legalCard == false)
					{
						currAmt += 1;
						compHand[currAmt] = deck.Draw(); 
						cout << "The computer has drawn a card." << endl; 
						legalCard = true; 
						for(int i = 0; i < currAmt; i++)
							compHand[i].Show(); 
						system("pause"); 
					}//endif
				for(int i = 0; i < currAmt; i++)
				{
					if(compHand[i].GetSuit() == topCard.GetSuit() || compHand[i].GetValue() == topCard.GetValue())
					{
					
						currAmt -= 1;
						topCard = compHand[i]; 
						cout << discard.Push(topCard) << endl; 
						cout << currAmt << endl;
						swap(compHand[i], compHand[currAmt]);
						for( int i = 0; i < currAmt; i++)
							compHand[i].Show(); 
						system("pause");
						break;
					}
				}//end the second loop
#pragma endregion 
			system("cls"); //Resets the screen to clean things up. 

			//First and foremost, check if the game is over...
		 
			if ( currentAmt <= 0 || currAmt <= 0 || deck.IsEmpty() == true )
				break; 

			} //end main game loop
			if( currentAmt <= 0 || currentAmt < currAmt )
			{
				//Probably will want to add more to the player score here, too. 
				cout << FS::Green << "YOU WON!!!!";

				//Now add to the player score and save it here.  
				playerScore += 200 + currAmt*20; 
				hum.SetScore(playerScore);
				outfile << hum.GetName() << endl;
				outfile << playerScore << endl; //Saves name and score here.
				outfile.close();
			}else{
				cout << FS::Red << "You lost, pal...";
			}//endif 

			cout << FS::Default << endl; 

			//Create a temp array to see if they want to play again
			int yesOrNo;
			cout << "Do you want to play again?\n"
				 << "1) Yes\n"
				 << "2) No\n"
				 << "(Type 1 or 2...)\n";
			if(cin >> yesOrNo && (yesOrNo == 1 || yesOrNo == 2))
			{
				if(yesOrNo == 1){
					m_state = GAME_INIT; // Set the state back again. (Yay! They loved it!)
					//Again, just in case...
					currentAmt = 5; 
					currAmt = 5; 
				}else if(yesOrNo == 2){
					//We're going to set the current amounts back just to see if we can prevent crashing
					currentAmt = 5; 
					currAmt = 5; 
					//....And hopefully that helps
					m_state = GAME_END; // Set the state to End.
				}//endif

			} else {
				cin >> yesOrNo;
			} // end if
			//m_state = GAME_END; // Just in case, set the state to end the game here. (May not need it now?)
			break; //Our default break thingy... 
		case GAME_END:
			// The game is over, change the bool to stop the loop.
			run = false;
			break;
		}
	}
}


void MakeChoice(void)
{
	//Now give the player an option...
	cout << endl;
	cout << "Which card will you play? (# Represents your hand in order from left to right) " << endl;
	cout << " 1) Card 1\n "
			<< "2) Card 2\n "
			<< "3) Card 3\n "
			<< "4) Card 4\n "
			<< "5) Card 5\n "
			<< "6) Card 6\n "
			<< "7) Card 7\n "
			<< "8) Card 8\n ";
	cout << "Enter a number:"; 
}

void MakeMove(void)
{
	cout << endl; 
	cout << "What will you do?\n"
		 << "1) Play a card\n"
		 << "2) Draw a card\n";
	cout << "Enter a number:"; 
}


#pragma region test
//duighdfgjkdghdfkghdfgjkhghdfk
//Just tested to see if this thingy actually works.
#pragma endregion