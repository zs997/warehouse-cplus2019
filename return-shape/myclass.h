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
   	public: static void calcul_pij(); //1�����㵫�ǲ�֪����ô�����
		   

		    static void calcul_overallABC(); //2
	    	static void calcul_non_empty();//3

			static void data_processing(); //1 2 3�ϳ�

			static int panduan(int a,int b,int c); //�����ж�
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
		void set_location(int type); //����ط���Ҫ���о��о�
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
		vector<location> loca ; //��ָ����С

		double enterprob;
		double Eli;

		float lastprob;
		double Elc;	
		
		double cost;

public:
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

	void calcul_Eli(); //��Ҫ��λ������� 2

	void calcul_enterprob(); //��Ҫ��λ������� 2
	void calcul_lastprob(int sumA,int sumB,int sumC); //��ͨ��1��ĳһͨ��һ���õ�ABC����  2 ���Զ�������
	
	void calcul_Elc(int NO); //3 ��Ҫ����� enterprob��lastprob

	void calcul_cost(int NO,int sumA,int sumB,int sumC,int numA,int numB,int numC); //4  �Ӹ�Դ��λ�������
	void calcul_cost(int NO,int sumA,int sumB,int sumC); //�����λ������ϣ�Eli enterprob ���������
	
	double get_cost();
	void set_lastABC(int a,int b,int c);
		
};



#endif