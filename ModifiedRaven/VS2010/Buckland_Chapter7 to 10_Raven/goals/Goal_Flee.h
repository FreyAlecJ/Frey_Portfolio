
#ifndef GOAL_FLEE_H
#define GOAL_FLEE_H
#pragma warning (disable:4786)

#include "Goals/Goal.h"
#include "2d/Vector2D.h"
#include "Raven_Goal_Types.h"
#include "../Raven_Bot.h"


class Goal_Flee : public Goal<Raven_Bot>
{
private:

public:

	Goal_Flee(Raven_Bot* pBot);

	//the usual suspects
	void Activate();
	int  Process();
	void Terminate();

};




#endif