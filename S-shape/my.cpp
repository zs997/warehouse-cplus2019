#include"Data.h"
#include"myclass.h"
#include<ctime>
extern int M,N,f,wa;
extern double wc, a_of_location,b_of_location,c_of_location,a_of_order,b_of_order,c_of_order;
extern int Orderlength;
extern double pij_index[3]; 
extern int overall_A,overall_B,overall_C;
extern double non_empty;

int main()
{
	
	clock_t start,end;
	start=clock();//��ʼ��ʱ
	double time_cost;

	int caseNO=10;
	Read(caseNO);

//	calcul::data_processing();
	calcul::data_processing(caseNO);
	vector<answer> ans;
	calcul::doDP(&ans);

	end=clock(); 
	time_cost=(double)(end-start)/CLOCKS_PER_SEC; //������ʱ 


	Write(&ans,caseNO,time_cost);


/***************�������ɵĽ��������д���ļ�********************************/
//	Check_Data();



/****************************************************************************/
	cout<<"ok"<<endl;	
	return 0;


}

/*****************���ԸĽ��ĵط�**********************************************
Ŀǰ����Ƚ�ɵ�ƣ���
  20622/26971=0.765�ռ��˷� ��κ�������������һ���ܴ�����⣡��
  �ռ���������0.2354  �ر�� ��θĽ�������

�Ľ��� 1* ���ȱ���������Ŀ����Ҫ����ͨ����ϣ�����
	   2* ���������ڴ���ݻ������ƺ�ͨ����С�ۺϷ��䣡����
	   
S-shape �Ѿ��ɹ����� ���� ��η�װ����һЩ
�����������ô���� ���Ҽ�����ȷ�� �ϸ��벻�ϸ�Ľ������֣���

*****************************************************************************/




