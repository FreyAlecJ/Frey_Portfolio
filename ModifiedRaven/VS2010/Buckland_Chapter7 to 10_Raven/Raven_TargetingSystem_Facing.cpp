#include "Raven_TargetingSystem_Facing.h"
#include "Raven_Bot.h"
#include "Raven_SensoryMemory.h"



//-------------------------------- ctor ---------------------------------------
//-----------------------------------------------------------------------------
Raven_TargetingSystem_Facing::Raven_TargetingSystem_Facing(Raven_Bot* owner) :
	Raven_TargetingSystem(owner)
{
	targetUpdates = 0;
}



//----------------------------- Update ----------------------------------------

//-----------------------------------------------------------------------------
void Raven_TargetingSystem_Facing::Update()
{
	if (targetUpdates == 0)
	{
		double ClosestDistSoFar = MaxDouble;
		m_pCurrentTarget = 0;

		//grab a list of all the opponents the owner can sense
		std::list<Raven_Bot*> SensedBots;
		SensedBots = m_pOwner->GetSensoryMem()->GetListOfRecentlySensedOpponents();

		//targets bots facing the opposite direction
		std::list<Raven_Bot*>::const_iterator curBot = SensedBots.begin();
		for (curBot; curBot != SensedBots.end(); ++curBot)
		{
			//make sure the bot is alive and that it is not the owner
			if ((*curBot)->isAlive() && (*curBot != m_pOwner))
			{
				double dist = Vec2DDistanceSq((*curBot)->Pos(), m_pOwner->Pos());

				//enemy facing the other direction----> SNEAK ATTACK
				if (!(*curBot)->hasLOSto(m_pOwner->Pos()))
				{
					m_pCurrentTarget = *curBot;
					break;
				}
				else if (dist < ClosestDistSoFar)
				{
					ClosestDistSoFar = dist;
					m_pCurrentTarget = *curBot;
				}
			}
		}
	}
	else
	{
		targetUpdates += 1;
		if (targetUpdates == 10)
		{
			targetUpdates = 0;
		}
	}

}


