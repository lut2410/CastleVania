#ifndef _MUMMY_H_
#define _MUMMY_H_

#include "DynamicObject.h"
#include "MagicalBall.h"
#include <vector>
#include "Bandages.h"
using namespace std;

#define QUEEN_medusa_SLEEP_STATE 10
#define QUEEN_medusa_STOP_STATE 2
#define QUEEN_medusa_SPEED_X 0.3f
#define LITTLE_SNAKE_SPEED_X 0.3f
#define QUEEN_medusa_DIE_RATE 10
#define DEAD_TIME 1500
#define PI 3.14f
#define T 1000
#define A 20
#define QUEEN_medusa_SleepinG_RightCameraATE 1

enum EMummyState
{
	Mummy_Stoping,
	Mummy_moving
};

class Mummy : public DynamicObject
{
protected:
	

	int _timeSpan;
	bool _drawLeft;
	bool _isSleeping;
	EMummyState _state;
	bool _attackmode;
	int deltaX;
	int oldX;
	int timeDelay;
	
	vector<D3DXVECTOR2*> _listStopPos;
	D3DXVECTOR2* _nextStopPos;
	int _previousStopPos;
	int _currentStopPos;
	DWORD _localTime;

	list<DynamicObject*> *_bandages;

	
	D3DXVECTOR2* _playerPos;
	float _deltaPhi;
	float _posY0;


	void _initialize();


	bool _leaveStopPos(D3DXVECTOR2 boss_, D3DXVECTOR2 _nextStopPos);

	void _drawBandages(GCamera* camera_);

	void _updateBandages(int deltaTime_);

public:

	bool HasGetUp;
	Mummy(void);
	Mummy(float posX, float posY);
	//virtual void Update(int deltaTime_);
	virtual void Update(int, int, int);
//	void Update(int deltaTime_, D3DXVECTOR2* playerPos_);
	virtual void Draw(GCamera* camera_);
	virtual void Collision(list<GameObject*> obj, int dt);
	void getUp();
	void setDead();
	//void ReceiveDamage(int damagePoint);
	bool StateCancel();
	~Mummy(void);
public:

};

#endif

