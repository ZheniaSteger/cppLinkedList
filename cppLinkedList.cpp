//============================================================================
// Author		: Zhenia Steger
// Purpose		: To demonstrate a linked list in C++
//					Creates a simple linked list with object data from file and
//					input into console.
// ============================================================================
#include <iostream>
#include <fstream>

using namespace std;

// PROTOTYPE CLASSES / FUNCTIONS
class Node;
class LL;

// TYPE DEFINITION FOR NODE POINTER
typedef Node* NodePtr;

// ============================================================================
// NODE CLASS
class Node
{
	friend class LL;
	private:
		int stId;
		string stName;
		string stEmail;
		int stAge;
		NodePtr nextStudent;
};

// ============================================================================
// LINKED LIST CLASS
class LL
{
	private:
		NodePtr top;
		int  numOfNodes;
		void destroy(NodePtr&);

	public:
		LL();
		LL(const LL& source);
		~LL();
		void insertDataFromFile();
		void print();
		bool search(int);
		void insertAfterFirst(int id, string name, string email, int age);
		void insertBeforeFirst(int id, string name, string email, int age);
		void insertAfterLast(int id, string name, string email, int age);
		void insertBeforeLast(int id, string name, string email, int age);
		void remove(int);
		void copy(NodePtr top1, NodePtr& top2);
};

// ============================================================================
// DEFAULT CONSTRUCTOR
LL::LL()
{
	top = NULL;
	numOfNodes = 0;
}

// ============================================================================
// DEFAULT COPY CONSTRUCTOR
LL::LL(const LL& source)
{
	NodePtr curr = source.top;
	while(curr != NULL)
	{
		insertAfterLast(curr->stId, curr->stName, curr->stEmail, curr->stAge);
		curr = curr->nextStudent;
	}
}

// ============================================================================
// DEFAULT DESTRUCTOR
LL::~LL()
{
	// cout << "calling the destructor..." << endl;
	NodePtr curr, temp;
	curr = top;
	while(curr != NULL)
	{
		temp = curr;
		curr = curr->nextStudent;
		delete temp;
		numOfNodes--;
	}
	top = NULL;
}

// ============================================================================
// PURPOSE: Inserts data from a file into the linked list
void LL::insertDataFromFile()
{
	cout << "opening 'transaction.txt'." << endl;
	ifstream fin;
	fin.open("transaction.txt");
	if(!fin) cout << "File Does not exist." << endl;

	while(!fin.eof())
	{
		int id;
		string name;
		string email;
		int age;
		NodePtr addedNode;
		addedNode = new Node;
		numOfNodes++;
		fin >> id >> name >> email >> age;

		insertAfterLast(id, name, email, age);
	}
}

// ============================================================================
// PURPOSE: Prints the contents of the linked list
void LL::print()
{
	NodePtr curr;
	curr = top;
	while(curr != NULL)
	{
		cout << "---------------------------------------" << endl;
		cout << "Students ID: " << curr->stId << endl;
		cout << "Students Name: " << curr->stName << endl;
		cout << "Students email: " << curr->stEmail << endl;
		cout << "Students Age: " << curr->stAge << endl;
		cout << "---------------------------------------" << endl;
		curr = curr->nextStudent;
	}
	cout << endl;
}

// ============================================================================
// Searches the linked list for the student id 'key'
bool LL::search(int key)
{
	NodePtr curr;
	bool found;
	curr = top;
	found = false;
	while((curr != NULL) && (!found))
	{
		if(curr->stId == key)
			found = true;
		else curr = curr->nextStudent;
	}
	return found;
}

// ============================================================================
// PURPOSE: Inserts an element into the list right after the first element
void LL::insertAfterFirst(int id, string name, string email, int age)
{
	NodePtr curr = top;
	NodePtr next;
	NodePtr newNode;
	newNode = new Node;
	numOfNodes++;
	newNode->stId = id;
	newNode->stName = name;
	newNode->stEmail = email;
	newNode->stAge = age;

	next = curr->nextStudent;
	curr->nextStudent = newNode;
	newNode->nextStudent = next;
}

// ============================================================================
// PURPOSE: Inserts an element into the list right before the first element
void LL::insertBeforeFirst(int id, string name, string email, int age)
{
	NodePtr curr = top;
	NodePtr newNode;
	newNode = new Node;
	numOfNodes++;
	newNode->stId = id;
	newNode->stName = name;
	newNode->stEmail = email;
	newNode->stAge = age;

	newNode->nextStudent = top;
	top = newNode;
}

// ============================================================================
// PURPOSE: Inserts an element into the list after the last element
void LL::insertAfterLast(int id, string name, string email, int age)
{
	NodePtr curr = top;
	NodePtr prev = NULL;
	NodePtr newNode;
	newNode = new Node;
	numOfNodes++;

	newNode->stId = id;
	newNode->stName = name;
	newNode->stEmail = email;
	newNode->stAge = age;

	while((curr != NULL))
	{
		prev = curr;
		curr = curr->nextStudent;
	}
	if(prev == NULL)
		top = newNode;
	else prev->nextStudent = newNode;
	newNode->nextStudent = NULL;
}

// ============================================================================
// PURPOSE: Inserts an element into the list right before the last element
void LL::insertBeforeLast(int id, string name, string email, int age)
{
	NodePtr curr = top;
	NodePtr prev2 = NULL;
	NodePtr prev = NULL;
	NodePtr newNode;
	newNode = new Node;
	numOfNodes++;
	newNode->stId = id;
	newNode->stName = name;
	newNode->stEmail = email;
	newNode->stAge = age;

	while((curr != NULL))
	{
		if(id == curr->stId)
			cout << "This record already exists.. Updating." << endl;
		else {
			prev2 = prev;
			prev = curr;
			curr = curr->nextStudent;
		}
	}
	prev2->nextStudent = newNode;
	newNode->nextStudent = prev;
}

// ============================================================================
// PURPOSE: Removes an element from the list matching the 'key' to stId
void LL::remove(int id)
{
	NodePtr curr, temp, prev;
	curr = top;
	if(curr->stId == id)
	{
		cout << "Deleting entry number " << id << endl;
		temp = top;
		top = top->nextStudent;
	}
	else
	{
		while(curr->nextStudent->stId != id)
		{
			prev = curr;
			curr = curr->nextStudent;
		}

		if(curr->nextStudent == NULL)
		{
			cout << "Deleting entry number " << id << endl;
			prev->nextStudent = NULL;
			temp = curr;

		}

		cout << "Deleting entry number " << id << endl;
		temp = curr->nextStudent;
		curr->nextStudent = curr->nextStudent->nextStudent;
	}
	delete temp;
	numOfNodes--;
}

// ============================================================================
// PURPOSE: Copies one list to another
void LL::copy(NodePtr top1, NodePtr &top2)
{
	destroy(top2);
	NodePtr curr = top1;
	while(curr != NULL)
	{
		top2->stId = curr->stId;
		top2->stName = curr->stName;
		top2->stEmail = curr->stEmail;
		top2->stAge = curr->stAge;

		curr = curr->nextStudent;
		top2 = top2->nextStudent;
	}
}
// ============================================================================
// PURPOSE: Destroys without destroying the list
void LL::destroy(NodePtr& top)
{
	NodePtr curr, temp;
	curr = top;
	while(curr != NULL)
	{
		temp = curr;
		curr = curr->nextStudent;
		delete temp;
		numOfNodes--;
	}
	top = NULL;
}

// ============================================================================
// PURPOSE: Main method runs the program
int main ()
{
	LL list1;
	cout << "inserting data..." << endl;
	list1.insertDataFromFile();
	cout << "printing list..." << endl;
	list1.print();
	cout << "inserting after 1st" << endl;
	list1.insertAfterFirst (54321, "Jim", "jim@csusm.edu", 25);
	cout << "insering before 1st" << endl;
	list1.insertBeforeFirst (54123, "Joe", "joe@csusm.edu", 35);
	cout << "inserting after last" << endl;
	list1.insertAfterLast (63421, "Adam", "adam@csusm.edu", 20);
	cout << "inserting before last" << endl;
	list1.insertBeforeLast (66641, "Nancy", "nancy@csusm.edu", 27);
	cout << "printing list..." << endl;
	list1.print();
	cout << "searching the list... 12321" << endl;
	bool  found = list1.search (12321);
	if (found)
	   cout << "the record was found" << endl;
	else
	   cout << "the record was not found" << endl;
	cout << "removing 54321" << endl;
	list1.remove(54321);
	cout << "printing list..." << endl;
	list1.print();
	cout << "copying list1 to list2" << endl;
	LL list2(list1);
	cout << "printing list2" << endl;
	list2.print();
	return 0;
}
// END OF PROGRAM