#include "GameOverScreen.h"
#include "ProjectConstants.h"
#include "Game.h"

GameOverScreen::GameOverScreen() {
}

GameOverScreen::~GameOverScreen() {
}

void GameOverScreen::init() {
	m_img.load(ProjectConstants::IMG_PATH_SCREEN_GAMEOVER);
}

void GameOverScreen::render() {
	ofSetRectMode(OF_RECTMODE_CORNER);
	ofSetColor(ofColor::white);
	m_img.draw(0, 0);
}