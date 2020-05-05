#include "Opening.h"
#include "ProjectConstants.h"

OpeningScreen::OpeningScreen() {
}

OpeningScreen::~OpeningScreen() {
}

void OpeningScreen::init() {
	m_img.load(ProjectConstants::IMG_PATH_SCREEN_OPENING);
}

void OpeningScreen::render() {
	ofSetRectMode(OF_RECTMODE_CORNER);
	m_img.draw(0, 0);
}