#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H


template<typename Type>
class BST 
{
	struct Node
	{
		Type element;
		Node *left, *right;
	};

	Node* root;

	void pPrint(const Node* n) const
	{
		if(n!= nullptr)
		{
			pPrint(n->left);
			cout << n->element << ' ';
			pPrint(n->right);
		}
	}

	void pDelete(Node* n)
	{
		if(n!= nullptr)
		{
			pDelete(n->left);
			pDelete(n->right);
			delete n;
			n = nullptr;
		}
	}

	void pPreOrderCopy(Node* n)
	{
		if(n!= nullptr)
		{
			insert(n->element);
			pPreOrderCopy(n->left);
			pPreOrderCopy(n->right);
		}
	}

public:
	/////////////////////////////////////////////////
	// Function : Constructor
	// Notes : constructs an empty BST
	/////////////////////////////////////////////////
	BST();

	/////////////////////////////////////////////////
	// Function : Destructor
	// Notes : destroys the BST cleaning up any dynamic
	//         memory
	/////////////////////////////////////////////////
	~BST();

	/////////////////////////////////////////////////
	// Function : assignment operator
	/////////////////////////////////////////////////
	BST& operator=(const BST& assign);

	/////////////////////////////////////////////////
	// Function : copy constructor
	/////////////////////////////////////////////////
	BST(const BST& copy);

	/////////////////////////////////////////////////
	// Function : insert
	// Paramters : v - the item to insert
	/////////////////////////////////////////////////
	void insert(const Type& v);

	/////////////////////////////////////////////////
	// Function : findAndRemove
	// Parameters : v - the item to find (and remove if
	//                  it is found)
	// Return : bool - true if the item was removed, false
	//                 otherwise
	/////////////////////////////////////////////////
	bool findAndRemove(const Type& v);

	/////////////////////////////////////////////////
	// Function : find
	// Parameters : v - the item to find
	// Return : bool - true if the item was found, false
	//                 otherwise
	/////////////////////////////////////////////////
	bool find(const Type& v) const;

	/////////////////////////////////////////////////
	// Function : clear
	// Notes : clears the BST, cleaning up any dynamic
	//         memory
	/////////////////////////////////////////////////
	void clear();

	/////////////////////////////////////////////////
	// Function : printInOrder
	// Notes : prints the contents of the BST to the screen,
	//         in ascending order
	/////////////////////////////////////////////////
	void printInOrder() const;


};

/////////////////////////////////////////////////
// Function : Constructor
// Notes : constructs an empty BST
/////////////////////////////////////////////////
template<typename Type>
BST<Type>::BST()
{
	//root = new Node; //This is the root. 
	root = nullptr; 
	//root->right = nullptr;  // this would be way to create any extending leaves.
	//root->left = nullptr;
}

/////////////////////////////////////////////////
// Function : Destructor
// Notes : destroys the BST cleaning up any dynamic
//         memory
/////////////////////////////////////////////////
template<typename Type>
BST<Type>::~BST()
{
	clear();
}

/////////////////////////////////////////////////
// Function : assignment operator
/////////////////////////////////////////////////
template<typename Type>
BST<Type>& BST<Type>::operator=(const BST<Type>& assign)
{
	if(this != &assign)
	{
		this->clear();

		pPreOrderCopy(assign.root);
	}
	return *this;
}

/////////////////////////////////////////////////
// Function : copy constructor
/////////////////////////////////////////////////
template<typename Type>
BST<Type>::BST(const BST& copy)
{
	root = nullptr;

	*this = copy;
}

/////////////////////////////////////////////////
// Function : insert
// Paramters : v - the item to insert
/////////////////////////////////////////////////
template<typename Type>
void BST<Type>::insert(const Type& v)
{
	
	//Create a new Node n, initialize it
	Node* n = new Node; //Creating new temp node
	n->left = n->right = nullptr;
	n->element = v;

	
	//If the root is NULL
	//	attach at the root, return 
	if(root == nullptr)
	{
		root = n; //Setting root to the new node.
		return;
	} 
	//cur = root
	Node * cur = root; //In this case, set cur to root.

	
	while(true)
	{
		/*
		Compare n’s value against cur’s value
			If less 
				 if left is NULL add there, return
				 if not insert into left subtree
			If greater than or equal to
				 if right is NULL add there, return
				 if not insert into right subtree
		*/
		if(n->element < cur->element)
		{
			if(cur->left == nullptr)
			{
				cur->left = n; 
				return;
			}
			else
			{
				cur = cur->left;
			}
		}
		else
		{
			if(cur->right == nullptr)
			{
				cur->right = n;
				return;
			}
			else
			{
				cur = cur->right;
			}
		}
	}



	//else if( v < root->element){
	//	 

	//	if(n->element < cur->element)
	//	{
	//		if(cur->left == nullptr)
	//			cur->left = n;
	//		else 
	//			cur->left->left = n;

	//		return;
	//	}//endif


	//} else if( v > root->element){
	//	cur = root;

	//	if(n->element > cur->element)
	//	{
	//		if(cur->right == nullptr)
	//			cur->right = n;
	//		else 
	//			cur->right->right = n;

	//		return;
	//	}//endif

	//}//endif 
}

/////////////////////////////////////////////////
// Function : findAndRemove
// Parameters : v - the item to find (and remove if
//                  it is found)
// Return : bool - true if the item was removed, false
//                 otherwise
/////////////////////////////////////////////////
template<typename Type>
bool BST<Type>::findAndRemove(const Type& v)
{
	Node *cur = root;
	Node *prev = nullptr;

	Node *minimum = nullptr;
	Node *minimumParent = nullptr;

	while(true)
	{
		if( cur == nullptr)
			return false; 

		if(v < cur->element)
		{
			prev = cur;
			cur = cur->left;
		}
		else if(v > cur->element )
		{
			prev = cur;
			cur = cur->right;
		}
		else if(v == cur->element)
		{
			break;
		}
	}

	//==============================================================================================================

	while(true)
	{
		if(cur->element == v)
		{
			// case 0: no children
			if(cur->left == nullptr && cur->right == nullptr)
			{
				
				if(prev->right == cur)
				{
					prev->right = nullptr;
				} 
				else if (prev->left == cur) 
				{
					prev->left = nullptr; 
				}
				else 
				{
					root = nullptr;
				}
				
				delete cur;
				cur = nullptr;

				return true;
			}
			// case 1: one child
			else if(cur->left != nullptr && cur->right == nullptr)
			{
				prev->left = cur->left;
				//cur->right = cur;
				//delete cur;
				cur = nullptr;

				return true;
			}
			// case 1: one child
			else if(cur->left == nullptr && cur->right != nullptr)
			{
				prev->right = cur->right;
				//cur->right = cur;
				//delete cur;
				cur = nullptr;

				return true;
			} else {
				return false;
			}
		}
		// Check to see if the currents element is less than v
		else if(cur->element < v)
		{
			// increment to the left of the current node
			prev = cur;
			cur = cur->left;
		}
		// check to see if the currents element is greater than v
		else if(cur->element > v)
		{
			// increment to the right of the current node
			prev = cur;
			cur = cur->right;
		}
	}
}

/////////////////////////////////////////////////
// Function : find
// Parameters : v - the item to find
// Return : bool - true if the item was found, false
//                 otherwise
/////////////////////////////////////////////////
template<typename Type>
bool BST<Type>::find(const Type& v) const
{
	Node *cur = root; //Setting a current node to v;

	/*if( v < cur->element )
		find(cur->left);
	else if ( v > cur->element )
		find(cur->right);
	else if ( v == cur->element)
		return true;
	else if (v == nullptr)
		return false;*/

	/*
	cur = root
	Compare v against cur’s value
		If less 
			 try to find left
		If greater 
			 try to find right
		If equal
			 found
	Not found on NULL

	*/

	while(true)
	{
		if( cur == nullptr)
			return false; 

		if(v < cur->element)
		{
			cur = cur->left;
		}
		else if(v > cur->element )
		{
			cur = cur->right;
		}
		else if(v == cur->element)
		{
			return true;
		}
	}
}

/////////////////////////////////////////////////
// Function : clear
// Notes : clears the BST, cleaning up any dynamic
//         memory
/////////////////////////////////////////////////
template<typename Type>
void BST<Type>::clear()
{
	if(root != nullptr)
	{
		pDelete(root->left);
		pDelete(root->right);

		delete root;
		root = nullptr;
	}
}

/////////////////////////////////////////////////
// Function : printInOrder
// Notes : prints the contents of the BST to the screen,
//         in ascending order
/////////////////////////////////////////////////
template<typename Type>
void BST<Type>::printInOrder() const
{
	pPrint(root);
	cout << '\n';
}


#endif