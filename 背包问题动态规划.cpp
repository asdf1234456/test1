#include<iostream>
#include<cmath>
#include<cstring>
#define N 20
using namespace std;
int main(){	
int w[N]={0,4,6,2,2,5,1},v[N]={0,8,10,6,3,7,2};	
int m[N][N];	
memset(m,0,sizeof(m));	
int n=6,c=12;   //n,c均要小于N 	
for(int i=1;i<=n;i++)	
for(int j=1;j<=c;j++)	{		
if(j>=w[i])		{		
	m[i][j]=max(m[i-1][j],m[i-1][j-w[i]]+v[i]);		
	}	
		else		{			
		m[i][j]=m[i-1][j];	
			}	}   
			 cout<<m[n][c]<<endl; //从前往后    
			  /*	for(int i=n;i>=1;i--)	
			  for(int j=1;j<=c;j++)	{	
			  	if(j>=w[i])		{		
				  m[i][j]=max(m[i+1][j],m[i+1][j-w[i]]+v[i]);		}	
				  	else		{		
					  	m[i][j]=m[i+1][j];	
						  	}	}    
							  cout<<m[1][c]<<endl;//从后往前	*/	
							  return 0;}

