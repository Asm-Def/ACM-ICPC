/*
    Problem: hiho round120 ����ص��ظ�K���Ӵ�����
    Content: SA's Code and Explanation
    Author : YxuanwKeith
*/

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 100005;

char ch[MAXN], All[MAXN];
int SA[MAXN], rk[MAXN], Height[MAXN], tax[MAXN], tp[MAXN], a[MAXN], n, m,st[MAXN][20];
//rk[i] ��i����׺������; SA[i] ����Ϊi�ĺ�׺λ��; Height[i] ����Ϊi�ĺ�׺������Ϊ(i-1)�ĺ�׺��LCP
//tax[i] ��������������; tp[i] rk�ĸ�������(���������еĵڶ��ؼ���),��SA����һ����
//aΪԭ��
void RSort() {
    //rk��һ�ؼ���,tp�ڶ��ؼ��֡�
    for (int i = 0; i <= m; i ++) tax[i] = 0;
    for (int i = 1; i <= n; i ++) tax[rk[tp[i]]] ++;
    for (int i = 1; i <= m; i ++) tax[i] += tax[i-1];
    for (int i = n; i >= 1; i --) SA[tax[rk[tp[i]]] --] = tp[i]; //ȷ�������һ�ؼ��ֵ�ͬʱ��������ڶ��ؼ��ֵ�Ҫ��
} //��������,���µĶ�Ԫ������

int cmp(int *f, int x, int y, int w) { return f[x] == f[y] && f[x + w] == f[y + w]; }
//ͨ����Ԫ�������±�ıȽϣ�ȷ�������Ӵ��Ƿ���ͬ

void Suffix() {
    //SA
    for (int i = 1; i <= n; i ++) rk[i] = a[i], tp[i] = i;
    m = 127 ,RSort(); //һ��ʼ���Ե����ַ�Ϊ��λ������(m = 127)

    for (int w = 1, p = 1, i; p < n; w += w, m = p) { //���Ӵ����ȷ���,����rk

        //w ��ǰһ���Ӵ��ĳ���; m ��ǰ��ɢ�������������
        //��ǰ��tp(�ڶ��ؼ���)��ֱ������һ�ε�SA�ĵõ�
        for (p = 0, i = n - w + 1; i <= n; i ++) tp[++ p] = i; //����Խ��,�ڶ��ؼ���Ϊ0
        for (i = 1; i <= n; i ++) if (SA[i] > w) tp[++ p] = SA[i] - w;

        //����SAֵ,����tp��ʱ������һ�ֵ�rk(����cmp�Ƚ�)
        RSort(), swap(rk, tp), rk[SA[1]] = p = 1;

        //���Ѿ���ɵ�SA���������������rk,����ɢrk
        for (i = 2; i <= n; i ++) rk[SA[i]] = cmp(tp, SA[i], SA[i - 1], w) ? p : ++ p;
    }
    //��ɢ������ȵ��ַ�����rk��Ϊ��ͬ��
    //LCP
    int j, k = 0;
    for(int i = 1; i <= n; Height[rk[i ++]] = k)
        for( k = k ? k - 1 : k, j = SA[rk[i] - 1]; a[i + k] == a[j + k]; ++ k);
    //���֪��ԭ���ͱȽϺ�������
    //for(int i=1;i<=n;i++)printf("%d ",rk[i]);printf("\n");
    //for(int i=1;i<=n;i++)printf("%d ",Height[i]);printf("\n");
}
void getst()
{
    int i,j;
    memset(st,0,sizeof(st));
    for(i=1;i<=n;i++)
        st[i][0]=Height[i];
    for(i=1;(1<<i)<=n;i++)
        for(j=1;j-1+(1<<i)<=n;j++)
        st[j][i]=min(st[j][i-1],st[j+(1<<(i-1))][i-1]);
}
int getmin(int l,int r)
{
    int k=0;
    while(1<<(k+1)<=(r-l+1))k++;//printf("%d %d %d %d %d\n",l,r,k,st[l][k],st[r-(1<<k)+1][k]);
    return min(st[l][k],st[r-(1<<k)+1][k]);
}
int main() {
    int k;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    Suffix();
    getst();
    int s=0;
    if(k==1)
        s=n;
    else
    {
        for(int i=2;i<=n-k+2;i++)
            s=max(s,getmin(i,i+k-2));
    }
    printf("%d\n", s);
}
