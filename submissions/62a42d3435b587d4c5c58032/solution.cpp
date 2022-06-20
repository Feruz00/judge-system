#include<bits/stdc++.h>
using namespace std;
int q,k,s,p,i,j,a[1000],b[1000];
char n[1000];
int main(){
//freopen("C:/Gmesele.in", "r", stdin);
cin>>n;
k=101;
for(i=strlen(n)-1;i>=0;i--){
k--;
a[k]=int(n[i])-48;
}
b[100]=1;
while(1!=0){
s=p=q=0;
for(i=1;i<=1000;i=i+2){
s=s+a[i];
p=p+a[i+1];
}
if(s==p){
for(i=1;i<=100;i++)
if(a[i]!=0) break;
for(j=i;j<=100;j++)
cout<<a[j];
exit(0);
}
for(i=100;i>=1;i--){
s=a[i]+b[i]+q;
a[i]=s%10;
q=s/10;
if(b[i]==0 & q==0) break;
}
}
}

