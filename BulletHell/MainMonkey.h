#pragma once

#include "Renderer2D.h"
#include "Hitbox.h"

class MainMonkey
{
public:
	MainMonkey();
	~MainMonkey();

	void moveMonkey();

	aie::Texture* getTexture();

	float m_monkeyPosX;
	float m_monkeyPosY;
	float m_height = 124.3;
	float m_width = 79.5;

	HitBox* m_hitbox = new HitBox;
private:
	aie::Texture* m_funkyTexture;
};

