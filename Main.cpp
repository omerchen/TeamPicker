#include <stdlib.h>
#include <stdio.h>
#include "FileHandler.h"
#include "FileLogger.h"
#include "FootballCalculator.h"
#include "DataSetHandler.h"
#include "PlayersListHandler.h"
#include "IOFile.h"

#define DS_CUR_PATH		("DataSet.new.bin")

void Append(char* name, EHeight height, EPhysical physical, EPenalty penalty, attr_t gk_rate, attr_t hpass, attr_t lpass, attr_t spass, attr_t fitness)
{
	GKPlayer gk;
	gk.basic_info.height = height;
	gk.basic_info.physical = physical;
	gk.basic_info.penalty_rate = penalty;
	gk.gk_rate = gk_rate;
	gk.hpass_rate = hpass;
	gk.lpass_rate = lpass;
	gk.spass_rate = spass;
	gk.basic_info.fitness = fitness;

	gk.basic_info.role = eRole_GK;

	strcpy(gk.basic_info.name, name);

	DataSetHandler ds(DS_CUR_PATH);
	ds.Append((GeneralPlayer*)&gk);
}

void Append(char* name, EHeight height, EPhysical physical, EPenalty penalty, attr_t attack, attr_t dribble,
			attr_t def, attr_t lpass, attr_t shoot, attr_t spass, attr_t speed, attr_t team, attr_t fitness)
{
	FieldPlayer fielder;
	fielder.basic_info.height = height;
	fielder.basic_info.physical = physical;
	fielder.basic_info.penalty_rate = penalty;
	fielder.attack_rate = attack;
	fielder.dribble_rate = dribble;
	fielder.def_rate = def;
	fielder.lpass_rate = lpass;
	fielder.shoot_rate = shoot;
	fielder.spass_rate = spass;
	fielder.speed_rate = speed;
	fielder.team_rate = team;
	fielder.basic_info.fitness = fitness;

	fielder.basic_info.role = eRole_Field;

	strcpy(fielder.basic_info.name, name);

	DataSetHandler ds(DS_CUR_PATH);
	ds.Append((GeneralPlayer*)&fielder);
}

void Update(char* name, EHeight height, EPhysical physical, EPenalty penalty, attr_t gk_rate, attr_t hpass, 
			attr_t lpass, attr_t spass, attr_t fitness)
{
	GKPlayer gk;
	gk.basic_info.height = height;
	gk.basic_info.physical = physical;
	gk.basic_info.penalty_rate = penalty;
	gk.gk_rate = gk_rate;
	gk.hpass_rate = hpass;
	gk.lpass_rate = lpass;
	gk.spass_rate = spass;
	gk.basic_info.fitness = fitness;

	gk.basic_info.role = eRole_GK;

	strcpy(gk.basic_info.name, name);

	DataSetHandler ds(DS_CUR_PATH);
	ds.Update((GeneralPlayer*)&gk);
}

void Update(char* name, EHeight height, EPhysical physical, EPenalty penalty, attr_t attack, attr_t dribble,
			attr_t def, attr_t lpass, attr_t shoot, attr_t spass, attr_t speed, attr_t team, attr_t fitness)
{
	FieldPlayer fielder;
	fielder.basic_info.height = height;
	fielder.basic_info.physical = physical;
	fielder.basic_info.penalty_rate = penalty;
	fielder.attack_rate = attack;
	fielder.dribble_rate = dribble;
	fielder.def_rate = def;
	fielder.lpass_rate = lpass;
	fielder.shoot_rate = shoot;
	fielder.spass_rate = spass;
	fielder.speed_rate = speed;
	fielder.team_rate = team;
	fielder.basic_info.fitness = fitness;

	fielder.basic_info.role = eRole_Field;

	strcpy(fielder.basic_info.name, name);

	DataSetHandler ds(DS_CUR_PATH);
	ds.Update((GeneralPlayer*)&fielder);
}

int main()
{
	GKPlayer omer;
	omer.basic_info.height = eHeight_Tall;
	omer.basic_info.physical = ePhysical_Strong;
	omer.basic_info.penalty_rate = ePenalty_Scorer;
	omer.gk_rate = 90;
	omer.hpass_rate = 60;
	omer.lpass_rate = 60;
	omer.spass_rate = 80;
	omer.basic_info.fitness = 75;
	printf("Omer Chen's grade is %d\n", Grade(omer));

	FieldPlayer yariv;
	yariv.basic_info.height = eHeight_Avg;
	yariv.basic_info.physical = ePhysical_Strong;
	yariv.basic_info.penalty_rate = ePenalty_Scorer;
	yariv.attack_rate = 75;
	yariv.dribble_rate = 80;
	yariv.def_rate = 90;
	yariv.lpass_rate = 85;
	yariv.shoot_rate = 85;
	yariv.spass_rate = 90;
	yariv.speed_rate = 75;
	yariv.team_rate = 95;
	yariv.basic_info.fitness = 90;
	printf("Yariv Gavriel's grade is %d\n", Grade(yariv));

	FieldPlayer avihai;
	avihai.basic_info.height = eHeight_Avg;
	avihai.basic_info.physical = ePhysical_Strong;
	avihai.basic_info.penalty_rate = ePenalty_Scorer;
	avihai.attack_rate = 95;
	avihai.dribble_rate = 90;
	avihai.def_rate = 85;
	avihai.lpass_rate = 85;
	avihai.shoot_rate = 95;
	avihai.spass_rate = 90;
	avihai.speed_rate = 95;
	avihai.team_rate = 85;
	avihai.basic_info.fitness = 95;
	printf("Avihai Ben David's grade is %d\n", Grade(avihai));

	strcpy(omer.basic_info.name, "Omer Chen");
	strcpy(yariv.basic_info.name, "Yariv Gavriel");
	strcpy(avihai.basic_info.name, "Avihai Ben David");

	omer.basic_info.role = eRole_GK;
	yariv.basic_info.role = eRole_Field;
	avihai.basic_info.role = eRole_Field;

	GeneralPlayer* playersArr[3];
	playersArr[0] = (GeneralPlayer*)(&omer);
	playersArr[1] = (GeneralPlayer*)(&yariv);
	playersArr[2] = (GeneralPlayer*)(&avihai);

	DataSetHandler ds("DataSet.bin");

	//printf("%d\n",ds.WriteAll(playersArr, 2));

	GeneralPlayer** readArr;
	size_t len = ds.ReadAll(readArr);

	printf("the appending work?? %d\n", ds.Append((GeneralPlayer*)&omer));
	printf("the appending work?? %d\n", ds.Append((GeneralPlayer*)&omer));
	printf("the appending work?? %d\n", ds.Append((GeneralPlayer*)&yariv));
	printf("the appending work?? %d\n", ds.Append((GeneralPlayer*)&omer));
	
	PlayersListHandler listHandler;
	listHandler.LoadDataSet(readArr, len);
	GeneralPlayer* playersByNames[4] = { 0 };
	char* names[4] = { 0 };
	char name0[] = "Yariv Gavriel";
	char name1[] = "Omer Chen";
	names[0] = name0;
	names[1] = name1;
	names[2] = name0;
	names[3] = name0;
	listHandler.FillListByNames(names, playersByNames, 4);
	FREE_PLAYERS_ARR(readArr, len);

	Append("Ben Dotan", eHeight_Avg, ePhysical_Weak, ePenalty_Good, 65, 60, 85, 85, 90);
	Append("Aviv Ben Aharon", eHeight_Short, ePhysical_Weak, ePenalty_Good, 70, 85, 60, 75, 70, 88, 90, 85, 90);
	Update("Aviv Ben Aharon", eHeight_Short, ePhysical_Weak, ePenalty_Good, 70, 0, 60, 75, 70, 88, 90, 0, 90);

	TPInput input;
	if (IOFile::ReadInput(input))
	{
		printf("work :) :)\n");
	}

	TPOutput output;
	strcpy(output.names[0][0], "Omer Chen");
	strcpy(output.names[0][1], "Yariv Gavriel");
	strcpy(output.names[0][2], "Amit Tzoref");
	strcpy(output.names[0][3], "Noam Weinberger");
	strcpy(output.names[0][4], "Yoni Kliger");
	strcpy(output.names[1][0], "Dor Manella");
	strcpy(output.names[1][1], "Avishai Idel");
	strcpy(output.names[1][2], "Avihai Ben David");
	strcpy(output.names[1][3], "Erez Hasson");
	strcpy(output.names[1][4], "Aviv Ben Aharon");
	strcpy(output.names[2][0], "Bar Fux");
	strcpy(output.names[2][1], "Golan Madmon");
	strcpy(output.names[2][2], "Amit Shkuri");
	strcpy(output.names[2][3], "Yotam Cohen");
	strcpy(output.names[2][4], "Hagay Ainemer");

	if (IOFile::WriteOutput(output))
	{
		printf("output work also! :)\n");
	}
	getchar();
	return 0;
}