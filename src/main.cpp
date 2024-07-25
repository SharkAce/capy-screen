#include <cstdlib>
#include <ctime>
#include "capy.hpp"

constexpr float imageScalling = 3.f;
constexpr float actionTime = 10.f;
constexpr float idleTime = 3.f;
constexpr int frameRate = 30;

sf::Vector2u randomLocation(sf::IntRect bounds) {
	unsigned int x = bounds.left + std::rand() % bounds.width;
	unsigned int y = bounds.top + std::rand() % bounds.height;
	return sf::Vector2u(x, y);
}

void updateLocation(sf::Vector2u& currentLocation, const sf::Vector2u& targetLocation) {
	if (currentLocation.x < targetLocation.x) currentLocation.x++;
	if (currentLocation.x > targetLocation.x) currentLocation.x--;
	if (currentLocation.y < targetLocation.y) currentLocation.y++;
	if (currentLocation.y > targetLocation.y) currentLocation.y--;
}

int main() {
	std::srand(std::time(0));

	sf::Texture background;
	if (!background.loadFromFile("res/background.png")) std::terminate();
	sf::Sprite backgroundSprite(background);
	backgroundSprite.setScale(imageScalling, imageScalling);

	int windowWidth = backgroundSprite.getGlobalBounds().width;
	int windowHeight = backgroundSprite.getGlobalBounds().height;
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "CapyScreen");
	window.setFramerateLimit(frameRate);

	Capy capy;

	auto mouvementBounds = sf::IntRect(250, 265, 550, 150);
	bool actionStarted = false;
	bool idle = true;
	bool flipX = false;
	sf::Vector2u targetLocation = randomLocation(mouvementBounds);
	sf::Vector2u currentLocation = randomLocation(mouvementBounds);
	sf::Clock actionClock;
	sf::Clock idleClock;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		if (actionStarted) {
			if (actionClock.getElapsedTime().asSeconds() > actionTime) {
				actionStarted = false;
				idle = true;
				capy.startStanding();
				idleClock.restart();
			}
		} else if (idle) {
			if (idleClock.getElapsedTime().asSeconds() > idleTime) {
				idle = false;
				targetLocation = randomLocation(mouvementBounds);
				flipX = targetLocation.x > currentLocation.x;
				capy.startWalking();
			}
		} else if (currentLocation != targetLocation) {
			updateLocation(currentLocation, targetLocation);
		} else {
			if (std::rand() % 2 == 0) {
				capy.startMunching();
			} else {
				capy.startSitting();
			}
			actionStarted = true;
			actionClock.restart();
		}

		capy.update();
		window.clear();
		window.draw(backgroundSprite);
		capy.draw(window, currentLocation, flipX);
		window.display();
	}

	return 0;
}
