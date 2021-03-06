#include"myclass.h"
#include <cmath> 
#include<ctime>
#include<algorithm>
 int M,N,f,wa;
 double wc,a_of_location,b_of_location,c_of_location,a_of_order,b_of_order,c_of_order;
 int Orderlength;
 int overall_A,overall_B,overall_C;
 double pij_index[3]; 
 double non_empty;
double G[24+2][24+2][24+2];

/*******************************calcul类*************************************************************************/
 void calcul::calcul_pij()
	{
		int	all=M*N;
		pij_index[0]=Orderlength*a_of_order/(all*a_of_location);
		pij_index[1]=Orderlength*b_of_order/(all*b_of_location);
		pij_index[2]=Orderlength*c_of_order/(all*c_of_location);
		
	}
 void calcul::calcul_pij(int flag)
 {
	switch(flag)
	{
		case 1:
				pij_index[0]=4.0/85;
				pij_index[1]=3.0/500;
				pij_index[2]=1.0/840;
				break;
		case 2:
				pij_index[0]=1.0/34;
				pij_index[1]=3.0/250;
				pij_index[2]=1.0/210;
				break;
		case 3:
				pij_index[0]=4.0/17;
				pij_index[1]=3.0/100;
				pij_index[2]=1.0/168;
				break;
		case 4:
				pij_index[0]=5.0/34;
				pij_index[1]=3.0/50;
				pij_index[2]=1.0/42;
				break;
		case 5:
				pij_index[0]=8.0/17;
				pij_index[1]=3.0/50;
				pij_index[2]=1.0/84;
				break;
		case 6:
				pij_index[0]=5.0/17;
				pij_index[1]=3.0/25;
				pij_index[2]=1.0/21;
				break;
		default:
				calcul::calcul_pij();
				break;
	}
 }

 
 void calcul::calcul_overallABC()
 {
	int all=N*M;
	overall_C=calcul::round(all*c_of_location);		//c是整数 先不舍弃c
	overall_A=calcul::round(all*a_of_location);
	overall_B=all-overall_A-overall_C;
	
 }

 void calcul::calcul_non_empty()
 {
	non_empty=1-pow((1-pij_index[0]),overall_A)*pow((1-pij_index[1]),overall_B)*pow((1-pij_index[2]),overall_C);
 }

void calcul::data_processing() //1~9对应九个案例 其他数输入  调用内部计算pij函数 计算方法不对
 {
	calcul::calcul_pij(); //内部数据 pij 第*案例
	calcul::calcul_overallABC();
	calcul::calcul_non_empty();
 }
void calcul::data_processing(int flag)
{
	calcul::calcul_pij(flag);
	calcul::calcul_overallABC();
	calcul::calcul_non_empty();
}

 int calcul::panduan(int a,int b,int c)
{
	/***符合货物总数条件的输出0，不符合输出1 ***/
	if((a<=overall_A)&&(b<=overall_B)&&(c<=overall_C))
		return 0;
	else
		return 1;
}

 int calcul::round(double x)  
 {
	 /**********四舍五入******/
	 int y=ceil(x);
	 return (x-y)<0.5?y:(y+1);	
 }

 double calcul::max(double x,double y)
 {
	 return x>y?x:y;
 }


 /************************动态规划算法的核心*************************************************************/
 void calcul::doDP(vector<answer> *ans)
{

	culum ***v;
	culum **vv;
	v=new culum **[M];	
	for(int m=0;m<M;m++)
	{	
		if(m==0)
		{
			int all=N;
			v[0]=new culum * [all+1];
			vv=new culum *[all+1];
			culum cu; 
			for(int i=0;i<=all;i++)
				{
					 v[0][i]=new culum[all-i+1];
					 vv[i]=new culum[all-i+1];
				   
					for(int j=0;j<=all-i;j++)		
					{
						int k=all-i-j;
						if(calcul::panduan(i,j,k))//判断是否满足各类数目小于总货物数
							continue;
						
						cu.calcul_cost(1,i,j,k,i,j,k); // 第一批i,j,k到某通道用到的货物个数统计，第二批ijk该通道货物数统计				
						cu.set_lastABC(0,0,0);
						cu.Sofar_length=cu.get_cost();
						v[m][i][j]=cu;

						cu.do_ours(i,j,k);
						vv[i][j]=cu;

					}
				}
		}		
		else if(m!=(M-1)) //不是最后一个通道也不是第一个通道的情况 
		{
			culum cu;
			culum cu_temp; 
			culum cu_temp1;

			int all=N*(m+1);
			v[m]=new culum *[all+1];
			for(int i=0;i<=all;i++)
				{
					v[m][i]=new culum[all-i+1];
					for(int j=0;j<=all-i;j++)		
					{
						int k=all-i-j;
						if(calcul::panduan(i,j,k)) //判断是否满足各类数目小于总货物数
							continue;					
						int all_last=N*m;
						

						cu.Sofar_length=9999;
						//穷举前一个通道所有状态解，就是查询数组，并且和本阶段的状态结合，取最优
						for(int o=0;o<=all_last;o++)//穷举上一个通道解的状态
							{
								for(int p=0;p<=all_last-o;p++)
								{	
									int q=all_last-o-p;
									if(calcul::panduan(o,p,q)) //判断是否满足各类数目小于总货物数
										continue;
									int ma=i-o; 	// (i-o) m通道a个数 
									int mb=j-p;		//(j-p)  m通道b个数
									int mc=k-q;  	//(all-i-j)-(all_last-o-p)  m通道c个数
									if((ma<0)||(mb<0)||(mc<0)) //m通道不可行  但是没有用最优化条件
										continue;	
									if((ma+mb+mc)!=N)  //这一项是必须的 保证ma(或者mb,mc)不超过N
										continue;  //只有加和为N才能继续运行 否则跳转
								//	int lastI=o-v[m-1][o][p].lastA;
								//	int lastJ=p-v[m-1][o][p].lastB;
								//	int lastK=q-v[m-1][o][p].lastC;
								//	if(ma>lastI||(ma+mb)>(lastI+lastJ)) //最优化条件，条件要搞清楚
								//		continue;	
								
									cu_temp=v[0][ma][mb]; //单个通道的库位分配 只有库位分配 ELi enterprob有价值							
									cu_temp1=vv[ma][mb]; //单个通道的库位分配 只有库位分配 ELi enterprob有价值												
									cu_temp.calcul_cost(m+1,i,j,k,v[m-1][o][p].get_firstprob(),v[m-1][o][p].get_enterprob()); //计算lastprob,Elc,以及cost 
									cu_temp1.calcul_cost(m+1,i,j,k,v[m-1][o][p].get_firstprob(),v[m-1][o][p].get_enterprob());
									
									if(cu_temp.get_cost()>cu_temp1.get_cost()) //assignment 默认是1
									{
										cu_temp=cu_temp1;
										cu_temp.assignment_mode=0;
									}															
									
									if(v[m-1][o][p].Sofar_length+cu_temp.get_cost()<cu.Sofar_length)
									{
										cu=cu_temp; //除了Sofar_length和 lastABC都已经更新完毕

										cu.Sofar_length=v[m-1][o][p].Sofar_length+cu.get_cost();

										cu.set_lastABC(o,p,q);//cu.lastA=o;cu.lastB=p;cu.lastC=q;									
										//这里m=2~M-2是第3~M-1通道 ，o p 是状态(m,i,j)的上一状态最优解
									}						

								}

							}

						v[m][i][j]=cu;						
					}
				}
		
		}
		else //对应最后一个通道情况 m=M-1时
		{
			int i=overall_A;
			int j=overall_B;
			int k=overall_C;
			v[m]=new culum *[1];
			v[m][0]=new culum[1];

			int all_last=N*m;	
			
			culum cu; //1 代表通道号
			cu.Sofar_length=9999;
			culum cu_temp; 
			//穷举前一个通道所有状态解，就是查询数组，并且和本阶段的状态结合，取最优
			for(int o=0;o<=all_last;o++)//穷举上一个通道解的状态
				{
				for(int p=0;p<=all_last-o;p++)
					{	
						int q=all_last-o-p;
						if(calcul::panduan(o,p,q)) //判断是否满足各类数目小于总货物数
							continue;
						int ma=i-o; 	// (i-o) m通道a个数 
						int mb=j-p;		//(j-p)  m通道b个数
						int mc=k-q;  	//(all-i-j)-(all_last-o-p)  m通道c个数	
						if((ma+mb+mc)!=N)
							continue;
						if(ma<0||mb<0||mc<0) //m通道不可行  但是没有用最优化条件
							continue;				
					//  int lastI=o-v[m-1][o][p].lastA;
					//	int lastJ=p-v[m-1][o][p].lastB;
					//  int lastK=q-v[m-1][o][p].lastC;
					//	if(ma>lastI||(ma+mb)>(lastI+lastJ)) //最优化条件
					//		continue;					
																
						cu_temp=v[0][ma][mb];

						cu_temp.calcul_cost(m+1,i,j,k,v[m-1][o][p].get_firstprob(),v[m-1][o][p].get_enterprob());
					
						if(v[m-1][o][p].Sofar_length+cu_temp.get_cost()<cu.Sofar_length)
						{
							cu=cu_temp;
							cu.Sofar_length=v[m-1][o][p].Sofar_length+cu.get_cost();
							cu.set_lastABC(o,p,q);//cu.lastA=o;cu.lastB=p;cu.lastC=q;			
							//这里m=2~M-2是第3~M-1通道 所以 o p 是状态(m,i,j)的第一个通道最优解				
						}	

					}
				}
			v[m][0][0]=cu;						
		}
	}


/********追踪解的算法,解的保存****************************************************************************************/
	int orA=v[M-1][0][0].lastA; 	
	int orB=v[M-1][0][0].lastB;
	int orC=v[M-1][0][0].lastC;

	answer reco(M,v[M-1][0][0].numA,v[M-1][0][0].numB,v[M-1][0][0].numC,v[m-1][0][0].get_cost(),v[m-1][0][0].assignment_mode);
	(*ans).push_back(reco);

	for(int ii=M-2;ii>=0;ii--) // 若 M==7 ii从5开始 v[5][][]
	{
		 reco.set_answer(ii+1,v[ii][orA][orB].numA,v[ii][orA][orB].numB,v[ii][orA][orB].numC,v[ii][orA][orB].get_cost(),v[ii][orA][orB].assignment_mode);
		(*ans).push_back(reco);
	
		int orA_temp,orB_temp;

		orA_temp=v[ii][orA][orB].lastA;orB_temp=v[ii][orA][orB].lastB;		
		orC=v[ii][orA][orB].lastC;
		orA=orA_temp;	
		orB=orB_temp;
	}
	answer reco1(M,overall_A,overall_B,overall_C,v[M-1][0][0].Sofar_length,v[M-1][0][0].assignment_mode);
	(*ans).push_back(reco1);
	//dataFile<<"/* v["<<M-1<<"]["<<overall_A<<"]["<<overall_B<<"]="<<v[M-1][0][0].Sofar_length<<" */"<<endl; //最优解
/****************************以上追踪算法*********************************************************************************/



}

/****************************************************************************************************************************/
 


/***********************定义类location***********************************************************************************/
location::location(int type) //改成构造函数？
	{	
		this->type=type;
		pij=pij_index[type];
	}
location::location()
	{
		type=0;
		pij=0;
	}

void location::set_location(int type) //这个地方需要多研究研究
	{
		this->type=type;
		pij=pij_index[type];
	}

void location::print()
{
	cout<<"type="<<type<<" "<<"pij="<<pij<<endl;
}

float location::get_pij()
{
	return pij;
}
int  location::get_type()
{
	return type;
}
/****************************************************************************************************************************/



/************************定义类culum*****************************************************************************************/
culum::culum(int numA,int numB)
	{
		this->numA=numA;
		this->numB=numB;
		this->numC=N-numA-numC;

		lastA=-1;
		lastB=-1;
		lastC=-1;

		for(int i=0;i<numA;i++)
		{
			location aa(0);
			loca.push_back(aa);
		}
		for(;i<(numA+numB);i++)
		{
			location aa(1);
			loca.push_back(aa);
		}
		for(;i<N;i++)
		{
			location aa(2);
			loca.push_back(aa);
		}
	}
culum::culum()
{
	numA=0;
	numB=0;
	numC=0;

	for(int i=0;i<N;i++)
	{
		location aa(0);
		loca.push_back(aa);
	}
			
	lastA=-1;
	lastB=-1;
	lastC=-1;
	assignment_mode=1;

}

void culum::assignment_abc(int numA,int numB,int numC)
{
		this->numA=numA;
		this->numB=numB;
		this->numC=numC;
		
		for(int i=0;i<numA;i++)
		{
			loca[i].set_location(0);
		}
		for(;i<(numA+numB);i++)
		{
			loca[i].set_location(1);
		}
		for(;i<N;i++)
		{
			loca[i].set_location(2);
		}
}

void culum::assignment_abc(int numA,int numB)
{
	
	assignment_abc(numA,numB,N-numA-numB);
	
}

void culum::assignment_abc_sym(int numA,int numB,int numC) //对称分配
{
		this->numA=numA;
		this->numB=numB;
		this->numC=numC;

		int half_A=ceil(numA/2.0),half_B=ceil(numB/2.0); //numA/2 若是小数向上取整，整除开，不变化
		
		for(int i=0;i<half_A;i++)
		{
			loca[i].set_location(0);
		}
		for(;i<(half_A+half_B);i++)
		{
			loca[i].set_location(1);
		}
		for(;i<(half_A+half_B+numC);i++)
		{
			loca[i].set_location(2);
		}
		for(;i<(half_A+numB+numC);i++)
		{
			loca[i].set_location(1);
		}
		for(;i<N;i++)
		{
			loca[i].set_location(0);
		}
}

void culum::assignment_abc_sym(int numA,int numB) //对称分配
{
	assignment_abc_sym(numA,numB,N-numA-numB); 
}
void culum::assignment_abc(int numA,int numB,int numC,int flag)
{
	if(flag)
		assignment_abc(numA,numB,numC);
	else
		assignment_abc_sym(numA,numB,numC);
}
void culum::calcul_Gi()
{
 /**************这个函数有待大改进*************************/
	int gl,gc;
 
	for(gl=1;gl<=N+1;gl++)
		for(gc=1;gc<=gl;gc++)
			G[N+1][gc][gl]=gl;
	
	for(gl=1;gl<=N;gl++)
		for(gc=1;gc<=gl;gc++)
			G[N][gc][gl]=(1-loca[N-1].get_pij())*G[N+1][int(gc+0.5*f+wc)][int(calcul::max(gl,gc+0.5*f+wc))]
			+loca[N-1].get_pij()*G[N+1][int(0.5*f+wc)][int(calcul::max(gl,0.5*f+wc))];

	for(int j=N-1;j>=1;j--)
	{
		for(gl=1;gl<=j;gl++)
			for(gc=1;gc<=gl;gc++)
				G[j][gc][gl]=(1-loca[j-1].get_pij())*G[j+1][int(gc+f)][int(calcul::max(gl,gc+f))]
			+loca[j-1].get_pij()*G[j+1][f][int(calcul::max(gl,f))];
	
	}
	Gi=G[1][1][1];
}

void culum::calcul_enterprob()
	{
		double multi=1;
		for(int i=0;i<N;i++)
		{
			multi=multi*(1-loca[i].get_pij());
		}
		enterprob=1-multi;
	}


void culum::calcul_lastprob(int sumA,int sumB,int sumC)
{
	lastprob=pow((1-pij_index[0]),overall_A-sumA)*pow((1-pij_index[1]),overall_B-sumB)*pow((1-pij_index[2]),overall_C-sumC);
}

void culum::calcul_firstprob(double firstprob_last,double Pi_last)
{
	firstprob=firstprob_last*(1-Pi_last);
}

void culum::calcul_Eli_r()
{
	double sum=0;
	double multi;
	for(int j=1;j<=N;j++)
	{
		double base=(wc+j*f-0.5*f)*(loca[j-1].get_pij());			
		 multi=1;
		for(int h=j+1;h<=N;h++) 
		{
			multi=multi*(1-loca[h-1].get_pij());		
		}			
		sum+=2*multi*base;		
	}
	Eli_r=sum;	
}

void culum::calcul_Eli_1()
{
	double sum=0;
	int half_N=ceil(N/2.0);
	double multi;
	double base;
	for(int j=half_N+1;j<=N;j++) //起点应为 halfN
	{
		 base=(wc+(N-j)*f+0.5*f)*(loca[j-1].get_pij());			
		 multi=1;
		for(int h=half_N+1;h<j;h++) //起点应为 halfN
		{
			multi=multi*(1-loca[h-1].get_pij());		
		}	
		sum+=2*multi*base;		
	}
	Eli_1=sum;	
}

void culum::calcul_Eli_2()
{
	double sum=0;
	int half_N=ceil(N/2.0);
	double base;
	double multi;
	for(int j=1;j<=half_N;j++) //起点为0
	{
		 base=(wc+j*f-0.5*f)*(loca[j-1].get_pij());			
		 multi=1;
		for(int h=j+1;h<=half_N;h++) //起点为j
		{
			multi=multi*(1-loca[h-1].get_pij());		
		}			
		
		sum+=2*multi*base;		
	}
	Eli_2=sum;	
}

void culum::calcul_Eli_ours()
{
	calcul_Eli_r();
	calcul_Eli_1();
	calcul_Eli_2();
}

void culum::do_ours(int numA,int numB,int numC)
{
	assignment_abc_sym(numA,numB,numC);  //对称分配库位
	calcul_enterprob();
	calcul_Gi();
	calcul_Eli_r();
}
void culum::do_ours(int numA,int numB,int numC,int flag)
{
	assignment_abc(numA,numB,numC,flag);  //对称分配库位
	calcul_enterprob();
	calcul_Gi();
	calcul_Eli_r();
}
void culum::calcul_Eli() //s-shape 需要知道firstprob,lastprob,enterprob;
{	
		double sum;
		sum=Eli_r*firstprob*lastprob+(2*wc+N*f)*enterprob*(firstprob+lastprob-2*firstprob*lastprob)
			+(1-firstprob)*(1-lastprob)*2*(2*wc+N*f-Gi);
		Eli=sum;
}


void culum::calcul_Elc(int NO)
{
	Elc=2*wa*(NO-1)*enterprob*lastprob;
}

void culum::calcul_cost(int NO,int sumA,int sumB,int sumC,int numA,int numB,int numC)
{
	/***********************从根源计算，适合于通道1*********************/
	assignment_abc(numA,numB,numC);  //第一通道一定是这样分配
	
	calcul_Gi();
	calcul_enterprob();
	calcul_Eli_r();	

	set_firstprob(1.0);
	calcul_lastprob(sumA,sumB,sumC);

	calcul_Elc(NO);

	calcul_Eli();
	cost=(Eli+Elc)/non_empty;
}


void culum::calcul_cost(int NO,int sumA,int sumB,int sumC,double firstprob_last,double Pi_last)
{	
	/***********分配好库位，计算完enterprob,Eli,再进行调用************************/
	calcul_lastprob(sumA,sumB,sumC); //这两个参数改变 影响了路径长度
	calcul_firstprob(firstprob_last,Pi_last);
	
	calcul_Elc(NO);
	
	calcul_Eli();

	cost=(Eli+Elc)/non_empty;
}

void culum::calcul_cost(int NO,int sumA,int sumB,int sumC,int numA,int numB,int numC,double Pe_last,double Pi_last)
{
	/**********************检验计算的时候使用************************************************/
		assignment_abc(numA,numB,numC); 

		calcul_enterprob();
		calcul_lastprob(sumA,sumB,sumC);
		calcul_Elc(NO);
		calcul_Eli_r();
		calcul_Eli();
		cost=(Eli+Elc)/non_empty;

}

void culum::print()
{
	cout<<"该通道数据如下:"<<endl;
	cout<<"*********************"<<endl;
	cout<<"numA="<<numA<<" "<<"numB="<<numB<<" "<<"numC="<<numC<<" "<<"enterprob="<<enterprob<<" "<<"Eli="<<Eli<<endl;
	for(int i=0;i<N;i++)
		loca[i].print();

}



double culum::get_cost()
{
	return cost;
}

void culum::set_lastABC(int a,int b,int c)
{
	lastA=a;
	lastB=b;
	lastC=c;
}

double culum::get_enterprob()
{
	return enterprob;
}

void culum::set_firstprob(double firstprob)
{
	this->firstprob=firstprob;
}

double culum::get_firstprob()
{
	return firstprob;
}

double culum::get_Gi()
{
	return Gi;
}




/**********************************************************************************************************************/



/************************结果类函数*************************************************************************************/
answer::answer(int rowNO,int numA,int numB,int numC,double value,int assignment_mode)
{
	this->rowNO=rowNO;
	this->numA=numA;
	this->numB=numB;
	this->numC=numC;
	this->value=value;
	this->assignment_mode=assignment_mode;
}

answer::answer()
{
	this->rowNO=0;
	this->numA=0;
	this->numB=0;
	this->numC=0;
	this->value=0;
	this->assignment_mode=0;
}

void answer::set_answer(int rowNO,int numA,int numB,int numC,double value,int assignment_mode)
{
	this->rowNO=rowNO;
	this->numA=numA;
	this->numB=numB;
	this->numC=numC;
	this->value=value;
	this->assignment_mode=assignment_mode;
}