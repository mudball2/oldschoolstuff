#pragma once

// OK, we've been using class templates for a while now: let's take control and create one ourselves. The following line designates the
//	code that follows to be a sort of blueprint which the compiler will follow when instructed to implicitly instantiate a DList object
//	of some particular Stuff data type. For giggles, a default argument is given to the template argument of type int so if the
//	instantiation is specified with empty angle brackets then an integer version will be made (the angle brackets, although empty, would
//	still be required as otherwise the compiler will look in vain for a nonexistent non-parameterized type named DList). Instead of
//	typename, the older keyword class can be substituted if desired (give it a shot).
// Another method of creating an abstract data type is to use typedef or even #define to declare the Stuff identifier. However, those
//	approaches are much less flexible as then the Stuff can be but a single data type for all DList's in the entire project instead
//	of whatever data type the programmer desires when they declare an instance of this templated DList.
// The compiler will always reuse implicit instantiations whenever possible - if, say, an int implicit instantiation has previously
//	been created and then another object (or even an array!) of int Stuff are declared, then the code will NOT be copied-and-pasted
//	again as the previous int methods are still available and will be called instead. If a long long implicit instantiation is the
//	desired type then the compiler will have to copy-and-paste versions for that data type of Stuff if they haven't been done yet. This
//	saves memory as even if there are a thousand separate DList objects that hold, for example, bool data they will all share the same
//	bool-using generated class methods, i.e., there will be just one bool push_back() class member function (and if the above versions
//	exist in the same program, just one int push_back() and one long long push_back() as well). There WOULD be one thousand unique
//	copies of all the data members like first, last and count though so each instance can hold different information.
// By the way, the template argument list can have more than one identifier in it, including non-data type parameters as the STL needs
//	that kind of power to fuel its more complex containers.
template <typename Stuff = int> // NB6 template, class template, parameterized type, generic paradigm, typename
class DList
{
public:
	// Mimic the vector's abstraction as much as possible so DList can be a direct substitute for it in our program.
	typedef unsigned int size_type;

private:
	// Declare a data type to hold the information required to properly store things in a linked list. Linked lists have one node per
	//	item of info, regardless of if they're singly, doubly, triply, etc. linked. This means that if one contains a half dozen things
	//	and it's a sextuply-linked list with first, last and middle pointers, it'd still have just six nodes.
	// The following declaration is an example of NB6 nesting
	// Nesting can also be done with loops, namespaces and try blocks (if the program is using exceptions).
	// The node class declaration is within the DList class declaration, so the containing class DList "owns" it and its scope is
	//	limited to within DList, i.e., if this were public and someone outside of DList wanted to make an integer-holding node, they
	//	would have to use the scope resolution operator, like "DList<int>::node". The angle brackets are also necessary thanks to
	//	DList being a template class but they could omit the int as we happen to have that as our default argument anyway. This is all
	//	moot as long as node is declared in the private section of DList, as even if they typed all the angle brackets and colon-colons
	//	properly they would still be denied access to the private node data type.
	class node
	{
		// Note although it's nested within DList, DList has no special privileges and can only directly access node's public
		//	areas. Interestingly, the reverse is not true - node is considered to be a friend class of DList and therefore, if
		//	given a DList object, could directly access ALL parts of that DList: public, protected AND private! This is more powerful
		//	than derived classes (children), as even they cannot directly access their base class' private sections although they can
		//	get at the protected members which the outside world cannot. Friends can always directly access everything in their buddy
		//	class so choose them wisely!
	public: // Grant DList direct access but note since the node itself is in DList's private section everyone outside DList is denied.
		// If Stuff is actually a class or struct data type, this models
		//	the NB6 has-a relationship, composition, containment, layering, subobject
		Stuff data; // What they want us to remember for them.
		// Each node knows about two other nodes, so it is a NB6 doubly-linked list
		node *prev, *next; // Who is before (0 [null] if we're the first) and after (0 if we're the last) us.

		// By explicitly writing a constructor, we can set data's value in the member initializer list, which is the perfect place in
		//	case it happens to be a subobject. This also makes any code that creates a node cleaner although always assuming the next
		//	pointer should be null is a JIT decision.
		// The parameter d is passed by constant reference just in case Stuff is a large data type, like maybe an MP3 or AVI. Passing
		//	it by value would always cause a copy to be sent which could be quite expensive in both memory and processor effort. The
		//	const guarantees we promise to only look at the data (like when it's duplicated) in the address sent and not alter it.
		node(Stuff const &d, node *p) : data(d), prev(p), next(0) { }
	}; // <=- Always remember to semicolon terminate your class and struct declarations!!

	// These two list pointers do NOT make us doubly-linked; it's the number of node pointers declared in the node above that
	//	determines that. These are simply convenient ways to teleport to known important locations in our collection.
	node *first, *last; // Where the beginning and ending of our list are (0 if we're empty and thus have no nodes to point at).

	size_type count; // How many items (nodes) we currently have.

	// Save some development time by disabling the copy constructor and assignment operator with "dummy" definitions. Now that we've
	//	written them the compiler won't bother plus by placing them in the private section if anyone actually tries to use them they'll
	//	get compiler errors saying they can't be accessed. This converts a subtle, difficult to find runtime bug (where the compiler
	//	provides shallow-copying versions in our public section implicitly) to a blatant build error which prevents an executable from
	//	even being created. If later it's decided we need to copy and/or assign DList's, we can always write thorough deep-copying
	//	methods and move them to our public section so everyone can use 'em. Any volunteers?
	DList(const DList &) { } // Don't bother doing ANYTHING as no one is ever supposed to call this NB6 copy constructor
	DList & operator =(DList const &) { return *this; } // We still have to satisfy the promised return type of an NB6 assignment operator

public:
	// Start empty so set everything to zero.
	DList(void) : first(0), last(0), count(0) { }

	virtual ~DList(void);

	void push_back(Stuff const & info);
	void push_front(Stuff const & info);

	size_type size() const { return count; } // A good NB6 inline
	void clear(void);
	bool erase(int index);

	// Anyone using this class would appreciate it if they could treat it like a typical array, i.e., ask for [0] for the first item,
	//	[1] for the second and so on. This will make it more intuitive and appealing, nice selling points if the code engine may
	//	eventually be offered for licensing or purchase.
	// To offer this functionality, we're going to overload the NB6 bracket operator, array subscript operator
	// The first version is a combination accessor and modifier/mutator - they can look and touch thanks to the non-constant
	//	reference that's returned. The second protects both the return value and the invoking object from alteration and will be used
	//	on read-only objects.
	// Always return a reference to whatever data type your collection is storing when defining your own array subscript operators, as
	//	it matches what the default versions do and avoids unnecessary copies that passing by value would cause.
	Stuff & operator [](int index); // Accept an int although it could take any data type other than void.
	Stuff const & operator [](int index) const;
};

// We are going to have to place all our code for this class template in the header file instead of splitting it between a .h and .cpp.
//	This is only because our compiler doesn't support NB6 export

// The following methods are too large to be NB6 inline
// Although it takes extra decoration to get them to compile properly outside the above class declaration, it's worth it to show the
//	interview examiner we know the right stuff for a non-inline class template function definition.

template <typename Stuff> // Use the same template heading the class has without any default arguments.
DList<Stuff>::~DList(void) // Add angle brackets after the class name containing just the template argument identifiers.
{
	node *temp; // Hire a temporary pointer but don't bother to initialize it as it will get assigned to soon.
	while (last) // As long as there's even one node to remove, keep looping. When this is null it'll evaluate to false and we'll quit.
	{
		temp = last; // Remember the current address of the final node.
		last = last->prev; // Move backwards towards the front - if we're already on the first node this makes last null.
		delete temp; // Annihilate the "old" last node.
	}

	// If this code was in a Clear() function, now would be a good time to set first and count to zero as well since we're empty.
	//	However, this is the destructor and the entire object is being obliterated anyway once we leave this method, so the extra
	//	assignments would consume processor time unnecessarily.
}

template <typename Stuff>
void DList<Stuff>::push_back(Stuff const & info)
{
	// To really visualize what's happening with each line of code, feel free to draw the action as you step statement-by-statement. This
	//	technique is awesome for getting the big picture of how each line depends on things being done before it and what it will then
	//	contribute to the creation of the linked list. It's also great for finding bad pointers that need to be updated as later items
	//	are added.

	// To get started, draw the node as a box with a number (1, 2, 3, etc.) inside for the data and two arrows going out of it
	//	representing the prev and next pointers. If they are null, have the arrows terminate pointing at a zero with a slash drawn
	//	through it or some other unique symbol signifying the null pointer. Otherwise, terminate them near the node box they are
	//	holding the address of.
	node *n = new node(info, last); // Initialize a fresh node with the passed data, the current last node and assume a next of null.
	// After adding this node box to your diagram, be sure to write an "n" and an arrow pointing from it to the new node to denote
	//	the pointer n holding its address (note n is the ONLY variable in the program that knows where this new node lives right now).

	if (!first) // first is null if we have no nodes yet (what the constructor initialized it to).
		// If we're currently empty, this is automatically going to be the first node. This will never happen again unless we
		//	implement methods to remove nodes at will from our list.
		first = n; // Make sure the illustration has a "first" arrow pointing to the same node n is pointing.
	else
		// We're the second, third, etc. node so fix the "broken arrow" (bad pointer) of the node just before us. It's still going
		//	to be pointing at null at the moment (the arrow in the picture should show this) but now we're after it so it needs to point
		//	to us.
		last->next = n; // Conveniently, last is still pointing at the old node whose next we need to change.
	// In the chart, update the old node's next arrow so that instead of pointing to null it now indicates n's node as the one after it.

	// Since we're appending to the end of the list, we're now the last node. By doing this assignment after taking care of the broken
	//	pointers above we were able to use last to refer to what is now officially the old last node.
	last = n; // Add a "last" arrow pointing to where n is pointing to in the diagram.
	++count; // Got another one!

	// n is a local (AUTOmatic) variable so it goes out of scope and is now lost. However, we haven't really forgotten where the new
	//	node is since last is pointing to it (as well as the next of the previous node if there is one). That's one major reason to
	//	have list pointers like first and last as they are data members and won't go out of scope until the whole object is destroyed,
	//	when we don't really need them anymore anyway. You might want to erase the "n" arrow since it's gone.

	// Check your chart to see if everything looks right, i.e., the arrows are all pointing at an appropriate node or null if there
	//	shouldn't be one (like the prev of the first node and the next of the last node). If something is amiss, it usually means some
	//	needed code is missing and/or out of the proper order. When you're creating your own singly, doubly, triply, etc. linked lists
	//	from scratch please use this drawing method to help ensure the code is doing the right things at the right time to
	//	correctly generate the list, adding/removing/shifting code as guided by the illustration to guarantee it's going smoothly. This
	//	is usually much easier than using the debugger to fix linked list code. Hint, start with a blank sheet of paper and draw the
	//	evolution of the linked list through at least three calls to this function to prove all's sweetness and light.
}

template <typename Stuff>
Stuff & DList<Stuff>::operator [](int index)
{
	// Do something the default array subscript operators don't: error-check the subscript to ensure it's within our container's
	//	bounds. Since this is a waste of time if the user's already ensured it's acceptable, it would be nice if we could somehow make
	//	this code only happen while we are developing and debugging our application and automatically remove it so the method can run
	//	faster when we go gold and ship. If we've got spare time in lecture, ask about NB6 #if defined(), _DEBUG, #endif
	if (index < 0 || index >= (int)count) // Note the greater-than or equal-to when checking the upper bound.
	{
		// cout is great for typical game messages but runtime errors can be sent somewhere else and written to a file if desired
		//	for our tech support team to analyze. To take advantage of this feature, use either cerr or clog (both ostream objects like
		//	cout and also nested in the std namespace) instead of cout, as they are attached to the standard error stream instead of the
		//	standard output stream like cout. cin is, as you may have already guessed, attached to the standard input stream. By default
		//	the standard error stream prints to the screen like cout but that can be remedied with NB6 I/O redirection
		cerr << "Bad index in the DList's array subscript operator!"; // NB6 cerr
		// There really isn't a good way to just sweep this problem under the rug and ignore it, unless we decide to use
		//	NB6 exception, try, throw, catch
		exit(1); // Leave the program immediately with a made-up error code of one using NB6 exit()
	}

	// Map the index they've indicated to the correct node in our linked list. Since our nodes aren't contiguous, we can't teleport
	//	instantly to the right one which would be true NB6 random access
	//
	// index	what they want
	// --------	-----------------------
	// 0		first->data
	// 1		first->NEXT->data
	// 2		first->NEXT->NEXT->data
	// ...and so on.
	node *temp = first; // We don't want to move first itself as that would mess-up future accesses. Use a temp instead.

	// Iterate through the collection until we've traversed the proper number of intermediate nodes to arrive at our final
	//	destination. Fortunately, the value of index happens to be exactly the number of times we need to follow a next pointer so we
	//	use the classic loop format: starting at zero, going less-than a number and incrementing by one each time. If that format is used
	//	you can guarantee the loop will execute exactly that number of times, i.e., whatever expression is to the right of the less-than.
	//	In our case, that means we iterate precisely index times which is what we want. As an added bonus, unlike the NB6 post-test loop
	//	do while, for's and while's can loop zero times which is perfect for when index is zero and thus temp is already pointing
	//	to the correct node since it was initialized to the first one.
	// For compactness, two things are being done in the loop update thanks to the comma operator. This means the loop didn't really
	//	need a body (an empty body like { } would have been fine) but instead of using the braces we have just put a semicolon after it
	//	instead, which emulates an empty body when tacked onto things like if's, for's and while's. Beware, though, that most peoples'
	//	eyes will skip right over the semicolon without really noticing it and therefore they'll think that we've forgotten to specify a
	//	body for the loop or worse, that the return statement will actually be used as the body! Therefore this shortcut may be
	//	frowned upon in certain quarters so you might want to ask if it's OK before using it. Watch carefully for these
	//	seemingly innocuous "extra" semicolons as they can drastically alter the expected behavior of affected code - the debugger is
	//	helpful in identifying what they'll do as you can see the impact step-by-step. You have been warned, grin!
	for (int i = 0; i < index; i++, temp = temp->next); // NB6 comma operator
	return temp->data; // They don't want the node (it's private anyway), just the info inside it.
}

template <typename Stuff>
Stuff const & DList<Stuff>::operator [](int index) const
{
	if (index < 0 || index >= int(count))
	{
		clog << "Bad index in the DList's constant array subscript operator!"; // NB6 clog
		exit(-1); // It's a different function, so for fun use a different arbitrary error code.
	}

	node *temp = first;
	for (int i = 0; i < index; i++, temp = temp->next);
	return temp->data;
}

//Here, I will add the methods that we were asked to add for the turn-in 
template <typename Stuff>
void DList<Stuff>::clear(void)
{
	//Remove all nodes and make the list empty. 

	this->first = nullptr;
	this->last = nullptr;

}

template <typename Stuff>
bool DList<Stuff>::erase(int index)
{
	if( index < 0 || index == NULL)
	{
		return false;
	} else {
		index = NULL;
		return true; 
	}
}


template <typename Stuff>
void DList<Stuff>::push_front(Stuff const & info)
{
	node *n = new node(info, 0);

	if (!last) 
		last = n; 
	else
		n->next = first; 
	++count; 

}