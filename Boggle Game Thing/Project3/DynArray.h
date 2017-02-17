#ifndef DYN_ARRAY_H
#define DYN_ARRAY_H

template<typename Type>
class DynArray 
{
public:
	//////////////////////////////////////////////////////////
	//Function: Constructor
	//Notes: Constructs an emtpy array ( Size 0 Capacity 0)
	//////////////////////////////////////////////////////////
	DynArray();


	//////////////////////////////////////////////////////////
	//Function: Destructor
	// Notes: cleans up any dynamic memory
	//////////////////////////////////////////////////////////
	~DynArray();

	//////////////////////////////////////////////////////////
	//Function: Copy Constructor
	//////////////////////////////////////////////////////////
	DynArray(const DynArray<Type>& copy);

	//////////////////////////////////////////////////////////
	//Function : Assignment Operator
	//////////////////////////////////////////////////////////
	DynArray<Type>& operator=(const DynArray<Type>& thing);

	//////////////////////////////////////////////////////////
	//Function: operator[]
	//Parameters: index - the index to access
	//Return: Type & - returns the array element at [index]
	//Notes: performs no error checking. user should ensure index
	//       is valid with size() method
	///////////////////////////////////////////////////////////
	Type& operator[](const unsigned int index);

	///////////////////////////////////////////////////////////
	//Function: operator[]
	//Parameters: index - the index to access
	//Return: const Type & - returns the array element at [index]
	//Notes : performs no error checking. user should ensure index
	//        is valid with size() method
	///////////////////////////////////////////////////////////
	const Type& operator[](const unsigned int index) const;

	///////////////////////////////////////////////////////////
	//Function: size
	//Returns: int - returns the number of times being stored
	//Notes : this function returns the number of items being stored.
	///////////////////////////////////////////////////////////
	unsigned int size() const;

	///////////////////////////////////////////////////////////
	//Function: capacity 
	//Returns: int- returns the number of times the array can store
	//         before the next resize
	//Notes : this function returns the number of items the array can
	//        store, not the number of bytes
	///////////////////////////////////////////////////////////
	unsigned int capacity() const;

	///////////////////////////////////////////////////////////
	//Function: clear
	//Notes: cleans up any dynamic memory and resets size and 
	//       capacity to 0
	///////////////////////////////////////////////////////////
	void clear();

	///////////////////////////////////////////////////////////
	//Function: append
	//Parameters: item - the item to appended to the next open
	//                   spot
	//Notes : this function will append the item to the next open
	//       spot. if no room exists, the array's capacity will be
	//       doubled and then the item will be added
	///////////////////////////////////////////////////////////
	void append(const Type& item);

	///////////////////////////////////////////////////////////
	//Function: reserve
	//Parameters: newCap - the new capacity
	// Notes: - default paramter - reserve more space in the array,
	//        based on the expansion rate (100%, 1 minimum).
	//        - non-default parameter, expand to the specified capacity
	//        - if newCap is LESS than the current capacity, do nothing.
	//        This function should NOT make the array smaller.
	///////////////////////////////////////////////////////////
	void reserve(const unsigned int & newCap = 0);


private:
	//All fields...
	unsigned int nSize;
	unsigned int cap;
	Type* arr;
};

//////////////////////////////////////////////////////////
//Function: Constructor
//Notes: Constructs an emtpy array ( Size 0 Capacity 0)
//////////////////////////////////////////////////////////
template<typename Type>
DynArray<Type>::DynArray()
{
	//Assign fields.
	nSize = 0;
	cap = 0;

	arr = nullptr;
}


//////////////////////////////////////////////////////////
//Function: Destructor
// Notes: cleans up any dynamic memory
//////////////////////////////////////////////////////////
template<typename Type>
DynArray<Type>::~DynArray()
{
    clear(); //Call the clear function.
}

//////////////////////////////////////////////////////////
//Function: Copy Constructor
//////////////////////////////////////////////////////////
template<typename Type>
DynArray<Type>::DynArray(const DynArray<Type>& copy)
{
	arr = nullptr; //Set array to nullptr.

	*this = copy; //Assign invoking object to parameter.
}

//////////////////////////////////////////////////////////
//Function : Assignment Operator
//////////////////////////////////////////////////////////
template<typename Type>
DynArray<Type>& DynArray<Type>::operator=(const DynArray<Type>& assign)
{
	//Paranoia check.
	if(this != &assign)
	{
		delete[] arr; //Delete the current array. 

		this->cap = assign.cap; //Assign this capacity to the assign.capacity

		if(cap == 0)
			return *this; //If capacity is 0, return.

		arr = new Type[cap]; //Assign arr to new type of capacities.

		for(unsigned int i = 0; i < assign.nSize; i++)
			arr[i] = assign.arr[i]; //Assign all indicies of arr to assign.arr indicies. 

		this->nSize = assign.nSize; //Assign this size to assign.size

	}

	return *this; //Finally, return this pointer.
}

//////////////////////////////////////////////////////////
//Function: operator[]
//Parameters: index - the index to access
//Return: Type & - returns the array element at [index]
//Notes: performs no error checking. user should ensure index
//       is valid with size() method
///////////////////////////////////////////////////////////
template<typename Type>
Type& DynArray<Type>::operator[](const unsigned int index)
{
	return arr[index]; // return the index being called. 
}

///////////////////////////////////////////////////////////
//Function: operator[]
//Parameters: index - the index to access
//Return: const Type & - returns the array element at [index]
//Notes : performs no error checking. user should ensure index
//        is valid with size() method
///////////////////////////////////////////////////////////
template<typename Type>
const Type& DynArray<Type>::operator[](const unsigned int index) const
{
	return arr[index]; //Return the index being called, but don't allow it to be changed.
}

///////////////////////////////////////////////////////////
//Function: size
//Returns: int - returns the number of times being stored
//Notes : this function returns the number of items being stored.
///////////////////////////////////////////////////////////
template<typename Type>
unsigned int DynArray<Type>::size() const
{
	return nSize; // Return size data member.
}

///////////////////////////////////////////////////////////
//Function: capacity 
//Returns: int- returns the number of times the array can store
//         before the next resize
//Notes : this function returns the number of items the array can
//        store, not the number of bytes
///////////////////////////////////////////////////////////
template<typename Type>
unsigned int DynArray<Type>::capacity() const
{
	return cap; //Return capacity data member.
}

///////////////////////////////////////////////////////////
//Function: clear
//Notes: cleans up any dynamic memory and resets size and 
//       capacity to 0
///////////////////////////////////////////////////////////
template<typename Type>
void DynArray<Type>::clear()
{
	//Delete dynamic memory.
	delete[] arr;
	arr = nullptr;

	//Reset fields.
	nSize = 0;
	cap = 0;
}

///////////////////////////////////////////////////////////
//Function: append
//Parameters: item - the item to appended to the next open
//                   spot
//Notes : this function will append the item to the next open
//       spot. if no room exists, the array's capacity will be
//       doubled and then the item will be added
///////////////////////////////////////////////////////////
template<typename Type>
void DynArray<Type>::append(const Type& item)
{

	if(cap == nSize) reserve(); //Call reserve if size and capacity are equal.

	arr[nSize++] = item; //Increase array size when new item is added.
}

///////////////////////////////////////////////////////////
//Function: reserve
//Parameters: newCap - the new capacity
// Notes: - default paramter - reserve more space in the array,
//        based on the expansion rate (100%, 1 minimum).
//        - non-default parameter, expand to the specified capacity
//        - if newCap is LESS than the current capacity, do nothing.
//        This function should NOT make the array smaller.
///////////////////////////////////////////////////////////
template<typename Type>
void DynArray<Type>::reserve(const unsigned int & newCap = 0)
{
	if(newCap != 0 && newCap < cap ) return;

	if(newCap == 0)
	{
		if(cap == 0)
			cap = 1;
		else
			cap *= 2;
	} else {
		cap = newCap;
	}


	Type* temp = new Type[cap];

	for( unsigned int i = 0; i < nSize; i++)
		temp[i] = arr[i];

	delete[] arr;

	arr = temp;
}



#endif