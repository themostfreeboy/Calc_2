/*

�޸�����һ���汾������ᵽ��bug����������������ڵķ�������ġ��������ݾ�δ�ı䡣

����˵����
�˳�������󲽽��У�
��һ����ɨ����׺���ʽ������׺���ʽת��Ϊ��׺���ʽ��
�ڶ���������ת����ĺ�׺���ʽ��
�˳��򴴽�mydata�������ʹ���Ϊ�˵�һ�����ڵ�һ���н���׺���ʽת��Ϊ��׺���ʽ�洢��data�����У������м������֣����з��ţ��������ֻ��Ǹ����ͣ�����ͨ��mydata���е�isNumber�����жϴ�ֵΪ���ֻ��Ƿ��ţ����Ϊtrue����Ϊ���֣���ʱ��������(sign)�������ֵ������ν��������ʹ��Ĭ��ֵ0����֮���Ϊfalse����Ϊ���ţ���ʱ��������(number)�������ֵ������ν��������ʹ��Ĭ��ֵ0��
���������У���Ȼ����ʹ����ͬһ��ջ*s����ʵ��������ջ��ȫ��������һ����ջ������Ԫ�ؾ�Ϊ���ţ��ڶ�����ջ������Ԫ�ؾ�Ϊ���������֣�ʵ���ϴ˴���ȫ������C++��templateģ�����װд�õ�stack��ջ�������˴�����δʹ��C++�ṩ��ջ��ʹ�����Լ�д��ջ��û��ʹ��ģ���࣬����Ϊ�˱���д������ͬ���͵�ջ������ʹ����ջ��Ԫ��Ϊ�Լ���Ƶ�mydata�࣬��ʵ���ϣ���һ��ѹ���Ԫ��ȫ��Ϊ����(isNumber=false)���ڶ���ѹ���Ԫ��ȫ��Ϊ����(isNumber=true)��
�ڵ�һ���ж�ȡ��׺���ʽ�����У�Ŀǰֻ����0-9��С����(.)��С����(()������Ƕ�׶�㣬����ʶ��������([])�ʹ�����({}))��sin������cos����,log������ln����������ʶ��pi��e�ȳ�����
�ڷ��ŵĴ�������У���ͨ����ѹջʱsign���Դ����Ϊ�÷��ŵ�ASC2ֵ���������⺯������sin��cos��log��ln��ֱ�������Զ����1��2��3��4����ǰ��������ͨ���ŵ�ASC2ֵ������ͻ������ֵ���£�
sign˵����
+:43(ASC2)
-:45(ASC2)
*:42(ASC2)
/:47(ASC2)
^:94(ASC2)
(:40(ASC2)
):41(ASC2)
.:46(ASC2)
=:61(ASC2)
sin:1(�Զ���)
cos:2(�Զ���)
log:3(�Զ���)
ln:4(�Զ���)
�˳�����һ�汾����һ��bugδ�������Ϊ����Ҫ�����Ϊ������float�����ԣ����ֵĴ�����ǽ��ַ�ת��Ϊ���ֲ�������Ӧ�����㣬Ȼ���ٶ�����һ���������ַ�ʱ�Ž�������ѹջ������������=ǰ�������)�������ֵĻ��������һ�������޷�ѹջ�����Դ˴������˵����жϴ�����Ϊ�п��ܴ���(�������ַ�����һ�����������Բ���ֻҪ�Ƿ����־ͽ��ղŵ�����ѹջ����������ѹջѹ�ص��������bug������Ŀǰ������жϻ��ƾ�������ѹջ��ͽ�tempnumber=0�������ֻ�����һ�����ص�bug��������ʽ�б������һ������ľ���0������ѹջʱ����ԣ��Ӷ����º������ݴ������ֺ����ص�bug��(Ŀǰ�뵽һ���Ƚ��鷳�Ľ���취���½�һ���������ڶ����һ������ʱ�����˱�����Ϊһ��ֵ(��ʾ�����ֶ�ȡ�Ҵ�����δѹջ)������ȡ�������ַ�ʱ���ٴ��жϴ˱�����ֵ������ղŵ�����δѹ��ջ���򽫴�����ѹ��ջ�����۴������Ƿ�Ϊ0(��ʹΪ0Ҳ��ջ��˵���û�����ľ���0����)��ͬʱ���˱�����Ϊ����һ��ֵ(��ʾĿǰû��δѹջ�����ֶ���)��)
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define num 100

class mydata
{
public:
	float number;//�洢����
	char sign;//�洢��������ߺ�����
	bool isNumber;//ָ��ջ�ڵ�Ԫ���Ƿ�Ϊ����
	mydata(float n=0,char s=0,bool b=false):number(n),sign(s),isNumber(b){};
};

class stack
{
public:
	mydata data[num];
	int top;
	void push(mydata x);//��ջ
	mydata pop();//��ջ
	bool Full();//ջ��
	bool Empty();//ջ��
	stack():top(-1){};
	void copy(stack *s);//ջ�����ݸ���
};

void stack::push(mydata x)//��ջ
{
	if(top<num-1)    data[++top]=x;
}

mydata stack::pop()//��ջ
{
	if(top>-1)    return data[top--];
}

bool stack::Full()//ջ��
{
	return (top==num-1)?true:false;
}

bool stack::Empty()//ջ��
{
	return (top==-1)?true:false;
}

void stack::copy(stack *s)//ջ�����ݸ���
{
	for(int i=0;i<=s->top;i++)
	{
		push(s->data[i]);
	}
}

int main()
{
	mydata data[100];//���ڴ洢��׺���ʽת����ĺ�׺���ʽ
	int datanumber=0;//��¼data������Ԫ�صĸ���
	stack *s=new stack;
	char tempchar=0;
	float tempnumber=0;
	float tempratio=0;//��¼�Ƿ���С��������Լ�����С�����ĵڼ�λ
	bool haveNumber=false;//רΪ��һ�汾��bug�޸�������ı���
	while((tempchar=getchar())!='=')//��ȡ��׺���ʽ������׺���ʽת��Ϊ��׺���ʽ(ɨ����Ŀǰֻ����0-9��С����(.)��С����(()������Ƕ�׶�㣬����ʶ��������([])�ʹ�����({}))��sin������cos����,log������ln����������ʶ��pi��e�ȳ���)
	{
		if(tempchar>='0' && tempchar<='9')//����
		{
			haveNumber=true;
			if(tempratio==0)//��С�������
			{
				tempnumber=tempnumber*10+(tempchar-'0');
			}
			else//��С�������
			{
				tempratio=tempratio*0.1;
				tempnumber=tempnumber+(tempchar-'0')*tempratio;
			}
		}
		else if(tempchar=='.')//С����
		{
			haveNumber=true;
			tempratio=1;
		}
		else if(tempchar=='+' || tempchar=='-')//+��-
		{
			if(haveNumber==true)
			{
				mydata md(tempnumber,0,true);
			    data[datanumber++]=md;
	            tempnumber=0;
	            tempratio=0;
				haveNumber=false;
			}
			while(!s->Empty())//ջΪ��(��ջ)��ջ�ǿ�(�����������ȼ����ڻ���ڸ��������ջ��Ԫ�أ�Ȼ�󽫸��������ջ)
			{
				if(s->data[s->top].sign=='(' || s->data[s->top].sign==1 || s->data[s->top].sign==2 || s->data[s->top].sign==3 || s->data[s->top].sign==4)//���ȼ����ڸ������
				{
					break;
				}
				data[datanumber++]=s->pop();
			}
			mydata md(0,tempchar,false);
			s->push(md);
		}
		else if(tempchar=='*' || tempchar=='/')//*��/
		{
			if(haveNumber==true)
			{
				mydata md(tempnumber,0,true);
			    data[datanumber++]=md;
	            tempnumber=0;
	            tempratio=0;
				haveNumber=false;
			}
			while(!s->Empty())//ջΪ��(��ջ)��ջ�ǿ�(�����������ȼ����ڻ���ڸ��������ջ��Ԫ�أ�Ȼ�󽫸��������ջ)
			{
				if(s->data[s->top].sign=='+' || s->data[s->top].sign=='-' || s->data[s->top].sign=='(' || s->data[s->top].sign==1 || s->data[s->top].sign==2 || s->data[s->top].sign==3 || s->data[s->top].sign==4)//���ȼ����ڸ������
				{
					break;
				}
				data[datanumber++]=s->pop();
			}
			mydata md(0,tempchar,false);
			s->push(md);
		}
		else if(tempchar=='^')//^
		{
			if(haveNumber==true)
			{
				mydata md(tempnumber,0,true);
			    data[datanumber++]=md;
	            tempnumber=0;
	            tempratio=0;
				haveNumber=false;
			}
			while(!s->Empty())//ջΪ��(��ջ)��ջ�ǿ�(�����������ȼ����ڻ���ڸ��������ջ��Ԫ�أ�Ȼ�󽫸��������ջ)
			{
				if(s->data[s->top].sign=='+' || s->data[s->top].sign=='-' || s->data[s->top].sign=='*' || s->data[s->top].sign=='/' || s->data[s->top].sign=='(' || s->data[s->top].sign==1 || s->data[s->top].sign==2 || s->data[s->top].sign==3 || s->data[s->top].sign==4)//���ȼ����ڸ������
				{
					break;
				}
				data[datanumber++]=s->pop();
			}
			mydata md(0,tempchar,false);
			s->push(md);
		}
		else if(tempchar=='(')//(
		{
			if(haveNumber==true)
			{
				mydata md(tempnumber,0,true);
			    data[datanumber++]=md;
	            tempnumber=0;
	            tempratio=0;
				haveNumber=false;
			}
			mydata md(0,tempchar,false);
			s->push(md);
		}
		else if(tempchar==')')//)
		{
			if(haveNumber==true)
			{
				mydata md(tempnumber,0,true);
			    data[datanumber++]=md;
	            tempnumber=0;
	            tempratio=0;
				haveNumber=false;
			}
			while(!s->Empty())//��ջֱ������(
			{
				
				if(s->data[s->top].sign=='(')//(
				{
					s->pop();//��(�����������뵽data��
					break;
				}
				else if(s->data[s->top].sign==1 || s->data[s->top].sign==2 || s->data[s->top].sign==3 || s->data[s->top].sign==4)//sin(��cos(��log(��ln(
				{
				    data[datanumber++]=s->pop();
					break;
				}
				else//��������
				{
					data[datanumber++]=s->pop();
				}
			}
			
		}
		else//��������
		{
			if(haveNumber==true)
			{
				mydata md(tempnumber,0,true);
			    data[datanumber++]=md;
	            tempnumber=0;
	            tempratio=0;
				haveNumber=false;
			}
			if(tempchar=='s')//sin
			{
				if((tempchar=getchar())=='i')
				{
					if((tempchar=getchar())=='n')
					{
						if((tempchar=getchar())=='(')
						{
							mydata md(0,1,false);
			                s->push(md);
						}
					}
				}
			}
			else if(tempchar=='c')//cos
			{
				if((tempchar=getchar())=='o')
				{
					if((tempchar=getchar())=='s')
					{
						if((tempchar=getchar())=='(')
						{
							mydata md(0,2,false);
			                s->push(md);
						}
					}
				}
			}
			else if(tempchar=='l')//log��ln
			{
				if((tempchar=getchar())=='o')//log
				{
					if((tempchar=getchar())=='g')
					{
						if((tempchar=getchar())=='(')
						{
							mydata md(0,3,false);
			                s->push(md);
						}
					}
				}
				else if((tempchar=getchar())=='n')//ln
				{
					if((tempchar=getchar())=='(')
					{
						mydata md(0,4,false);
			            s->push(md);
					}
				}
			}
		}
	}
	if(haveNumber==true)//���=ǰ���һ���ַ������ֶ������������ţ������һ�����ֲ�δ�洢��data��(��ô���һ������ᵼ�����һ�����������0����ֺ����ص�bug)
	{
		mydata md(tempnumber,0,true);
		data[datanumber++]=md;
		haveNumber=false;
	}
	while(!s->Empty())//��ջ��ʣ��Ԫ��ȫ������
	{
		data[datanumber++]=s->pop();
	}
//���˺�׺���ʽȫ��ת�����

#if 0
	printf("datanumber=%d\n",datanumber);
	for(int i=0;i<datanumber;i++)//��ʾ��׺���ʽ������
	{
		if(data[i].isNumber==true)
		{
			printf("%g\t",data[i].number);
		}
		else
		{
			//printf("%c\t",data[i].sign);
			printf("%d\t",data[i].sign);
		}
	}
	printf("\n");
#endif

	for(int i=0;i<datanumber;i++)//��ʼ�����׺���ʽ
	{
		if(data[i].isNumber==true)//����
		{
			s->push(data[i]);
		}
		else//����
		{
			if(data[i].sign=='+')//+
			{
				float num1=s->pop().number;
				float num2=s->pop().number;
				mydata md(num2+num1,0,true);
				s->push(md);
			}
			else if(data[i].sign=='-')//-
			{
				float num1=s->pop().number;
				float num2=s->pop().number;
				mydata md(num2-num1,0,true);
				s->push(md);
			}
			else if(data[i].sign=='*')//*
			{
				float num1=s->pop().number;
				float num2=s->pop().number;
				mydata md(num2*num1,0,true);
				s->push(md);
			}
			else if(data[i].sign=='/')///
			{
				float num1=s->pop().number;
				float num2=s->pop().number;
				mydata md(num2/num1,0,true);
				s->push(md);
			}
			else if(data[i].sign=='^')//^
			{
				float num1=s->pop().number;
				float num2=s->pop().number;
				mydata md(pow(num2,num1),0,true);
				s->push(md);
			}
			else if(data[i].sign==1)//sin
			{
				float num1=s->pop().number;
				mydata md(sin(num1),0,true);
				s->push(md);
			}
			else if(data[i].sign==2)//cos
			{
				float num1=s->pop().number;
				mydata md(cos(num1),0,true);
				s->push(md);
			}
			else if(data[i].sign==3)//log
			{
				float num1=s->pop().number;
				mydata md(log10(num1),0,true);
				s->push(md);
			}
			else if(data[i].sign==4)//ln
			{
				float num1=s->pop().number;
				mydata md(log(num1),0,true);
				s->push(md);
			}
		}
	}
	float result=s->pop().number;//��������ջ��һ��ֻ��һ��Ԫ�أ������
	delete s;
	printf("%g\n",result);
	system("pause");
	return 0;
}