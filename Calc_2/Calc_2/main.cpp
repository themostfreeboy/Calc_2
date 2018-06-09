/*

修复了上一个版本的最后提到的bug，就是用最后括号内的方法解决的。其他内容均未改变。

程序说明：
此程序分两大步进行：
第一步，扫描中缀表达式，将中缀表达式转化为后缀表达式；
第二步，计算转化后的后缀表达式。
此程序创建mydata数据类型纯属为了第一步，在第一步中将中缀表达式转化为后缀表达式存储于data数组中，数组中既有数字，又有符号，而且数字还是浮点型，所以通过mydata类中的isNumber属性判断此值为数字还是符号，如果为true，则为数字，此时符号属性(sign)中所存何值已无所谓，程序中使用默认值0，反之如果为false，则为符号，此时数字属性(number)中所存何值已无所谓，程序中使用默认值0。
在这两大步中，虽然程序使用了同一个栈*s，但实质两步的栈完全独立，第一步的栈内所有元素均为符号，第二步的栈内所有元素均为浮点型数字，实际上此处完全可以用C++用template模板类封装写好的stack堆栈来处理，此处由于未使用C++提供的栈，使用了自己写的栈，没有使用模板类，所以为了避免写两个不同类型的栈，所以使用了栈内元素为自己设计的mydata类，而实际上，第一步压入的元素全部为符号(isNumber=false)，第二步压入的元素全部为数字(isNumber=true)。
在第一步中读取中缀表达式过程中，目前只包括0-9，小数点(.)，小括号(()，可以嵌套多层，但不识别中括号([])和大括号({}))，sin函数，cos函数,log函数，ln函数，但不识别pi和e等常数。
在符号的处理过程中，普通符号压栈时sign属性存入的为该符号的ASC2值，其他特殊函数，如sin，cos，log，ln则分别存入了自定义的1，2，3，4，与前面所有普通符号的ASC2值均不冲突，具体值如下：
sign说明：
+:43(ASC2)
-:45(ASC2)
*:42(ASC2)
/:47(ASC2)
^:94(ASC2)
(:40(ASC2)
):41(ASC2)
.:46(ASC2)
=:61(ASC2)
sin:1(自定义)
cos:2(自定义)
log:3(自定义)
ln:4(自定义)
此程序上一版本中有一个bug未解决，因为数字要求可以为浮点型float，所以，数字的处理均是将字符转化为数字并做以相应的运算，然后再读入下一个非数字字符时才将此数字压栈，而且如果最后=前如果不是)而是数字的话，则最后一个数字无法压栈，所以此处进行了单独判断处理。因为有可能存在(与其他字符连在一起的情况，所以不能只要是非数字就将刚才的数字压栈，否则会出现压栈压重的情况导致bug，所以目前整体的判断机制均是数字压栈后就将tempnumber=0，而这种机制有一个严重的bug，如果表达式中本身就有一项输入的就是0，则在压栈时会忽略，从而导致后期数据处理会出现很严重的bug。(目前想到一个比较麻烦的解决办法，新建一个变量，在读入第一个数字时，将此变量置为一个值(表示有数字读取且此数字未压栈)，当读取非数字字符时，再次判断此变量的值，如果刚才的数字未压入栈，则将此数字压入栈，无论此数字是否为0(即使为0也入栈，说明用户输入的就是0本身)，同时将此变量置为另外一个值(表示目前没有未压栈的数字读入)。)
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define num 100

class mydata
{
public:
	float number;//存储数字
	char sign;//存储运算符或者函数名
	bool isNumber;//指明栈内的元素是否为数字
	mydata(float n=0,char s=0,bool b=false):number(n),sign(s),isNumber(b){};
};

class stack
{
public:
	mydata data[num];
	int top;
	void push(mydata x);//入栈
	mydata pop();//出栈
	bool Full();//栈满
	bool Empty();//栈空
	stack():top(-1){};
	void copy(stack *s);//栈内内容复制
};

void stack::push(mydata x)//入栈
{
	if(top<num-1)    data[++top]=x;
}

mydata stack::pop()//出栈
{
	if(top>-1)    return data[top--];
}

bool stack::Full()//栈满
{
	return (top==num-1)?true:false;
}

bool stack::Empty()//栈空
{
	return (top==-1)?true:false;
}

void stack::copy(stack *s)//栈内内容复制
{
	for(int i=0;i<=s->top;i++)
	{
		push(s->data[i]);
	}
}

int main()
{
	mydata data[100];//用于存储中缀表达式转化后的后缀表达式
	int datanumber=0;//记录data数组内元素的个数
	stack *s=new stack;
	char tempchar=0;
	float tempnumber=0;
	float tempratio=0;//记录是否有小数点出现以及出现小数点后的第几位
	bool haveNumber=false;//专为上一版本的bug修复所定义的变量
	while((tempchar=getchar())!='=')//读取中缀表达式，将中缀表达式转化为后缀表达式(扫描中目前只包括0-9，小数点(.)，小括号(()，可以嵌套多层，但不识别中括号([])和大括号({}))，sin函数，cos函数,log函数，ln函数，但不识别pi和e等常数)
	{
		if(tempchar>='0' && tempchar<='9')//数字
		{
			haveNumber=true;
			if(tempratio==0)//无小数点出现
			{
				tempnumber=tempnumber*10+(tempchar-'0');
			}
			else//有小数点出现
			{
				tempratio=tempratio*0.1;
				tempnumber=tempnumber+(tempchar-'0')*tempratio;
			}
		}
		else if(tempchar=='.')//小数点
		{
			haveNumber=true;
			tempratio=1;
		}
		else if(tempchar=='+' || tempchar=='-')//+或-
		{
			if(haveNumber==true)
			{
				mydata md(tempnumber,0,true);
			    data[datanumber++]=md;
	            tempnumber=0;
	            tempratio=0;
				haveNumber=false;
			}
			while(!s->Empty())//栈为空(入栈)，栈非空(弹出所有优先级大于或等于该运算符的栈顶元素，然后将该运算符入栈)
			{
				if(s->data[s->top].sign=='(' || s->data[s->top].sign==1 || s->data[s->top].sign==2 || s->data[s->top].sign==3 || s->data[s->top].sign==4)//优先级低于该运算符
				{
					break;
				}
				data[datanumber++]=s->pop();
			}
			mydata md(0,tempchar,false);
			s->push(md);
		}
		else if(tempchar=='*' || tempchar=='/')//*或/
		{
			if(haveNumber==true)
			{
				mydata md(tempnumber,0,true);
			    data[datanumber++]=md;
	            tempnumber=0;
	            tempratio=0;
				haveNumber=false;
			}
			while(!s->Empty())//栈为空(入栈)，栈非空(弹出所有优先级大于或等于该运算符的栈顶元素，然后将该运算符入栈)
			{
				if(s->data[s->top].sign=='+' || s->data[s->top].sign=='-' || s->data[s->top].sign=='(' || s->data[s->top].sign==1 || s->data[s->top].sign==2 || s->data[s->top].sign==3 || s->data[s->top].sign==4)//优先级低于该运算符
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
			while(!s->Empty())//栈为空(入栈)，栈非空(弹出所有优先级大于或等于该运算符的栈顶元素，然后将该运算符入栈)
			{
				if(s->data[s->top].sign=='+' || s->data[s->top].sign=='-' || s->data[s->top].sign=='*' || s->data[s->top].sign=='/' || s->data[s->top].sign=='(' || s->data[s->top].sign==1 || s->data[s->top].sign==2 || s->data[s->top].sign==3 || s->data[s->top].sign==4)//优先级低于该运算符
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
			while(!s->Empty())//弹栈直到出现(
			{
				
				if(s->data[s->top].sign=='(')//(
				{
					s->pop();//将(弹出但不存入到data中
					break;
				}
				else if(s->data[s->top].sign==1 || s->data[s->top].sign==2 || s->data[s->top].sign==3 || s->data[s->top].sign==4)//sin(或cos(或log(或ln(
				{
				    data[datanumber++]=s->pop();
					break;
				}
				else//其他符号
				{
					data[datanumber++]=s->pop();
				}
			}
			
		}
		else//其他函数
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
			else if(tempchar=='l')//log或ln
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
	if(haveNumber==true)//如果=前最后一个字符是数字而不是其他符号，则最后一个数字并未存储到data中(这么挫后一步处理会导致如果一个数本身就是0会出现很严重的bug)
	{
		mydata md(tempnumber,0,true);
		data[datanumber++]=md;
		haveNumber=false;
	}
	while(!s->Empty())//将栈内剩余元素全部弹出
	{
		data[datanumber++]=s->pop();
	}
//至此后缀表达式全部转化完毕

#if 0
	printf("datanumber=%d\n",datanumber);
	for(int i=0;i<datanumber;i++)//显示后缀表达式的内容
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

	for(int i=0;i<datanumber;i++)//开始计算后缀表达式
	{
		if(data[i].isNumber==true)//数字
		{
			s->push(data[i]);
		}
		else//符号
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
	float result=s->pop().number;//最后计算完栈内一定只有一个元素，即结果
	delete s;
	printf("%g\n",result);
	system("pause");
	return 0;
}