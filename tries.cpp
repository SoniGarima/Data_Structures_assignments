//solution for programming evaluation 4
#include<iostream>
using namespace std;
int len=32;//length of string
int score=0;//count for search2 function
int siz=0;//size of input pattern in search2
class node{
    public:
        char c;
        int dollar;//augmenting a value to keep track of common sub strings 
        node* right;
        node* left;
        node* centre;
        node(char r){
            dollar=0;
            c=r;
            centre=NULL;
            right=NULL;
            left=NULL;
        }
};
class trie{
    public:
        node* root;
        trie(){
            root=new node('2');
        }
        int search(string s){//function for searching a single string in the trie
            node* temp=root;
            int i=0;
            while(i<len){
                if(s[i]=='0'){
                    if(temp->left==NULL){
                        return 0;
                    }
                    else{
                        temp=temp->left;
                    }
                }
                else{
                    if(temp->right==NULL){
                        return 0;
                    }
                    else{
                        temp=temp->right;
                    }
                }
                i++;
            }
            if(temp->centre->c=='$'){//string is present only when it is ending with a dollar
                temp->dollar++;
                return 1;
            }
            else{
                return 0;
            }
        }
        int insert(string s){//insert for a basic trie
            if(search(s)==1){
                return 0;
                }
            int i=0;
            node* temp=root;
            while(i<len){
                if(s[i]=='0'){
                        if(temp->left==NULL){
                            temp->left=new node('0');
                            temp=temp->left;
                            temp->dollar++;
                        }
                        else{
                            temp=temp->left;
                            temp->dollar++;
                        }
                    }
                    else{
                        if(temp->right==NULL){
                            temp->right=new node('1');
                            temp=temp->right;
                            temp->dollar++;
                        }
                        else{
                            temp=temp->right;
                            temp->dollar++;
                        }
                    }
                i++;
            } 
            temp->centre=new node('$');
            return 1;   
        }
        int remove(string s){//remove for a basic trie
            if(search(s)==0){
                return 0;
            }
            node* temp=root;
                int i=0;
                while(i<len){
                    if(s[i]=='0'){
                            temp=temp->left;
                            temp->dollar--;
                    }
                    else{
                            temp=temp->right;
                            temp->dollar--;
                    }
                i++;
                }
                temp->centre=new node('#');
                return 1;
        }
        int insert1(string s){//insert for suffix trie
            if(search(s)==1){
                return 0;
                }
            int k=len-1;
            while(k>=0){
                node* temp=root;
                int i=k;
                while(i<len){
                    if(s[i]=='0'){
                        if(temp->left==NULL){
                            temp->left=new node('0');
                            temp=temp->left;
                            temp->dollar++;
                        }
                        else{
                            temp=temp->left;
                            temp->dollar++;
                        }
                    }
                    else{
                        if(temp->right==NULL){
                            temp->right=new node('1');
                            temp=temp->right;
                            temp->dollar++;
                        }
                        else{
                            temp=temp->right;
                            temp->dollar++;
                        }
                    }
                i++;
                }
            temp->centre=new node('$');
            k--;  
            }
            return 1;
        }
        int remove1(string s){//remove for suffix trie
            if(search(s)==0){
                return 0;
            }
            int k=len-1;
            while(k>=0){
                node* temp=root;
                int i=k;
                while(i<len){
                    if(s[i]=='0'){
                            temp=temp->left;
                            temp->dollar--;
                    }
                    else{
                            temp=temp->right;
                            temp->dollar--;
                    }
                i++;
                }
            temp->centre=new node('#');
            k--;  
            }
            return 1;
        }
        int search1(string s){//function for finding the number of occurances of a pattern in all 32 bit strings.
            int size=0;
            while(s[size]!='\0'){
                size++;
            }
            node* temp=root;
            int i=0;
            while(i<size){
                if(s[i]=='0'){
                    if(temp->left!=NULL){
                        temp=temp->left;
                    }
                    else{
                        return 0;
                    }
                }
                else{
                    if(temp->right!=NULL){
                        temp=temp->right;
                    }
                    else{
                        return 0;
                    }
                }
                i++;
            }
            return temp->dollar; 
        }
        void helper(string s,int st,node* f){//helper function for search2
            if(f==NULL){
                return;
            }
            else if(st>siz-1){
                return;
            }
            else{
                if(s[st]=='0'){
                    if(f->left==NULL){
                        return ;
                    } 
                    else{
                        score=score+f->left->dollar;
                        helper(s,st+1,f->left);
                    }
                }
            
                else if(s[st]=='1'){
                    if(f->right==NULL){
                        return ;
                    } 
                    else if(f->right!=NULL){
                        score+=f->right->dollar;
                        helper(s,st+1,f->right);
                    }
                }
                else if(s[st]=='?'){
                    if(f->left==NULL && f->right==NULL){
                        return;
                    }
                    else if(f->left==NULL){
                        score+=f->right->dollar;
                        helper(s,st+1,f->right);
                    }
                    else if(f->right==NULL){
                        score+=f->left->dollar;
                        helper(s,st+1,f->left);
                    }
                    else{
                        score+=(f->left->dollar+f->right->dollar);
                    helper(s,st+1,f->left);
                    helper(s,st+1,f->right);
                    }
                }
            }
            
        }
        void search2(string s){
            while(s[siz]!='\0'){
                siz++;
            }
            node* temp=root;
            score=0;
            helper(s,0,temp);//recursively calling the helper function
        }
};

int main(){
    trie ds;//basic trie
    trie suff;//suffix trie
    int t;
    cin>>t;
    while(t--){
        int q;//input section
        cin>>q;
        if(q==1){
            string in;
            cin>>in;
            ds.insert(in);//inserting in both suffix trie and basic trie
            suff.insert1(in);
        }
        else if(q==2){
            string in;
            cin>>in;
            ds.remove(in);
            suff.remove1(in);
        }
        else if(q==3){
            string in;
            cin>>in;
            cout<<suff.search1(in)<<endl;
        }
        else{
            string in;
            cin>>in;
            ds.search2(in);
            cout<<score<<endl;
        }
    }
}

