#ifndef GOAL_FLEE_FROM_ENEMY_H
#define GOAL_FLEE_FROM_ENEMY_H
#pragma warning (disable:4786)

#include "Goals/Goal_Composite.h"
#include "2D/Vector2D.h"
#include "../Raven_Bot.h"
#include "Raven_Goal_Types.h"



class Goal_FleeFromEnemy : public Goal_Composite<Raven_Bot>
{

public:

	Goal_FleeFromEnemy(Raven_Bot* pBot) :

		Goal_Composite<Raven_Bot>(pBot,
			goal_flee_from_enemy)
	{}

	//the usual suspects
	void Activate();
	int  Process();
	void Terminate() {}
};





#endif
