/**
* created by Omer Chen
* @since - MAY 2017
*/

#pragma once

#include "Definitions.h"
#include "SPlayer.h"

//Magic Numbers
#define CALCULATOR_ERROR					(-1)

// CALCULATOR-CONFIGURATIONS (%)
#define GKPLAYER_HEIGHT_IMPORTENCE			(5)
#define GKPLAYER_PYHSICAL_IMPORTENCE		(5)
#define GKPLAYER_PENALTY_IMPORTENCE			(1)
#define GKPLAYER_GK_IMPORTENCE				(67)
#define GKPLAYER_SPASS_IMPORTENCE			(6)
#define GKPLAYER_LPASS_IMPORTENCE			(8)
#define GKPLAYER_HPASS_IMPORTENCE			(7)
#define GKPLAYER_FITNESS_IMPORTENCE			(1)

#define FIELDER_HEIGHT_IMPORTENCE			(3)
#define FIELDER_PHYSICAL_IMPORTENCE			(7)
#define FIELDER_PENALTY_IMPORTENCE			(3)
#define FIELDER_ATTACK_IMPORTENCE			(22)
#define FIELDER_SHOOT_IMPORTENCE			(6)
#define FIELDER_DEF_IMPORTENCE				(17)
#define FIELDER_LPASS_IMPORTENCE			(3)
#define FIELDER_SPASS_IMPORTENCE			(6)
#define FIELDER_SPEED_IMPORTENCE			(7)
#define FIELDER_DRIBBLE_IMPORTENCE			(8)
#define FIELDER_TEAM_IMPORTENCE				(8)
#define FIELDER_FITNESS_IMPORTENCE			(10)


#define TEAM_GK_BONUS						(50)

attr_t Grade(GKPlayer p)
{
	attr_t height_grade = (p.basic_info.height * MAX_RATE) / (eHeight_SIZE - 1);
	attr_t physical_grade = (p.basic_info.physical * MAX_RATE) / (ePhysical_SIZE - 1);
	attr_t penalty_grade = (p.basic_info.penalty_rate * MAX_RATE) / (ePenalty_SIZE - 1);

	return (PRECENT(p.gk_rate, GKPLAYER_GK_IMPORTENCE) + PRECENT(p.hpass_rate, GKPLAYER_HPASS_IMPORTENCE) + 
			PRECENT(p.lpass_rate, GKPLAYER_LPASS_IMPORTENCE) +   PRECENT(p.spass_rate, GKPLAYER_SPASS_IMPORTENCE) +
			PRECENT(penalty_grade, GKPLAYER_PENALTY_IMPORTENCE) + PRECENT(height_grade, GKPLAYER_HEIGHT_IMPORTENCE) +
			PRECENT(physical_grade, GKPLAYER_PYHSICAL_IMPORTENCE) + PRECENT(p.basic_info.fitness, GKPLAYER_FITNESS_IMPORTENCE));
}

attr_t Grade(FieldPlayer p)
{
	attr_t height_grade = (p.basic_info.height * MAX_RATE) / (eHeight_SIZE - 1);
	attr_t physical_grade = (p.basic_info.physical * MAX_RATE) / (ePhysical_SIZE - 1);
	attr_t penalty_grade = (p.basic_info.penalty_rate * MAX_RATE) / (ePenalty_SIZE - 1);

	return (PRECENT(height_grade, FIELDER_HEIGHT_IMPORTENCE) + PRECENT(physical_grade, FIELDER_PHYSICAL_IMPORTENCE) +
			PRECENT(penalty_grade, FIELDER_PENALTY_IMPORTENCE) + PRECENT(p.attack_rate, FIELDER_ATTACK_IMPORTENCE) +
			PRECENT(p.def_rate, FIELDER_DEF_IMPORTENCE) + PRECENT(p.dribble_rate, FIELDER_DRIBBLE_IMPORTENCE) +
			PRECENT(p.shoot_rate, FIELDER_SHOOT_IMPORTENCE) + PRECENT(p.speed_rate, FIELDER_SPEED_IMPORTENCE) +
			PRECENT(p.lpass_rate, FIELDER_LPASS_IMPORTENCE) + PRECENT(p.spass_rate, FIELDER_SPASS_IMPORTENCE) +
			PRECENT(p.team_rate, FIELDER_TEAM_IMPORTENCE) + PRECENT(p.basic_info.fitness, FIELDER_FITNESS_IMPORTENCE));
}

attr_t Grade(GeneralPlayer* p)
{
	switch (p->basic_info.role)
	{
		case eRole_GK:
		{
			return Grade(*(GKPlayer*)p);
		}
		case eRole_Field:
		{
			return Grade(*(FieldPlayer*)p);
		}
		default:
		{
			return -1;
		}
	}
}

attr_t Grade(GeneralPlayer** players, size_t amount)
{
	if (amount == 0 || players == nullptr)
	{
		return CALCULATOR_ERROR;
	}

	double avg_players_grades = 0;
	int gk_counter = 0;

	for (int i = 0; i < amount; i++)
	{
		attr_t curGrade = Grade(players[i]);

		if (curGrade == CALCULATOR_ERROR)
		{
			return CALCULATOR_ERROR;
		}

		avg_players_grades += curGrade;

		if (players[i]->basic_info.role == eRole_GK)
		{
			gk_counter++;
		}
	}

	if (gk_counter > 1)
	{
		return CALCULATOR_ERROR;
	}

	avg_players_grades /= amount;

	if (gk_counter == 1)
	{
		avg_players_grades += PRECENT(avg_players_grades, TEAM_GK_BONUS);
	}

	return (attr_t)avg_players_grades;

}