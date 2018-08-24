#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Hitbox.h"
#include "MainMonkey.h"
#include "ItemPool.h"
#include "Enemy.h"

const unsigned int TOTAL_MISSILES = 10;
const unsigned int TOTAL_STARS = 25;
const unsigned int TOTAL_ENEMIES = 5;

class BulletHellApp : public aie::Application {
public:

	BulletHellApp();
	virtual ~BulletHellApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();


protected:
	const float m_moveSpeed = 6.0f;

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	aie::Texture*		m_missileTexture;
	aie::Texture*		m_starTexture;

	

	MainMonkey* monkey1;
	Enemy*		enemies[TOTAL_ENEMIES];

	// return a random number, taking in the minimum and maximum
	float getRandBetween(float min, float max);

	// each item had an "add" and "remove" function where I needed them
	void addMissile();
	void addStar();
	void addEnemy();
	void removeMissile(int iterator);
	void removeEnemy(int iterator);

	// sets hitbox of each missile, kept in here because missiles do not yet have a class
	void setMissileBox();
	HitBox* m_missileHit[TOTAL_MISSILES];

	ItemPool* m_stars[TOTAL_STARS];

	ItemPool* m_funkyShot[TOTAL_MISSILES];

	int m_missileCount = 0;
	int m_starCount = 0;
	int m_enemyCount = 0;

	float m_missilePosX;
	float m_missilePosY;


};