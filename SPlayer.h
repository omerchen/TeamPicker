/**
* created by Omer Chen
* @since - MAY 2017
*/

#pragma once

#include <stdint.h>
#include "Definitions.h"

#define VERSION			(0)

// DON'T CHANGE THIS!!
#define MIN_RATE		(0)
#define MAX_RATE		(100)

typedef int8_t attr_t;

enum EHeight
{
	eHeight_Short = 0,
	eHeight_Avg,
	eHeight_Tall,
	eHeigh_Huge,
	eHeight_SIZE
};

enum EPhysical
{
	ePhysical_Weak = 0,
	ePhysical_Strong,
	ePhysical_SIZE
};

enum EPenalty
{
	ePenalty_Bad = 0,
	ePenalty_Good,
	ePenalty_Scorer,
	ePenalty_SIZE
};

enum ERole
{
	eRole_GK,
	eRole_Field
};

struct Player
{
	char*		first_name;
	char*		last_name;
	EHeight		height;
	EPhysical	physical;
	ERole		role;
	EPenalty	penalty_rate;
	attr_t		fitness;
};

struct GeneralPlayer
{
	Player		basic_info;
};

struct GKPlayer
{
	Player		basic_info;
	attr_t		gk_rate;
	attr_t		spass_rate;
	attr_t		lpass_rate;
	attr_t		hpass_rate;
};

struct FieldPlayer
{
	Player		basic_info;
	attr_t		def_rate;
	attr_t		attack_rate;
	attr_t		shoot_rate;
	attr_t		spass_rate;
	attr_t		lpass_rate;
	attr_t		speed_rate;
	attr_t		dribble_rate;
	attr_t		team_rate;
};
