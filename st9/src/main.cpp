#include <chrono>
#include <random>
#include <array>
#include <SFML/Graphics.hpp>


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

int Main(int argc, char**argv) {
	sf::Event event{};

	std::random_device s;
	std::mt19937_64 random_engine((std::random_device()()));
	srand(static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()));
	sf::RenderWindow window(sf::VideoMode(720, 480), "window", sf::Style::Close);

	while (window.isOpen()) {


		while (window.pollEvent(event)) {
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}
		window.clear();
		window.display();
	}
	return 0;
}