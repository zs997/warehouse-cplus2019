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
	start=clock();	//��ʱ��ʼ

	int caseNO=6;
	double time_cost;

	Read(caseNO);
	calcul::data_processing(); //������������ ������ ��ʾ����ĳһ������
	//calcul::data_processing();
	vector<answer> ans;
	calcul::doDP(&ans);

	end=clock(); //��ʱ����
    time_cost=(double)(end-start)/CLOCKS_PER_SEC;
	Write(&ans,time_cost,caseNO);

	


/***************�������ɵĽ��������д���ļ�********************************/
//	Check_Data();



/****************************************************************************/
//	cout<<"time_cost="<<time_cost<<"s"<<endl;
	cout<<"ok"<<endl;	
	return 0;


}

/*****************���ԸĽ��ĵط�**********************************************
Ŀǰ����Ƚ�low����
  20622/26971=0.765�ռ��˷� ��κ�������������һ���ܴ�����⣡��
  �ռ���������0.2354  �ر�� ��θĽ�������
���� ����ͨ������7����� ������ABC�޷��������� ����������һЩ��һ��
�Ľ��� 1* ���ȱ���������Ŀ����Ҫ����ͨ����ϣ�����
	   2* ���������ڴ���ݻ������ƺ�ͨ����С�ۺϷ��䣡����
	   
S-shape �Ѿ��ɹ����� ���� ��η�װ����һЩ
�����������ô���� ���Ҽ�����ȷ�� �ϸ��벻�ϸ�Ľ������֣���

*****************************************************************************/




