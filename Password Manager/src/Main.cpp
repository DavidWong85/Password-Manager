#include "Menu.h"

#include <memory>

int main()
{
	unique_ptr<Menu> menu(new Menu());
	menu->menu();

	return 0;
}