#include <stdio.h>
#include <iostream>
#include <cmath>
#include <stack>
#include <string>
#include <cctype>

using namespace std;
stack<int> num_stack;
stack<char> ope_stack;

inline int get_priority(char ope){
	if(ope=='+'||ope=='-')
		return 0;
	else if(ope=='*'||ope=='/'||ope=='%')
		return 1;
	else if (ope=='^')
		return 2;
	else
		return -1;
}

inline void print_error(){
	cout<<"数学式不合法，请检查"<<endl;
}

namespace n{
	class Calculate
	{
		/**两个数字的运算**/
		public:
		inline int cal_two(int left,int right,char ope){
			switch (ope)
			{
			case '+':
				return left+right;
			case '-':
				return left-right;
			case '*':
				return left*right;
			case '/':
				if(right!=0)
					return left/right;
			case '%':
				return left%right;
			case '^':
				return pow(left,right);
			}
			return -1;
		}

		/**一个数字的运算，即计算阶乘**/
		inline int cal_one(int num){
			int ret=1;
			for(int i=num;i>0;i--){
				ret*=i;
			}
			return ret;
		}

		inline void stack_cal(){
			int n2=num_stack.top();
			num_stack.pop();
			int n1=num_stack.top();
			num_stack.pop();
			char ope=ope_stack.top();
			num_stack.push(cal_two(n1,n2,ope));
			ope_stack.pop();
		}
	};

	class Equation
	{
		const char* equation;
		
		public:
			Equation(string str)
			{
				equation=str.c_str();
			}
		
		void handle(){
			int temp;
			int chtonum;
			int priority_top,priority_ch;
			Calculate *calculate=new Calculate();
			int num_ope=0;	//记录上一次进栈的是数字（1）还是运算符（2） 
			while(*equation!=NULL){
				const char ch=*equation;
				switch (ch)
				{
				case '(':
					if(num_ope!=1){		//前面不能是数字
						ope_stack.push(ch);
						break;
					}
					print_error();
					return;
				case ')':
					if(num_ope==1){
						while(ope_stack.top()!='('){
							calculate->stack_cal();
						}
						ope_stack.pop();
						break;
					}
					print_error();
					return;
				case '+':
				case '-':
				case '*':
				case '/':
				case '%':
				case '^':
					if(num_ope==1){
						while(!ope_stack.empty()&&ope_stack.top()!='('){
							priority_top=get_priority(ope_stack.top());
							priority_ch=get_priority(ch);
							if(priority_ch<=priority_top){
								calculate->stack_cal();
							}
							else
								break;
						}
						ope_stack.push(ch);
						num_ope=2;
						break;
					}
					print_error();
					return;
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					if(num_ope!=1){
						chtonum=ch;
						chtonum-=48;
						num_stack.push(chtonum);
						num_ope=1;
						break;
					}
					print_error();
				case '!':
					temp=num_stack.top();
					num_stack.pop();
					num_stack.push(calculate->cal_one(temp));
					break;
				default:
					print_error();
				}
				equation++;
			}
			while(!ope_stack.empty()){
				calculate->stack_cal();
			}
			cout<<num_stack.top()<<endl;
			num_stack.pop();
		}
	};
}

int main(int argc, char *argv[])
{
	string input;	
	cout<<"请确认输入法为英文并输入数学表达式"<<endl;
	cin>>input;
	using namespace n;
	Equation equation=Equation(input);
	equation.handle();
	return 0;
}
