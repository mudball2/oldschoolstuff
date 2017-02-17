//#include "windows.h"
#pragma comment (lib, "user32.lib")
#include "MenuItem.h"

#define NUM_ITEMS 4

class Menu
{
	MenuItem m_items[NUM_ITEMS];
	int m_index;
public:
	Menu() { m_index = 0; }
	void load();
	void display() const;
	void input();
};