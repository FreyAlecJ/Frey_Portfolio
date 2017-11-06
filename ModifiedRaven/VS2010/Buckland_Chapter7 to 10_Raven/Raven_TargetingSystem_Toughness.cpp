#include "Raven_TargetingSystem_Toughness.h"
#include "Raven_Bot.h"
#include "Raven_SensoryMemory.h"



//-------------------------------- ctor ---------------------------------------
//-----------------------------------------------------------------------------
Raven_TargetingSystem_Toughness::Raven_TargetingSystem_Toughness(Raven_Bot* owner) :
	Raven_TargetingSystem(owner)
{}



//----------------------------- Update ----------------------------------------

//-----------------------------------------------------------------------------
void Raven_TargetingSystem_Toughness::Update()
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
}





