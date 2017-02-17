#include "Computer.h"


CComputer::CComputer(void)
{
	m_szcomName = "Computer";
	//SetName("Name"); 
}


CComputer::~CComputer(void)
{
	//Nothing to deallocate here 
}

/*
//We create a modifier or accessor for the computer name data member
void CComputer::SetName(const char* szName)
{
	strcpy_s(comName, strlen(comName)+1, szName); 
}

char CComputer::GetName(void)
{
	return comName[NAME_LEN]; //Returns this for now. 
}*/ //For now, this is pissing me off, so I'm going to try again later and continue with a straight forward approach...

void CComputer::Show(void)
{
	//Should simply call the base class's Show() function 
	CPlayer::Show(); 
	cout << m_szcomName << endl;
}