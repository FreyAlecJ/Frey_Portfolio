#include "Raven_TargetingSystem_BotRange.h"
#include "Raven_Bot.h"
#include "Raven_SensoryMemory.h"
#include "Raven_WeaponSystem.h"
#include "armory\Raven_Weapon.h"



//-------------------------------- ctor ---------------------------------------
//-----------------------------------------------------------------------------
Raven_TargetingSystem_BotRange::Raven_TargetingSystem_BotRange(Raven_Bot* owner) :
	Raven_TargetingSystem(owner)
{}



//----------------------------- Update ----------------------------------------

//-----------------------------------------------------------------------------
void Raven_TargetingSystem_BotRange::Update()
{
	double ClosestDistSoFar = MaxDouble;
	m_pCurrentTarget = 0;

	//grab a list of all the opponents the owner can sense
	std::list<Raven_Bot*> SensedBots;
	SensedBots = m_pOwner->GetSensoryMem()->GetListOfRecentlySensedOpponents();

	//select a target if the bots range is greater than the enemys range
	std::list<Raven_Bot*>::const_iterator curBot = SensedBots.begin();
	for (curBot; curBot != SensedBots.end(); ++curBot)
	{
		//make sure the bot is alive and that it is not the owner
		if ((*curBot)->isAlive() && (*curBot != m_pOwner))
		{
			double dist = Vec2DDistanceSq((*curBot)->Pos(), m_pOwner->Pos());

			double enRange = (*curBot)->GetWeaponSys()->GetCurrentWeapon()->GetIdealRange();
			double botRange = m_pOwner->GetWeaponSys()->GetCurrentWeapon()->GetIdealRange();
			if (botRange > enRange)
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

