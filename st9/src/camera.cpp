#include "camera.h"
#include "Player.h"

camera::camera(sf::RenderWindow* w) {
	wPtr = w;
	pPtr = nullptr;
}
camera::camera(sf::RenderWindow* w, Player* p) {
	wPtr = w;
	pPtr = p;
}
camera::~camera() {

}
void camera::setPlayer(Player* p) {
	pPtr = p;
}
Player* camera::getPlayer() {
	return pPtr;
}
void camera::moveCamToPlayer() {
	wPtr->setView(sf::View(sf::Vector2f(pPtr->get_pos()[0], pPtr->get_pos()[1]), sf::Vector2f(1920, 1080)));	//Methode um die Player Position zu bekommen unbekant 
}
void camera::moveToPos(int x, int y) {
	wPtr->setView(sf::View(sf::Vector2f(x, y), sf::Vector2f(1920, 1080)));
}
void camera::moveToPos(sf::Vector2f v) {
	wPtr->setView(sf::View(v, sf::Vector2f(1920, 1080)));
}
void camera::moveToPos(sf::View v) {
	wPtr->setView(v);
}