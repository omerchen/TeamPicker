#include <stdlib.h>
#include <stdio.h>
#include "FileHandler.h"
#include "FileLogger.h"
#include "FootballCalculator.h"
#include "DataSetHandler.h"
#include "PlayersListHandler.h"

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

	printf("the appending work?? %d\n", ds.AppendPlayer((GeneralPlayer*)&omer));
	printf("the appending work?? %d\n", ds.AppendPlayer((GeneralPlayer*)&omer));
	printf("the appending work?? %d\n", ds.AppendPlayer((GeneralPlayer*)&yariv));
	printf("the appending work?? %d\n", ds.AppendPlayer((GeneralPlayer*)&omer));

	
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
	getchar();
	return 0;
}