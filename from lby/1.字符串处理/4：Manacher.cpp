����һ�����Ȳ�����110000���ַ���T��������������Ӵ�����ʱ�临�Ӷ�ΪO(n)
#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;
const int N=200005<<1;

char T[N];   //ԭ�ַ���
char S[N];   //ת������ַ���
int  R[N];   //���İ뾶

void Init(char *T)
{
    S[0]='$';
    int len=strlen(T);
    for(int i=0; i<=len; i++)
    {
        S[2*i+1]='#';
        S[2*i+2]=T[i];
    }
}

void Manacher(char *S)
{
    int k=0,mx=0;
    int len=strlen(S);
    for(int i=0; i<len; i++)
    {
        if(mx>i)
            R[i]=R[2*k-i]<mx-i? R[2*k-i] : mx-i;
        else
            R[i]=1;
        while(S[i+R[i]]==S[i-R[i]])
            R[i]++;
        if(R[i]+i>mx)
        {
            mx=R[i]+i;
            k=i;
        }
    }
}

int main()
{
    while(~scanf("%s", T))
    {
        Init(T);
        Manacher(S);
        int len=strlen(S);
        int ans=1;
        for(int i=0; i<len; i++)
            ans=R[i]>ans? R[i] : ans;
        printf("%d\n", ans-1);
    }
    return 0;
}