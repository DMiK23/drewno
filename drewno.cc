#include <iostream>
#include "ERRORS.h"
#include <queue>

using namespace std;

struct AVLNode
{
	int data ;
	int balfact ;
	AVLNode *left ;
	AVLNode *right ;
} ;
 
class Avltree
{
	private :
		AVLNode *root ;
	public :
		Avltree( ) ;
		AVLNode*  insert ( int data, bool *h ) ;
		static AVLNode* buildtree ( AVLNode *root, int data, bool *h ) ;
		void display( AVLNode *root ) ;
		AVLNode* deldata ( AVLNode* root, int data, bool *h ) ;
		static AVLNode* del ( AVLNode *node, AVLNode* root, bool *h ) ;
		static AVLNode* balright ( AVLNode *root, bool *h ) ;
		static AVLNode* balleft ( AVLNode* root, bool *h ) ;
		//void setroot ( AVLNode *avl ) ;
		int height();
		void draw ();
		int count (AVLNode* n);
		bool isEmpty ();
		~Avltree( ) ;
		static void deltree ( AVLNode *root ) ;
} ;
Avltree :: Avltree( )
{
	root = NULL ;
}
AVLNode* Avltree :: insert ( int data, bool *h )
{
	root = buildtree ( root, data, h ) ;
	return root ;
}
AVLNode* Avltree :: buildtree ( AVLNode *root, int data, bool *h )
{
	AVLNode *node1, *node2 ;
 
	if ( root == NULL )
	{
		try{
		root = new AVLNode ;
		} catch (std::bad_alloc){
			throw MemoryFull();
		}
		root -> data = data ;
		root -> left = NULL ;
		root -> right = NULL ;
		root -> balfact = 0 ;
		*h = true ;
		return ( root ) ;
	}
	if ( data < root -> data )
	{
		root -> left = buildtree ( root -> left, data, h ) ;
 
		// If left subtree is higher
		if ( *h )
		{
			switch ( root -> balfact )
			{
				case 1 :
					node1 = root -> left ;
					if ( node1 -> balfact == 1 )
					{
						cout << endl << "Right rotation." ;
						root -> left = node1 -> right ;
						node1 -> right = root ;
						root -> balfact = 0 ;
						root = node1 ;
					}
					else
					{
						cout << endl <<"Double rotation, left then right." ;
						node2 = node1 -> right ;
						node1 -> right = node2 -> left ;
						node2 -> left = node1 ;
						root -> left = node2 -> right ;
						node2 -> right = root ;
						if ( node2 -> balfact == 1 )
							root -> balfact = -1 ;
						else
							root -> balfact = 0 ;
						if ( node2 -> balfact == -1 )
							node1 -> balfact = 1 ;
						else
							node1 -> balfact = 0 ;
						root = node2 ;
					}
					root -> balfact = 0 ;
					*h = false ;
					break ;
 
				case 0 :
					root -> balfact = 1 ;
					break ;
				case -1 :
					root -> balfact = 0 ;
					*h = false ;
			}
		}
	}
 
	if ( data > root -> data )
	{
		root -> right = buildtree ( root -> right, data, h ) ;
 
		if ( *h )
		{
			switch ( root -> balfact )
			{
				case 1 :
					root -> balfact = 0 ;
					*h = false ;
					break ;
				case 0 :
					root -> balfact = -1 ;
					break ;
				case -1 :
					node1 = root -> right ;
					if ( node1 -> balfact == -1 )
					{
						cout << endl << "Left rotation." ;
						root -> right = node1 -> left ;
						node1 -> left = root ;
						root -> balfact = 0 ;
						root = node1 ;
					}
					else
					{
						cout << endl << "Double rotation, right then left." ;
						node2 = node1 -> left ;
						node1 -> left = node2 -> right ;
						node2 -> right = node1 ;
						root -> right = node2 -> left ;
						node2 -> left = root ;
						if ( node2 -> balfact == -1 )
							root -> balfact = 1 ;
						else
							root -> balfact = 0 ;
						if ( node2 -> balfact == 1 )
							node1 -> balfact = -1 ;
						else
							node1 -> balfact = 0 ;
						root = node2 ;
					}
					root -> balfact = 0 ;
					*h = false ;
			}
		}
	}
	return ( root ) ;
}
void Avltree :: display ( AVLNode* root )
{
	if ( root != NULL )
	{
		display ( root -> left ) ;
		cout << root -> data << "\t" ;
		display ( root -> right ) ;
	}
}
AVLNode* Avltree :: deldata ( AVLNode *root, int data, bool *h )
{
	AVLNode *node ;
	if ( root == NULL )
	{
		throw NoSuchData();
		return ( root ) ;
	}
		if ( data < root -> data )
		{
			root -> left = deldata ( root -> left, data, h ) ;
			if ( *h )
				root = balright ( root, h ) ;
		}else{
		if ( data > root -> data )
		{
			root -> right = deldata ( root -> right, data, h ) ;
			if ( *h )
				root = balleft ( root, h ) ;
		}else{
			node = root ;
			if ( node -> right == NULL )
			{
				root = node -> left ;
				*h = true ;
				delete ( node ) ;
			}else{
				if ( node -> left == NULL )
				{
					root = node -> right ;
					*h = true ;
					delete ( node ) ;
				}else{
					node -> right = del ( node -> right, node, h ) ;
					if ( *h )
						root = balleft ( root, h ) ;
				}
			}
		}
	}
	return ( root ) ;
}
AVLNode* Avltree :: del ( AVLNode *succ, AVLNode *node, bool *h )
{
	AVLNode *temp = succ ;
 
	if ( succ -> left != NULL )
	{
		succ -> left = del ( succ -> left, node, h ) ;
		if ( *h )
			succ = balright ( succ, h ) ;
	}
	else
	{
		temp = succ ;
		node -> data = succ -> data ;
		succ = succ -> right ;
		delete ( temp ) ;
		*h = true ;
	}
	return ( succ ) ;
}
AVLNode* Avltree :: balright ( AVLNode *root, bool *h )
{
	AVLNode *temp1, *temp2 ;
	switch ( root -> balfact )
	{
		case 1 :
			root -> balfact = 0 ;
			break ;
		case 0 :
			root -> balfact = -1 ;
			*h  = false ;
			break ;
		case -1 :
			temp1 = root -> right ;
			if ( temp1 -> balfact <= 0 )
			{
				cout << endl << "Left rotation." ;
				root -> right = temp1 -> left ;
				temp1 -> left = root ;
				if ( temp1 -> balfact == 0 )
				{
					root -> balfact = -1 ;
					temp1 -> balfact = 1 ;
					*h = false ;
				}
				else
				{
					root -> balfact = temp1 -> balfact = 0 ;
				}
				root = temp1 ;
			}
			else
			{
				cout << endl << "Double rotation, right then left." ;
				temp2 = temp1 -> left ;
				temp1 -> left = temp2 -> right ;
				temp2 -> right = temp1 ;
				root -> right = temp2 -> left ;
				temp2 -> left = root ;
				if ( temp2 -> balfact == -1 )
					root -> balfact = 1 ;
				else
					root -> balfact = 0 ;
				if ( temp2 -> balfact == 1 )
					temp1 -> balfact = -1 ;
				else
					temp1 -> balfact = 0 ;
				root = temp2 ;
				temp2 -> balfact = 0 ;
			}
	}
	return ( root ) ;
}
AVLNode* Avltree :: balleft ( AVLNode *root, bool *h )
{
	AVLNode *temp1, *temp2 ;
	switch ( root -> balfact )
	{
		case -1 :
			root -> balfact = 0 ;
			break ;
 
		case 0 :
			root -> balfact = 1 ;
			*h = false ;
			break ;
 
		case 1 :
			temp1 = root -> left ;
			if ( temp1 -> balfact >= 0 )
			{
				cout << endl << "Right rotation." ;
				root -> left = temp1 -> right ;
				temp1 -> right = root ;
 
				if ( temp1 -> balfact == 0 )
				{
					root -> balfact = 1 ;
					temp1 -> balfact = -1 ;
					*h = false ;
				}
				else
				{
					root -> balfact = temp1 -> balfact = 0 ;
				}
				root = temp1 ;
			}
			else
			{
				cout << endl << "Double rotation, left then right." ;
				temp2 = temp1 -> right ;
				temp1 -> right = temp2 -> left ;
				temp2 -> left = temp1 ;
				root -> left = temp2 -> right ;
				temp2 -> right = root ;
				if ( temp2 -> balfact == 1 )
					root -> balfact = -1 ;
				else
					root -> balfact = 0 ;
				if ( temp2-> balfact == -1 )
					temp1 -> balfact = 1 ;
				else
					temp1 -> balfact = 0 ;
				root = temp2 ;
				temp2 -> balfact = 0 ;
			}
	}
	return ( root ) ;
}

int Avltree::height(){
	AVLNode* n;
	n = root;
	int i = 0;
	while (n != NULL){
		i++;
		n = n->left;
	}
	return i;
}

void Avltree::draw (){
	int d = height();
	AVLNode* LineToken;
	LineToken = new AVLNode;
	std::queue < AVLNode* > cueue1;
	cueue1.push (root);
	cueue1.push (LineToken);
	//cout << cueue1.front()->data<<endl;
	while (!cueue1.empty()){
		AVLNode* current;
		current = cueue1.front();
		cueue1.pop ();
		if (current != NULL){
			for (int i = 0; i < d; i++)
				cout << "\t";
			cout << current->data;
			cueue1.push (current->left);
			cueue1.push (current->right);
		}else
			cout << "\tx";
		if (cueue1.front() == LineToken){
			cueue1.pop();
			cout << endl;
			d--;
			if (current != NULL)
				cueue1.push (LineToken);
		}
	}
	cout << endl;
}
		


int Avltree::count (AVLNode* n){
	if (n !=NULL)
		return 1 + count (n->left) + count (n->right);
	else return 0;
}
bool Avltree::isEmpty (){
	return root == NULL;
}

Avltree :: ~Avltree( )
{
	delete ( root ) ;
}
 
 
void Avltree :: deltree ( AVLNode *root )
{
	if ( root != NULL )
	{
		deltree ( root -> left ) ;
		deltree ( root -> right ) ;
	}
	delete ( root ) ;
}
int main( )
{
	Avltree at ;
	AVLNode *avl = NULL ;
	bool h ;
	avl = at.insert ( 20, &h ) ;
//	at.setroot ( avl ) ;
	avl = at.insert ( 6, &h ) ;
//	at.setroot ( avl ) ;
	avl = at.insert ( 29, &h ) ;
//	at.setroot ( avl ) ;
	avl = at.insert ( 5, &h ) ;
//	at.setroot ( avl ) ;
	avl = at.insert ( 12, &h ) ;
//	at.setroot ( avl ) ;
	avl = at.insert ( 25, &h ) ;
//	at.setroot ( avl ) ;
	avl = at.insert ( 32, &h ) ;
//	at.setroot ( avl ) ;
	avl = at.insert ( 10, &h ) ;
//	at.setroot ( avl ) ;
	avl = at.insert ( 15, &h ) ;
//	at.setroot ( avl ) ;
	avl = at.insert ( 27, &h ) ;
//	at.setroot ( avl ) ;
	avl = at.insert ( 13, &h ) ;
//	at.setroot ( avl ) ;
	cout << endl << "AVL tree:" << endl ;
	at.display ( avl ) ;
	//avl = at.deldata ( avl, 20, &h ) ;
//	at.setroot ( avl ) ;
	//avl = at.deldata ( avl, 12, &h ) ;
//	at.setroot ( avl ) ;
	//cout << endl << "AVL tree after deletion of a node:" << endl ;
	//at.display ( avl ) ;
	cout << endl;
	at.draw ();
	return 0;
}