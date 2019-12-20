#include<bits/stdc++.h>

using namespace std;
int x,n,m,a,b;
long S,s;
struct str{
    long  X;
    long  Y;
    long  Z;
    long  W;
};
str A[400010];
 
void build(int nod,int st,int dr){
    if(st==dr){
        cin>>x;
        A[nod].X=A[nod].Y=A[nod].Z=A[nod].W=x;
    }
    else{
        int mid=(st+dr)/2;
        build(2*nod,st,mid);
        build(2*nod+1,mid+1,dr);
        A[nod].X=A[2*nod].X+A[2*nod+1].X;
        A[nod].Y=max(A[2*nod].Y,A[2*nod].X+A[2*nod+1].Y);
        A[nod].Z=max(A[2*nod+1].Z,A[2*nod].Z+A[2*nod+1].X);
        A[nod].W=max(max(A[2*nod].W,A[2*nod+1].W),A[2*nod].Z+A[2*nod+1].Y);
    }
 
}
void querry(int nod,int st,int dr,int a,int b){
    if(a<=st&&b>=dr){
        S=max(S,max(A[nod].W,A[nod].Y+s));
        s=max(s+A[nod].X,A[nod].Z);
        S=max(S,s);
    }
    else{
        int mid=(st+dr)/2;
        if(a<=mid)
            querry(2*nod,st,mid,a,b);
        if(b>mid)
            querry(2*nod+1,mid+1,dr,a,b);
    }
}
int main(){   
    while(cin >> n >> m){
    build(1,1,n);
    for(int i=1;i<=m;i++){
        cin>>a>>b;
        S=s=INT_MIN;
        querry(1,1,n,a,b);
        cout<<S<<"\n";
    }
    }
    return 0;
}