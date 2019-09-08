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
       	void setx(T val)                   // All the data for any node is encapsulated by declaring it private
       	    {x=val;}                       // so, for accessing that data, we need to create some public functions
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
class BST 
    {
public:
        Node<T> *root; // root node
        int n; // total number of nodes

        BST(T val){
            root=new Node<T>;
            root->setx(val);
            n=1;
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
                        cout<<"key found"<<endl;
                        return 1;}
                
                else{temp=temp->getleft();}
            }
            cout<<"key not found"<<endl;
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
                return 1;
                }
            else{
                p->setleft(f);
                f->setparent(p);
                n++;
                return 1;
                }
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
                    n--;
                    return 1;
                }
                else{
                    temp->getparent()->setright(NULL);
                    n--;
                    return 1;
                }
            }
            else if(temp->getleft()==NULL){
                if(temp==temp->getparent()->getleft()){
                    temp->getparent()->setleft(temp->getright());
                    temp->getright()->setparent(temp->getparent());
                    n--;
                    return 1;
                }
                else{
                    temp->getparent()->setright(temp->getright());
                    temp->getright()->setparent(temp->getparent());
                    n--;
                    return 1;
                }
            }
            else if(temp->getright()==NULL){
                if(temp==temp->getparent()->getleft()){
                    temp->getparent()->setleft(temp->getleft());
                    temp->getleft()->setparent(temp->getparent());
                    n--;
                    return 1;
                }
                else{
                    temp->getparent()->setright(temp->getleft());
                    temp->getleft()->setparent(temp->getparent());
                    n--;
                    return 1;
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
                    n--;
                    return 1;       
            }
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
BST<int> tree(5);
tree.insert(9);
tree.insert(2);
tree.search(3);
tree.search(9);
tree.insert(7);
tree.remove(9);
tree.inorder_traversal(tree.root);
cout<<endl;
cout<<tree.n<<endl;
return 0;
}

                        
                        
