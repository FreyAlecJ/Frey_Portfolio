#include "Raven_TargetingSystem_Nemesis.h"
#include "Raven_Bot.h"
#include "Raven_SensoryMemory.h"



//-------------------------------- ctor ---------------------------------------
//-----------------------------------------------------------------------------
Raven_TargetingSystem_Nemesis::Raven_TargetingSystem_Nemesis(Raven_Bot* owner) :
	Raven_TargetingSystem(owner)
{
	targetUpdates = 0;
}



//----------------------------- Update ----------------------------------------

//-----------------------------------------------------------------------------
void Raven_TargetingSystem_Nemesis::Update()
{
	if (targetUpdates == 60)
	{
		m_pCurrentTarget = 0;

		//grab a list of all the opponents the owner can sense
		std::list<Raven_Bot*> SensedBots;
		SensedBots = m_pOwner->GetSensoryMem()->GetListOfRecentlySensedOpponents();

		int biggestNem = 0;

		//targets the enemy that has killed the bot the most times.
		std::list<Raven_Bot*>::const_iterator curBot = SensedBots.begin();
		for (curBot; curBot != SensedBots.end(); ++curBot)
		{
			//make sure the bot is alive and that it is not the owner
			if ((*curBot)->isAlive() && (*curBot != m_pOwner))
			{
				int currNem = m_pOwner->GetNem((*curBot)->ID());
				if (currNem >= biggestNem)
				{
					biggestNem = currNem;
					m_pCurrentTarget = *curBot;
				}
			}
		}
	}
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


