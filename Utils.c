/***********
* Roei Cohen
* 325714152
* 01
* ex6
***********/

#include <stdio.h>
#include "Utils.h"
#include "queue.h"

#define COUNT 8

/******************
* Function to print Trinary tree in 2D 
* It does reverse inorder traversal
******************/
void print2DUtil(Trin_Ari* root, int space)
{
	//I changed it because the root is never null FOR THE TREES HEAD, but the root->name is set to null if empty
	if (root == NULL || root->name == NULL)
		return;

	// Increase distance between levels 
	space += COUNT;

	// Process right child first 
	print2DUtil(root->right, space);
	for (int i = COUNT; i < space; i++)
		printf(" ");
	printf("%s %d\n", root->name, root->id);
	// Process middle child 
	print2DUtil(root->middle, space);
	printf("\n");
	// Process left child 
	print2DUtil(root->left, space);
}

/******************
* Function Name: printPreOrder
* Input: THE TREE'S ROOT
* Output: prints the tree by left order
* Function Operation: FIFO -> print the current item, then print the left, middle and right subtree
* HIRRACAL LIKE PRINTING
******************/
void printPreOrder(Trin_Ari* root)
{
	//I changed it because the root is never null FOR THE TREES HEAD, but the root->name is set to null if empty
	if (root == NULL || root->name == NULL)
		return;
	//first print the current subtree head
	printf("%s ID: %d\n", root->name, root->id);
	//then print its left subtree
	printPreOrder(root->left);
	//then print its middle subtree
	printPreOrder(root->middle);
	//then print its right subtree
	printPreOrder(root->right);
}

/******************
* Function Name:printLeftOrder
* Input: the tree's root
* Output: left order printing, using reccursion
* Function Operation: if the subtree is empty -> return (go back 1 level of reccursion)
* For each subtree ->
* Print the left subtree, then print the current root, then the right subtree
******************/
void printLeftOrder(Trin_Ari* root)
{
	//I changed it because the root is never null FOR THE TREES HEAD, but the root->name is set to null if empty
	if (root == NULL || root->name == NULL)
		return;
	//for each subtree -> print the left subtree, then print the current root, then the right subtree
	printLeftOrder(root->left);
	printf("%s ID: %d\n", root->name, root->id);
	printLeftOrder(root->middle);
	printLeftOrder(root->right);
}

/******************
* Function Name:addChildredToQueue
* Input: a Trin_Ari pointer and the queue list (*)
* Output: adds the root's children to the queue
* Function Operation: for each child, from LEFT-MIDDLE-RIGHT, do:
* if it exists, enter it to the queue (pointer)
* the enQueue function will return "MEMORY_FAILED" in case something went wrong
* in that case -> return MEMORY_FAILED
* OTHERWIZE -> MEMORY_SECCESS
******************/
int addChildredToQueue(Trin_Ari* root, QList* q)
{
	//initilizing the indicators to MEMORY_SECCESS
	int failSafe1 = MEMORY_SECCESS, failSafe2 = MEMORY_SECCESS, failSafe3 = MEMORY_SECCESS;
	//If we got a left child, enter it to the queue
	if (root->left != NULL)
		//saving the return value of it
		failSafe1 = enQueue(q, &(root->left->id));
	if (root->middle != NULL)
		failSafe2 = enQueue(q, &(root->middle->id));
	if (root->right != NULL)
		failSafe3 = enQueue(q, &(root->right->id));
	//if any of the queue allocations failed, return MEMORY_FAILURE
	if (failSafe1 == MEMORY_FAILURE || failSafe2 == MEMORY_FAILURE ||
		failSafe3 == MEMORY_FAILURE)
		return MEMORY_FAILURE;
	//if everything went ok, return MEMORY_SECCESS
	return MEMORY_SECCESS;
}

/******************
* Function Name:sendHome
* Input: A pointer to a Trin_Ari node
* Output: prints him to stay home
* Function Operation: if the node/member exist -> print "#StayHome! (name) (id)"
******************/
void sendHome(Trin_Ari* t)
{
	if (t != NULL)
		printf("#StayHome! %s %d\n", t->name, t->id);
}

/******************
* Function Name:isolationPrinting
* Input: a pointer to the suspected member
* Output: sends everyone whose came in direct contact with him to home
* Function Operation: using the "sendHome" function, we tell his
* ->parent
* ->himself
* ->children
* To stay at home
******************/
void isolationPrinting(Trin_Ari* susMember)
{
	sendHome(susMember->parent);
	sendHome(susMember);
	sendHome(susMember->left);
	sendHome(susMember->middle);
	sendHome(susMember->right);
}

/******************
* Function Name: printNameAndId
* Input: A pointer to a Trin_Ari node
* Output:prints his name and id
* Function Operation: if the node/member exist -> print "(name) (id)"
******************/
void printNameAndId(Trin_Ari* t)
{
	if (t != NULL || t->name != NULL)
		printf("%s %d\n", t->name, t->id);
}

/******************
* Function Name: bfs
* Input:a pointer to the root and a pointer to a printing function
* Output: prints the tree by depth using a BFS Algorithm
* Function Operation:1.if we have an empty tree, we return that there was no memory problem and we print nothing
* 2.creating a queue
* 3.setting the current to the root
* 4.adding the roots children to the queue
* 5.as long as the queue is not empty, do:
*	5.1.print the current node
* 	5.2.set the current as the first node of the queue (using casting from void* to trin_ari*)
* 	5.3.dequeue the queue
* 6.print the current item (it was dequeued before it could be printed)
* 7.free the whole queue
******************/
int bfs(Trin_Ari* root, printFunc print)
{
	//if we have an empty tree, we return that there was no memory problem and we print nothing
	if (root == NULL || root->name == NULL)
		return MEMORY_SECCESS;
	//failSafe is an indicator that checks if we encountered a memory allocation problem
	int failSafe;
	Trin_Ari* current = root;
	//creating a queue
	QList* q = createQueueList();
	if (q == NULL)
		//returning "MEMORY_FAIL" to ex6.c to indicate a memory error
		return MEMORY_SECCESS;
	failSafe = addChildredToQueue(root, q);
	//'addChildredToQueue' should return "MEMORY_FAILURE" in case of an allocation problem
	if (failSafe == MEMORY_FAILURE)
	{
		destroyQueue(q);
		return MEMORY_FAILURE;
	}

	/*
	* As long as the queue is not empty, do:
	* -> print the current item
	* -> set the current Trin_Ari to the first chain in the queue
	* -> remove the first item from the queue
	* -> add the first item's children to the end of the queue
	*/
	while (isEmpty(q) == 0)
	{
		//either prints the name and the id, or prints the #STAY HOME! massage
		print(current);
		//go to the adress of the first item in the queue and convert it from void* to Trin_Ari*
		current = (Trin_Ari*)(q->first->data);
		//remove the first item from the queue
		deQueue(q);
		//add current's children to the queue
		failSafe = addChildredToQueue(current, q);
		if (failSafe == MEMORY_FAILURE)
		{
			destroyQueue(q);
			return MEMORY_FAILURE;
		}
	}
	//the queue has emptied but we still need to print the current last item
	print(current);
	//freeing the queue
	destroyQueue(q);
	//in case we didnt encounter any allocation errors, we tell the program the allocation went good
	return MEMORY_SECCESS;
}
