﻿#include "Singleton.h"
#include <string>
#include <sstream>
#include <windows.h>
#include <iostream>
#include <malloc.h>

using namespace std;

Singleton* Singleton::single = NULL;

Singleton* Singleton::getInstance()
{
	if (single == NULL)
		single = new Singleton();
	return single;
}

Singleton::Singleton()
{
	player = new GTexture("Resources/player.png", 8, 3, 24);

	morningStar = new GTexture("Resources/morningstar.png", 3, 3, 9);
	//playerDeath = new GTexture("Resources/playerdeath.png", 1, 1, 1);

	//Enemy
	Ghouls = new GTexture("Resources/enemy/1.png", 2, 1, 2);
	MedusaHeads = new GTexture("Resources/enemy/6.png", 2, 1, 2);
	Bats = new GTexture("Resources/enemy/0.png", 4, 1, 4);
	Panthers = new  GTexture("Resources/enemy/2.png", 4, 1, 4);
	Fishmen = new GTexture("Resources/enemy/3.png", 3, 1, 3);

	//ground
	candle = new GTexture("Resources/ground/1.png", 2, 1, 2);
	largeCandle = new GTexture("Resources/ground/0.png", 2, 1, 2);


	

	largeHeartItem = new GTexture("Resources/item/1.png", 1, 1, 1);
	smallHeartItem = new GTexture("Resources/item/0.png", 1, 1, 1);
	moneyBagItem = new GTexture("Resources/item/2.png", 3, 1, 3);
	crossItem = new GTexture("Resources/item/6.png", 1, 1, 1);
	morningStarItem = new GTexture("Resources/item/3.png", 1, 1, 1);
	fireBombItem = new GTexture("Resources/item/9.png", 1, 1, 1);
	daggerItem = new GTexture("Resources/item/4.png", 1, 1, 1);
	boomerangItem = new GTexture("Resources/item/8.png", 1, 1, 1);
	axeItem = new GTexture("Resources/item/7.png", 1, 1, 1);
	watchItem = new GTexture("Resources/item/5.png", 1, 1, 1);

	magicalCrystal = new GTexture("Resources/item/13.png", 2, 1, 2);

	phantombat = new GTexture("Resources/boss/0.png", 3, 1, 3);
	queenMedusaHeads = new GTexture("Resources/boss/1.png", 5, 1, 5);
	littleSnake = new GTexture("Resources/boss/2.png", 2, 1, 2);
	rewardItem = new GTexture("Resources/other/1.png", 3, 1, 3);
	water = new GTexture("Resources/other/2.png", 1, 1, 1);
	fireBall = new GTexture("Resources/fireball.png", 1, 1, 1);

	bgMenu = new GTexture("Resources/mainmenu.png", 1, 1, 1);


	helicopter = new GTexture("Resources/helicopter.png", 1, 1, 1);
	introBackground = new GTexture("Resources/intro.png", 1, 1, 1);
	bat = new GTexture("Resources/bat.png", 2, 1, 2);


	gameScore = new GTexture("Resources/blackboard.png", 1, 1, 1);
	hp = new GTexture("Resources/heal.png", 3, 1, 3);

	fallingCastle = new GTexture("Resources/FallingCastle.png", 3, 1, 3);
	


}

GTexture* Singleton::getTexture(EnumID id)
{
	switch (id)
	{
	case EnumID::Player_ID:
		return player;
	case EnumID::PlayerDeath_ID:
		return playerDeath;

		//Enemy
	case EnumID::Ghouls_ID:
		return Ghouls;
	case EnumID::MedusaHeads_ID:
		return MedusaHeads;
	case EnumID::Bats_ID:
		return Bats;
	case EnumID::Panthers_ID:
		return Panthers;
	case EnumID::Fishmen_ID:
		return Fishmen;


	case EnumID::FireBall_ID:
		return fireBall;
		//ground
	case EnumID::Candle_ID:
		return candle;
	case EnumID::LargeCandle_ID:
		return largeCandle;


	case EnumID::MorningStar_ID:
		return morningStar;
	case EnumID::Water_ID:
		return water;
		//Boss
	case EnumID::PhantomBat_ID:
		return phantombat;
		// Other


	case EnumID::HP_ID:
		return hp;

	case EnumID::GameUI_ID:
		return gameScore;

	case EnumID::Reward_ID:
		return rewardItem;


		// Items:
	case EnumID::Large_Heart:
		return largeHeartItem;
	case EnumID::Small_Heart:
		return smallHeartItem;
	}
}