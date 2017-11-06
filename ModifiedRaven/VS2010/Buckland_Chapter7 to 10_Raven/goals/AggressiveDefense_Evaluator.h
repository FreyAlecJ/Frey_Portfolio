#pragma once
#ifndef AGGRESSIVEDEFENSE_EVALUATOR
#define AGGRESSIVEDEFESNE_EVALUATOR
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Aggressive Defense _Evaluator.h
//
//  Author: Alec Frey
//
//  Desc:  class to calculate the desireability of going on an aggressive defense.
//-----------------------------------------------------------------------------

#include "Goal_Evaluator.h"
#include "../Raven_Bot.h"


class AggressiveDefense_Evaluator : public Goal_Evaluator
{
public:

	AggressiveDefense_Evaluator(double bias) :Goal_Evaluator(bias) {}

	double CalculateDesirability(Raven_Bot* pBot);

	void  SetGoal(Raven_Bot* pEnt);

	void RenderInfo(Vector2D Position, Raven_Bot* pBot);
};



#endif