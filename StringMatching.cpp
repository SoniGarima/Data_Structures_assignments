#include<iostream>
#include<math.h>                      //For using the log(n) function only.
#define ll long long int
using namespace std;

ll power(int p,ll i){                 //To calculate power of p to the i using binary method.  
    if(i==0){
        return 1;
    }
    else if(i%2 == 0){ 
        ll ans=power(p,i/ 2);
        return ans*ans; 
    }
    else{
        ll ans=power(p,i/ 2);
        return p*ans*ans; 
    }
} /*time complexity =O(nlog(i)),i has max value =n,hence time<=O(nlog(n)) */

void gcd(int a,int m,ll *x,ll *y){      // For finding modular inverse, we will have to backtrack the way from which we found gcd.
    if(a==0){
        *x=0;
        *y=1;
        return;
    }
    ll res1,res2;
    gcd(m%a,a,&res1,&res2);
    *x=res2-(m/a)*(res1);
    *y=res1;
    return;
}/*time=O(log(n))*/

int main(){
    ll n,m;// inputs
    cin>>n;
    string s;
    cin>>s;
    cin>>m;
    ll a,b,c,d;
    ll query[m][4];
    ll ans[m];
    for(ll w=0;w<m;w++){
        ans[w]=1;
    }/*Time=O(m)*/
    for(ll u=0;u<m;u++){
        cin>>a>>b>>c>>d;
        query[u][0]=a-1;
        query[u][1]=b-1;
        query[u][2]=c-1;
        query[u][3]=d-1;
    }  /*Time=O(m)*/  

    int t=clock();                    // take modulo of hash values so that they may lie in range and dont overflow.  
    srand(t);// seeding the random functions so that they give different values everytime.
    ll k=4*(log(n))*(log(n))*log(n);
    ll primes[k];
    for(ll i=0;i<k;i++){
        ll rand_p=rand()%(n*n*n*n-3);
        if(rand_p%2==0){
            primes[i] = rand_p+31;    // If random number is even, we will have to make it odd somehow because our p is 2 and we  
        }                             // dont want that our modular inverse finding function to fail because of gcd not being unity.   
        else{                         //we chose 31 because its a prime number and odd too.  
            primes[i] = rand_p;
        }  
    }/*as k=O(log(n)), time=O(log(n))*/
    for(ll e=0;e<k;e++){  
        //ll g=1000000009 ;                //Iterating the queries k times to find the majority answers.
        ll g=primes[e];
        ll arr[n];
        ll temp = int(s[0])-48;
        arr[0]=temp%g;
        int p=2;
        for(ll i=1; i<n;i++){                                           
            temp=temp+ (((int(s[i])-48)%g)*((power(p,i))%g))%g;        
            arr[i] = (temp)%g;
        }/*time=O(nlog(n))*/
        for(ll f=0;f<m;f++){                //Making a 2D array for storing queries so that we can retreive their values
            ll a,b,c,d;                     // in every iteration will help in reducing time complexity.
            a=query[f][0];
            b=query[f][1];
            c=query[f][2];
            d=query[f][3];
            //base cases
            if(a==c){
            cout<<"1"<<endl;
            continue;
            }
            //equility cases
            else if(a==b && c==d){
                if(s[a]==s[c]){
                    cout<<"1"<<endl;
                    continue;
                }
                else{
                    cout<<"0"<<endl;
                    continue;
                }
            }
            ll p_i1=power(p,a);
            ll x,y;
            gcd(p_i1,g,&x,&y);
            ll re1=(x%g+g)%g;//as x can be negative, we will have to make it positive.
            ll val1;
            //base case
            if(a==0){
                val1=arr[b];
            }
            else{
                val1=(re1*(arr[b]-arr[a-1])%g)%g;  //finding hash value of substring.            
            }
            ll p_i2=power(p,c);
            gcd(p_i2,g,&x,&y);
            ll re2=(x%g+g)%g;
            ll val2;
            //base cases
            if(c==0){
                val2=arr[d];
            }
            else{
                val2=(re2*(arr[d]-arr[c-1])%g)%g;
            }
            if(val1==val2){
                ans[f]+=1;                        // incrementing the value of array element corresponding to that value.
            }
            else{
                ans[f]+=0;
            }
        }/*time=O(mlog(n))*/
    }
    for(ll gs=0;gs<m;gs++){
        if(ans[gs]>=floor(k/2)){                 // approximating the answer to be that boolean value which occurs maximum time in the 
            ans[gs]=1;                          // array we maintained.
        }                                       //we can take another values of this threshold to optimize our answer.
        else{
            ans[gs]=0;
        }
    }/*time=O(m)*/
    for(ll op=0;op<m;op++){
        cout<<ans[op]<<endl;          //outputs
    }/*time=O(m)*/
}    
/*The time complexity of whole program is given by=O((n+m)*(log(n))_{c}), which is required. */
//taking g=1000000009 will also give correct outputs with high probability(observation).
