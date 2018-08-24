#include "BulletHellApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <cassert>
#include <random>

BulletHellApp::BulletHellApp() {

}

BulletHellApp::~BulletHellApp() {

}

bool BulletHellApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	monkey1 = new MainMonkey(getWindowHeight(), getWindowWidth());

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("font/consolas.ttf", 32);
	m_missileTexture = new aie::Texture("textures/cartoon_Missile.png");
	m_starTexture = new aie::Texture("textures/Star-3.png");

	monkey1->m_monkeyPosX = getWindowWidth() * 0.5f;
	monkey1->m_monkeyPosY = getWindowHeight() * 0.5f;

	for (unsigned int i = 0; i < TOTAL_ENEMIES; i++)
	{
		enemies[i] = new Enemy(getWindowWidth(), getWindowHeight());
	}

	for (unsigned int i = 0; i < TOTAL_MISSILES; i++)
	{
		m_funkyShot[i] = new ItemPool;
		m_missileHit[i] = new HitBox;
	}
	for (unsigned int i = 0; i < TOTAL_STARS; i++)
	{
		m_stars[i] = new ItemPool;
	}

	return true;
}

void BulletHellApp::shutdown() {

	for(unsigned int i = 0; i < TOTAL_ENEMIES; i++)
	{
		delete enemies[i];
	}
	for (unsigned int i = 0; i < TOTAL_MISSILES; i++)
	{
	delete m_funkyShot[i];
	delete m_missileHit[i];
	}
	for (unsigned int i = 0; i < TOTAL_STARS; i++)
	{
		delete m_stars[i];
	}
	delete m_font;
	delete m_2dRenderer;
}

void BulletHellApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_W) && monkey1->m_hitbox->top < getWindowHeight())
	{
		monkey1->m_monkeyPosY += m_moveSpeed;
	}

	if (input->isKeyDown(aie::INPUT_KEY_S) && monkey1->m_hitbox->bottom > 0)
	{
		monkey1->m_monkeyPosY -= m_moveSpeed;
	}

	if (input->isKeyDown(aie::INPUT_KEY_D) && monkey1->m_hitbox->right < getWindowWidth())
	{
		monkey1->m_monkeyPosX += m_moveSpeed;
	}

	if (input->isKeyDown(aie::INPUT_KEY_A) && monkey1->m_hitbox->left > 0)
	{
		monkey1->m_monkeyPosX -= m_moveSpeed;
	}

	if (getRandBetween(0, 100) < 5)
	{
		addEnemy();
	}

	monkey1->setHitBox();

	for (int i = 0; i < m_missileCount; i++)
	{
		if (m_funkyShot[i]->posY > getWindowHeight())
		{
			removeMissile(i);
		}
	}
	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
	{
		addMissile();
	}

	for (unsigned int i = 0; i < m_starCount; i++)
	{
		if (m_stars[i]->posY < 0)
		{
			m_stars[i]->inUse = false;
			std::swap(m_stars[i], m_stars[--m_starCount]);
		}
	}
	if (rand() % 20 == 1)
	{
		addStar();
	}

	for (unsigned int i = 0; i < m_enemyCount; i++)
	{
		if (enemies[i]->pool.posY < 0)
		{
			removeEnemy(i);
		}
	}

	setMissileBox();

	for (unsigned int i = 0; i < m_enemyCount; i++)
	{
		for (unsigned int j = 0; j < m_missileCount; j++)
		{
			for (int t = m_missileHit[j]->left; t < m_missileHit[j]->right; t++)
			{
				if (enemies[i]->m_hitBox->bottom < m_missileHit[j]->top && enemies[i]->m_hitBox->top > m_missileHit[j]->top && enemies[i]->m_hitBox->left < t && enemies[i]->m_hitBox->right > t)
				{
					removeEnemy(i);
					removeMissile(j);
				}
			}
		}
	}

	for (unsigned int i = 0; i < m_missileCount; i++)
	{
		m_funkyShot[i]->posY += 10.0f;
	}
	for (unsigned int i = 0; i < m_starCount; i++)
	{
		m_stars[i]->posY -= 5/*getRandBetween(1.0f, 10.0f)*/;
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
	m_2dRenderer->drawText(m_font, "Press space to shoot", 0, 60, -0.1f);
	m_2dRenderer->drawText(m_font, "WASD to move", 0, 32, -0.1f);
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0, -0.1f);

	m_2dRenderer->drawSprite(monkey1->getTexture(), monkey1->m_monkeyPosX, monkey1->m_monkeyPosY, monkey1->m_width, monkey1->m_height);
	
	for (int i = 0; i < m_missileCount; i++)
	{
		if (m_funkyShot[i]->inUse)
		{
			m_2dRenderer->drawSprite(m_missileTexture, m_funkyShot[i]->posX, m_funkyShot[i]->posY, 24.01f, 53.69f, 0.0f, 0.1f);
		}
	}
	for (unsigned int i = 0; i < m_starCount; i++)
	{
		if (m_stars[i]->inUse)
		{
			m_2dRenderer->drawSprite(m_starTexture, m_stars[i]->posX, m_stars[i]->posY, 0, 0, 0, 0.2);
		}
	}
	for (unsigned int i = 0; i < m_enemyCount; i++)
	{
		if (enemies[i]->pool.inUse)
		{
			m_2dRenderer->drawSprite(enemies[i]->getTexture(), enemies[i]->pool.posX, enemies[i]->pool.posY, 0, 0, enemies[i]->pool.rotate);
			enemies[i]->pool.posY -= 2;
			enemies[i]->setHitBox();
		}
	}

	// done drawing sprites
	m_2dRenderer->end();
}

float BulletHellApp::getRandBetween(float min, float max)
{
	assert(min != max && min < max && "min must be less than max");

	int range = max - min + 1.0f;

	return (rand() % range) + min;
}

void BulletHellApp::addMissile()
{
	if (m_missileCount < TOTAL_MISSILES)
	{
		m_funkyShot[m_missileCount]->inUse = true;
		m_funkyShot[m_missileCount]->posX = monkey1->m_monkeyPosX + 25.0f;
		m_funkyShot[m_missileCount]->posY = monkey1->m_monkeyPosY + 60.0f;

		setMissileBox();

		m_missileCount++;
	}
}

void BulletHellApp::addStar()
{
	if (m_starCount < TOTAL_STARS)
	{
		m_stars[m_starCount]->inUse = true;
		m_stars[m_starCount]->posX = getRandBetween(0.0f, getWindowWidth());
		m_stars[m_starCount]->posY = getWindowHeight();
		m_starCount++;
	}
}

void BulletHellApp::addEnemy()
{
	if (m_enemyCount < TOTAL_ENEMIES)
	{
		float randomNum = getRandBetween(0, getWindowWidth());
		enemies[m_enemyCount]->pool.inUse = true;
		enemies[m_enemyCount]->pool.posY = getWindowHeight();
		
		enemies[m_enemyCount]->pool.posX = randomNum;
		
		m_enemyCount++;
	}
}

void BulletHellApp::removeMissile(int iterator)
{
	m_funkyShot[iterator]->inUse = false;
	if (m_missileCount > 0)
	{
		m_missileCount--;
	}
	std::swap(m_missileHit[iterator], m_missileHit[m_missileCount]);
	std::swap(m_funkyShot[iterator], m_funkyShot[m_missileCount]);
	setMissileBox();
}

void BulletHellApp::removeEnemy(int iterator)
{
	enemies[iterator]->pool.inUse = false;
	enemies[iterator]->setHitBox();
	std::swap(enemies[iterator], enemies[--m_enemyCount]);
	enemies[iterator]->setHitBox();
}

void BulletHellApp::setMissileBox()
{
	for (int i = 0; i < m_missileCount; i++)
	{
		m_missileHit[i]->top = m_funkyShot[i]->posY + 26.845f;
		m_missileHit[i]->bottom = m_funkyShot[i]->posY - 13.4225;
		m_missileHit[i]->right = m_funkyShot[i]->posX + 12.005;
		m_missileHit[i]->left = m_funkyShot[i]->posX - 12.005;
	}
}
