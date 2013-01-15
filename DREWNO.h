#ifndef DREWNO_H
#define DREWNO_H

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
		int height();
		void draw ();
		int count (AVLNode* n);
		bool isEmpty ();
		~Avltree( ) ;
		static void deltree ( AVLNode *root ) ;
} ;


#endif