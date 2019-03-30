#include<iostream>
#include<cmath>
using namespace std;
class U{//������ȷ������ 
	public:
		void getValue();//��Щ���Ǽ������� 
		void getPlace();
		void getData();//���ݾ������� 
		void updValue(double nval);
		void updPlace(double nplace);
		void updData(double da);
		double showValue();//������cout���������ֵ���� 
		double showPlace();
		double showData();  
	private:
		double value;//��ȷ����ֵ  
		double place;//��Ч����λ�� 
		double data;
};

void U::getValue(){
    cin>>value;
}
void U::getPlace(){
	cin>>place; 
}
void U::getData(){
	cin>>data;
}
void U::updValue(double nval){
	value=nval;
}
void U::updPlace(double nplace){
	//��δ������ 
	place=nplace;
}
void U::updData(double da){
	data=da;
}
double U::showValue(){
	return value;
}
double U::showPlace(){
   return place;
}
double U::showData(){
	return data;
}

double smallPlace(U u1,U u2){
	double smaller;
	smaller=u1.showValue();
	if(u2.showValue()<smaller) smaller=u2.showValue();
	return smaller;
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
		ss=floor(s1*tens+0.5);//�������� 
		if((ss/tens)<s1) ss=ss+1;
		ss=ss/tens;
	} 
	return ss;
}
int main(){
	U ux;//ux ? xy
	U uy;//��Ԫ����������������֣���name �޹أ� 
	U uz;//�����ȷ���� 
	char op;//����� ��ʹ��switchת�� 
	int swi;//�������������ڣ����� 
	cout<<"��Ϊ���ڼ�Ӳ�����ȷ���ȵĶ�Ԫ���� by TomatoLin"<<endl;
	cout<<"Ŀǰ��֧�ֶ�Ԫ����ļ�Ӳ�����ȷ���ȣ����ҽ��޼Ӽ��˳�"<<endl<<endl;
	cout<<"��������һ����"<<endl;
	cout<<"(��һX�͵ڶ�ԪY��)���� ��ȷ���� ��Ч����λ�� XY�������� ���Z������"<<endl;
	
	cout<<"��������������ʼ�������ݡ�����������"<<endl;
	cout<<"��һ������X: "<<endl; 
	cout<<"�����������ݣ���������ƽ��ֵ����"<<endl;
	ux.getData();
	cout<<"���벻ȷ���ȵ�ֵ��"<<endl;
	ux.getValue();
	cout<<"���벻ȷ���ȵ���Ч����λ����"<<endl;
	ux.getPlace();
	

	cout<<"�ڶ�������Y: "<<endl;//����ڶ��� 
	cout<<"�����������ݣ���������ƽ��ֵ����"<<endl;
	uy.getData();
	cout<<"���벻ȷ���ȵ�ֵ��"<<endl;
	uy.getValue() ;
	cout<<"���벻ȷ���ȵ���Ч����λ����"<<endl;
	uy.getPlace() ;
	
 cout<<"����XY֮����������"<<endl;//1 2֮�������� 
	cin>>op;
	int flag=0;
	do{
		if(flag==1){
		cout<<"ERROR! �����������ǷǷ��ַ������������������: (����+-*/)"<<endl;
		cin>>op;
	    }
	flag=0;
	switch(op){//ֱ��������Ū����� 
		case '+':uz.updData(ux.showData()+uy.showData());break; 
		case '-':uz.updData(ux.showData()-uy.showData());break;
		case '*':uz.updData(ux.showData()*uy.showData());break;
		case '/':uz.updData(ux.showData()/uy.showData());break; 
		default:{
			//cout<<"ERROR! �����������ǷǷ��ַ������������������: (����+-*/)"<<endl;
			flag=1;
			//cin>>op;
			break;
		}
	}
	
  }while(flag==1);
  
	cout<<"���������������ݴ����С�����������"<<endl;

	switch(op){//ֱ��������Ū����� 
		case '+':; 
		case '-':{
			double val;
			val=sqrt(ux.showValue()*ux.showValue()+uy.showValue()*uy.showValue());
			uz.updValue(getValid(val,smallPlace(ux,uy)));
			break;
		}
		case '*':;
		case '/':{
			double val;
			val=ux.showValue()/ux.showData()*ux.showValue()/ux.showData()+uy.showValue()/uy.showData()*uy.showValue()/uy.showData();
            val=uz.showData()*sqrt(val);
            uz.updValue(getValid(val,smallPlace(ux,uy)));
		    break;
		} 
		default:break;
	}
  

cout<<"������������������������������"<<endl;
cout<<"���ݵı��ʽΪ��X "<<op<<" Y =Z"<<endl;
cout<<"Z������Ϊ��"<<uz.showData()<<endl;
cout<<"��Ӳ�����ȷ����Ϊ��"<<uz.showValue()<<endl;
cout<<"����������������������������"<<endl;
cout<<"��0�˳����������Ͻ�X�ر�"<<endl;
char stoop;//���������󴥳��� 
	do{
		cin>>stoop;
	}while(stoop!='0');

	return 0;
}
