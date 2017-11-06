#include "Defense_Evaluator.h"
#include "Goal_Think.h"
#include "Raven_Goal_Types.h"
#include "../Raven_WeaponSystem.h"
#include "../Raven_ObjectEnumerations.h"
#include "misc/cgdi.h"
#include "misc/Stream_Utility_Functions.h"
#include "Raven_Feature.h"
#include "../armory/Raven_Weapon.h"


#include "debug/DebugConsole.h"

//------------------ CalculateDesirability ------------------------------------
//
//  returns a value between 0 and 1 that indicates the Rating of a bot (the
//  higher the score, the stronger the bot).
//-----------------------------------------------------------------------------
double Defense_Evaluator::CalculateDesirability(Raven_Bot* pBot)
{
	double Desirability = 0.0;
	Raven_WeaponSystem* weaponsys = pBot->GetWeaponSys();
	Raven_Weapon* curWep = weaponsys->GetCurrentWeapon();

	//only do the calculation if the bots health is low/it is running out of ammo and hs los to enemy
	if ((pBot->Health() < 30 || weaponsys->GetAmmoRemainingForWeapon(curWep->GetType()) < 10) &&
		(pBot->InCombat()))
	{
		const double Tweaker = 3.0;

		Desirability = Tweaker *
			(1-Raven_Feature::Health(pBot)) * //multiplies by 1-health so the more health missing, the more desireable
			Raven_Feature::TotalWeaponStrength(pBot);

		//bias the value according to the personality of the bot
		Desirability *= m_dCharacterBias;
	}


	return Desirability;
}

//----------------------------- SetGoal ---------------------------------------
//-----------------------------------------------------------------------------
void Defense_Evaluator::SetGoal(Raven_Bot* pBot)
{
	int targetId = pBot->HighestRecentDamage(); //changes the target to the bot w/ most rec damage
	debug_con << pBot->ID() <<  " Bot FLeeing From " << targetId << "";
	pBot->GetTargetSys()->SetNewTarget(targetId);
	pBot->GetBrain()->AddGoal_FleeFromEnemy();
	//debug_con << "Oh, they are after me! RUNNN " << pBot->ID() << "";
}

//-------------------------- RenderInfo ---------------------------------------
//-----------------------------------------------------------------------------
void Defense_Evaluator::RenderInfo(Vector2D Position, Raven_Bot* pBot)
{
	gdi->TextAtPos(Position, "AT: " + ttos(CalculateDesirability(pBot), 2));
	return;

	std::string s = ttos(Raven_Feature::Health(pBot)) + ", " + ttos(Raven_Feature::TotalWeaponStrength(pBot));
	gdi->TextAtPos(Position + Vector2D(0, 12), s);
}