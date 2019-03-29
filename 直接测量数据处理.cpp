#include<iostream>
#include<cmath>
using namespace std;
double getValid(double so,double prec);//��ȷ����Ϊprec 
double getUnPrec(double so);//��ȷ���ȵ���Ч���� ��ֻ�����ݴ������ 
double get2Deviation(double s1[],double num,double av);
double getStdDeviation(double s1[],double num,double d2,double prec);
double get_tp(double num);
double get_uA(double num,double d,double prec);
double get_uB(double insChange,double prec);
double get_u(double uA,double uB,double tp,double prec);
double getAverage(double s1[],double num,double prec);
double get_ur(double av,double u);
void dataProcess(double s[],double s1[],double num,double change);
void getData(double s[],double num);

int main(){
	double num;//���ݸ��� 
	double s[40];//���ݾ������� 
	double s1[40];//��������������! 
	double change,insChange;//������������ 
	double tp;//0.683�����Ÿ����µ�tp���� �Ĵ�С 
	char unit[10];//��λ ���ַ����� 
	double prec;//��Ч����λ�� 
	
	//��������׶� 
	cout<<"��Ϊ����ֱ�Ӳ������ݵ����ݴ��� by TomatoLin"<<endl<<endl;
	cout<<"��������һ����"<<endl;
	cout<<"���ݸ��� �������� ��Ч����λ�� ������� ��λ ������"<<endl;
	cout<<"��������������ʼ�������ݡ�����������"<<endl;
	cout<<"�������ݸ�������������40��"<<endl;
	cin>>num;
	cout<<"�������ݣ��Կո�ָ�����" <<endl;
    getData(s,num);
    cout<<"������Ч����λ��: "<<endl;
    cin>>prec;
    cout<<"����������"<<endl;
	cin>>insChange;
    cout<<"���뵥λ��"<<endl;
	cin>>unit;
	cout<<"���������"<<endl;
	cin>>change;


	cout<<"���������������ݴ����С�����������"<<endl;
	dataProcess(s,s1,num,change);
	double av=getAverage(s1,num,prec);
	double d2=get2Deviation(s1,num,av);
	double d=getStdDeviation(s1,num,d2,prec);
	double uA=get_uA(num,d,prec);
	double uB=get_uB(insChange,prec);
	tp=get_tp(num);
	double u=get_u(uA,uB,tp,prec);
	double ur=get_ur(av,u);
	
	cout<<"������������������������������"<<endl;
	cout<<"����ƽ��ֵ��average= "<<av<<" "<<unit<<endl;
	cout<<"���ݱ�ʾ��"<<endl<<"{ X="<<av<<" +- "<<u<<" "<<unit<<endl;
	cout<<"{ P=0.683"<<endl;
	cout<<"{ ur="<<ur<<"%"<<endl;
	cout<<"A�಻ȷ���� uA="<<uA<<endl;
	cout<<"B�಻ȷ���� uB="<<uB<<endl;
	cout<<"tp���� tp="<<tp<<endl;
	cout<<"���� ="<<d2<<endl;
	cout<<"��׼�� ="<<d<<endl;
	cout<<"����������������������������"<<endl;
	cout<<"��0�˳����������Ͻ�X�ر�"<<endl;
	
	char stoop;
	do{

		cin>>stoop;
	}while(stoop!='0');
	//system("pause");
}

double getValid(double so,double prec){
//��ʱΪprecλ 
    double s1,ss;//s1����ֵ��ss���ս�� 
    s1=so;
    
	double ten_more=pow(10.000f,prec);//��Ч����λ�� 
	if(floor(s1)==s1) ss=s1;//����û��С�� 
    else if(s1>1){//����1 
    	ss=floor(s1 * ten_more + 0.5) / ten_more;//ʹ��floor����ȡ��Ȼ��ɧ����ȡprecλС�� 
	} 
	else if(s1<1){//С��1 
		double s=s1;
		double flag=0;
		double i=1;
		do{
			s=s*10.000f;
			flag=floor(s);
			if(flag==0) i=i+1;
		}while(flag==0);
		double tens=pow(10.0,i+1);
		ss=floor(s1*tens);
		if((ss/tens)<s1) ss=ss+1;
		ss=ss/tens;
	} 
	return ss;
}

double getUnPrec(double so){
	double s1,ss;//��û�о���ֵemm 
    s1=so;
 
	if(floor(s1)==s1) ss=s1;//����û��С�� 
    else if(s1>=1){//����1 

    	ss=floor(s1 * 100.000f + 0.5) / 100.000f;//ʹ��floor����ȡ��Ȼ��ɧ����ȡ��λС�� 
	}
	else if(s1<1){//С��1 
		double s=s1;
		double flag=0;
		double i=1;
		do{
			s=s*10.000f;
			flag=floor(s);
			if(flag==0) i=i+1;
		}while(flag==0);
		double tens=pow(10.0,i+1);
		ss=floor(s1*tens);
		if((ss/tens)<s1) ss=ss+1;
		ss=ss/tens;
	} 
	return ss;
} 
 
void getData(double s[],double num){
	int i;
	for(i=0;i<num;i++){
		cin>>s[i];
	}
}

void dataProcess(double s[],double s1[],double num,double change){
	int i;
	for(i=0;i<num;i++){
		s1[i]=s[i]-change;
	}
}

double getAverage(double s[],double num,double prec){//!
	double av,sum=0;
	int i;
	for(i=0;i<num;i++){
		sum+=s[i];
	}
	av=sum/num;
	av=getValid(av,prec);
	return av;
}

double get2Deviation(double s[],double num,double av){
	int i;
	double sum=0;
	for(i=0;i<num;i++){
		sum=sum+(s[i]-av)*(s[i]-av);
	}
	return sum;
}

double getStdDeviation(double s[],double num,double d2,double prec){//!
	double sum2;
	sum2=d2/(num-1);
	sum2=sqrt(sum2);
	sum2=getValid(sum2,prec);
	return sum2;
}

double get_tp(double num){
	double tp;
	int n=floor(num);
	switch(n)
	{
		case 3: tp=1.32;break;
		case 4: tp=1.20;break;
		case 5: tp=1.14;break;
		case 6: tp=1.11;break;
		case 7: tp=1.09;break;
		case 8: tp=1.08;break;
		case 9: tp=1.07;break;
		case 10: tp=1.06;break;
		case 15: tp=1.04;break;
		case 20: tp=1.03;break;
		default: tp=1;break;
	}
	return tp;
}

double get_uA(double num,double d,double prec){//!
	double n1=sqrt(num);
	double uA=d/n1;
	uA=getUnPrec(uA);
	return uA;
}

double get_uB(double insChange,double prec){//!
	double uB;
	uB=insChange/sqrt(3);
	uB=getUnPrec(uB);
	return uB;
}

double get_u(double uA,double uB,double tp,double prec){//!
	double u;
	u=sqrt(tp*tp*uA*uA+uB*uB);
	u=getUnPrec(u);
	return u;
}

double get_ur(double av,double u){
	double ur;
	ur=u/av;
	ur=ur*100;
	return ur;
}
