#include "Enemy.h"
#include "Texture.h"
//#include <Random>

Enemy::Enemy(float windowWidth, float windowHeight)
{
	m_enemyTexture = new aie::Texture("../bin/textures/ship.png");
	pool.posY = windowHeight;
	pool.posX = windowWidth * 0.25f;
	pool.rotate = 3.1415926f;

	setHitBox();
}


Enemy::~Enemy()
{
	delete m_enemyTexture;
}

aie::Texture * Enemy::getTexture()
{
	return m_enemyTexture;
}

void Enemy::setHitBox()
{
	m_hitBox->top = pool.posY + (m_height / 2);
	m_hitBox->bottom = pool.posY - (m_height / 2);
	m_hitBox->right = pool.posX + (m_width / 2);
	m_hitBox->left = pool.posX - (m_width / 2);
}
