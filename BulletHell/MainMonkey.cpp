#include "MainMonkey.h"
#include "Texture.h"
#include "Input.h"
#include "Application.h"




MainMonkey::MainMonkey(float windowHeight, float windowWidth)
{
	//the following font should be changed on release
	m_funkyTexture = new aie::Texture("textures/main_Monkey.png");
	
	m_monkeyPosX = windowWidth * 0.5f;
	m_monkeyPosY = windowHeight * 0.5f;
	
	setHitBox();
}


MainMonkey::~MainMonkey()
{
	delete m_funkyTexture;
	delete m_hitbox;
}



aie::Texture* MainMonkey::getTexture()
{
	return m_funkyTexture;
}

void MainMonkey::setHitBox()
{
	m_hitbox->top = m_monkeyPosY + (m_height / 2);
	m_hitbox->bottom = m_monkeyPosY - (m_height / 2);
	m_hitbox->left = m_monkeyPosX - (m_width / 2);
	m_hitbox->right = m_monkeyPosX + (m_width / 2);
}
