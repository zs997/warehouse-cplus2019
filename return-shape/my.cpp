#include"Data.h"
#include"myclass.h"
extern int M,N,f,wa;
extern double wc, a_of_location,b_of_location,c_of_location,a_of_order,b_of_order,c_of_order;
extern int Orderlength;
extern double pij_index[3]; 
extern int overall_A,overall_B,overall_C;
extern double non_empty;

int main()
{
	int caseNO=12;
	Read(caseNO);
	calcul::data_processing();
	vector<answer> ans;
	calcul::doDP(&ans);

	Write(&ans);


/***************�������ɵĽ��������д���ļ�********************************/
	Check_Data();



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
	
*****************************************************************************/




