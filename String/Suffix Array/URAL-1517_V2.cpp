https://vjudge.net/problem/URAL-1517

#include <bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
const int alpha = 128;

char s[N];
int n;
int suff[N], rnk[N], newrnk[N],len, newSuff[N], bst[N];
int LCP[N];

void buildSuffix_N_logN(){
    int *head=newSuff, *nxt = newrnk;
    memset(head, -1, alpha*sizeof(head[0]));
    for(len=0;!len||s[len-1];++len){
        suff[len]=len;
        nxt[len] = head[s[len]];
        head[s[len]]=len;
    }
    int p=0, b=-1;

    for(int i=0;i<alpha;i++){
        if(head[i]==-1)
            continue;
        bst[++b]=p;

        for(int j=head[i];~j;j=nxt[j])
        {
            rnk[j]=b;
            suff[p++] = j;
        }
    }
    int cur=1;
    newrnk[0]=0;
    newSuff[0]=suff[0];
    do{
        auto cmp = [cur](int a , int b){return rnk[a]<rnk[b] || rnk[a]==rnk[b]&& rnk[a+cur]<rnk[b+cur];};

        for(int i=0;i<len;++i){
            int j = suff[i]-cur;
            if(j<0)
                continue;
            newSuff[bst[rnk[j]]++]=j;

        }
        for(int i=1;i<len;++i){
            suff[i] = newSuff[i];
            bool cmpres =  (cmp(suff[i-1], suff[i]));
            newrnk[i] = newrnk[i-1] + cmpres ;
            if(cmpres)
                bst[newrnk[i]]=i;
        }
        for(int i=0;i<len;++i){
            rnk[suff[i]] = newrnk[i];
        }
        cur<<=1;
    }while(newrnk[len-1]!=len-1);
}


void buildSuffix_N2_logN(){
    for(len=0;!len||s[len-1];++len)
        suff[len]=len;
    sort(suff, suff+len,[](int a,int b){return strcmp(s+a,s+b)<0;});
}

void buildLCP(){
    int cnt=0;
    for(int i=0;s[i];++i){
        int j = suff[rnk[i]-1];
        while(s[i+cnt]==s[j+cnt])
            cnt++;
        LCP[rnk[i]] = cnt;
        if(cnt)
            cnt--;
    }
}

int t;
int main()
{
    scanf("%d",&n);
    scanf("%s",s);
    s[n]='$';
    scanf("%s",s+n+1);
    buildSuffix_N_logN();
    buildLCP();
    int mx=-1;
    int pos=-1;
    for(int i=1;i<len;i++){
        if((suff[i]<n)!=(suff[i-1]<n)){
            if(LCP[i]>mx){
                mx=LCP[i];
                pos=suff[i];
            }
        }
    }
    s[mx+pos]=0;
    puts(s+pos);
    return 0;
}
