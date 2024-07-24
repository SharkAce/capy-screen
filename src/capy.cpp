#include "capy.hpp"

Capy::Capy() {
	if (!spriteSheet.loadFromFile(spriteSheetLocation)) std::terminate();
	if (!shadowTexture.loadFromFile(shadowLocation)) std::terminate();
	animationFrame = 0;
	currentAnimation = 0;
	animationTimer.restart();
}

void Capy::draw(sf::RenderWindow& window, const sf::Vector2u& position, bool flipX) {
	sf::Sprite capySprite = getSprite();
	sf::Sprite shadowSprite;
	shadowSprite.setTexture(shadowTexture);

	capySprite.setOrigin(capySprite.getLocalBounds().width / 2, 0);
	capySprite.setPosition(position.x, position.y);
	capySprite.setScale(flipX ? 2.3 : -2.3, 2.3);

	shadowSprite.setOrigin(shadowSprite.getLocalBounds().width / 2, 0);
	shadowSprite.setPosition(position.x + (flipX ? -10 : 10), position.y + 60);
	shadowSprite.setScale(1.6, 1.5);
	shadowSprite.setColor(sf::Color(255, 255, 255, 100));

	window.draw(shadowSprite);
	window.draw(capySprite);
}

void Capy::update() {
	if (animationTimer.getElapsedTime().asMilliseconds() <= frameTime) return;

	animationTimer.restart();
	if (animationFrame + 1 > animationSizes.at(currentAnimation)) {
		if (!targetAnimations.empty()) {
			currentAnimation = targetAnimations.front();
			targetAnimations.pop();
		}
		animationFrame = 0;
	} else {
		animationFrame ++;
	}
}

void Capy::startStanding() {
	animationFrame = 0;
	switch(currentAnimation) {
		case 2: 
			currentAnimation = 3;
			targetAnimations.push(0);
			break;
		case 5:
			currentAnimation = 6;
			targetAnimations.push(0);
			break;
		default:
			targetAnimations.push(0);
	}
}

void Capy::startWalking() {
	animationFrame = 0;
	switch(currentAnimation) {
		case 2: 
			currentAnimation = 3;
			targetAnimations.push(7);
			break;
		case 5:
			currentAnimation = 6;
			targetAnimations.push(7);
			break;
		default:
			currentAnimation = 7;
	}
}

void Capy::startSitting() {
	animationFrame = 0;
	currentAnimation = 1;
	targetAnimations.push(2);
}

void Capy::startMunching() {
	animationFrame = 0;
	currentAnimation = 4;
	targetAnimations.push(5);
}


sf::Sprite Capy::getSprite() {
	sf::Rect<int> spriteRect;
	spriteRect.height = spriteSize;
	spriteRect.width = spriteSize;
	spriteRect.left = animationFrame * spriteSize;
	spriteRect.top = currentAnimation * spriteSize + yOffset;

	return sf::Sprite(spriteSheet, spriteRect);
}
