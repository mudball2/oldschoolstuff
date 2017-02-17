#include "Computer.h"


CComputer::CComputer(void)
{
	//m_szComputerName = new char[5][MAX_LEN];  
}


CComputer::~CComputer(void)
{
}


void CComputer::Show(void)
{
	//Enter a return value here  
	char* m_szComputerName[5] = {"Dealer", "Josh", "Anna", "David", "Michelle"}; 
	srand(unsigned int (time(0))); 
	int randName = rand()%5;

	cout << m_szComputerName[0]; 


	//Enter the stuff here 
	//CPlayer::Show(); 
}