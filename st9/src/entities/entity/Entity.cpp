#include "Entity.h"
#include <fstream>
#include <iostream>

#include "Utils/Log.h"

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

glm::vec3 Entity::get_pos() const
{
	return m_pos;
}

void Entity::set_pos(const glm::vec3 i_pos)
{
	m_pos = i_pos;
}

sf::Sprite& Entity::get_sprite()
{
	return m_sprite;
}

glm::vec3 Entity::get_hit_box() const
{
	return m_hitbox;
}

void Entity::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}

void Entity::take_damage(const double damage)
{
	
	m_health -= damage;
	if (m_health < 0)
		m_health = 0;
	else if (m_health > 20)
		m_health = 20;
}

double Entity::get_hp() const
{
	return m_health;
}
