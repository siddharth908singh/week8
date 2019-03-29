//Binary search tree
#include<iostream>
using namespace std;

//defining the class node

class node{
	public:
	int data;
	node* left;
	node* right;
	node* parent;

	
	//Constructor making pointers to null
	node(int val){
		left = NULL;
		right = NULL;
		parent = NULL;		
		data = val;
	}
};

//The tree class
class bst3{
	public:
	node* root;
	int count;
	//Constructor making rrot point null
	bst3(){
		root = NULL;
	}

	
//Insert
void insert(int value){
//root case
	if(root==NULL){
		root = new node(value);
		count++;
		return;
	}
	insertHelper(root, value);
	count++;
}

void insertHelper(node* curr, int value){
//moving accordingly and checking
	if(curr->data > value){
	//If the next position is NULL, insert
		if(curr->left==NULL){
			curr->left = new node(value);
			curr->left->parent = curr;
			return;
		}
		//else go for recursion
		else{
			insertHelper(curr->left, value);
		}
	}
	else{
	//If the next position is NULL, insert
		if(curr->right==NULL){
			curr->right = new node(value);
			curr->right->parent = curr;
			return;
		}
		//else go for recursion
	 	else {
			insertHelper(curr->right, value);
		}
	}
		
}
//display
void display(){
	display2(root);
	cout<<"\b "<<endl;
}
	
//This is inorder display...
void display2(node* curr){
	//Base condition
	if(curr == NULL){
		return;
	}
	//display left
	display2(curr->left);
	//display current
	cout << curr->data << ",";
	//display right
	display2(curr->right);
}

//Search
node* search(int val){
	return search2(val, root);
}

node* search2(int val,node* curr){
//If tree is empty or reached the end of tree or value found
	if(curr == NULL || curr->data == val){
		return curr;
	}
	else if(curr->data > val){
		return search2(val, curr->left);
	}
	else{
		return search2(val, curr->right);
	}
}

//Find minimum
node* fmin(int val){
	node* curr = search(val);
	if(root==NULL||curr==NULL){
		return NULL;
	}
	return fmin2(val,curr);
	}

node* fmin2(int val, node* curr){
	if(curr->left==NULL){
		return curr;
	}
	else{
		fmin2(val, curr->left);
	}
}
	
//Count
int Count(){
	return count;
}

//Delete
void Delete(int val){
	node* curr = search(val);
	//If node does not exist exist
	if(curr==NULL){
		cout << "This value doesn't exist in the tree.\nTry again!"<<endl;
	}
	else{
		count--;
		//condition for one node
		if(curr->left&&curr->right==NULL||curr->left==NULL&&curr->right){
			//left
			if(curr->left&&curr->right==NULL){
				node* temp = curr->left;
					//if current is root
					if(curr==root){
						root=temp;
					}
					else{
						//left or right
						if((curr->data)<(curr->parent->data)){
							curr->parent->left=temp;}

						else{
							curr->parent->right=temp;
						}
					}
				temp->parent=curr->parent;
			}
			//If right child exist
			else{
				node* temp = curr->right;
				//if current is root
				if(curr==root){
					root=temp;
				}
					else{
						//Wether curr is left child or right one
						if((curr->data)<(curr->parent->data)){
							curr->parent->left=temp;}
						else{curr->parent->right=temp;}
					}
				temp->parent=curr->parent;
				}		
				delete curr;
				return;
			}
			//condition for 2 nodes
			if(curr->left&&curr->right){
			
				node* temp = fmin(curr->right->data);
				curr->data = temp->data;
				
				if(temp->right){
					temp->parent->left=temp->right;
					temp->right->parent=temp->parent;
				}
				else{
					temp->parent->left=NULL;
				}
				delete temp;
				return;
			}
			if(curr->left==NULL&&curr->right==NULL){
				//if current is root
				if(curr==root){root=NULL;}
				//removing previous links
				if((curr->data)<(curr->parent->data)){
					curr->parent->left=NULL;
				}
				else{curr->parent->right=NULL;}
				delete curr;
			}
		}
	}

//print range
	void printrange(int low,int high){	
		printrange2(root,low,high);
	}
	void printrange2(node* curr,int low,int high){
		//Base condition
		if(curr == NULL){return;}
		//display left
		printrange2(curr->left,low,high);
		//display current if within range
		if((curr->data)>=low && (curr->data)<=high){cout << curr->data << ",";}
		//display right
		printrange2(curr->right,low,high);
	}
//count nodes and values
	int rangecount(int low,int high){	
		return rangecount2(root,low,high);
	}

	int rangecount2(node* curr,int low,int high){
		//Base case
		if(!curr){return 0;}
		
		if(curr->data == high && curr->data == low){return 1;}

		
		if((curr->data)<=high && (curr->data)>=low)
			{return 1 + rangecount2(curr->left,low,high) + rangecount2(curr->right,low,high);}

		else if((curr->data)<low){return rangecount2(curr->right,low,high);}

		
		else{return rangecount2(curr->left,low,high);}
	}
//height
	int height(){
		return height2(root);
	}

	int height2(node* curr){
	//Base case
		if(!curr){return 0;}

		//Create two parameters
		int lh = height2(curr->left);
		int rh = height2(curr->right);

		
		if(lh>rh){return (lh+1);}
		else {return (rh+1);}
	}
};


int main(){
	
	bst3 b1;

	//Inserting in tree and checking with display
	b1.insert(7);
	b1.insert(28);
	b1.insert(6);
	b1.insert(16);
	b1.insert(4);
	b1.insert(9);
	b1.insert(97);
	b1.insert(6);
	b1.insert(54);
	b1.display();

	
	node* find = b1.search(16);
	if (find!=NULL){cout << find->data << endl;}
	else{cout << "The number is not there in the tree" << endl;} 
	

	node* parent = b1.fmin(4);
	cout << parent-> data << endl;

	int right = b1.Count();
	cout << "No of nodes = " << right << endl;
	b1.display();

	
	b1.Delete(9);
	b1.display();

	cout << "Now comes range search."<<endl;
	cout << "Give the ranges."<<endl;
	int x,y;
	cin >> x >> y;
	cout << "Items in between the range:-"<<endl;
	b1.printrange(x,y);
	cout << endl <<"Number of items in the range = " << b1.rangecount(x,y) <<endl;
	cout << "range search over" << endl;


	cout << "The height of tree = " << b1.height() << endl;
	
return 0;
}
