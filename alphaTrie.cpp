//a trie which can insert and search strings containing lowercase english letters.
#include<iostream>
using namespace std;
int n;
//New Branch 
class node{
    public:
        char c;
        int dollar;
        node* pointers[27];
        node(char r){
            dollar=0;
            c=r;
            for(int i=0;i<27;i++){
                pointers[i]=NULL;
            }
        }
};
class trie{
    public:
        node* root;
        trie(){
            root=new node('*');
        }
        int search(string s){
            node* temp=root;
            int i=0;
            while(i<n){
                    if(temp->pointers[int(s[i])-97]==NULL){
                        return 0;
                    }
                    else{
                        temp=temp->pointers[int(s[i])-97];
                    }
                i++;
            }
            if(temp->pointers[26]->c=='$'){
                return 1;
            }
            else{
                return 0;
            }
        }
        
        int insert(string s){
            if(search(s)==1){
                return 0;
                }
            int k=n-1;
            while(k>=0){
                node* temp=root;
                int i=k;
                while(i<n){
                        if(temp->pointers[int(s[i])-97]==NULL){
                            temp->pointers[int(s[i])-97]=new node(s[i]);
                            temp=temp->pointers[int(s[i])-97];
                        }
                        else{
                            temp=temp->pointers[int(s[i])-97];
                        }
                        i++;
                    }
            temp->pointers[26]=new node('$');
            k--;  
            }
            return 1;
        }
        
};
int main(){
    trie T;
    T.insert("alphabet");
    T.insert("alphawaves");
    T.search("alpha");

}
