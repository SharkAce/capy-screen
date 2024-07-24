#ifndef CAPY_HPP
#define CAPY_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>
#include <queue>

class Capy {
public:
	Capy();
	void draw(sf::RenderWindow& window, const sf::Vector2u& position, bool flipX);
	void update();

	void startStanding();
	void startSitting();
	void startMunching();
	void startWalking();

private:
	static constexpr int spriteSize = 64;
	static constexpr int yOffset = 80;
	static constexpr int frameTime = 140;

	sf::Clock animationTimer;
	sf::Sprite getSprite();

	const std::string spriteSheetLocation = "res/charlieTheCapybaraAnimationSheet.png";
	const std::string shadowLocation = "res/shadow.png";
	const std::vector<int> animationSizes = {7,2,7,2,3,7,3,7};

	sf::Texture spriteSheet;
	sf::Texture shadowTexture;

	std::queue<int> targetAnimations;
	sf::Vector2<int> spriteSelector;
	int& animationFrame = spriteSelector.x; 
	int& currentAnimation = spriteSelector.y; 
};

#endif
