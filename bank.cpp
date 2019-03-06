#include<bits/stdc++.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include <iostream>
#include <sstream>
using namespace std;
int noofacc=4;
string to_string(int num)
{
    stringstream ss;
    ss << num;
    return ss.str();
}
int currentaccount,currentgift;
struct transact
{
	int transid,transbal;
	string itempurchased;
};
struct giftcard
{
	long int giftid,pin,giftbal;
	int redeempoints;
	struct transact t[100];
	int nooftrans;
	int blocked; 
};

struct account
{
	int custid;
	string accno;
	string name;
	long int balance;
	string password;
	struct giftcard g[100];
	int noofgift;
};

struct account a[100];

int giftfound(long int x)
{
	int i;
	for(i=0;i<a[currentaccount].noofgift;i++)
	{
		if(a[currentaccount].g[i].blocked==1)
		continue;
		if(x==a[currentaccount].g[i].giftid)  
		break;
	}
	currentgift=i;
	if(i<a[currentaccount].noofgift)
	return 1;
	return 0;
}
void blockcard()
{
	
	long int k;
	cout<<"enter gift card id:";
	cin>>k;
	if(giftfound(k)==0)
	{
		cout<<"\n\n                 Gift Card not found        \n";
		system("pause");
		return;
	}
	else
	{
		//cout<<"\n"<<a[currentaccount].g[currentgift].giftbal<<endl;
		a[currentaccount].balance+=a[currentaccount].g[currentgift].giftbal;
		a[currentaccount].g[currentgift].giftbal=0;
		a[currentaccount].g[currentgift].blocked=1;
		cout<<"\n\n                           successfully blocked\n";
		//cout<<"\n"<<a[currentaccount].balance<<endl;
		system("pause");
		return;
	}	
}
void createGiftCard(int noofgift)
{
	system("cls");
	cout<<"\n----------------------Create a gift card----------------------------\n";
	cout<<"enter a 5 digited gift card number:";
	a[currentaccount].g[noofgift].blocked=0;
	a[currentaccount].g[noofgift].nooftrans=0;
	a[currentaccount].g[noofgift].redeempoints=0;
	cin>>a[currentaccount].g[noofgift].giftid;
	if(to_string(a[currentaccount].g[noofgift].giftid).length()!=5)
	{
		cout<<"\n\n                         must contain 5 digits\n";
		system("pause");
		return;
	}
	//cout<<a[currentaccount].noofgift<<endl;
	//cout<<giftfound(a[currentaccount].g[noofgift].giftid)<<endl;
	if(giftfound(a[currentaccount].g[noofgift].giftid)==1)
	{
		cout<<"\n\n            gift card already exist\n";
		system("pause");
		return;
	}
	cout<<"enter a 4 digited gift pin:";
	cin>>a[currentaccount].g[noofgift].pin;
	if(to_string(a[currentaccount].g[noofgift].pin).length()!=4)
	{
		cout<<"\n\n                         must contain 4 digits\n";
		system("pause");
		return;
	}

	cout<<"enter amount to the gift card:";
	cin>>a[currentaccount].g[noofgift].giftbal;
	if(a[currentaccount].g[noofgift].giftbal>a[currentaccount].balance)
	{
		cout<<"\n\n                         Insufficient Balance\n";
		system("pause");
		return;
	}
	a[currentaccount].balance-=a[currentaccount].g[noofgift].giftbal;
	a[currentaccount].noofgift++;
	cout<<"\n\n                         Gift Card Successfully created\n";
	//cout<<"\n"<<a[currentaccount].balance<<endl;
	system("pause");
	return;
}
int accountfound(string x,string y,int noofacc)
{
	int flag=0,i,j;
	for(i=0;i<noofacc;i++)
	{
		if(x.compare(a[i].accno)==0)
		{
			flag=1;
			break;
		}
	}
	if(flag==0)
		return 0;
	if(y.size()!=a[i].password.size())
		return 0;
	for(j=0;j<y.size();j++)
	{
		if(y[j]>='a'&&y[j]<='y'&&(y[j]==a[i].password[j]-1))		continue;
		if(y[j]>='A'&&y[j]<='Y'&&(y[j]==a[i].password[j]-1))		continue;
		if(y[j]>='0'&&y[j]<='8'&&(y[j]==a[i].password[j]-1))		continue;
		if(y[j]=='z'&&a[i].password[j]=='a')		continue;
		if(y[j]=='Z'&&a[i].password[j]=='A')		continue;
		if(y[j]=='9'&&a[i].password[j]=='0')		continue;
		break;
	}
	if(j<y.size())
	return 0;
	currentaccount=i;
	return 1;
}
void topup()
{
	int k,l;
	system("cls");
	cout<<"\n------------------------------Top Up a card----------------------------\n";
	cout<<"enter gift card id:";
	cin>>k;
	if(giftfound(k)==0)
	{
		cout<<"                    gift card not found\n\n";
		system("pause");
		return;
	}
	cout<<"enter balance to top up:";
	cin>>l;
	if(l>a[currentaccount].balance)
	{
		cout<<"\n\n                         Insufficient Balance\n";
		system("pause");
		return;
	}
	a[currentaccount].balance-=l;
	a[currentaccount].g[currentgift].giftbal+=l;
	cout<<"\n\n                         Successfully topped up\n";
		system("pause");
		return;
}
void printtrans()
{
	long int x,i,l;
	system("cls");
	cout<<"--------------------TRANSACTIONS---------------------------\n";
	cout<<"Enter gift card id:";
	cin>>x;
	if(giftfound(x)==0)
	{
		cout<<"\n---------------GIFT CARD NOT FOUND------------------\n";
		system("pause");
		return;
	}
	else
	{
		l=a[currentaccount].g[currentgift].nooftrans;
		cout<<"\n--------------------------------------------------------\n";
		for(i=0;i<l;i++)
		{
		cout<<"item id:"<<a[currentaccount].g[currentgift].t[i].transid<<" item purchased:"<<a[currentaccount].g[currentgift].t[i].itempurchased<<" cost:"<<a[currentaccount].g[currentgift].t[i].transbal<<endl;	
		}
		cout<<"\n--------------------------------------------------------\n";
		system("pause");
	}
	
	
	
	
}
void logIn(int noofacc)
{
	system("cls");
	string x,y;
	cout<<"------------------------------------Log In-------------------------------\n\n";
	cout<<"User Name:";
	cin>>x;
	cout<<"Password:";
	cin>>y;
	//cout<<x<<endl;
	//cout<<y<<endl<<"\n\n";
	if(accountfound(x,y,noofacc)==0)
	{
		cout<<"\n\n                 Inavlid Credintials\n\n";
		system("pause");
		return;	
	}
	//cout<<"\n\n                 account found\n\n";
	//	system("pause");
	int x1;
	do{
	system("cls");
	printf("\n---------------------------- ACCOUNT MENU --------------------------------------\n");
	printf("\n         1:Create a new gift card");
	printf("\n         2:Top up the exitsing card");
	printf("\n         3:Show transactions");
	printf("\n         4:block a card");
	printf("\n         5:logout");
	printf("\n\n----------------------------------------------------------------------------");
	printf("\n\nEnter an Option : ");
	scanf("%d",&x1);
	switch(x1)
	{
		case 1://printf("\n\nYou had selected 1\n\n");
			//system("pause");
			createGiftCard(a[currentaccount].noofgift);
			break;
		case 2://printf("\n\nYou had selected 2\n\n");
			//system("pause");
			topup();
			break;
		case 3://printf("\n\nYou had selected 3\n\n");
			//system("pause");
			printtrans();
			break;
		case 4:system("cls");
		printf("\n\n--------------------------Block Gift card---------------------------------\n\n");
			blockcard();
			//system("pause");
			break;
		case 5:cout<<"\n\n            Successfully logged out\n";
		system("pause");
			break;
		default:printf("\n\n         Invalid Option\n\n");
		system("pause");
			
	}
}while(x1!=5);
currentaccount=-1;	
	return;
}

void purchase()
{
	system("cls");
	cout<<"-------------------------Purchase-------------------------------";
	string x;
	long int y,k,l,i;
	cout<<"\n\nEnter item name:";
	cin>>x;
	cout<<"\nEnter cost of item:";
	cin>>y;
	cout<<"\n\nEnter gift card id:";
	cin>>k;
	for(i=0;i<noofacc;i++)
	{
		currentaccount=i;
		if(giftfound(k)==1)
			break;
	}
	if(i==noofacc)
	{
		cout<<"\n---------------GIFT CARD NOT FOUND------------------\n";
		system("pause");
		return;
	}
	else
	{
		cout<<"\nEnter pin:";
		cin>>l;
		if(a[currentaccount].g[currentgift].pin!=l)
		{
		cout<<"\n---------------INVALID PIN------------------\n";
		system("pause");
		return;
		}
		else
		{
			if(a[currentaccount].g[currentgift].giftbal<y)
			{
				cout<<"\n----------------Insufficient balance--------------------\n";
				system("pause");
				return;
			}
			else
			{
				
				a[currentaccount].g[currentgift].giftbal-=y;
				l=a[currentaccount].g[currentgift].nooftrans;
				cout<<"\n----------------Purchased Successfully--------------------\n";
				a[currentaccount].g[currentgift].t[l].transid=l+1;
				a[currentaccount].g[currentgift].t[l].transbal=y;
				cout<<"\n\nGift Balance:"<<y;
				a[currentaccount].g[currentgift].t[l].itempurchased=x;
				a[currentaccount].g[currentgift].nooftrans++;
				a[currentaccount].g[currentgift].redeempoints+=1;
				cout<<"\nRedeem points:"<<a[currentaccount].g[currentgift].redeempoints<<endl;
				if(a[currentaccount].g[currentgift].redeempoints==10)
				{
					cout<<"\n\n---------10 rupees added to account for ten redeem points-------\n";
					a[currentaccount].g[currentgift].giftbal+=10;
					a[currentaccount].g[currentgift].redeempoints=0;
				}
				system("pause");
			}
		}
	}
}
int main()
{
	
	int x,ch;
	a[0].custid=11;		a[0].accno="11011";		a[0].name="kumar";		a[0].balance=10000;		a[0].password="ApipNvjm";		a[0].noofgift=0;
	a[1].custid=22;		a[1].accno="22022";		a[1].name="madhu";		a[1].balance=20000;		a[1].password="Cboljoh";		a[1].noofgift=0;
	a[2].custid=33;		a[2].accno="33033";		a[2].name="robin";		a[2].balance=30000;		a[2].password="kbwb22";			a[2].noofgift=0;
	a[3].custid=33;		a[3].accno="44044";		a[3].name="akhil";		a[3].balance=40000;		a[3].password="bcd";			a[3].noofgift=0;
	
	do{
	system("cls");
	system("color a");
	//cout<<a[0].custid<<"		"<<a[0].accno<<"		"<<a[0].name<<"		"<<a[0].balance<<"		"<<a[0].password<<endl;
	//cout<<a[1].custid<<"		"<<a[1].accno<<"		"<<a[1].name<<"		"<<a[1].balance<<"		"<<a[1].password<<endl;
	//cout<<a[2].custid<<"		"<<a[2].accno<<"		"<<a[2].name<<"		"<<a[2].balance<<"		"<<a[2].password<<endl;
	printf("\n---------------------------- MAIN MENU --------------------------------------\n");
	printf("\n         1:Login");
	printf("\n         2:Purchase");
	printf("\n         3:Exit");
	printf("\n\n----------------------------------------------------------------------------");
	printf("\n\nEnter an Option : ");
	scanf("%d",&x);
	switch(x)
	{
		case 1://printf("\n\nYou had selected Login\n\n");
			//system("pause");
			logIn(noofacc);
			break;
		case 2://printf("\n\nYou had selected Purchase\n\n");
			//system("pause");
			purchase();
			break;
		case 3:cout<<"\n\n            Thank You\n";
			break;
		default:printf("\n\n         Invalid Option\n\n");
		system("pause");
	}
}while(x!=3);
	return 0;
}
