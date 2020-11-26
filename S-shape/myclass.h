#ifndef _MYCLASS_H
#define _MYCLASS_H

#include<iostream>
#include<vector>
using namespace std;

class answer
{
	public: int rowNO,numA,numB,numC;
			double value;
	public:
		answer(int rowNO,int numA,int numB,int numC,double value);

};

class calcul
{
   	public: static void calcul_pij(); //1，计算但是不知道怎么计算的
		    static void calcul_pij(int flag);

		    static void calcul_overallABC(); //2
	    	static void calcul_non_empty();//3

			static void data_processing(); //1 2 3合成
			static void data_processing(int flag);

			static int panduan(int a,int b,int c); //条件判断
			static int round(double x);
			static void doDP(vector<answer> *ans);
};

class location
{
private:	
		int type;
		float pij;
public:
		location(int type);
		location();		
		void set_location(int type); //这个地方需要多研究研究
		void print();
		float get_pij();
		int get_type();
};

class culum
{
private:
		int numA; 
		int numB;
		int numC;
		vector<location> loca ; //不指定大小

		double enterprob; //1
		double Pe; //2
		float lastprob; //2
		double Eli; //3
		
		double Elc;	//3
			
		double cost; //4

public:
		double Eli_ours;
		int lastA;
		int lastB;
		int lastC;
		double Sofar_length;

public:
	culum(int numA,int numB);
	culum(int num);
	culum();
	void print();

	void assignment_abc(int numA,int numB,int numC); //1
	void assignment_abc(int numA,int numB); //1

	
	void calcul_Pe(double Pe_last,double pi_last);
	void calcul_enterprob(); //需要库位分配完毕 2
	void calcul_lastprob(int sumA,int sumB,int sumC); //从通道1到某一通道一共用的ABC个数  2 可以独立计算
	
	void calcul_Elc(int NO); //3 需要计算过 enterprob和lastprob
	
	void calcul_Eli(); //需要库位分配完毕 2
	void calcul_Eli_ours();

	void calcul_cost(int NO,int sumA,int sumB,int sumC,int numA,int numB,int numC); //4  从根源库位分配计算
	void calcul_cost(int NO,int sumA,int sumB,int sumC,double Pe_last,double pi_last); //假设库位分配完毕，Eli enterprob 都计算好了

	double get_cost();
	void set_lastABC(int a,int b,int c);

	double get_enterprob();

	void set_Pe(double Pe);
	double get_Pe();
		
};



#endif