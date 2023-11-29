#include <chrono>
#include <execution>
#include <SFML/Graphics.hpp>
#include "Utils/Utils.h"
#include <SFML/OpenGL.hpp>
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
    Utils::ScopedTimer scoped_timer("scoped_tt");
  //  std::vector<uint32_t> arr;
  //  arr.reserve(10);
  //  for (int i = 0; i < 100; i++)
  //      arr.push_back(Utils::Random::UInt());
  //  for (int i = 0; i < 100; i++)
  //      LOG_INFO("arr[{}]: {}", i, arr[i]);
  //  uint32_t max = 0;
  //  for (uint32_t i = 0; i < arr.size(); i++) max = (i > arr[i]) ? arr[i] : max;
  //  LOG_ERROR("max: {}", max);
  //  int8_t s = 65;
  //  LOG_INFO("{0} {0} {0} {0} {0}", s);
  //  std::for_each(std::execution::par, arr.begin(), arr.end(), [](uint32_t z)
  //  {
  //    LOG_INFO("{}", z);
  //  });

    sf::Event event{};
    std::string vertexShader =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "\n"
        "\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos, 1.0);\n"
        "}";

    std::string fragmentShader =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "uniform vec2 iResolution;\n"
        "uniform float iTime;\n"
        "\n"
        "\n"
        "void mainImage( out vec4 fragColor, in vec2 fragCoord )\n"
        "{\n"
        "    vec2 uv = fragCoord / iResolution.xy;\n"
        "    vec3 col = 0.5 + 0.5 * cos(iTime + vec3(uv.xyx) + vec3(0, 2, 4));\n"
        "    fragColor = vec4(col, 1.0);\n"
        "}\n"
        "void main()\n"
        "{\n"
        "    mainImage(FragColor, gl_FragCoord.xy);\n"
        "}";

    sf::Shader shader;
    
    shader.loadFromMemory(vertexShader, sf::Shader::Type::Vertex);
    shader.loadFromMemory(fragmentShader, sf::Shader::Type::Fragment);
	sf::RectangleShape rect ({2560,1440});
    rect.setFillColor(sf::Color::White);
    sf::RenderWindow window(sf::VideoMode(2560, 1440), "window", sf::Style::Fullscreen);
     Utils::Timer t;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if(event.key.code == sf::Keyboard::Escape)
                    window.close();
            default:
                
                break;
            }
        }
    
        shader.setUniform("iResolution", sf::Glsl::Vec2{ 2560,1440 });
        shader.setUniform("iTime", t.Elapsed());

        window.clear();
        window.draw(rect,&shader);
        window.display();
    }
    return 0;
}