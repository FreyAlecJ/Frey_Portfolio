#include "Raven_TargetingSystem_Anger.h"
#include "Raven_Bot.h"
#include "Raven_SensoryMemory.h"



//-------------------------------- ctor ---------------------------------------
//-----------------------------------------------------------------------------
Raven_TargetingSystem_Anger::Raven_TargetingSystem_Anger(Raven_Bot* owner) :
		Raven_TargetingSystem(owner)
{
	targetUpdates = 0;
}



//----------------------------- Update ----------------------------------------

//-----------------------------------------------------------------------------
void Raven_TargetingSystem_Anger::Update()
{
	//game has went on long enough for anger to be established.
	if (targetUpdates == 15)
	{
		m_pCurrentTarget = 0;

		//grab a list of all the opponents the owner can sense
		std::list<Raven_Bot*> SensedBots;
		SensedBots = m_pOwner->GetSensoryMem()->GetListOfRecentlySensedOpponents();

		int mostAnger = 0;

		//selects enemy that has done the most damage to the bot in the game.
		std::list<Raven_Bot*>::const_iterator curBot = SensedBots.begin();
		for (curBot; curBot != SensedBots.end(); ++curBot)
		{
			//make sure the bot is alive and that it is not the owner
			if ((*curBot)->isAlive() && (*curBot != m_pOwner))
			{
				int currAnger = m_pOwner->GetAnger((*curBot)->ID());
				if (currAnger >= mostAnger)
				{
					mostAnger = currAnger;
					m_pCurrentTarget = *curBot;
				}
			}
		}
	}
	//not enough anger yet to effectively target an enemy. use default distance
	else
	{
		double ClosestDistSoFar = MaxDouble;
		m_pCurrentTarget = 0;

		//grab a list of all the opponents the owner can sense
		std::list<Raven_Bot*> SensedBots;
		SensedBots = m_pOwner->GetSensoryMem()->GetListOfRecentlySensedOpponents();

		std::list<Raven_Bot*>::const_iterator curBot = SensedBots.begin();
		for (curBot; curBot != SensedBots.end(); ++curBot)
		{
			//make sure the bot is alive and that it is not the owner
			if ((*curBot)->isAlive() && (*curBot != m_pOwner))
			{
				double dist = Vec2DDistanceSq((*curBot)->Pos(), m_pOwner->Pos());

				if (dist < ClosestDistSoFar)
				{
					ClosestDistSoFar = dist;
					m_pCurrentTarget = *curBot;
				}
			}
		}

		targetUpdates += 1;
	}

}

