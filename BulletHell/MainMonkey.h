#pragma once

#include "Renderer2D.h"
#include "Hitbox.h"

class MainMonkey
{
public:
	MainMonkey(float windowHeight, float windowWidth);
	~MainMonkey();

	aie::Texture* getTexture();

	float m_monkeyPosX;
	float m_monkeyPosY;
	const float m_height = 124.3f;
	const float m_width = 79.5f;
	
	void setHitBox();

	HitBox* m_hitbox = new HitBox;
private:
	aie::Texture* m_funkyTexture;
};

