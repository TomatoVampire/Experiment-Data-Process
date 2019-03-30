#include<iostream>
#include<cmath>
using namespace std;
class U{//建立不确定度类 
	public:
		void getValue();//这些都是键盘输入 
		void getPlace();
		void getData();//数据具体内容 
		void updValue(double nval);
		void updPlace(double nplace);
		void updData(double da);
		double showValue();//并不是cout输出，返回值！！ 
		double showPlace();
		double showData();  
	private:
		double value;//不确定度值  
		double place;//有效数字位数 
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
	//？未定规则 
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
		ss=floor(s1*tens+0.5);//四舍五入 
		if((ss/tens)<s1) ss=ss+1;
		ss=ss/tens;
	} 
	return ss;
}
int main(){
	U ux;//ux ? xy
	U uy;//二元运算的两个对象名字（和name 无关） 
	U uz;//结果不确定度 
	char op;//运算符 ，使用switch转换 
	int swi;//运算符换整型入口（？） 
	cout<<"此为对于间接测量不确定度的二元运算 by TomatoLin"<<endl;
	cout<<"目前仅支持二元计算的间接测量不确定度，而且仅限加减乘除"<<endl<<endl;
	cout<<"输入内容一览："<<endl;
	cout<<"(第一X和第二元Y的)数据 不确定度 有效数字位数 XY间的运算符 结果Z的数据"<<endl;
	
	cout<<"………………开始输入数据………………"<<endl;
	cout<<"第一个数据X: "<<endl; 
	cout<<"输入数据内容（不含误差，即平均值）："<<endl;
	ux.getData();
	cout<<"输入不确定度的值："<<endl;
	ux.getValue();
	cout<<"输入不确定度的有效数字位数："<<endl;
	ux.getPlace();
	

	cout<<"第二个数据Y: "<<endl;//输入第二个 
	cout<<"输入数据内容（不含误差，即平均值）："<<endl;
	uy.getData();
	cout<<"输入不确定度的值："<<endl;
	uy.getValue() ;
	cout<<"输入不确定度的有效数字位数："<<endl;
	uy.getPlace() ;
	
 cout<<"输入XY之间的运算符："<<endl;//1 2之间的运算符 
	cin>>op;
	int flag=0;
	do{
		if(flag==1){
		cout<<"ERROR! 运算符输入的是非法字符！请重新输入运算符: (仅限+-*/)"<<endl;
		cin>>op;
	    }
	flag=0;
	switch(op){//直接在这里弄运算吧 
		case '+':uz.updData(ux.showData()+uy.showData());break; 
		case '-':uz.updData(ux.showData()-uy.showData());break;
		case '*':uz.updData(ux.showData()*uy.showData());break;
		case '/':uz.updData(ux.showData()/uy.showData());break; 
		default:{
			//cout<<"ERROR! 运算符输入的是非法字符！请重新输入运算符: (仅限+-*/)"<<endl;
			flag=1;
			//cin>>op;
			break;
		}
	}
	
  }while(flag==1);
  
	cout<<"………………数据处理中………………"<<endl;

	switch(op){//直接在这里弄运算吧 
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
  

cout<<"………………结果输出………………"<<endl;
cout<<"数据的表达式为：X "<<op<<" Y =Z"<<endl;
cout<<"Z的数据为："<<uz.showData()<<endl;
cout<<"间接测量不确定度为："<<uz.showValue()<<endl;
cout<<"………………结束………………"<<endl;
cout<<"按0退出，或者右上角X关闭"<<endl;
char stoop;//结束，防误触程序 
	do{
		cin>>stoop;
	}while(stoop!='0');

	return 0;
}
