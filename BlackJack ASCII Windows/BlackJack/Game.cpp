#include "Human.h"
#include "Computer.h" 
#include "Deck.h"


#include "Game.h"


Game::Game()
{
	m_state = GAME_INIT;
}
void Game::Run()
{
	// Bool to control whether the game should continue to run.
	bool run = true;
	
	// Initialize any objects here, because for some reason, the compiler doesn't like it anywhere else. 
	CDeck hand;
	CHuman player;
	CComputer* computer = new CComputer[4]; 

	//Initialize variables
	int call; //For your decisions in game
	dealerMoney = 10000; 
	playerMoney = 1000;

	betTotal = 0; 

	insured = false; 

	// Loop while our bool remains true.
	while(run)
	{
		switch(m_state)
		{
		case GAME_INIT:
			// Insert initialization code here.
			break;
		case GAME_PLAY:
			// Insert game play code here.

			
			
			player.Ask(); 
			cout << endl;
			cout << endl; 
			player.Show(); 
			hand.Shuffle(); 
			playerVal = hand.Draw();
			playerVal2 = hand.Draw();
			cout << endl;
			totPlayerVal = playerVal+playerVal2;
			cout << "Your total value is: "<< totPlayerVal << endl;
			cout << endl;
			cout << "Your cash amount is: " << playerMoney << endl; 
			cout << endl; 

			//Now show the computer's stuff. 
			computer[0].Show();
			cout << endl; 
			dealerVal = hand.Draw(); 
			cout << FS::Gray;
			hand.CDeck::hideCard = true; 
			dealerVal2 = hand.Draw(); 
			totDealerVal = dealerVal+dealerVal2; 
			hand.CDeck::hideCard = false; 
			cout << endl; 

			//Set a bet of 50 for each player
			playerMoney = playerMoney - 50;
			dealerMoney = dealerMoney - 50;
			betTotal = 100; 

			cout << "A bet of 50 has been set." << endl;
			cout << "You have " << playerMoney << " cash." << endl;

			//Now start the cooking...
			cout << FS::White << endl; 
			if (dealerVal == 11 )
			{
				int ins;
				for ( ; ; )
				{
					cout << "Do you want insurance?\n"
						 << "1) Yes\n"
						 << "2) No\n";
					cin >> ins;
					if (cin.good() && ( ins == 1 || ins == 2))
					{
						break;
					}else{
						cin.clear();
						cin.ignore(INT_MAX, '\n');
					}
				}
				insured = true;
				}

			cout << "\tIt's your call..."
				 << "\t(Input the corresponding value)\n"
				 << "\t1)Hit\n"
				 << "\t2)Stand\n"
				 << "\t3)Double Down\n"
				 << "\t0)Leave Game\n";

			cout << endl;
			for ( ; ; )
			{
				cout << "Type in your choice: ";
				cin >> call;
				if ( cin.good() && (call == 1 || call == 2 || call == 3 || call == 0))
					break;
				else
					cin >> call;

				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}

			if ( call == 1) {
				player.Show();
				playerVal3 = hand.Draw();
				totPlayerVal = totPlayerVal + playerVal3;
				cout << "Your total value is: " << totPlayerVal << endl;
				if(totPlayerVal > 21){
					cout << endl;
					cout << "You busted, "; 
					player.Show(); 
				} else if ( totPlayerVal < 21){
					cout << FS::White << endl; 
					cout << "\tIt's your call..."
						 << "\t(Input the corresponding value)\n"
						 << "\t1)Hit\n"
						 << "\t2)Stand\n"
						 << "\t3)Double Down\n"
						 << "\t0)Leave Game\n";

					cout << endl;
					for ( ; ; )
					{
						cout << "Type in your choice: ";
						cin >> call;
						if ( cin.good() && (call == 1 || call == 2 || call == 3 || call == 0))
							break;
						else
							cin >> call;

						cin.clear();
						cin.ignore(INT_MAX, '\n');
					}
					if( call == 1)
					{
						player.Show();
						playerVal3 = hand.Draw();
						totPlayerVal = totPlayerVal + playerVal3;
						cout << "Your total value is: " << totPlayerVal << endl;
					} else {
						call = 2; 
					} //endelseif
				}//endif
				call = 2; 
			} else if ( call == 2 ){
				//Now compare values and have computer make decisions if any. 
				if (totDealerVal < 21)
				{
					computer[0].Show();
					cout << " drew a card...." << endl; 
					dealerVal3 = hand.Draw(); 
					totDealerVal = totDealerVal + dealerVal3; 
				} else if (totDealerVal > totPlayerVal) {
					//Do nothing....
				} // endif
				//SetState(GAME_END);
			} else if ( call == 3 ){
				//Add more money to the "pot" and draw a card for the player. 
				
				playerMoney = playerMoney - 50;
				dealerMoney = dealerMoney - 50;

				betTotal = betTotal + 100; 
				playerVal4 = hand.Draw(); //Draw the card
				totPlayerVal = totPlayerVal + playerVal4; // Add to the player's value 

				call = 2; // Now make it the Dealer's turn...and see who wins! :O

			} else {
				SetState(GAME_END);
			} // end if

			//Decide winner
			if (totDealerVal == 21)
			{
				cout << endl;
				computer[0].Show();
				cout << "'s value is: " << totDealerVal;
				cout << endl;
				computer[0].Show();
				cout << " wins." << endl; 
			}

			if( totDealerVal >= totPlayerVal || totPlayerVal > 21){
				cout << endl;
				computer[0].Show();
				cout << "'s value is: " << totDealerVal;
				if ( totDealerVal <= 21 ){
					cout << endl; 
					computer[0].Show(); 
					cout << " wins." << endl; 
					dealerMoney += betTotal;  
					if ( totDealerVal == 21 && insured == true){
						insured = false;
						playerMoney += 50;
						betTotal = betTotal - 100; 
						cout << endl; 
						cout << "Your money is returned to you." << endl;
					} else if ( totDealerVal == 21 ){
						cout << endl;
						computer[0].Show();
						cout << " wins." << endl;
						dealerMoney += betTotal;
					} //endelseif
				} else {
					cout << endl;
					computer[0].Show();
					cout << " has busted..." << endl;
					
					cout << endl; 
					player.Show();
					cout << " wins!!!" << endl; 
					playerMoney += betTotal; 
				}//endif

			} else if(totPlayerVal > totDealerVal || totPlayerVal == 21){
				cout << endl;
				computer[0].Show();
				cout << "'s value is: " << totDealerVal;
				/*
				if( totDealerVal > 21){
					cout << endl;
					computer[0].Show();
					cout << " has busted..." << endl;
				}//endif
				*/
				cout << endl; 
				player.Show();
				cout << " wins!!!" << endl; 
				playerMoney += betTotal; 
			} // endif 
			
			int replayOrNot;
			for( ; ; )
			{
				cout << endl; 
				cout << "Go Again...?\n" 
					 << "1) Yes\n"
					 << "2) No\n";
				cin >> replayOrNot;
				if ( cin.good() && ( replayOrNot == 1 || replayOrNot == 2))
					break; 
				else
					cin >> replayOrNot;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}//endreplayloop

			if( replayOrNot == 1 )
			{
				SetState(GAME_PLAY);
				system("cls");
			}else{
				SetState(GAME_END);
			}
			break;
		case GAME_END:
			// The game is over, change the bool to stop the loop.
			run = false;
			break;
		}
	}
}