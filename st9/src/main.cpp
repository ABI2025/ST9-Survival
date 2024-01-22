#include <chrono>
#include <execution>
#include <SFML/Graphics.hpp>
#include "Utils/Utils.h"
#include <imgui.h>

#include "Camera.h"
#include "Game.h"
#include "imgui-SFML.h"
#include "Player.h"
#include "Game.h"

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
    Game *game = Game::erstelleGame();
    game->runGame(0);
  //  Utils::Init();
  //  Utils::ScopedTimer scoped_timer("scoped");
  //std::vector<uint32_t> arr;
  //arr.reserve(10);
  //for (int i = 0; i < 100; i++)
  //      arr.push_back(Utils::Random::UInt());
  //for (int i = 0; i < 100; i++)
  //      LOG_INFO("arr[{}]: {}", i, arr[i]);
  //uint32_t max = 0;
  //for (uint32_t i = 0; i < arr.size(); i++) max = (i > arr[i]) ? arr[i] : max;
  //LOG_ERROR("max: {}", max);
  //int8_t s = 65;
  //LOG_INFO("{0} {0} {0} {0} {0}", s);
  //std::for_each(std::execution::par, arr.begin(), arr.end(), [](uint32_t z)
  //{
  //    LOG_INFO("{}", z);
  //});

   /* sf::Event event{};
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
    sf::RenderWindow window(sf::VideoMode(2560, 1440), "Fenster");
    if (!ImGui::SFML::Init(window)) return -1;
    int k = Game::erstelleGame()->renderMap(window);
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    window.setFramerateLimit(60);
    Utils::Timer t;
    Player p;
    Camera c(&window,&p);
    //Utils::Log::GetLogger()->set_level(spdlog::level::info);
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("Resources/background__r172093591.jpg")) {
        // Handle loading failure
        return -1;
    }
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);
    
    c.move_cam_to_player();
    p.set_pos({ window.getSize().x / 2.0f -50.0f, window.getSize().y / 2.0f - 50.0f, 0 });
    float speed_scalar = 1;
    sf::Clock deltaClock;
    int x = 0, y = 0;
    while (window.isOpen())
    {
		//LOG_INFO("window view x:{} y:{}",window.getView().getCenter().x, window.getView().getCenter().y);
		//LOG_INFO("player center x:{} y:{}",p.get_pos().x,p.get_pos().y);
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                x = event.size.width;
                y = event.size.height;
                c.set_window_size(x, y);
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
            default:

                break;
            }
        }
        ImGui::SFML::Update(window, deltaClock.restart());
        glm::vec3 dir (0);
    
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            dir += glm::vec3(-1,0,0);
        }
    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            dir += glm::vec3(1, 0, 0);
        }
    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            dir += glm::vec3(0, -1, 0);
        }
    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            dir += glm::vec3(0, 1, 0);
        }
        if(dir != glm::vec3{0,0,0}) //um undefiniertes verhalten zu verhindern und zur optimierung
        {
           
        	/*LOG_TRACE("before normalize x:{:03.2f} y:{:03.2f} z:{:03.2f}", dir.x, dir.y, dir.z);
            dir = glm::normalize(dir);
            /*LOG_TRACE("after normalize x:{:03.2f} y:{:03.2f} z:{:03.2f}", dir.x, dir.y, dir.z);
            dir *= speed_scalar;
           /* LOG_TRACE("after multiplying with 5 x:{:03.2f} y:{:03.2f} z:{:03.2f}", dir.x, dir.y, dir.z);

        }

        glm::vec3 newpos = dir + p.get_pos();
    	p.set_pos(newpos);
        p.update();
        shader.setUniform("iResolution", sf::Glsl::Vec2{ 2560,1440 });
        shader.setUniform("iTime", t.Elapsed());
		c.move_cam_to_player();

        ImGui::Begin("Hello, world!");
        ImGui::SliderFloat("scale",&speed_scalar,1,50);
        ImGui::End();
    	ImGui::Begin("Hello, world2!");
        ImGui::SliderFloat("scale2",&speed_scalar,1,50);
        ImGui::End();
        LOG_TRACE("x:{:03.2f} y:{:03.2f} z:{:03.2f}", p.get_pos().x, p.get_pos().y, p.get_pos().z);

        window.clear();
        window.draw(rect);
        window.draw(backgroundSprite);
        window.draw(p, &shader);

        ImGui::SFML::Render(window);
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }
        */
        //window.display();
    //}
   // ImGui::SFML::Shutdown();

    return 0;
}
