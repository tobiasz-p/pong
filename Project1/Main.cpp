#include <iostream>
#include <gameManager.h>
#include <SFML/Graphics.hpp>
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
//linker->system-> Okna (/SUBSYSTEM:WINDOWS)
using namespace std;

int main()
{	
	int windowWidth = 1024;
	int windowHeight = 768;
	gameManager c(windowWidth, windowHeight);
	c.Run();
	return 0;
}