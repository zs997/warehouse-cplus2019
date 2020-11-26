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


/***************检验刚完成的结果，并且写入文件********************************/
	Check_Data();



/****************************************************************************/
	cout<<"ok"<<endl;	
	return 0;


}

/*****************可以改进的地方**********************************************
目前程序比较傻逼！！
  20622/26971=0.765空间浪费 如何合理设置数组是一个很大的问题！！
  空间利用率是0.2354  特别低 如何改进？？？

改进点 1* 优先遍历货物数目，不要遍历通道组合！！！
	   2* 分配数组内存根据货物限制和通道大小综合分配！！！ 
	
*****************************************************************************/




