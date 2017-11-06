#include "Raven_TargetingSystem_Visibility.h"
#include "Raven_Bot.h"
#include "Raven_SensoryMemory.h"



//-------------------------------- ctor ---------------------------------------
//-----------------------------------------------------------------------------
Raven_TargetingSystem_Visibility::Raven_TargetingSystem_Visibility(Raven_Bot* owner) :
	Raven_TargetingSystem(owner)
{}



//----------------------------- Update ----------------------------------------

//-----------------------------------------------------------------------------
void Raven_TargetingSystem_Visibility::Update()
{
	m_pCurrentTarget = 0;

	//grab a list of all the opponents the owner can sense
	std::list<Raven_Bot*> SensedBots;
	SensedBots = m_pOwner->GetSensoryMem()->GetListOfRecentlySensedOpponents();

	double longestVisible = 0;

	//targets the bot that has been visible the longest
	std::list<Raven_Bot*>::const_iterator curBot = SensedBots.begin();
	for (curBot; curBot != SensedBots.end(); ++curBot)
	{
		//make sure the bot is alive and that it is not the owner
		if ((*curBot)->isAlive() && (*curBot != m_pOwner))
		{
			double timeVisible = m_pOwner->GetSensoryMem()->GetTimeOpponentHasBeenVisible(*curBot);
			if (timeVisible > longestVisible)
			{
				longestVisible = timeVisible;
				m_pCurrentTarget = *curBot;
			}
		}
	}
}


