#include <chrono>
#include <random>
#include <array>
#include <SFML/Graphics.hpp>
#include "Random.h"
#include "Log.h"

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

int Main(int argc, char** argv) {
    sf::Event event{};
    Blank::Log::Init();
    Blank::Random::Init();
    LOG_ERROR("Hallo welt");
    sf::RenderWindow window(sf::VideoMode(720, 480), "window", sf::Style::Close);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
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