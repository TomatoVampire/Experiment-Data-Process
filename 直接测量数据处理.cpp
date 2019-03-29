#include<iostream>
#include<cmath>
using namespace std;
double getValid(double so,double prec);//不确定度为prec 
double getUnPrec(double so);//不确定度的有效数字 ，只是数据处理规则 
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
	double num;//数据个数 
	double s[40];//数据具体内容 
	double s1[40];//处理后的数据内容! 
	double change,insChange;//零点误差，仪器误差 
	double tp;//0.683的置信概率下的tp因子 的大小 
	char unit[10];//单位 是字符串！ 
	double prec;//有效数字位数 
	
	//数据输入阶段 
	cout<<"此为对于直接测量数据的数据处理 by TomatoLin"<<endl<<endl;
	cout<<"输入内容一览："<<endl;
	cout<<"数据个数 数据内容 有效数字位数 仪器误差 单位 零点误差"<<endl;
	cout<<"………………开始输入数据………………"<<endl;
	cout<<"输入数据个数：（不多于40）"<<endl;
	cin>>num;
	cout<<"输入数据（以空格分隔）：" <<endl;
    getData(s,num);
    cout<<"输入有效数字位数: "<<endl;
    cin>>prec;
    cout<<"输入仪器误差："<<endl;
	cin>>insChange;
    cout<<"输入单位："<<endl;
	cin>>unit;
	cout<<"输入零点误差："<<endl;
	cin>>change;


	cout<<"………………数据处理中………………"<<endl;
	dataProcess(s,s1,num,change);
	double av=getAverage(s1,num,prec);
	double d2=get2Deviation(s1,num,av);
	double d=getStdDeviation(s1,num,d2,prec);
	double uA=get_uA(num,d,prec);
	double uB=get_uB(insChange,prec);
	tp=get_tp(num);
	double u=get_u(uA,uB,tp,prec);
	double ur=get_ur(av,u);
	
	cout<<"………………结果输出………………"<<endl;
	cout<<"数据平均值：average= "<<av<<" "<<unit<<endl;
	cout<<"数据表示："<<endl<<"{ X="<<av<<" +- "<<u<<" "<<unit<<endl;
	cout<<"{ P=0.683"<<endl;
	cout<<"{ ur="<<ur<<"%"<<endl;
	cout<<"A类不确定度 uA="<<uA<<endl;
	cout<<"B类不确定度 uB="<<uB<<endl;
	cout<<"tp因子 tp="<<tp<<endl;
	cout<<"方差 ="<<d2<<endl;
	cout<<"标准差 ="<<d<<endl;
	cout<<"………………结束………………"<<endl;
	cout<<"按0退出，或者右上角X关闭"<<endl;
	
	char stoop;
	do{

		cin>>stoop;
	}while(stoop!='0');
	//system("pause");
}

double getValid(double so,double prec){
//暂时为prec位 
    double s1,ss;//s1绝对值，ss最终结果 
    s1=so;
    
	double ten_more=pow(10.000f,prec);//有效数字位数 
	if(floor(s1)==s1) ss=s1;//根本没有小数 
    else if(s1>1){//大于1 
    	ss=floor(s1 * ten_more + 0.5) / ten_more;//使用floor向下取整然后骚操作取prec位小数 
	} 
	else if(s1<1){//小于1 
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
	double s1,ss;//并没有绝对值emm 
    s1=so;
 
	if(floor(s1)==s1) ss=s1;//根本没有小数 
    else if(s1>=1){//大于1 

    	ss=floor(s1 * 100.000f + 0.5) / 100.000f;//使用floor向下取整然后骚操作取两位小数 
	}
	else if(s1<1){//小于1 
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
