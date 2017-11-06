#ifndef GOAL_FOLLOWPARTIALPATH
#define GOAL_FOLLOWPARTIALPATH
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Goal_AdjustRange.h
//
//  Author: Mat Buckland (ai-junkie.com)
//
//  Desc:   
//
//-----------------------------------------------------------------------------
#include "Goals/Goal_Composite.h"
#include "Raven_Goal_Types.h"
#include "../Raven_Bot.h"
#include "../navigation/Raven_PathPlanner.h"
#include "../navigation/PathEdge.h"

class Goal_FollowPartialPath : public Goal_Composite<Raven_Bot>
{
public:
	Goal_FollowPartialPath();
	~Goal_FollowPartialPath();
};


#endif

