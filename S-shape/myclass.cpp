#include"myclass.h"
#include <cmath> 
 int M,N,f,wa;
 double wc,a_of_location,b_of_location,c_of_location,a_of_order,b_of_order,c_of_order;
 int Orderlength;
 int overall_A,overall_B,overall_C;
 double pij_index[3]; 
 double non_empty;

/*******************************calcul��*************************************************************************/
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
	overall_C=calcul::round(all*c_of_location);
	overall_A=calcul::round(all*a_of_location);
	overall_B=all-overall_C-overall_A;
 }
 void calcul::calcul_non_empty()
 {
	non_empty=1-pow((1-pij_index[0]),overall_A)*pow((1-pij_index[1]),overall_B)*pow((1-pij_index[2]),overall_C);
 }

void calcul::data_processing() //1~9��Ӧ�Ÿ����� ����������  �����ڲ�����pij���� ���㷽������
 {
	calcul::calcul_pij(); //�ڲ����� pij ��*����
	calcul::calcul_overallABC();
	calcul::calcul_non_empty();
 }

void calcul::data_processing(int flag) //1~9��Ӧ�Ÿ����� ����������  �����ڲ�����pij���� ���㷽������
 {
	calcul::calcul_pij(flag); //�ڲ����� pij ��*����
	calcul::calcul_overallABC();
	calcul::calcul_non_empty();
 }


 int calcul::panduan(int a,int b,int c)
{
	/***���ϻ����������������0�����������1 ***/
	if((a<=overall_A)&&(b<=overall_B)&&(c<=overall_C))
		return 0;
	else
		return 1;
}

 int calcul::round(double x)  
 {
	 /**********��������******/
	 int y=ceil(x);
	 return (x-y)<0.5?y:(y+1);	
 }

 /************************��̬�滮�㷨�ĺ���*************************************************************/
 void calcul::doDP(vector<answer> *ans)
{
	culum ***v;
	v=new culum **[M];	
	for(int m=0;m<M;m++)
	{	
		if(m==0)
		{
			int all=N;
			v[0]=new culum * [all+1];
			for(int i=0;i<=all;i++)
				{
					 v[0][i]=new culum[all-i+1];
					for(int j=0;j<=all-i;j++)		
					{
						int k=all-i-j;
						if(calcul::panduan(i,j,k))//�ж��Ƿ����������ĿС���ܻ�����
							continue;
						culum cu; 			

						cu.calcul_cost(1,i,j,k,i,j,k); // ��һ��i,j,k��ĳͨ���õ��Ļ������ͳ�ƣ��ڶ���ijk��ͨ��������ͳ��
				
						cu.set_lastABC(0,0,0);

						cu.Sofar_length=cu.get_cost();
						v[m][i][j]=cu;
					}
				}
		}		
		else if(m!=(M-1)) //�������һ��ͨ��Ҳ���ǵ�һ��ͨ������� 
		{
			int all=N*(m+1);
			v[m]=new culum *[all+1];
			for(int i=0;i<=all;i++)
				{
					v[m][i]=new culum[all-i+1];
					for(int j=0;j<=all-i;j++)		
					{
						int k=all-i-j;
						if(calcul::panduan(i,j,k)) //�ж��Ƿ����������ĿС���ܻ�����
							continue;					
						int all_last=N*m;
						
						culum cu;
						culum cu_temp; 

						cu.Sofar_length=9999;
						//���ǰһ��ͨ������״̬�⣬���ǲ�ѯ���飬���Һͱ��׶ε�״̬��ϣ�ȡ����
						for(int o=0;o<=all_last;o++)//�����һ��ͨ�����״̬
							{
								for(int p=0;p<=all_last-o;p++)
								{	
									int q=all_last-o-p;
									if(calcul::panduan(o,p,q)) //�ж��Ƿ����������ĿС���ܻ�����
										continue;
									int ma=i-o; 	// (i-o) mͨ��a���� 
									int mb=j-p;		//(j-p)  mͨ��b����
									int mc=k-q;  	//(all-i-j)-(all_last-o-p)  mͨ��c����
									if((ma<0)||(mb<0)||(mc<0)) //mͨ��������  ����û�������Ż�����
										continue;	
									if((ma+mb+mc)!=N)  //��һ���Ǳ���� ��֤ma(����mb,mc)������N
										continue;  //ֻ�мӺ�ΪN���ܼ������� ������ת
								//	int lastI=o-v[m-1][o][p].lastA;
								//	int lastJ=p-v[m-1][o][p].lastB;
								//	int lastK=q-v[m-1][o][p].lastC;
								//	if(ma>lastI||(ma+mb)>(lastI+lastJ)) //���Ż�����������Ҫ�����
								//		continue;	
								
								cu_temp=v[0][ma][mb]; //����ͨ���Ŀ�λ���� ֻ�п�λ���� ELi enterprob�м�ֵ
							
											
								cu_temp.calcul_cost(m+1,i,j,k,v[m-1][o][p].get_Pe(),v[m-1][o][p].get_enterprob()); //����lastprob,Elc,�Լ�cost 
								//��������������ڼ���Pe
								
									if(v[m-1][o][p].Sofar_length+cu_temp.get_cost()<cu.Sofar_length)
									{
										cu=cu_temp; //����Sofar_length�� lastABC���Ѿ��������

										cu.Sofar_length=v[m-1][o][p].Sofar_length+cu.get_cost();

										cu.set_lastABC(o,p,q);//cu.lastA=o;cu.lastB=p;cu.lastC=q;									
									//����m=2~M-2�ǵ�3~M-1ͨ�� ��o p ��״̬(m,i,j)����һ״̬���Ž�
									}														
								}

							}

						v[m][i][j]=cu;						
					}
				}
		
		}
		else //��Ӧ���һ��ͨ����� m=M-1ʱ
		{
			int i=overall_A;
			int j=overall_B;
			int k=overall_C;
			v[m]=new culum *[1];
			v[m][0]=new culum[1];

			int all_last=N*m;	
			
			culum cu; //1 ����ͨ����
			cu.Sofar_length=9999;
			culum cu_temp; 
			//���ǰһ��ͨ������״̬�⣬���ǲ�ѯ���飬���Һͱ��׶ε�״̬��ϣ�ȡ����
			for(int o=0;o<=all_last;o++)//�����һ��ͨ�����״̬
				{
				for(int p=0;p<=all_last-o;p++)
					{	
						int q=all_last-o-p;
						if(calcul::panduan(o,p,q)) //�ж��Ƿ����������ĿС���ܻ�����
							continue;
						int ma=i-o; 	// (i-o) mͨ��a���� 
						int mb=j-p;		//(j-p)  mͨ��b����
						int mc=k-q;  	//(all-i-j)-(all_last-o-p)  mͨ��c����	
						if((ma+mb+mc)!=N)
							continue;
						if(ma<0||mb<0||mc<0) //mͨ��������  ����û�������Ż�����
							continue;				
					//  int lastI=o-v[m-1][o][p].lastA;
					//	int lastJ=p-v[m-1][o][p].lastB;
					//  int lastK=q-v[m-1][o][p].lastC;
					//	if(ma>lastI||(ma+mb)>(lastI+lastJ)) //���Ż�����
					//		continue;					
																
						cu_temp=v[0][ma][mb];

						cu_temp.calcul_cost(m+1,i,j,k,v[m-1][o][p].get_Pe(),v[m-1][o][p].get_enterprob());
					
						if(v[m-1][o][p].Sofar_length+cu_temp.get_cost()<cu.Sofar_length)
						{
							cu=cu_temp;
							cu.Sofar_length=v[m-1][o][p].Sofar_length+cu.get_cost();
							cu.set_lastABC(o,p,q);//cu.lastA=o;cu.lastB=p;cu.lastC=q;			
							//����m=2~M-2�ǵ�3~M-1ͨ�� ���� o p ��״̬(m,i,j)�ĵ�һ��ͨ�����Ž�				
						}	
									
					}
				}
			v[m][0][0]=cu;						
		}
	}



/********׷�ٽ���㷨,��ı���****************************************************************************************/
	int orA=v[M-1][0][0].lastA; 	
	int orB=v[M-1][0][0].lastB;
	int orC=v[M-1][0][0].lastC;

	answer reco(M,overall_A-orA,overall_B-orB,overall_C-orC,v[m-1][0][0].get_cost());
	(*ans).push_back(reco);

	for(int ii=M-2;ii>=0;ii--) // �� M==7 ii��5��ʼ v[5][][]
	{
		answer reco(ii+1,orA-v[ii][orA][orB].lastA,orB-v[ii][orA][orB].lastB,orC-v[ii][orA][orB].lastC,v[ii][orA][orB].get_cost());
		(*ans).push_back(reco);
	
		int orA_temp,orB_temp;

		orA_temp=v[ii][orA][orB].lastA;orB_temp=v[ii][orA][orB].lastB;		
		orC=v[ii][orA][orB].lastC;
		orA=orA_temp;	
		orB=orB_temp;

	}
	answer reco1(M,overall_A,overall_B,overall_C,v[M-1][0][0].Sofar_length);
	(*ans).push_back(reco1);
	//dataFile<<"/* v["<<M-1<<"]["<<overall_A<<"]["<<overall_B<<"]="<<v[M-1][0][0].Sofar_length<<" */"<<endl; //���Ž�
/****************************����׷���㷨*********************************************************************************/



}

/****************************************************************************************************************************/
 


/***********************������location***********************************************************************************/
location::location(int type) //�ĳɹ��캯����
	{	
		this->type=type;
		pij=pij_index[type];
	}
location::location()
	{
		type=0;
		pij=0;
	}

void location::set_location(int type) //����ط���Ҫ���о��о�
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



/************************������culum*****************************************************************************************/
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
		this->numA=0;
		this->numB=0;
		this->numC=0;

	for(int i=0;i<N;i++)
	{
		location aa(0);
		loca.push_back(aa);
	}
			
		lastA=-1;
		lastB=-1;
		lastC=-1;

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


void culum::calcul_enterprob()
	{
		double multi=1;
		for(int i=0;i<N;i++)
		{
			multi=multi*(1-loca[i].get_pij());
		}
		enterprob=1-multi;
	}

void culum::calcul_Pe(double Pe_last,double pi_last) 
{
	Pe=Pe_last*(1-pi_last)+(1-Pe_last)*pi_last;

}

void culum::calcul_lastprob(int sumA,int sumB,int sumC)
{
	lastprob=pow((1-pij_index[0]),overall_A-sumA)*pow((1-pij_index[1]),overall_B-sumB)*pow((1-pij_index[2]),overall_C-sumC);
}

void culum::calcul_Eli_ours()
{
		double sum=0;
		for(int j=0;j<N;j++)
		{
			double base=(wc+(j+1)*f-0.5*f)*(loca[j].get_pij());			
			double multi=1;
			for(int h=j+1;h<N;h++)
			{
				multi=multi*(1-loca[h].get_pij());		
			}			
		
			sum+=2*multi*base;		
		}
		Eli_ours=sum;	
}

void culum::calcul_Eli() //s-shape ��Ҫ֪��pe,lastprob,enterprob;
{	
	//	calcul_Eli_ours();
		double sum;
		sum=Eli_ours*Pe*lastprob+(2*wc+N*f)*enterprob*(1-Pe*lastprob);
		Eli=sum;
}


void culum::calcul_Elc(int NO)
{
	Elc=2*wa*(NO-1)*enterprob*lastprob;
}

void culum::calcul_cost(int NO,int sumA,int sumB,int sumC,int numA,int numB,int numC)
{
	/***********************�Ӹ�Դ���㣬�ʺ���ͨ��1*********************/
	assignment_abc(numA,numB,numC); 
	set_Pe(1); //��ʼ��Pe
	calcul_enterprob();
	calcul_lastprob(sumA,sumB,sumC);
	calcul_Elc(NO);
	calcul_Eli_ours();
	calcul_Eli();
	cost=(Eli+Elc)/non_empty;
}
void culum::calcul_cost(int NO,int sumA,int sumB,int sumC,double Pe_last,double pi_last)
{
	calcul_Pe(Pe_last,pi_last);
	/***********����ÿ�λ��������enterprob,Eli,�ٽ��е���************************/
	calcul_lastprob(sumA,sumB,sumC);
	calcul_Elc(NO);
	
	calcul_Eli();
	cost=(Eli+Elc)/non_empty;
}

void culum::print()
{
	cout<<"��ͨ����������:"<<endl;
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


void culum::set_Pe(double Pe)
{
	this->Pe=Pe;
}
double culum::get_Pe()
{
	return Pe;
}




/**********************************************************************************************************************/



/************************����ຯ��*************************************************************************************/
answer::answer(int rowNO,int numA,int numB,int numC,double value)
{
	this->rowNO=rowNO;
	this->numA=numA;
	this->numB=numB;
	this->numC=numC;
	this->value=value;

}