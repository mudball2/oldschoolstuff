#ifndef SLL_LIST_H
#define SLL_LIST_H

//Forward declaration
template<typename Type> class SLLIter;

template<typename Type>
class SLList
{
	struct Node
	{
		Type element;
		Node *next;
	};

	Node *mHead;
	Node *mList;

	unsigned int nNodeCount;
	// the iterator is the list's friend
	friend class SLLIter<Type>;

public:
	//////////////////////////////////////////////
	// Function : Constructor
	// Notes : constructs an empty list
	//////////////////////////////////////////////
	SLList();

	//////////////////////////////////////////////
	// Function : Destructor
	// Notes : Destroys the list
	//////////////////////////////////////////////
	~SLList();

	//////////////////////////////////////////////
	// Function : Assignment Operator
	//////////////////////////////////////////////
	SLList<Type>& operator=(const SLList<Type>& assign);

	//////////////////////////////////////////////
	// Function : Copy Constructor
	//////////////////////////////////////////////
	SLList(const SLList<Type>& copy);

	//////////////////////////////////////////////
	// Function : addHead
	// Parameters : v - the item to add to the list
	//////////////////////////////////////////////
	void addHead(const Type& v);

	//////////////////////////////////////////////
	// Function : clear
	// Notes : clears the list, freeing any dynamic
	//         memory
	//////////////////////////////////////////////
	void clear();

	//////////////////////////////////////////////
	// Function : insert
	// Parameters : index - an iterator to the location
	//                      to insert at 
	//              v - the item to insert
	// Notes : do nothing on a bad iterator
	//////////////////////////////////////////////
	void insert(SLLIter<Type>& index, const Type& v);

	//////////////////////////////////////////////
	// Function : remove
	// Parameters : index - an iterator to the location
	//                      to remove from
	// Notes : do nothing on a bad iterator
	//////////////////////////////////////////////
	void remove(SLLIter<Type>& index);

	//////////////////////////////////////////////
	// Function : size
	// Return : the number of items in the linked list
	//////////////////////////////////////////////
	inline unsigned int size() const;

};

//////////////////////////////////////////////
// Function : Constructor
// Notes : constructs an empty list
//////////////////////////////////////////////
template<typename Type>
SLList<Type>::SLList()
{
	nNodeCount = 0;

	mHead = nullptr;
	mList = nullptr;
}

//////////////////////////////////////////////
// Function : Destructor
// Notes : Destroys the list
//////////////////////////////////////////////
template<typename Type>
SLList<Type>::~SLList()
{
	clear();
}

//////////////////////////////////////////////
// Function : Assignment Operator
//////////////////////////////////////////////
template<typename Type>
SLList<Type>& SLList<Type>::operator=(const SLList<Type>& assign)
{
	if( this != &assign)
	{
		Node *tmp = nullptr; 

		this->clear();

		if(assign.mHead == nullptr)
			return *this;

		Node *temp2;
		Node *temp3 = assign.mHead;

		for(unsigned int i= 0; i < assign.size(); i++)
		{
			mList = new Node;
			mList->element = temp3->element;

			temp3 = temp3->next;

			if( i == 0)
			{
				temp2 = mList;
				mList->next = nullptr;

				tmp = mList;

			} else {
				temp2->next = mList;
				temp2 = mList;

				mList->next = nullptr;
			}
		}
		this->nNodeCount = assign.nNodeCount;
		this->mHead = tmp;
	}

	return *this;
}

//////////////////////////////////////////////
// Function : Copy Constructor
//////////////////////////////////////////////
template<typename Type>
SLList<Type>::SLList(const SLList<Type>& copy)
{
	this->mHead = nullptr;
	*this = copy;
}

//////////////////////////////////////////////
// Function : addHead
// Parameters : v - the item to add to the list
//////////////////////////////////////////////
template<typename Type>
void SLList<Type>::addHead(const Type& v)
{
	Node *tmp = new Node;

	tmp->next = mHead;

	tmp->element = v;

	mHead = tmp;

	nNodeCount++;
}

//////////////////////////////////////////////
// Function : clear
// Notes : clears the list, freeing any dynamic
//         memory
//////////////////////////////////////////////
template<typename Type>
void SLList<Type>::clear()
{
	Node *tmp;

	while(mHead != nullptr)
	{
		tmp = mHead;
		mHead = mHead->next;

		delete tmp;
		nNodeCount--;
	}
}

//////////////////////////////////////////////
// Function : insert
// Parameters : index - an iterator to the location
//                      to insert at 
//              v - the item to insert
// Notes : do nothing on a bad iterator
//////////////////////////////////////////////
template<typename Type>
void SLList<Type>::insert(SLLIter<Type>& index, const Type& v)
{
	Node *temp = mHead;
	Node *temp2 = nullptr;

	if(index.cur != nullptr)
	{
		while(temp != index.cur)
		{
			temp2 = temp;
			temp = temp->next;
		}
		Node *node = new Node;
		node->element = v;
		if(temp2 == nullptr)
		{
			node->next = temp;
			mHead = node;

		} else {
			node->next = temp;
			temp2->next = node;
		}

		nNodeCount++;
		index.cur = node;
	}
}

//////////////////////////////////////////////
// Function : remove
// Parameters : index - an iterator to the location
//                      to remove from
// Notes : do nothing on a bad iterator
//////////////////////////////////////////////
template<typename Type>
void SLList<Type>::remove(SLLIter<Type>& index)
{
	Node *cur = mHead;
	Node *temp;
	Node *previous = nullptr;

	if(nNodeCount != 0)
	{
		while(cur != index.cur)
		{
			previous = cur;
			cur = cur->next;
		}

		//Final steps here...
		temp = cur;
		cur = cur->next;

		if(previous != nullptr)
			previous->next = cur;
		else
			mHead = cur;

		delete temp;

		nNodeCount--;
		index.cur = cur;
		index.previous = previous;
	}

}

//////////////////////////////////////////////
// Function : size
// Return : the number of items in the linked list
//////////////////////////////////////////////
template<typename Type>
inline unsigned int SLList<Type>::size() const
{
	return nNodeCount;
}


template<typename Type> 
class SLLIter
{

	typename SLList<Type>::Node *cur;
	typename SLList<Type>::Node *previous;

	SLList<Type> *list;
	// the list is the iterator's friend
	friend class SLList<Type>;

public:
	//////////////////////////////////////////////
	// Function : Constructor
	// Parameters : listToIterate - the list to interate
	//////////////////////////////////////////////
	SLLIter(SLList<Type>& listToIterate);

	//////////////////////////////////////////////
	// Function : begin
	// Notes : moves the iterator to the head of 
	//         the list
	//////////////////////////////////////////////
	void begin();

	//////////////////////////////////////////////
	// Function : end
	// Notes : returns true if we are at the end of
	//         the list, false otherwise
	//////////////////////////////////////////////
	bool end() const;

	//////////////////////////////////////////////
	// Function : operator++
	// Notes : move the iterator forward one node
	//////////////////////////////////////////////
	SLLIter<Type>& operator++();

	//////////////////////////////////////////////
	// Function : current
	// Notes : returns the item at the current 
	//         iterator location
	//////////////////////////////////////////////
	Type& current() const;
};

//////////////////////////////////////////////
// Function : Constructor
// Parameters : listToIterate - the list to interate
//////////////////////////////////////////////
template<typename Type>
SLLIter<Type>::SLLIter(SLList<Type>& listToIterate)
{
	list = &listToIterate;
	previous = nullptr;
	cur = list->mHead;
}

//////////////////////////////////////////////
// Function : begin
// Notes : moves the iterator to the head of 
//         the list
//////////////////////////////////////////////
template<typename Type>
void SLLIter<Type>::begin()
{
	cur = list->mHead;
	previous = nullptr;
}

//////////////////////////////////////////////
// Function : end
// Notes : returns true if we are at the end of
//         the list, false otherwise
//////////////////////////////////////////////
template<typename Type>
bool SLLIter<Type>::end() const
{
	if(cur == nullptr)
		return true;
	else
		return false;
}

//////////////////////////////////////////////
// Function : operator++
// Notes : move the iterator forward one node
//////////////////////////////////////////////
template<typename Type>
SLLIter<Type>& SLLIter<Type>::operator++()
{
	if(cur != nullptr)
	{
		
		this->previous = this->cur;
		this->cur = this->cur->next;
	}

	return *this;
}

//////////////////////////////////////////////
// Function : current
// Notes : returns the item at the current 
//         iterator location
//////////////////////////////////////////////
template<typename Type>
Type& SLLIter<Type>::current() const
{
	return cur->element;
}

#endif