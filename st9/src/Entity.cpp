#include "Entity.h"
#include <fstream>
#include <iostream>

Entity::Entity() {
	//std::ifstream file("Stats.txt");
	//std::string line;
	//int currentLine = 0;
	//std::string texturePath;

	//if (file.is_open()) {
	//    while (std::getline(file, line)) {
	//        ++currentLine;
	//        if (currentLine == id) {
	//            texturePath = line; // Speichert den Pfad aus der Datei
	//            break;
	//        }
	//    }
	//    file.close();
	//    if (!texturePath.empty()) {
	//        sf::Texture texture;
	//        if (texture.loadFromFile(texturePath)) {
	//            m_sprite.setTexture(texture);
	//        }
	//        else {
	//            std::cerr << "Failed to load texture: " << texturePath << std::endl;
	//        }
	//    }
	//}
	//else {
	//    std::cerr << "Unable to open file: " << id << std::endl;
	//}
}
Entity::~Entity()
{

}

glm::vec3 Entity::get_pos()
{
	return m_pos;
}

void Entity::set_pos(glm::vec3 i_pos)
{
	m_pos = i_pos;
}

sf::Sprite& Entity::get_sprite()
{
	return m_sprite;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}
