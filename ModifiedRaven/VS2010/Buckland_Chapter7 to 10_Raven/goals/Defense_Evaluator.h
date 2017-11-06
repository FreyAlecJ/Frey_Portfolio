#ifndef DEFENSE_EVALUATOR
#define DEFENSE_EVALUATOR
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   AttackTargetGoal_Evaluator.h
//
//  Author: Alec Frey
//
//  Desc:  class to calculate how desirable the goal of switching to the defense
//-----------------------------------------------------------------------------

#include "Goal_Evaluator.h"
#include "../Raven_Bot.h"


class Defense_Evaluator : public Goal_Evaluator
{
public:

	Defense_Evaluator(double bias) :Goal_Evaluator(bias) {}

	double CalculateDesirability(Raven_Bot* pBot);

	void  SetGoal(Raven_Bot* pEnt);

	void RenderInfo(Vector2D Position, Raven_Bot* pBot);
};



#endif
