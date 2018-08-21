#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Hitbox.h"
#include "MainMonkey.h"

const unsigned int TOTAL_MISSILES = 10;

class BulletHellApp : public aie::Application {
public:

	BulletHellApp();
	virtual ~BulletHellApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();


protected:
	MainMonkey* monkey1;


	void addMissile();

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	aie::Texture* m_missileTexture;



	struct Missile
	{
		bool inUse = false;
		float posX;
		float posY;
	};

	

	HitBox monkeyHitbox;

	Missile* m_funkyShot[TOTAL_MISSILES];

	unsigned int m_missileCount = 0;

	float m_missilePosX;
	float m_missilePosY;
};