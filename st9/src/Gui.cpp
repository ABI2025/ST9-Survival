#include "Gui.h"

#include "imgui-SFML.h"
#include "imgui.h"
#include "../Resources/images/Roboto-regular.embed"

bool init_sfml_imgui(sf::RenderWindow& window)
{
	
    if (!ImGui::SFML::Init(window)) return false;

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows // funktioniert nicht weil die sfml backends das nicht haben

    ImFontConfig font_config;
    font_config.FontDataOwnedByAtlas = false;
    ImFont* roboto_font = io.Fonts->AddFontFromMemoryTTF((void*)g_RobotoRegular, sizeof(g_RobotoRegular), 20.0f, &font_config);
    io.FontDefault = roboto_font;
    ImGui::SFML::UpdateFontTexture();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
    return true;
}

Gui::Gui(const std::initializer_list<GuiElement> gui_elements) : m_elements(gui_elements)
{ 
}
