﻿#include "Player.h"

#define PLAYER_FIGHT_RATE 20
#define Player_RATE 10
#define HURT_STATE 25

#define SPEED_X 0.3f
#define SPEED_Y 0.4f
#define MAX_HEIGHT 100.0f
#define A 0.005f
Player::Player(void) : DynamicObject()
{
}

Player::Player(int _posX, int _posY) : DynamicObject(_posX, _posY, 0, -SPEED_Y, EnumID::Player_ID)
{
	_action = Action::Idle;
	_a = 0.005f;
	// vị trí cầu thang
	posX1 = 160;
	posY1 = 64;
	_allowPress = true;
	_hasSit = false;
	_hasJump = false;
	_hasStair = true;
	_upStair = false;
	_downStair = false;
	_stair = NULL;
	playerJump = new GSprite(Singleton::getInstance()->getTexture(EnumID::Player_ID), 4, 4, 300);
	fightingSprite = new GSprite(Singleton::getInstance()->getTexture(EnumID::Player_ID), 5, 8, 1000 / PLAYER_FIGHT_RATE);
	fightingSittingSprite = new GSprite(Singleton::getInstance()->getTexture(EnumID::Player_ID), 15, 18, 1000 / PLAYER_FIGHT_RATE);
	playerStair = new GSprite(Singleton::getInstance()->getTexture(EnumID::Player_ID), 10, 13, 320);
	morningStar = new MorningStar(_posX, _posY, 0, 0, EnumID::MorningStar_ID, 1000 / PLAYER_FIGHT_RATE);
	Initialize();
}

void Player::Update(int deltaTime)
{
	switch (_action)
	{
	case Action::Run_Left:
		sprite->Update(deltaTime);
		break;
	case Action::Run_Right:
		sprite->Update(deltaTime);
		break;
	case Action::Fight:
		this->OnFight(deltaTime);
		break;
		/*case Action::Idle:
		sprite->SelectIndex(0);
		break;*/
	}
	if (_hasStair)
	{
		UpdatePlayerStair(deltaTime);
	}
	posX += vX * deltaTime;
#pragma region Xu ly nhay
	if (_hasJump)
	{
		sprite->SelectIndex(4);
		posY += vY * deltaTime + 0.5* deltaTime * deltaTime * _a;
		if (vY > -0.6f)
			vY += _a * deltaTime;
		if (posY < 64)//xét va chạm thì thay tại đây
		{
			posY = 64;// xét va chạm thì thay tại đây
			sprite->SelectIndex(0); // khi rơi xuống, posY sẽ <0, nên pải đưa về selectIndex = 0 
			_a = 0; // khi chạm đất rồi, a =0;
			_hasJump = false;// chạm đất r thì không còn nhảy
		}
		return;
	}
#pragma endregion

	//posY += vY *deltaTime;
}
void Player::Draw(GCamera* camera)
{
	D3DXVECTOR2 center = camera->Transform(posX, posY);
	// đi sang phải
	if (vX > 0 || _vLast > 0)
	{
		if (_action == Action::Fight) {
			if (!_hasSit) {
				fightingSprite->DrawFlipX(center.x, center.y);
				
			}
			else {
				fightingSittingSprite->DrawFlipX(center.x, center.y);
				
			}
			morningStar->Draw(camera);
			// vẽ Fight rồi return luôn
			return;
		}
		sprite->DrawFlipX(center.x, center.y);
	}
	// đi sang trái
	else
	{
		if (_action == Action::Fight) {
			if (!_hasSit) {
				fightingSprite->Draw(center.x, center.y);
				
			}
			else {
				fightingSittingSprite->Draw(center.x, center.y);
				
			}
			morningStar->Draw(camera);
			return;
		}
		sprite->Draw(center.x, center.y);
	}
	if (_onStair)
	{
		playerStair->DrawFlipX(center.x, center.y);
		return;
	}


}
void Player::UpdatePlayerStair(int t)
{
//vị trí cầu thang: posX1 = 400, posY1=64 (đầu dưới).
	// posX2 = 480, posY2 = 128 (đầu trên)
	//if (!_onStair) // nếu không trên cầu thang thì đi lên được. tính khoảng cách
	//{
	//	if (_hasStair) // nếu có cầu thang thì xử lý lên xuống cầu thang được
	//	{
	//		rangeStair = posX - posX1;
	//	}
	//	else if (_outStair) // nếu ra ngoài cầu thang
	//	{
	//		sprite->SelectIndex(0);
	//		_kindStair = EKindStair::None_Kind;
	//		_action = Action::Idle;
	//	}
	//}
	//else //  trên cầu thang ->đi lên, đi xuống đc.
	//{

	//}
	if (_hasStair)
	{
		rangeStair = posX - posX1;
	}
	
	playerStair->SelectIndex(12);
	//sprite->Update(t);
}
void Player::TurnLeft()
{
	if (_allowPress)
	{
		if (_hasJump)
			return;
		if (_hasSit)
			return;
		vX = -SPEED_X;
		_vLast = vX;
		_hasSit = false;
		_action = Action::Run_Left;
	}
}
void Player::TurnRight()
{
	if (_allowPress)
	{
		if (_hasJump)
			return;
		if (_hasSit)
			return;
		vX = SPEED_X;
		_vLast = vX;
		_hasSit = false;
		_action = Action::Run_Right;
	}
}
void Player::Jump()
{
	if (_allowPress)
	{
		if (_hasSit)
			return;
		if (!_hasJump)
		{
			//vY = -10;
			posY += 1;
			_a = -A;
			vY = sqrt(-2 * _a*MAX_HEIGHT);
			//_heightJump = 0;
			sprite->SelectIndex(4);
			_action = Action::Jump;
			_hasJump = true;
		}
	}
}
void Player::Fall()
{
}

void Player::Sit()
{
	if (_allowPress && !_hasSit && !_hasJump)
	{
		if (_action == Action::Fight)
			return;
		sprite->SelectIndex(4);
		vX = 0;
		posY -= 18;
		_hasSit = true;
		_action = Action::Sit;
	}
}
void Player::Fight() {
	if (_allowPress)
	{
		if (_action == Action::Fight)
			return;
		if (!_hasJump)
			vX = 0;

		_action = Action::Fight;
	}
}
void Player::OnFight(int t)
{
	if (_hasSit) {
		fightingSittingSprite->Update(t);
	}
	else {
		fightingSprite->Update(t);
	}
	morningStar->Update(t);

	// Update the Vx of morningStar
	float morningStarVx = -1;
	if (vX > 0 || _vLast > 0)
		morningStarVx = -morningStarVx;
	morningStar->updateVx(morningStarVx);

	morningStar->updateXY(posX, posY);
	if (!_hasSit && fightingSprite->GetIndex() >= 8)
	{
		_action = Action::Idle;
		fightingSprite->Reset();
		morningStar->reset();
	}

	else if (_hasSit && fightingSittingSprite->GetIndex() >= 18)
	{
		_action = Action::Sit;
		fightingSittingSprite->Reset();
		morningStar->reset();
	}
}

void Player::Stop() {
	/*if (_hasJump == true)
	{
	}
	else
	{
	_action = Action::Idle;
	vX = 0;
	}*/
	// Xử lý tạm thôi
	vX = 0;
	switch (_action)
	{
	case Action::Idle:
	case Action::Fight:
	case Action::Fall:
		return;
	}
	if (_hasSit)
	{
		posY = 64;// va chạm thay tại đây.
		_hasSit = false;
	}
	if ((_hasJump == true && posY == 64))
	{
		_hasJump = false;
		sprite->SelectIndex(0);
		_a = 0;
	}
	_action = Action::Idle;
	sprite->SelectIndex(0);
}
void Player::UpStair()
{
	if (_allowPress && _hasStair)
	{
		if (abs(rangeStair) < 20)
		{
			_upStair = true;
			//posX += 16;
			//posY += 3;
			//sprite->Update(1);
			posY += 3;
			playerStair->SelectIndex(13);
			//vY = sqrt(-2 * _a*MAX_HEIGHT);
		}
	}
}
bool Player::OnStair()
{
	return false;
}
Player::~Player(void)
{
}
D3DXVECTOR2* Player::getPos()
{
	return new D3DXVECTOR2(this->posX, this->posY);
}