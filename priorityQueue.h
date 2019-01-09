// Chaitanya Ingle
// Sec. 1002
// Ast. 08

// FILE: priorityQueue.h
// DESCRIPTION: Header file for priorityQueue template class with implementations.


// ---------------------------------- CLASS OVERVIEW ----------------------------------
//
// -------------- PRIVATE DATA MEMBERS --------------
//
//
// 	struct heapNode         
//	{
//		int priority;
//		myType item;
//	};
//		- Node for minHeap. Item contains data member and priority contains priority value in heap.
//
//	int count;
//		- Count of current size of minHeap.
//
//	int heapSize;
//		- Total size (memory allocated) currently for minHeap.
//
//	heapNode* myHeap;
//		- Pointer to minHeap.
//
//
// -------------- PUBLIC FUNCTIONS --------------
//
//
// 	priorityQueue(int defSize = 100);
//		- Initializes minHeap, count, and sets to initial heapSize, which has to be a minimum of defSize = 100.
//
// 	~priorityQueue();
//		- Deallocates minHeap.
//
// 	int entries() const;
//		- returns current count of minHeap.
//
//	void insert(const myType nEntry, const int prior);
//		- Inserts nEntry item of myType with priority prior into minHeap. Maintains order and structure 
//		  property using the reheapUp() function.
//
//	bool deleteMin(myType& , int& );
//		- Returns node at top and priority. Then, maintains order and structure property by using the 
//		  reheapDown() function.
//
//	bool isEmpty() const;
//		- If the minHeap is empty (count = 0), returns true. Else, returns false.
//
//	void printHeap() const;
//		- Prints heap by priority, with a linefeed in between each level.
//
//	bool readData(const string fName);
//		- Reads data from file fName. First, just inserts all data into heap. Then calls buildHeap() 
//		  function to reorganize heap to fit minHeap requirements.
//
//
// -------------- PRIVATE FUNCTIONS --------------
//
//
//	void reheapUp(int pos);
//		- [Recursive] For heapNode at pos in array, checks if priorty value is lower than that of parent. 
//		  If so, swap and reheapUp from parent.
//
//	void reheapDown(int pos);
//		- [Recursive] For heapNode at pos in array, checks if priority value is greater than that of both
//		  children. If so, swap with child with lower priority and reheapDown from that child position.
//
//	void buildHeap();
//		- Starting from the parent node of the last child node, calls reheapDown for all nodes in array
//		  until root node (nodes from count/2 to 1). 
//
//	void resize();
//		- Creates larger heap array of double the current heap. Copies all elements ove rand deletes old,
//		  smaller array.
//


#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H


#include <iostream>
#include <string>
#include <fstream>
#include <utility>

using namespace std;


template <class myType>
class priorityQueue
{
	public:

	// CONSTRUCTOR AND DESTRUCTOR

	priorityQueue(int defSize = 100);
	~priorityQueue();

	// PUBLIC FUNCTIONS
	
	int entries() const;
	void insert(const myType nEntry, const int prior);
	bool deleteMin(myType& min, int& prior);
	bool isEmpty() const;
	void printHeap() const;
	bool readData(const string fName);

	private:

	// PRIVATE DATA MEMBERS

	struct heapNode
	{
		int priority;
		myType item;
	};

	int count;
	int heapSize;
	heapNode* myHeap;

	// PRIVATE FUNCTIONS
	
	void reheapUp(int pos);
	void reheapDown(int pos);
	void buildHeap();
	void resize();

};

template <class myType>
priorityQueue<myType>::priorityQueue(int defSize)
{

	if (defSize < 100)
		heapSize = 100;
	else
		heapSize = defSize;
	myHeap = new heapNode[heapSize];
	count = 0;

}



template <class myType>
priorityQueue<myType>::~priorityQueue()
{

	delete [] myHeap;
	myHeap = NULL;

}



template <class myType>
int priorityQueue<myType>::entries() const
{

	return count;

}



template <class myType>
void priorityQueue<myType>::insert(const myType nEntry, const int prior)
{

	if (count >= heapSize)     // increase heap size if needed
		resize();

	count++;
	myHeap[count].item = nEntry;
	myHeap[count].priority = prior;
	reheapUp(count); 


}



template <class myType>
bool priorityQueue<myType>::isEmpty() const
{

	if (count == 0)
		return true;
	else
		return false;

}



template <class myType>
bool priorityQueue<myType>::deleteMin(myType& min, int& prior)
{
	if (isEmpty())                 // return if heap is empty
		return false;

	min = myHeap[1].item;          // return min by reference
	prior = myHeap[1].priority;

	myHeap[1] = myHeap[count];     // reorganize heap
	count--;
	reheapDown(1);
	return true;
}


template <class myType>
void priorityQueue<myType>::printHeap() const
{

	if (count == 0)      // don't print anything if heap is empty
		return;
		
	int level = 1;
	int position = 1;	
	
	while (position <= count) {
		for (int i = 0; i < level; i++) {
			cout<< myHeap[position].item<< "  "<< myHeap[position].priority<< endl;
			position++;
			if (position > count)
				break;
		}

		cout<< endl;
		level *= 2;
	}
}



template <class myType>
bool priorityQueue<myType>::readData(const string fName)
{

	ifstream infile;
	infile.open(fName.c_str());
	if (!infile) {
		cout<< "File not found."<< endl;
		return false;
	}

	myType tempItem;
	int tempPrior;

	while (infile>> tempItem) {
		infile>> tempPrior;
		if (count+2 > heapSize)
			resize();
		count++;
		myHeap[count].item = tempItem;
		myHeap[count].priority = tempPrior;
	}

	buildHeap();
	return true;

}



template <class myType>
void priorityQueue<myType>::reheapUp(int pos)
{

	if (pos > 1)
		if (myHeap[pos/2].priority > myHeap[pos].priority) {
			swap(myHeap[pos], myHeap[pos/2]);
			reheapUp(pos/2);
		}

}



template <class myType>
void priorityQueue<myType>::reheapDown(int pos)
{
	if (pos * 2 <= count) {

		if (pos * 2 + 1 > count)  { // Special case where last node only has one child
			if (myHeap[pos].priority >= myHeap[pos*2].priority) 
				swap(myHeap[pos], myHeap[pos*2]);	
				
		}
	
		else {
			if (myHeap[pos*2].priority <= myHeap[pos*2 + 1].priority) {
				if (myHeap[pos].priority >= myHeap[pos*2].priority) {
					swap(myHeap[pos], myHeap[pos*2]);
					reheapDown(pos*2);
				}
			}

			else {
				if (myHeap[pos].priority >= myHeap[pos*2 + 1].priority) {
					swap(myHeap[pos], myHeap[pos*2 + 1]);
					reheapDown(pos*2 + 1);
				}
			}
		}
	}

}



template <class myType>
void priorityQueue<myType>::buildHeap()
{

	for (int i = count/2; i > 0; i--) 
		reheapDown(i);

}



template <class myType>
void priorityQueue<myType>::resize()
{

	heapNode* temp;
	heapSize *= 2;
	
	temp = new heapNode[heapSize];
	
	for (int i = 0; i < count; i++)
		temp[i+1] = myHeap[i+1];

	delete [] myHeap;
	myHeap = temp;
	
}


#endif



