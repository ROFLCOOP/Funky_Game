#pragma once
#include "Renderer2D.h"
#include "Hitbox.h"
#include "ItemPool.h"

class Enemy
{
public:
	Enemy(float windowWidth, float windowHeight);
	~Enemy();

	aie::Texture* getTexture();


	ItemPool pool;
	const float m_height = 50;
	const float m_width = 40;

	void setHitBox();

	HitBox* m_hitBox = new HitBox;

protected:
	aie::Texture* m_enemyTexture;
};

