/*
 * InitAlgo.cpp
 *
 *  Created on: 2023/06/03
 *      Author: Ryu
 */

#include "Map.h"
#include "MiceStatus.h"
#include "MakePotential.h"
#include "Planning.h"
#include "IssueCommand.h"
#include "InputData.h"
#include "InitAlgo.h"
#include "Init_Controll_Objs.h"

Algorizm::Map map_obj;
Algorizm::MakePotential potential_obj;
Algorizm::MiceStatus status_obj;
Algorizm::Planning plan_obj;
Algorizm::IssueCommand issue_obj;
Algorizm::Pass_Generator pass_gene_obj;

void InitAlgo()
{
	map_obj.SetInputStatus(&input_obj, &status_obj);
	map_obj.Init_Row_Column();
	potential_obj.SetMap(&map_obj);
	plan_obj.SetObj(&status_obj, &potential_obj, &map_obj);
	issue_obj.SetPlan(&plan_obj);
	issue_obj.SetPassGene(&pass_gene_obj);
	pass_gene_obj.SetPlan(&plan_obj);
}

void UpDataAlgo()
{
	issue_obj.Tansaku();
	if(fail_obj.isFail)
	{
		plan_obj.UndoMazeData();
	}
}

void M_UpDataAlgo(int index)
{
	pass_gene_obj.PassZipSetting(true);
	issue_obj.Saitan(index);
	if(fail_obj.isFail)
	{
		plan_obj.UndoMazeData();
	}
}

void No_Zip_M_UpDataAlgo(int index)
{
	pass_gene_obj.PassZipSetting(false);
	issue_obj.Saitan(index);
	if(fail_obj.isFail)
	{
		plan_obj.UndoMazeData();
	}
}
