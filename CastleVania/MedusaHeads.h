#ifndef _MedusaHeads_H_
#define _MedusaHeads_H_

#include "DynamicObject.h"
#include "CEnum.h"

class MedusaHeads :public DynamicObject
{
protected:
	float _alpha;
	float _posY0;
public:
	MedusaHeads(void);
	MedusaHeads(float _x, float _y);
	void MoveSinPath(int deltaTime);
	void Update(int deltaTime);
	void Draw(GCamera*);
	void Collision(list<GameObject*> obj, int dt);
	~MedusaHeads(void);
};

#endif