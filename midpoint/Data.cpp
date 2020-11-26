#include"Data.h"

extern int M,N,f,wa;
extern double wc,a_of_location,b_of_location,c_of_location,a_of_order,b_of_order,c_of_order;
extern int Orderlength;
extern int overall_A,overall_B,overall_C;
extern double pij_index[3]; 
extern double non_empty;

/*************************读入原始数据*****************************************************/
void Read(int flag)
{
	ifstream infile;
	switch (flag)
	{
	case 1: 	infile.open("..\\data\\input\\input-case1.txt"); 
				break;
	case 2: 	infile.open("..\\data\\input\\input-case2.txt"); 
				break;
	case 3: 	infile.open("..\\data\\input\\input-case3.txt"); 
				break;
	case 4: 	infile.open("..\\data\\input\\input-case4.txt"); 
				break;
	case 5: 	infile.open("..\\data\\input\\input-case5.txt"); 
				break;
	case 6: 	infile.open("..\\data\\input\\input-case6.txt"); 
				break;
	case 7: 	infile.open("..\\data\\input\\input-case7.txt"); 
				break;
	case 8: 	infile.open("..\\data\\input\\input-case8.txt"); 
				break;
	case 9: 	infile.open("..\\data\\input\\input-case9.txt"); 
				break;
	case 10: 	infile.open("..\\data\\input\\input-case10.txt"); 
				break;
	case 11: 	infile.open("..\\data\\input\\input-case11.txt"); 
				break;
	case 12: 	infile.open("..\\data\\input\\input-case12.txt"); 
				break;
	default:	 infile.open("input\\input.txt");
					break;
	}

    if(!infile) cout<<"Read-data-error"<<endl; 
    double t1;
 
	vector<double>ve;
   
    while(infile>>t1)             //按空格读取，遇到空白符结束  
    {
        ve.push_back(t1);         
    }

    M=ve[0];
	Orderlength=ve[1];

	a_of_order=ve[2];
	b_of_order=ve[3];
	c_of_order=ve[4];

	wc=ve[5];
	f=ve[6]; 
	wa=ve[7]; 

	a_of_location=ve[8]; 
	b_of_location=ve[9]; 
	c_of_location=ve[10]; 

	N=ve[11];

	infile.close();

}
/*****************************************************************************************************************/


int Write(vector<answer> *ans,int caseNO,double time_cost)
{
	
/***********************************文件操作，写入解**************************************************************/
	ofstream dataFile;          //定义文件操作对象 fstream dataFile; 对应out情况
	dataFile.open("output\\output.txt",ios::out);  //创建一个文件 ios::out 代表重写 没有文件时候可以自动创建
	if(!dataFile)            //检查文件是否创建成功
	{
		cout<<"error-open-write"<<endl;
		return 0;   
	}
/****************************************************************************************************************/
	vector<answer>::const_iterator iterator = (*ans).begin();
	double sum=0;

	for(;iterator!=((*ans).end()-1);iterator++) //最后一个对象是总和 概念不一样
	{	 
		dataFile<<(*iterator).rowNO<<"   "<<(*iterator).numA<<"   "<<(*iterator).numB
			<<"   "<<(*iterator).numC<<"   "<<(*iterator).value<<"   "<<(*iterator).assignment_mode<<endl;
		sum+=(*iterator).value;
	}

	double average_routing_length=(*iterator).value;//最后一个对象
		dataFile<<(*iterator).rowNO<<"   "<<(*iterator).numA<<"   "<<(*iterator).numB
			<<"   "<<(*iterator).numC<<"   "<<average_routing_length<<"  "<<(*iterator).assignment_mode<<endl; //最后一个对象，表示总和

		dataFile<<"average_routing_length="<<average_routing_length<<endl
			<<"plus_cost=sum(cost(i))="<<sum<<endl
			<<"delta 1=plus_cost-average_routing_length="<<sum-average_routing_length<<endl;
		if((fabs(sum-average_routing_length)<0.01)&&(sum>0)&&(average_routing_length>0))
			dataFile<<"delta 1 合格"<<endl;
		else
			dataFile<<"delta 1 不合格"<<endl;
	dataFile<<"caseNO="<<caseNO<<endl<<"time_cost="<<time_cost<<endl<<"mid_point"<<endl;

	dataFile.close();
	return 1;

}


void Check_Data()
{
/******************读取解数据***********************************************/
	 ifstream infile;	
	 infile.open("output\\output.txt"); 	
	 if(!infile) cout<<"Read-data-error"<<endl; 
	 
	 double t1;  
	 vector<double>ve;   
    while(infile>>t1)             //按空格读取，遇到空白符结束  
	 {
        ve.push_back(t1);         
	}

	int numA,numB,numC;
	double length_cal=ve.back(); ve.pop_back(); //出栈,文件存储的路径总长度
	double length_check=0; //通过解 验算的路径总长度

	for(int i=0;i<4;i++)
		ve.pop_back();

	int sumA=0,sumB=0,sumC=0;
	
	culum cu_check;
	double Pe_temp,Pi_temp;
	int NO=1;
	while(!ve.empty())
	{
		ve.pop_back();
		numC=ve.back();	ve.pop_back();
		numB=ve.back();	ve.pop_back();
		numA=ve.back();	ve.pop_back();	
		ve.pop_back();
		sumA+=numA;sumB+=numB;sumC+=numC;
		if(NO==1)
		cu_check.calcul_cost(NO,sumA,sumB,sumC,numA,numB,numC);
		else
		cu_check.calcul_cost(NO,sumA,sumB,sumC,numA,numB,numC,Pe_temp,Pi_temp);
		
		Pi_temp=cu_check.get_enterprob();

		length_check+=cu_check.get_cost();

		NO++;
	}
	 
	 infile.close();
/*****************************************************************************************/

/***************************写入检验解数据，*************************************************/
	 ofstream dataFile;  
   	 dataFile.open("output\\output.txt",ios::app);
	 
	 dataFile<<"length_check="<<length_check<<endl
	 <<"delta 2=length_check-length_cal="<<length_check-length_cal<<endl;
    	if((length_check-length_cal<0.01)&&(length_check>0)&&(length_cal>0))
			dataFile<<"delta 2 合格"<<endl;
		else
			dataFile<<"delta 2 不合格"<<endl;

	 dataFile.close();
 /***************************************************************************************/
}

