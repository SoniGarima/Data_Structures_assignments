#include<iostream>
using namespace std;
template <typename T>
class Node
{
    private:
        T x;
        Node<T> *left;
        Node<T> *right;
        Node<T> *parent;
    public:
        Node(){
                left=NULL;
                right=NULL;
                parent=NULL;
                }
        void setx(T val)
            {x=val;}
        T getx()
            {return x;}
        void setleft(Node<T>* d)
            {left=d;}
        Node<T>* getleft()
            {return left;}
        void setright(Node<T>* d)
            {right=d;}
        Node<T>* getright()
            {return right;}
        void setparent(Node<T>* d)
            {parent=d;}
        Node<T>* getparent()
            {return parent;}
        

};

template <typename T>
class AVL 
    {
public:
        Node<T> *root; // root node
        int n; // total number of nodes

        AVL(T val){
            root=new Node<T>;
            root->setx(val);
            n=1;
        }
        int height_finder(Node<T>* n){
            //cout<<"I am at leaf node but outta it"<<endl;
            if(n==NULL)
                return 0;
            else if(n->getleft()==NULL && n->getright()==NULL){
                //cout<<"I am at leaf node"<<endl;
                return 1;
            }
            else{
                int e1=height_finder(n->getleft());
                int e2=height_finder(n->getright());
                int k=max(e1,e2);
                return k+1;
            }
        }

        int balance_factor(Node<T>* n){
            //cout<<"m in balance factor"<<endl;
            return(height_finder(n->getleft())-height_finder(n->getright()));
        }

        void left_rotation(Node<T>* p){
            Node<T>* t=p->getright();
            Node<T>* n=t->getleft();
            if(p->getparent()==NULL){
                root=t;
                t->setparent(NULL);
            }
            else if(p->getparent()->getright()==p){
                
                p->getparent()->setright(t);
                t->setparent(p->getparent());
            }
            else if(p->getparent()->getleft()==p){
                p->getparent()->setleft(t);
                t->setparent(p->getparent());
            }
            
            t->setleft(p);
            p->setparent(t);
            p->setright(NULL);
            if(n!=NULL){
                p->setright(n);
                n->setparent(p);
            }
            return;

        }
        void right_rotation(Node<T>* p){
            Node<T>* t=p->getleft();
            Node<T>* n=t->getright();
            if(p->getparent()==NULL){
                root=t;
                t->setparent(NULL);
            }
            else if(p->getparent()->getleft()==p){
                p->getparent()->setleft(t);
                t->setparent(p->getparent());

            }
            else{
                p->getparent()->setright(t);
                t->setparent(p->getparent());
            }
            
            t->setright(p);
            p->setparent(t);
            p->setleft(NULL);
            if(n!=NULL){
                p->setleft(n);
                n->setparent(p);
            }
            return;

        }

        void left_right_rotation(Node<T>* p){
            Node<T>* t=p->getleft();
            left_rotation(t);
            right_rotation(p);
            return ;
        }
        void right_left_rotation(Node<T>* p){
            Node<T>* t=p->getright();
            right_rotation(t);
            left_rotation(p);
            return ;

        }
        int balance(Node<T>*p)
        {
            if(balance_factor(p)==(0)||balance_factor(p)==1||balance_factor(p)==-1){
                //cout<<balance_factor(p)<<endl;
                return 0;
            }
            else{
                if(balance_factor(p)>1){
                    if(balance_factor(p->getleft())>0){
                        right_rotation(p);
                        return 1;
                    }
                    else if(balance_factor(p->getleft())<=0){
                        left_right_rotation(p);
                        return 1;
                    }
                    }
                else{
                    if(balance_factor(p->getright())<0){
                        left_rotation(p);
                        return 1;
                    }
                    else if(balance_factor(p->getright())>=0){
                        right_left_rotation(p);
                        return 1;
                    }
                }
                } 
            }
        
        int search(T val)
        {
            Node<T> *temp=root;
            while(temp!=NULL)
            {
                
                if(val>temp->getx())
                    {
                        temp=temp->getright();
                    }
                
                else if(val==temp->getx())
                    {
                        return 1;}
                
                else{temp=temp->getleft();}
            }
            //cout<<height_finder(root)<<endl;
            return 0;
            
          }
        int insert(T x)
        {   
            if(search(x)==1){return 0;}

            Node<T> *temp=root;
            Node<T>* p;
            while(temp!=NULL)
                {
                    p=temp;
                    if(x>temp->getx())
                        {
                            temp=temp->getright();
                        }
                    else{temp=temp->getleft();}
                
                }
            Node<T> *f=new Node<T>;
            f->setx(x);
            if(x>p->getx()){
                p->setright(f);
                f->setparent(p);
                n++;
                }
            else{
                p->setleft(f);
                f->setparent(p);
                n++;
                }
                while(f!=root->getparent()){
                    int b=balance(f);
                    if(b==0){f=f->getparent();
                        continue;}
                    else
                        break;
                        }
                    cout<<height_finder(root)<<endl;
                    return 1;
        }

        int remove(T x)
        {
            if(search(x)==0){return 0;}
            Node<T> *temp=root;
            while(temp!=NULL)
            {
                
                if(x>temp->getx())
                    {
                        temp=temp->getright();
                    }
                
                else if(x==temp->getx())
                    break;
                
                else{temp=temp->getleft();}
            }
            if(temp->getleft()==NULL && temp->getright()==NULL){
                if(temp==temp->getparent()->getleft()){
                    temp->getparent()->setleft(NULL);
                    
                    
                }
                else{
                    temp->getparent()->setright(NULL);
                
                }
            }
            else if(temp->getleft()==NULL){
                if(temp==temp->getparent()->getleft()){
                    temp->getparent()->setleft(temp->getright());
                    temp->getright()->setparent(temp->getparent());
                    
                }
                else{
                    temp->getparent()->setright(temp->getright());
                    temp->getright()->setparent(temp->getparent());
                    
                }
            }
            else if(temp->getright()==NULL){
                if(temp==temp->getparent()->getleft()){
                    temp->getparent()->setleft(temp->getleft());
                    temp->getleft()->setparent(temp->getparent());
                    
                }
                else{
                    temp->getparent()->setright(temp->getleft());
                    temp->getleft()->setparent(temp->getparent());
                }
            }
            else{
                
                    Node<T>* m=temp;
                    m=m->getright();
                    while(m->getleft()!=NULL){
                        m=m->getleft();
                    }
                    temp->setx(m->getx());
                    m->getparent()->setleft(NULL);
            }
            Node<T>* parent=temp->getparent();
            n--;
            while(parent!=NULL){
                int b=balance(parent);
                parent=parent->getparent();
            }
            cout<<height_finder(root)<<endl;
        }

        void inorder_traversal(Node<T>* R){
            Node<T>* temp=R;
            if(temp!=NULL){
                inorder_traversal(temp->getleft());
                cout<<temp->getx()<<" ";
                inorder_traversal(temp->getright());
            }
            else
                return;
        }
                        
    };    
        
                      
                        
int main()
{
AVL<int> tree(7);
tree.insert(6);
tree.insert(5);
tree.insert(9);
tree.insert(8);
tree.insert(4);
tree.insert(3);
tree.search(3);
tree.search(9);
tree.remove(7);
tree.remove(8);
tree.remove(9);
tree.remove(4);
tree.inorder_traversal(tree.root);
cout<<endl;
cout<<tree.root->getx()<<endl;
cout<<tree.n<<endl;
return 0;
}
