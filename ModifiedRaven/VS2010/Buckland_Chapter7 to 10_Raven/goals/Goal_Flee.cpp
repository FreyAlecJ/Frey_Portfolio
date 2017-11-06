#include "Goal_Flee.h"
#include "..\Raven_Bot.h"
#include "..\Raven_SteeringBehaviors.h"
#include "time/CrudeTimer.h"
#include "../navigation/Raven_PathPlanner.h"
#include "misc/cgdi.h"



#include "debug/DebugConsole.h"



//---------------------------- ctor -------------------------------------------
//-----------------------------------------------------------------------------
Goal_Flee::Goal_Flee(Raven_Bot* pBot) :

	Goal<Raven_Bot>(pBot,
		goal_flee_from_enemy)
{
}


//---------------------------- Activate -------------------------------------
//-----------------------------------------------------------------------------  
void Goal_Flee::Activate()
{
	m_iStatus = active;
	m_pOwner->GetSteering()->EvadeOn();
	m_pOwner->GetSteering()->WallAvoidanceOn();
}


//------------------------------ Process --------------------------------------
//-----------------------------------------------------------------------------
int Goal_Flee::Process()
{
	//if status is inactive, call Activate()
	ActivateIfInactive();

	Raven_Bot* target = m_pOwner->GetTargetBot();

	//test to see if the bot has reached the waypoint. If so terminate the goal
	if (target == NULL || !m_pOwner->hasLOSto(target->Pos()))
	{
		m_iStatus = completed;
	}

	return m_iStatus;
}


//---------------------------- Terminate --------------------------------------
//-----------------------------------------------------------------------------
void Goal_Flee::Terminate()
{
	m_pOwner->GetSteering()->EvadeOff();

	m_iStatus = completed;
}