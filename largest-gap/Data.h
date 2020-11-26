#ifndef _Data_H
#define _Data_H

#include <fstream>

#include <vector>

#include "myclass.h"
#include<cmath>

void Read(int flag);

int Write(vector<answer> *ans,double time_cost,int caseNO);

void Check_Data();

#endif