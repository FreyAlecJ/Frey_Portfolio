#include "Goal_FleeFromEnemy.h"
#include "../Raven_Bot.h"
#include "../Raven_Game.h"
#include "../navigation/Raven_PathPlanner.h"
#include "Messaging/Telegram.h"
#include "../Raven_Messages.h"
#include "misc/cgdi.h"

#include "Goal_SeekToPosition.h"
#include "Goal_Flee.h"
#include "Goal_FollowPath.h"
#include "Debug/DebugConsole.h"



//------------------------------- Activate ------------------------------------
//-----------------------------------------------------------------------------
void Goal_FleeFromEnemy::Activate()
{
	m_iStatus = active;

	//make sure the subgoal list is clear.
	RemoveAllSubgoals();

	//requests a path to the target position from the path planner. Because, for
	//demonstration purposes, the Raven path planner uses time-slicing when 
	//processing the path requests the bot may have to wait a few update cycles
	//before a path is calculated. Consequently, for appearances sake, it just
	//seeks directly to the target position whilst it's awaiting notification
	//that the path planning request has succeeded/failed
	AddSubgoal(new Goal_Flee(m_pOwner));
}

//------------------------------ Process --------------------------------------
//-----------------------------------------------------------------------------
int Goal_FleeFromEnemy::Process()
{
	//if status is inactive, call Activate()
	ActivateIfInactive();

	//process the subgoals
	m_iStatus = ProcessSubgoals();

	//if any of the subgoals have failed then this goal re-plans
	ReactivateIfFailed();

	return m_iStatus;
}



