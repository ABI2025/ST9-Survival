#include "Menu.h"

int Main(int argc, char** argv);


#if (defined(_WIN32) || defined (_WIN64)) && defined(DIST)

#include <windows.h>
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	return Main(__argc, __argv);
}

#else

int main(int argc, char** argv)
{
	return Main(argc, argv);
}

#endif

int Main(int argc, char** argv)
{
	Utils::Init();
	Menu::get_instance()->show_menu();
	Menu::delete_instance();
	return 0;
}