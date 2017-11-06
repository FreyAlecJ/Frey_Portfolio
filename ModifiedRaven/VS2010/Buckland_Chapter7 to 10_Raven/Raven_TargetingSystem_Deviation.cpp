#include "Raven_TargetingSystem_Deviation.h"
#include "Raven_Bot.h"
#include "Raven_SensoryMemory.h"
#include <cmath>

//uncomment to write object creation/deletion to debug console
#define  LOG_CREATIONAL_STUFF
#include "debug/DebugConsole.h"




//-------------------------------- ctor ---------------------------------------
//-----------------------------------------------------------------------------
Raven_TargetingSystem_Deviation::Raven_TargetingSystem_Deviation(Raven_Bot* owner) :
	Raven_TargetingSystem(owner)
{
	targetUpdates = 0;
}



//----------------------------- Update ----------------------------------------

//-----------------------------------------------------------------------------
void Raven_TargetingSystem_Deviation::Update()
{
	if (targetUpdates == 0)
	{
		double smallestDeviation = 1; // equals 1 radian (180*) for comparison to find the smallest
		m_pCurrentTarget = 0;

		//grab a list of all the opponents the owner can sense
		std::list<Raven_Bot*> SensedBots;
		SensedBots = m_pOwner->GetSensoryMem()->GetListOfRecentlySensedOpponents();

		//selects the target based on the smallest angle of deviation from its normal
		std::list<Raven_Bot*>::const_iterator curBot = SensedBots.begin();
		for (curBot; curBot != SensedBots.end(); ++curBot)
		{
			//make sure the bot is alive and that it is not the owner
			if ((*curBot)->isAlive() && (*curBot != m_pOwner))
			{
				//gets vectors for enemy and bot
				Vector2D enemyLocation = m_pOwner->GetSensoryMem()->GetLastRecordedPositionOfOpponent(*curBot);
				Vector2D botLocation = m_pOwner->Facing();

				//normalizes the vectors
				enemyLocation.Normalize();
				botLocation.Normalize();

				//find the dot product
				double dot = botLocation.Dot(enemyLocation);

				//find the inverse cos to give the angle in radians
				double deviation = acos(dot);

				if (deviation < smallestDeviation)
				{
					smallestDeviation = deviation;
					m_pCurrentTarget = *curBot;
				}


			}
		}
	}
	else
	{
		targetUpdates += 1;
		if (targetUpdates == 6)
		{
			targetUpdates = 0;
		}
	}
	
}

