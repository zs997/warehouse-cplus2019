#ifndef _Data_H
#define _Data_H

#include <fstream>

#include <vector>

#include "myclass.h"

void Read(int flag);

int Write(vector<answer> *ans,double caseNO,double time_cost);

void Check_Data();

#endif