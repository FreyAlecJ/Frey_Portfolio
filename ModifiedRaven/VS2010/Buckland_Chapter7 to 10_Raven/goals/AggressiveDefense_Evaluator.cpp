#include "AggressiveDefense_Evaluator.h"
#include "Goal_Think.h"
#include "Raven_Goal_Types.h"
#include "../Raven_WeaponSystem.h"
#include "../Raven_ObjectEnumerations.h"
#include "misc/cgdi.h"
#include "misc/Stream_Utility_Functions.h"
#include "Raven_Feature.h"


#include "debug/DebugConsole.h"

//------------------ CalculateDesirability ------------------------------------
//
//  returns a value between 0 and 1 that indicates the Rating of a bot (the
//  higher the score, the stronger the bot).
//-----------------------------------------------------------------------------
double AggressiveDefense_Evaluator::CalculateDesirability(Raven_Bot* pBot)
{
	double Desirability = 0.0;

	int mostDangerous = pBot->HighestRecentDamage();
	//debug_con << "Most dangerous: " << mostDangerous << " for bot : " << pBot->ID() << "";


	//only do the calculation if the bot has 
	if (pBot->Health() <= 70 && pBot->Health() > 40 && pBot->InCombat())
	{
		const double Tweaker = 3.0;

		float damage = pBot->RecentDamage(mostDangerous);
		damage = damage / pBot->MaxHealth(); //creates a fraction of how much damage the enemy has 
											 //done relative to the bot
		
		Desirability = Tweaker *
			Raven_Feature::Health(pBot) *
			Raven_Feature::TotalWeaponStrength(pBot) +
			damage;

		//debug_con << "Health: " << Raven_Feature::Health(pBot) << " Weapon Strngth: " << Raven_Feature::TotalWeaponStrength(pBot)
		//	<< "Damage: " << damage << " bot: " << pBot->ID() << "";


		//bias the value according to the personality of the bot
		Desirability *= m_dCharacterBias;
	}

	//debug_con << Desirability << " " << pBot->ID() << "";

	return Desirability;
}

//----------------------------- SetGoal ---------------------------------------
//-----------------------------------------------------------------------------
void AggressiveDefense_Evaluator::SetGoal(Raven_Bot* pBot)
{
	//debug_con << "Attempting to Agress" << "";
	int targetId = pBot->HighestRecentDamage(); //changes the target to the bot w/ most rec damage
	pBot->GetTargetSys()->SetNewTarget(targetId);
	pBot->GetBrain()->AddGoal_AttackTarget(); //begins attacking that bot
	//debug_con << "The best defense is a good offense! GET AGGRESSIVE! " << pBot->ID() <<  "";
}

//-------------------------- RenderInfo ---------------------------------------
//-----------------------------------------------------------------------------
void AggressiveDefense_Evaluator::RenderInfo(Vector2D Position, Raven_Bot* pBot)
{
	gdi->TextAtPos(Position, "AT: " + ttos(CalculateDesirability(pBot), 2));
	return;

	std::string s = ttos(Raven_Feature::Health(pBot)) + ", " + ttos(Raven_Feature::TotalWeaponStrength(pBot));
	gdi->TextAtPos(Position + Vector2D(0, 12), s);
}