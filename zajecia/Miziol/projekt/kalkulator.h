#include<iostream>
#include<math.h>
using namespace std;

void kalkulator()
{

cout<<"Witaj w kalkulatorze klasycznym.\nPodaj swoje działanie\n";
//zmienne
float a=0,b=0,w=0,l,r=0;
string s,r2;
bool t=true;
char z;
//głowna część programu
getline (cin,s);
//wczytywanie
for(int i=0;i<s.size();i++)
	{
	if(s[i]=='0')
		{
		if(t==true){a=a*10+0;}
		if(t==false){b=b*10+0;}
		}
	if(s[i]=='1')
		{
		if(t==true){a=a*10+1;}
		if(t==false){b=b*10+1;}
		}
	if(s[i]=='2')
		{
		if(t==true){a=a*10+2;}
		if(t==false){b=b*10+2;}
		}
	if(s[i]=='3')
		{
		if(t==true){a=a*10+3;}
		if(t==false){b=b*10+3;}
		}
	if(s[i]=='4')
		{
		if(t==true){a=a*10+4;}
		if(t==false){b=b*10+4;}
		}
	if(s[i]=='5')
		{
		if(t==true){a=a*10+5;}
		if(t==false){b=b*10+5;}
		}
	if(s[i]=='6')
		{
		if(t==true){a=a*10+6;}
		if(t==false){b=b*10+6;}
		}
	if(s[i]=='7')
		{
		if(t==true){a=a*10+7;}
		if(t==false){b=b*10+7;}
		}
	if(s[i]=='8')
		{
		if(t==true){a=a*10+8;}
		if(t==false){b=b*10+8;}
		}
	if(s[i]=='9')
		{
		if(t==true){a=a*10+9;}
		if(t==false){b=b*10+9;}
		}
	if(s[i]=='.'||s[i]==',')
		{
		i++;
		r=0;
		for( ; ; )
			{
			if(s[i]=='0')
				{
				r=r*10+0;
				}
			if(s[i]=='1')
				{
				r=r*10+1;
				}
			if(s[i]=='2')
				{
				r=r*10+2;
				}
			if(s[i]=='3')
				{
				r=r*10+3;
				}
			if(s[i]=='4')
				{
				r=r*10+4;
				}
			if(s[i]=='5')
				{
				r=r*10+5;
				}
			if(s[i]=='6')
				{
				r=r*10+6;
				}
			if(s[i]=='7')
				{
				r=r*10+7;
				}
			if(s[i]=='8')
				{
				r=r*10+8;
				}
			if(s[i]=='9')
				{
				r=r*10+9;
				}
			if(s[i]!='0'||s[i]!='1'||s[i]!='2'||s[i]!='3'||s[i]!='4'||s[i]!='5'||s[i]!='6'||s[i]!='7'||s[i]!='8'||s[i]!='9')
				{
				break;
				}
			i++;
			}
		r2=r;
		l=r2.size();
		r=r/(10.00*l);
		a=a+r;
		i++;
		}
	if(s[i]=='+')
		{
		z='+';
		t=false;
		}
	if(s[i]=='-')
		{
		z='-';
		t=false;
		}
	if(s[i]=='*')
		{
		z='*';
		t=false;
		}
	if(s[i]=='/')
		{
		z='/';
		t=false;
		}
	if(s[i]=='^')
		{
		z='^';
		t=false;
		}
	if(s[i]=='v')
		{
		z='v';
		t=false;
		}
	if(s[i]=='!')
		{
		z='!';
		t=false;
		}

	}
//koniec wczytywania
//obliczenia
if(z=='+')
	{
	w=a+b;
	}
if(z=='-')
	{
	w=a-b;
	}
if(z=='*')
	{
	w=a*b;
	}
if(z=='/')
	{
	w=a/b;
	}
if(z=='^')
	{
	w=pow(a,b);
	}
if(z=='v'&&a==0)
	{
	w=sqrt(b);
	}
if(z=='v'&&a!=0)
	{
	w=pow(b,(1/a));
	}
if(z=='!'&&a>=1)
	{
	w=1;
	for(int i=1;i<=a;i++)
		{
		w=w*i;
		}
	}

//wypisywanie wyniku
cout<<"Wynikiem działania "<<a<<z<<b<<" jest "<<w<<"\n";
cout<<a<<z<<b<<"="<<w<<"\n";

return;
}
