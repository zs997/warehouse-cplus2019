#ifndef _MYCLASS_H
#define _MYCLASS_H

#include<iostream>
#include<vector>
using namespace std;

class answer
{
	public: int rowNO,numA,numB,numC;
			double value;
			int assignment_mode;
	public:
		answer(int rowNO,int numA,int numB,int numC,double value,int assignment_mode);
		answer();
		void set_answer(int rowNO,int numA,int numB,int numC,double value,int assignment_mode);

};

class calcul
{
   	public: static void calcul_pij(); //1�����㵫�ǲ�֪����ô�����		   
			static void calcul_pij(int flag);
		    static void calcul_overallABC(); //2
	    	static void calcul_non_empty();//3

			static void data_processing(); //1 2 3�ϳ�
			static void data_processing(int flag); //1 2 3�ϳ�
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

		vector<location> loca ; //��ָ����С

		double enterprob; //1
		double firstprob;
		double lastprob; //2

		double Eli_1;
		double Eli_2;
		double Eli_r;
		double Eli; //3
		
		double Elc;	//3	
		double cost; //4

public:	
		int numA; 
		int numB;
		int numC;
		int lastA;
		int lastB;
		int lastC;
		double Sofar_length;
		int assignment_mode;

public:
	culum(int numA,int numB);
	culum(int num);
	culum();
	void print();

	void assignment_abc(int numA,int numB,int numC); //1
	void assignment_abc(int numA,int numB); //1
	void assignment_abc_sym(int numA,int numB,int numC); //�ԳƷ���
	void assignment_abc_sym(int numA,int numB); //�ԳƷ���
	
	void calcul_enterprob(); //��Ҫ��λ������� 2
	void calcul_lastprob(int sumA,int sumB,int sumC); //��ͨ��1��ĳһͨ��һ���õ�ABC����  2 ���Զ�������
	void calcul_firstprob(double firstprob_last,double Pi_last);

	void calcul_Elc(int NO); //3 ��Ҫ����� enterprob��lastprob
	
	void calcul_Eli_r();
	void calcul_Eli_1();
	void calcul_Eli_2();
	void calcul_Eli_ours();
	void calcul_Eli(); //��Ҫ��λ������� 2

	void do_ours(int numA,int numB,int numC);

	void calcul_cost(int NO,int sumA,int sumB,int sumC,int numA,int numB,int numC); //4  �Ӹ�Դ��λ�������
	void calcul_cost(int NO,int sumA,int sumB,int sumC,double firstprob_last,double Pi_last); //�����λ������ϣ�Eli enterprob ���������
	void calcul_cost(int NO,int sumA,int sumB,int sumC,int numA,int numB,int numC,double Pe_last,double Pi_last);
	
	

	void set_lastABC(int a,int b,int c);
	void set_firstprob(double firstprob);

	double get_enterprob();
	double get_cost();
	double get_firstprob();

	
	
		
};



#endif