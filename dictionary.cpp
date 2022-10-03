#include <iostream>
#include "Linked.cpp"
using namespace std;

/*struct dictionary{
	char word[50];
	char pron[60]; //pronunciation
	char type[4];
	char meaning[200];
};*/

/*template <class T>
struct nodeList{ //you can add constructor here
	T data;
	nodeList<T> * next;
};

template <class T>
struct dicIndex{
     char word[50];
     nodeList posList;// list of position(references) of record on the file
};*/


template <class T>
struct avlNode{
    T data;
    int height;
    avlNode<T> * left;
    avlNode<T> * right;

};

template <class T>
class AVL{
    public:
        AVL();//default constructor
        AVL(AVL<T> & avl); //copy constructor
        virtual ~AVL(); //destructor
        void makeEmpty(avlNode<T> * t);
        int isEmpty();
        void inorder();
	    void insert(T data); //uses insert private
		void remove(T target);//uses remove private
        void display(); //uses inorder private
        avlNode<T> * findMin(avlNode<T> * r);
        avlNode<T> * findMax(avlNode<T> * r);
    protected:
    private:
        avlNode<T> * root;
        int height(avlNode<T> * n);
        avlNode<T> * singleRightRotate(avlNode<T> * n);
        avlNode<T> * doubleRightRotate(avlNode<T> * n);
        avlNode<T> * singleLeftRotate(avlNode<T> * n);
        avlNode<T> * doubleLeftRotate(avlNode<T> * n);
        avlNode<T> *  getBalance(avlNode<T> * n);
        avlNode<T> * insert(T data, avlNode<T> * avlRoot);
        avlNode<T> * remove(T data, avlNode<T> * avlRoot);
        void inorder(avlNode<T> * avlRoot);
};

template <class T>
AVL<T>::AVL(){
	root=NULL;
}
template <class T>
AVL<T>::AVL(AVL<T> & avl){
	/*if(avl.root==NULL)
	{
		root=NULL;
	}
	else
	{
		avlNode<T> temp1=avl.root;
		
	}*/
}

template <class T>
AVL<T>::~AVL(){
	/*root=*/makeEmpty(root);
}

template <class T>
void AVL<T>::makeEmpty(avlNode<T> * t){
	if(t!=NULL)
	{
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
	t=NULL;
}
template <class T>
int AVL<T>::isEmpty(){
	return root==NULL;
}

template <class T>
void AVL<T>::insert(T data){
	insert(data,root);
}
template <class T>
void AVL<T>::remove(T target){
	remove(target,root);
}
template <class T>
void AVL<T>::display(){
	inorder(root);	
}
template <class T>
avlNode<T> * AVL<T>::findMin(avlNode<T> * r){
	if(r!=NULL)
	{
		while(r->left!=NULL)
		{
			r=r->right;
		}
	}
	return r;
}
template <class T>
avlNode<T> * AVL<T>::findMax(avlNode<T> * r){
	if(r!=NULL)
	{
		while(r->right!=NULL)
		{
			r=r->right;
		}
	}
	return r;
}
template <class T>
int AVL<T>::height(avlNode<T> * n){
	if(n==NULL)
		return 0;
	return n->height;
}
template <class T>
avlNode<T> * AVL<T>::singleRightRotate(avlNode<T> * n){
	avlNode<T> *temp;
	temp=n->right;
	n->right=temp->left;
	temp->left=n;
	return temp;
}
template <class T>
avlNode<T> * AVL<T>::doubleRightRotate(avlNode<T> * n){
	avlNode<T> *temp;
	temp=n->right;
	n->right=singleLeftRotate(temp);
	return singleRightRotate(n);
}
template <class T>
avlNode<T> * AVL<T>::singleLeftRotate(avlNode<T> * n){
	avlNode<T> *temp;
	temp=n->left;
	n->left=temp->right;
	temp->right=n;
	return temp;
}
template <class T>
avlNode<T> * AVL<T>::doubleLeftRotate(avlNode<T> * n){
	avlNode<T> *temp;
	temp=n->left;
	n->left=singleRightRotate(temp);
	return singleLeftRotate(n);
}
template <class T>
avlNode<T> * AVL<T>::getBalance(avlNode<T> *n){
	/*if(n==NULL)
		return 0;*/
	return height(n->left) - height(n->right);
}
template <class T>
avlNode<T> * AVL<T>::insert(T data, avlNode<T> * avlRoot){
	if(avlRoot==NULL)
	{
		avlRoot=new avlNode<T>;
		avlRoot->data=data;
		avlRoot->left=NULL;
		avlRoot->right=NULL;
		return avlRoot;
	}
	else if(data<avlRoot->data)
	{
		avlRoot->left=insert(data,avlRoot->left);
		avlRoot=getBalance(avlRoot);
	}
	else if(data>=avlRoot->data)
	{
		avlRoot->right=insert(data,avlRoot->right);
		avlRoot=getBalance(avlRoot);
	}
	return avlRoot;
}
template <class T>
avlNode<T> * AVL<T>::remove(T data, avlNode<T> * avlRoot){
	avlNode<T> *temp;
	if(avlRoot==NULL)
		return NULL;
	else if(data<avlRoot->data)
	{
		avlRoot->left=remove(data,avlRoot->left);
	}
	else if(data>avlRoot->data)  
	{
		avlRoot->right=remove(data,avlRoot->right);
	}
	else if(avlRoot->left && avlRoot->right)  //element has 2 children
	{
		temp=findMin(avlRoot->right);
		avlRoot->data=temp->data;
		avlRoot->right=remove(avlRoot->data,avlRoot->right);
	}
	else  //element has 1 or 0 child
	{
		temp=avlRoot;
		if(avlRoot->left==NULL)
			avlRoot=avlRoot->right;
		else if(avlRoot->right==NULL)
			avlRoot=avlRoot->left;
		delete temp;
	}
	if(avlRoot==NULL)
		return avlRoot;
	avlRoot=getBalance(avlRoot);
}
template <class T>
void AVL<T>::inorder(avlNode<T> * avlRoot){
	if(avlRoot==NULL)
	{
		return;
	}
	inorder(avlRoot->left);
	cout<<avlRoot->data<<" ";
	inorder(avlRoot->right);
	
}

int main()
{
	int choice,item;
	AVL<string> a;
	dictionary d;
	//LinkedList<string> Myl;
	while(1)
	{
		cout<<"\n--------------------------"<<endl
		    <<"1.Insert new word"<<endl
		    <<"2.Display record"<<endl
		    <<"3.Exit"<<endl;
		cout<<"Enter your choice\n";
		cin>>choice;
		int x;
		switch(choice)
		{
			case 1:
				cout<<"Enter the word\n";
				cin>>d.word;
				a.insert(d.word);
				cout<<"How many meaning does it have\n";
				cin>>x;
				cout<<"Enter meaning\n";
				if(x>1)
				{
					LinkedList<string> Myl;
					for(int i=0;i<=x;i++)
					{
						cin>>d.meaning;
						Myl.insert(d.meaning);
					}
				}
				cin>>d.meaning;
				
				cout<<"Enter type of word\n";
				cin>>d.type;
				cout<<"Enter pronouncation\n";
				cin>>d.pron;
				//a.insert(d.word);
			case 2:
				a.display();
				/*cout<<d.word<<endl;
				cout<<d.meaning<<endl;
				cout<<d.type<<endl;
				cout<<d.pron<<endl;*/
	}
}
}

