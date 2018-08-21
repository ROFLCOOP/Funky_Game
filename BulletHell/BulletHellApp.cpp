#include "BulletHellApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

BulletHellApp::BulletHellApp() {

}

BulletHellApp::~BulletHellApp() {

}

bool BulletHellApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	monkey1 = new MainMonkey;

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);
	m_missileTexture = new aie::Texture("../bin/textures/cartoon_Missile.png");

	monkey1->m_monkeyPosX = getWindowWidth() * 0.5f;
	monkey1->m_monkeyPosY = getWindowHeight() * 0.5f;


	for (unsigned int i = 0; i < TOTAL_MISSILES; i++)
	{
		m_funkyShot[i] = new Missile;
	}

	return true;
}

void BulletHellApp::shutdown() {

	for (unsigned int i = 0; i < TOTAL_MISSILES; i++)
	{
		delete m_funkyShot[i];
	}
	delete m_font;
	delete m_2dRenderer;
}

void BulletHellApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_W))
	{
		monkey1->m_monkeyPosY += 4;
	}

	if (input->isKeyDown(aie::INPUT_KEY_S))
	{
		monkey1->m_monkeyPosY -= 4;
	}

	if (input->isKeyDown(aie::INPUT_KEY_D))
	{
		monkey1->m_monkeyPosX += 4;
	}

	if (input->isKeyDown(aie::INPUT_KEY_A))
	{
		monkey1->m_monkeyPosX -= 4;
	}

	for (int i = 0; i < m_missileCount; i++)
	{
		if (m_funkyShot[i]->posX > getWindowWidth() || m_funkyShot[i]->posX < 0 || m_funkyShot[i]->posY > getWindowHeight() || m_funkyShot[i]->posY < 0)
		{
			m_funkyShot[i]->inUse = false;
			std::swap(m_funkyShot[i], m_funkyShot[--m_missileCount]);
		}
	}
	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
	{
		addMissile();
	}

	for (int i = 0; i < m_missileCount; i++)
	{
		m_funkyShot[i]->posY += 10.0f;
	}
	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void BulletHellApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	m_2dRenderer->drawSprite(monkey1->getTexture(), monkey1->m_monkeyPosX, monkey1->m_monkeyPosY, monkey1->m_width, monkey1->m_height);
	
	for (int i = 0; i < m_missileCount; i++)
	{
		if (m_funkyShot[i]->inUse)
		{
			m_2dRenderer->drawSprite(m_missileTexture, m_funkyShot[i]->posX, m_funkyShot[i]->posY, 30.0f, 55.0f, 0.0f, 0.1f);
		}
	}

	// done drawing sprites
	m_2dRenderer->end();
}

void BulletHellApp::addMissile()
{
	if (m_missileCount < TOTAL_MISSILES)
	{
		m_funkyShot[m_missileCount]->inUse = true;
		m_funkyShot[m_missileCount]->posX = monkey1->m_monkeyPosX + 25.0f;
		m_funkyShot[m_missileCount]->posY = monkey1->m_monkeyPosY + 60.0f;
		m_missileCount++;
	}
}
