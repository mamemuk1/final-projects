#include <iostream>
using namespace std;

struct dictionary{
	char word[50];
	char pron[60]; //pronunciation
	char type[4];
	char meaning[200];
};

template <class T>
struct nodeList{ //you can add constructor here
	T data;
	nodeList<T> * next;
};

template <class T>
struct dicIndex{
     char word[50];
     nodeList<T> posList; // list of position(references) of record on the file
};




template <class T>
void DefaultDisplayer(T data){
	cout << data << " ";
}

template <class T>
class LinkedList
{
    public:
        LinkedList(); //constructor
        LinkedList(bool sorted);//constructor
        virtual ~ LinkedList(); //destructor
        bool isEmpty(); //returns true if list is empty
        bool insert(T newdata); //insert data
        bool remove(T targetData);  //remove targetData
        nodeList<T> * findNode(T target); //returns reference to the node
        void insertRangeAfter(T after, LinkedList <T> range); //inserts range of nodes range to list
	    void removeRange(T target1, T target2); //removes range of nodes from target1 to target2
	    LinkedList<T> getRange(T target1, T target2, bool remove=true);//return range of node from list (either removing or copying) from target1 to target 2 if fails returns false
       int count();//no of element
       void clear();//truncate the list to empty
    protected:
    private:
        nodeList<T> * head;
        nodeList<T> * tail;
        bool sorted;
        void insertNode(nodeList<T> * p, nodeList<T> * prev);
        nodeList<T> * deleteNode(nodeList<T> * prev); //remove node
        nodeList<T> * insertionSlot(nodeList<T> * p);//it finds after which to insert
        bool nodeToDelete(T  targetData, nodeList<T> * & prev);
};


template <class T>
LinkedList<T>::LinkedList(){
	head=tail=NULL;
}

template <class T>
LinkedList<T>::LinkedList(bool sorted){
	head=tail=NULL;
	this->sorted=sorted;
}

template <class T>
LinkedList<T>::~LinkedList(){
	nodeList<T> *temp;
	while(head!=NULL)
	{
		temp=head;
		head=head->next;
		delete temp;
	}
	tail=NULL;
}
 
template <class T>
bool LinkedList<T>::isEmpty(){
	return head==NULL;
}    

template <class T>
bool LinkedList<T>::insert(T newdata){
	nodeList<T> *p,pred,q;
	p=new nodeList<T>;
	if(p==NULL)
		return 0;
	p->data=newdata;
	pred=insertionSlot(newdata);
	insertNode(p,pred);
	return 1;
	
}

template <class T>
bool LinkedList<T>::remove(T targetData){
	nodeList<T> *p=findNode(targetData);
	if(p!=NULL)
	{
		deleteNode(p);
		return 1;
	}
	return 0;
	
}

template <class T>
nodeList<T> *LinkedList<T>::findNode(T target){
	if(head==NULL)
	{
		return NULL;
	}
	else if(target > tail->data && sorted)
	{
		return NULL;
	}
	else
	{
		nodeList<T> *p=head;
		if(sorted)
		{
			while(p!=NULL && p->data <= target)
			{
				if(p->data == target)
					return p;
				p=p->next;
			}
			return NULL;
		}
		else
		{
			while(p!=NULL)
			{
				if(p->data ==target)
				{
					return p;
				}
				p=p->next;
			}
			return NULL;
		}
	}
}

/*template <class T>
void LinkedList<T>::insertRangeAfter(T after, LinkedList<T> range){
	nodeList<T> *p=head, *curr=NULL;
	bool stop=false;
	if(sorted)
	{
		if(range->sorted==true && after)
	}
}

template <class T>
void LinkedList<T>::removeRange(T target1, T target2){
	
}

template <class T>
LinkedList<T>:: getRange(T target1, T target2, bool remove=true){
	
}*/

template <class T>
void LinkedList<T>::clear(){
	~LinkedList();	
}

template <class T>
void LinkedList<T>::insertNode(nodeList<T> * p, nodeList<T> * prev){
	if(head==NULL)
	{
		p->next=NULL;
		head=tail=p;
	}
	else if(prev==NULL)
	{
		p->head=NULL;
		head=p;
	}
	else
	{
		p->next=prev->next;
		prev->next=p;
		if(prev==tail)
			tail=p;
	}
	sorted=true;
	count++;
}

template <class T>
nodeList<T> *LinkedList<T>::deleteNode(nodeList<T> * prev){
	if(prev == head)
	{
		head=head->next;
	}
	
}

template <class T>
nodeList<T> * LinkedList<T>::insertionSlot(nodeList<T> * p){
	if(!sorted)
	{
		return tail;
	}
	nodeList<T> *q=head,*pred=NULL;
	while(q!=NULL && q->data < p->data)
	{
		pred=q;
		q=q->next;
	}
	return pred;
}

template <class T>
bool LinkedList<T>::nodeToDelete(T  targetData, nodeList<T> * & prev){
	
}
