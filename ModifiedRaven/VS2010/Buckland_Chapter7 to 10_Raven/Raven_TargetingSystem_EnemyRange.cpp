#include "Raven_TargetingSystem_EnemyRange.h"
#include "Raven_Bot.h"
#include "Raven_SensoryMemory.h"
#include "Raven_WeaponSystem.h"
#include "armory\Raven_Weapon.h"



//-------------------------------- ctor ---------------------------------------
//-----------------------------------------------------------------------------
Raven_TargetingSystem_EnemyRange::Raven_TargetingSystem_EnemyRange(Raven_Bot* owner) :
	Raven_TargetingSystem(owner)
{}



//----------------------------- Update ----------------------------------------

//-----------------------------------------------------------------------------
void Raven_TargetingSystem_EnemyRange::Update()
{
	double ClosestDistSoFar = MaxDouble;
	m_pCurrentTarget = 0;

	//grab a list of all the opponents the owner can sense
	std::list<Raven_Bot*> SensedBots;
	SensedBots = m_pOwner->GetSensoryMem()->GetListOfRecentlySensedOpponents();

	//only targets enemies that are at their max range
	std::list<Raven_Bot*>::const_iterator curBot = SensedBots.begin();
	for (curBot; curBot != SensedBots.end(); ++curBot)
	{
		//make sure the bot is alive and that it is not the owner
		if ((*curBot)->isAlive() && (*curBot != m_pOwner))
		{
			double dist = Vec2DDistanceSq((*curBot)->Pos(), m_pOwner->Pos());

			double enRange = (*curBot)->GetWeaponSys()->GetCurrentWeapon()->GetIdealRange();
			double botRange = m_pOwner->GetWeaponSys()->GetCurrentWeapon()->GetIdealRange();

			if (dist < ClosestDistSoFar && botRange >= enRange)
			{
				ClosestDistSoFar = dist;
				m_pCurrentTarget = *curBot;
			}

		}

	}
}


