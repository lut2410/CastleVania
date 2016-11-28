﻿#include "QGameObject.h"


QGameObject::QGameObject(void)
{
}

int QGameObject::RemoveAllObjectInCamera(D3DXVECTOR2 viewport)
{
	int score = 0;
	list<GameObject*>::iterator it = _dynamicObject->begin();
	while (it != _dynamicObject->end())
	{
		GameObject* other = (*it);
		if (other->active && !(other->posX + other->width / 2 <= viewport.x
			|| other->posX - other->width / 2 >= viewport.x + G_ScreenWidth
			|| other->posY + other->height / 2 <= viewport.y - G_ScreenHeight
			|| other->posY - other->height / 2 >= viewport.y))
		{
			if (other->type == ObjectType::Enemy_Type)
			{
				switch (other->id)
				{
				
					
					_dynamicObject->erase(it++);
					break;
				}
			}
			else ++it;
		}
		else ++it;
	}
	return score;
}

//Được gọi khi load Stage
//Filename là tên file Stage
QGameObject::QGameObject(string fileName)
{
	ifstream map(fileName);

	// GameObject :_staticObject,_dynamicObject
	_staticObject = new list<GameObject*>();
	_dynamicObject = new list<GameObject*>();

	if (map.is_open())
	{
		float posX, posY; int width, height, value;
		int count;
		map >> count >> width >> height;
		int id;
		int x = 0;
		// duyệt từng dòng của file Stage
		for (int i = 0; i < count; i++)
		{
			map >> id >> value >> posX >> posY >> width >> height;

			// ứng với giá trị value tương ứng để khởi tạo các object tương tứng
			switch (value)
			{
			case 0:
				_staticObject->push_back(new Brick(posX, posY, width, height));
				break;
			
			case 6:
				_staticObject->push_back(new Candle(posX, posY));
				break;
		
			case 10:
				_dynamicObject->push_back(new Zombie(posX, posY));
				break;
		
			case 25:
				posDoor.x = posX;
				posDoor.y = posY;
				break;
			case 26:
				G_MinSize = posX;
				break;
			case 27:
				G_MaxSize = posX;
				break;
			default:
				break;
			}
		}
	}
	
}

D3DXVECTOR2 QGameObject::GetPosDoor()
{
	return posDoor;
}

void QGameObject::Draw(GCamera *camera)
{
	for (list<GameObject*>::iterator i = _staticObject->begin(); i != _staticObject->end(); i++)
	{
		GameObject* obj = (*i);
	
		if (obj->active)
		{
			obj->Draw(camera);
		}
	}

	for (list<GameObject*>::iterator i = _dynamicObject->begin(); i != _dynamicObject->end(); i++)
	{
		GameObject* obj = (*i);
	
		if (obj->active)
		{
			obj->Draw(camera);
		}
	}
}
void QGameObject::Update(int deltaTime)
{
	list<GameObject*>::iterator it = _staticObject->begin();
	while (it != _staticObject->end())
	{
		
		{
			(*it)->Update(deltaTime);
			++it;
		}
	}

	it = _dynamicObject->begin();
	while (it != _dynamicObject->end())
	{
		
	}
}



QGameObject::~QGameObject(void)
{
}