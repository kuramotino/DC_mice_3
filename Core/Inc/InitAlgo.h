/*
 * InitAlgo.h
 *
 *  Created on: 2023/06/03
 *      Author: Ryu
 */

#ifndef INC_INITALGO_H_
#define INC_INITALGO_H_

#include "Map.h"
#include "MiceStatus.h"
#include "MakePotential.h"
#include "Planning.h"
#include "IssueCommand.h"
#include "InputData.h"
#include "Pass_Generator.h"

extern Algorizm::Map map_obj;
extern Algorizm::MakePotential potential_obj;
extern Algorizm::MiceStatus status_obj;
extern Algorizm::Planning plan_obj;
extern Algorizm::IssueCommand issue_obj;
extern Algorizm::Pass_Generator pass_gene_obj;

void InitAlgo();
void UpDataAlgo();
void M_UpDataAlgo(int index);
void No_Zip_M_UpDataAlgo(int index);

#endif /* INC_INITALGO_H_ */
