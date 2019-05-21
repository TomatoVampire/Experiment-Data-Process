#include<iostream>
#include<cmath>
#include <iomanip>
using namespace std;
double getValid(double so,double prec);//²»È·¶¨¶ÈÎªprec 
double getUnPrec(double so,double &units);//²»È·¶¨¶ÈµÄÓÐÐ§Êý×Ö £¬Ö»ÊÇÊý¾Ý´¦Àí¹æÔò 
double get2Deviation(double s1[],double num,double av);
double getStdDeviation(double s1[],double num,double d2,double prec);
double get_tp(double num);
double get_uA(double num,double d,double prec,double &unitA);
double get_uB(double insChange,double prec,double &unitB);
double get_u(double uA,double uB,double tp,double prec,double &unitU);
double getAverage(double s1[],double num,double prec);
double get_ur(double av,double u);
void dataProcess(double s[],double s1[],double num,double change);
void getData(double s[],double num);

int main(){
	double num;//Êý¾Ý¸öÊý 
	double s[40];//Êý¾Ý¾ßÌåÄÚÈÝ 
	double s1[40];//´¦ÀíºóµÄÊý¾ÝÄÚÈÝ! 
	double change,insChange;//ÁãµãÎó²î£¬ÒÇÆ÷Îó²î 
	double tp;//0.683µÄÖÃÐÅ¸ÅÂÊÏÂµÄtpÒò×Ó µÄ´óÐ¡ 
	char unit[10];//µ¥Î» ÊÇ×Ö·û´®£¡ 
	double prec;//ÓÐÐ§Êý×ÖÎ»Êý 
	
	//Êý¾ÝÊäÈë½×¶Î 
	cout<<"´ËÎª¶ÔÓÚÖ±½Ó²âÁ¿Êý¾ÝµÄÊý¾Ý´¦Àí by TomatoLin"<<endl<<endl;
	cout<<"ÊäÈëÄÚÈÝÒ»ÀÀ£º"<<endl;
	cout<<"Êý¾Ý¸öÊý Êý¾ÝÄÚÈÝ ÓÐÐ§Êý×ÖÎ»Êý ÒÇÆ÷Îó²î µ¥Î» ÁãµãÎó²î"<<endl;
	cout<<"¡­¡­¡­¡­¡­¡­¿ªÊ¼ÊäÈëÊý¾Ý¡­¡­¡­¡­¡­¡­"<<endl;
	cout<<"ÊäÈëÊý¾Ý¸öÊý£º£¨²»¶àÓÚ40£©"<<endl;
	cin>>num;
	cout<<"ÊäÈëÊý¾Ý£¨ÒÔ¿Õ¸ñ·Ö¸ô£©£º" <<endl;
    getData(s,num);
    cout<<"ÊäÈëÓÐÐ§Êý×ÖÎ»Êý: "<<endl;
    cin>>prec;
    cout<<"ÊäÈëÒÇÆ÷Îó²î£º"<<endl;
	cin>>insChange;
    cout<<"ÊäÈëµ¥Î»£º"<<endl;
	cin>>unit;
	cout<<"ÊäÈëÁãµãÎó²î£º"<<endl;
	cin>>change;


	cout<<"¡­¡­¡­¡­¡­¡­Êý¾Ý´¦ÀíÖÐ¡­¡­¡­¡­¡­¡­"<<endl;
	double unitA,unitB,unitU;//Èý¸ö²»È·¶¨¶ÈµÄ¾«¶È¡­ 
	dataProcess(s,s1,num,change);
	double av=getAverage(s1,num,prec);
	double d2=get2Deviation(s1,num,av);
	double d=getStdDeviation(s1,num,d2,prec);
	double uA=get_uA(num,d,prec, unitA);
	double uB=get_uB(insChange,prec, unitB);
	tp=get_tp(num);
	double u=get_u(uA,uB,tp,prec,unitU);
	double ur=get_ur(av,u);
	
	cout<<"¡­¡­¡­¡­¡­¡­½á¹ûÊä³ö¡­¡­¡­¡­¡­¡­"<<endl;
	//cout<<"av= "<<av<<endl;//test
	cout.setf(ios::fixed);
	cout<<"Êý¾ÝÆ½¾ùÖµ£ºaverage= "<<fixed<< setprecision(prec+1)<<av<<" "<<unit<<endl;
	cout<<"Êý¾Ý±íÊ¾£º"<<endl<<"{ X="<<av<<" ¡À ";
	cout.unsetf(ios::fixed);
	
	cout.setf(ios::fixed);
	cout<<fixed<< setprecision(unitU) <<u<<" "<<unit<<endl;
	cout.unsetf(ios::fixed);
	
	cout<<"{ P=0.683"<<endl;
	cout<<"{ ur="<<ur<<"%"<<endl;
	
	cout.setf(ios::fixed);
	cout<<"AÀà²»È·¶¨¶È uA="<<fixed<< setprecision(unitA) <<uA<<' '<<unit<<endl;
	cout.unsetf(ios::fixed);
	
	cout.setf(ios::fixed);
	cout<<"BÀà²»È·¶¨¶È uB="<<fixed<< setprecision(unitB)<<uB<<' '<<unit<<endl;
	cout.unsetf(ios::fixed);
	
	cout.setf(ios::fixed);
	cout<<"ºÏ³É²»È·¶¨¶È u="<<fixed<< setprecision(unitU)<<u<<' '<<unit<<endl;
	cout.unsetf(ios::fixed);
	
	cout<<"tpÒò×Ó tp="<<tp<<endl;
	cout<<"·½²î ="<<d2<<endl;
	cout<<"±ê×¼²î ="<<d<<endl;
	cout<<"¡­¡­¡­¡­¡­¡­½áÊø¡­¡­¡­¡­¡­¡­"<<endl;
	cout<<"°´0ÍË³ö£¬»òÕßÓÒÉÏ½ÇX¹Ø±Õ"<<endl;
	
	char stoop;
	do{
		cin>>stoop;
	}while(stoop!='0');
	//system("pause");
}

double getValid(double so,double prec){
//ÔÝÊ±ÎªprecÎ» 
    double s1,ss;//s1¾ø¶ÔÖµ£¬ss×îÖÕ½á¹û 
    s1=so;
    
	double ten_more=pow(10.000f,prec);//ÓÐÐ§Êý×ÖÎ»Êý 
	if(floor(s1)==s1) ss=s1;//¸ù±¾Ã»ÓÐÐ¡Êý 
    else if(s1>1){//´óÓÚ1 
    	ss=floor(s1 * ten_more + 0.5) / ten_more;//Ê¹ÓÃfloorÏòÏÂÈ¡ÕûÈ»ºóÉ§²Ù×÷È¡precÎ»Ð¡Êý 
	} 
	else if(s1<1){//Ð¡ÓÚ1 
		double s=s1;
		double flag=0;
		double i=1;
		do{
			s=s*10.000f;
			flag=floor(s);
			if(flag==0) i=i+1;
		}while(flag==0);
		double tens=pow(10.0,i+1);
		ss=floor(s1*tens+0.5);//ËÄÉáÎåÈë 
		//if((ss/tens)<s1) ss=ss+1;
		ss=ss/tens;
	} 
	return ss;
}

double getUnPrec(double so,double &units){
	double s1,ss;//²¢Ã»ÓÐ¾ø¶ÔÖµemm 
    s1=so;
    double i=1;
	if(floor(s1)==s1) ss=s1;//¸ù±¾Ã»ÓÐÐ¡Êý 
    else if(s1>=1){//´óÓÚ1 
    	ss=floor(s1 * 100.000f + 0.5) / 100.000f;//Ê¹ÓÃfloorÏòÏÂÈ¡ÕûÈ»ºóÉ§²Ù×÷È¡Á½Î»Ð¡Êý 
	}
	else if(s1<1){//Ð¡ÓÚ1 
		double s=s1;
		double flag=0;
		i=1;
		do{
			s=s*10.000f;
			flag=floor(s);
			if(flag==0) i=i+1;
		}while(flag==0);
		double tens=pow(10.0,i+1);
		ss=floor(s1*tens);
		if((ss/tens)<s1) ss=ss+1;//²»ËÄÉáÎåÈë£¬È«¶¼½øÎ»£»Èç¹ûºóÃæ¶¼ÊÇ0¾Í²»ÐèÒª 
		ss=ss/tens;
	} 
	units=i+1;
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
	//cout<<av<<endl;//test
	av=getValid(av,prec);
	//av=getUnPrec(av,prec);//
	cout<<av<<endl;//
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

double get_uA(double num,double d,double prec,double &unitA){//!
	double n1=sqrt(num);
	double uA=d/n1;
	uA=getUnPrec(uA,unitA);
	return uA;
}

double get_uB(double insChange,double prec,double &unitB){//!
	double uB;
	uB=insChange/sqrt(3.00f);
	uB=getUnPrec(uB,unitB);
	return uB;
}

double get_u(double uA,double uB,double tp,double prec,double &unit){//!
	double u;
	u=sqrt(tp*tp*uA*uA+uB*uB);
	u=getUnPrec(u,unit);
	return u;
}

double get_ur(double av,double u){
	double ur;
	ur=u/av;
	ur=ur*100.00f;
	return ur;
}
