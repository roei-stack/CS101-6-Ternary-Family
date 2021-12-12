/***********
* Roei Cohen
* 325714152
* 01
* ex6
* queue.h is included because is contains "MEMORY_FAILURE" and "MEMORY_SECCUES" indicators
* utils.h will have all of the major printing operations
***********/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ex6.h"
#include "Utils.h"
#include "queue.h"

//FOR THE BUILT IN "print2Dutility" function
#define PRINT_SPACES_BETWEEN 3
#define NAME_SIZE 50
#define NEW_LINE 1

//ignoring scanf errors -> remove the following line when compiling outside of vs
#pragma warning(disable:4996)

/******************
* Function Name: initFamily
* Input: none
* Output: an allocated Trin_Ari* pointer root
* Function Operation: allocated memory for a new trin_ari structer and saves it by a pointer
* if the memory allocation fails -> print an error massage and exit with code 1
* set the roots values to null
******************/
Trin_Ari* initFamily()
{
	Trin_Ari* root = (Trin_Ari*)malloc(sizeof(Trin_Ari));
	if (root == NULL)
	{
		puts("Malloc Failed!");
		//since we are initilizing the family just now, there is no memory to free
		exit(1);
	}
	root->parent = NULL;
	root->name = NULL;
	root->left = NULL;
	root->middle = NULL;
	root->right = NULL;
	return root;
}

/******************
* Function Name: setFamilyRoot
* Input: a pointer to an initilized Trin_Ari root, an id (int) and a name (char[])
* Output: sets the roots values from the pointer to these values
* Function Operation: first -> try to allocate memory for the name (the exact amount of memory needed)
* then -> insert the id, and the name
******************/
void setFamilyRoot(Trin_Ari* r, int id, char name[])
{
	//pre-allocating memory for the name in the heap
	r->name = (char*)calloc(strlen(name) + NEW_LINE, sizeof(char));
	if (r->name == NULL)
	{
		//since we were just attempting to create the family, no freeing is needed besides the family root
		puts("Malloc Failed!");
		free(r);
		exit(1);
	}
	//inserting the id
	r->id = id;
	//copying the name
	strcpy(r->name, name);
	//the children were initilized to NULL already by the 'initFamily' function
}

/******************
* Function Name: freeTrinAri
* Input: a pointer to a Trin_Ari, and an indicator (int) on weather we are freeing due to memory fail or not
* Output: frees the whole subtree of the node
* Function Operation: if the Subtree is empty, return
* first delete all 3 subtrees
* then delete the node
* its also important to set the pointer to the parent to null and set the parent's pointer to that child to null
******************/
void freeTrinAri(Trin_Ari* t, int didMemoryFail)
{
	//if the child does not exist -> return
	if (t == NULL)
		return;
	//if the tree is empty(because then root->name is NULL) -> free the chain and return
	if (t->name == NULL)
	{
		free(t);
		return;
	}
	//deleting all 3 subtrees
	freeTrinAri(t->left, didMemoryFail);
	freeTrinAri(t->middle, didMemoryFail);
	freeTrinAri(t->right, didMemoryFail);

	/*
	* saving a pointer to the parent so we can disconnect both
	* the pointer from the child to the parent and the pointer from the parent to the child
	* i could have written this without nested if statements, but the code would have been worse
	* both in terms of complexity and harder to understand, so i prefer it that way
	*/
	Trin_Ari* parent = t->parent;
	
	if (parent != NULL)
	{
		//if he has a parent, the parent must have a left child
		if (parent->left != NULL && parent->left->id == t->id)
			parent->left = NULL;
		//if the left child's id does not match, the parent must have a middle child
		else if (parent->middle != NULL && parent->middle->id == t->id)
			parent->middle = NULL;
		else
			//in this case the child must be the right one, and we "disconnect it" from its parent
			parent->right = NULL;
	}
	if (didMemoryFail == MEMORY_SECCESS)
		//debug printing, before we free the chain: (in case we are not freeing due to memory failure)
		printf("%s ID: %d Survived!\n", t->name, t->id);
	//disconnecting the child's pointer to its parent (VERY SAD)
	t->parent = NULL;
	//since we are freeing from the buttom, its ok to set the children to NULL (not losing access to data)
	t->left = NULL;
	t->middle = NULL;
	t->right = NULL;
	//freeing the name inside the structure since its a pointer
	free(t->name);
	//freeing the whole structure block
	free(t);
}

/******************
* Function Name: searchById
* Input: an id (int) and a pointer to the tree's root (Trin_Ari*)
* Output: a pointer to a Trin_Ari with that specific id
* Function Operation: look for that node on the left subtree, then on the middle one, and on the right one
* if the node is not empty, compare the id's and check if they match
******************/
Trin_Ari* searchById(int id, Trin_Ari* root)
{
	//if the subtree is empty, return null -> not found
	if (root == NULL)
		return NULL;
	//if both ids match, return a pointer to that id
	if (root->id == id)
		return root;
	//look for the person in the left, middle and right subtrees
	Trin_Ari* t = searchById(id, root->left);
	//if you didnt find the person in the left subtree, look for him at the middle subtree
	if (t == NULL)
		t = searchById(id, root->middle);
	//searching the person in the right subtree
	if (t == NULL)
		t = searchById(id, root->right);
	//at this point we scanned the whole tree and we return either a pointer to the person or NULL
	return t;
}

/******************
* THIS IS THE MAIN FUNCTION FOR SUB-QUESTION 1
* Function Name: createFamily
* Input: THE trees root
* Output: non (void), but it sets the family head's values (name and id)
* Function Operation: 1. if the family was already created, return
* 2. get the name and id from the user
* 3. insert these into the family root, using the oddly named "setFamilyRoot" function
******************/
void createFamily(Trin_Ari* root)
{
	//if the root itself is not empty, then the family has been created
	if (root->name != NULL)
	{
		puts("The family has already been created");
		return;
	}
	int id;
	//MEMORY ALLOCATION WILL BE DONE LATER!
	char name[NAME_SIZE];
	//getting the name and id
	puts("enter name");

	scanf(" %[^\n]s", name);
	puts("enter ID");
	scanf("%d", &id);
	//inserting these values
	setFamilyRoot(root, id, name);
	//friendly output massage
	printf("Hello %s, ID: %d\n", root->name, root->id);
}

/******************
* Function Name: newTrinAri
* Input: an id (int) a name, and Trin_Ari pointers to the parent and to root
* Output:creates a new trin_ari with these id, name and parents and returns the pointer to it
* Function Operation: 1. Allocate memory for the child
* 2. Try to allocate memory for the name (saved by a pointer on the structure)
* 3. Insert the id, and copy the name
* 4. Set the pointer to the parent to the parent provided in the input
* 5. Set all of its children to NULL (because it doesnt have any)
* 6. Set a pointer from the parent to the children
******************/
Trin_Ari* newTrinAri(int id, char name[], Trin_Ari* parent, Trin_Ari* root)
{
	Trin_Ari* child = (Trin_Ari*)malloc(sizeof(Trin_Ari));
	if (child == NULL)
	{
		//destroy the tree and exit with code 1
		freeTrinAri(root, MEMORY_FAILURE);
		exit(1);
	}
	//ALLOCATING THE RIGHT AMOUNT OF MEMORY SO NO MEMORY IS WASTED!!
	child->name = (char*)calloc(strlen(name) + NEW_LINE, sizeof(char));
	if (child->name == NULL)
	{
		free(child);
		freeTrinAri(root, MEMORY_FAILURE);
		exit(1);
	}
	//setting the id
	child->id = id;
	//copying the name
	strcpy(child->name, name);
	//the new child is "a leaf", and he does not have any children currently
	child->left = NULL;
	child->middle = NULL;
	child->right = NULL;
	//setting up the pointer to it's parent
	child->parent = parent;

	/*
	* Connecting the created child to the parent:
	* first we try the left child spot -> if its empty:
	* we then try the middle child spot -> if its empty:
	* try the right child spot -> and if its also empty, return null
	* ***RETURN NULL == USER ATTEMPTED TO ADD A FOURTH CHILD -> ERROR***
	*/
	if (parent->left == NULL)
		parent->left = child;
	else if (parent->middle == NULL)
		parent->middle = child;
	else if (parent->right == NULL)
		parent->right = child;
	return child;
}

/******************
* THIS IS THE MAIN FUNCTION FOR SUB-QUESTION 2
* Function Name: addFamilyMeeting
* Input: a pointer to the trees root (Trin_Ari*)
* Output: tries to create an appointment, according to the user input
* Function Operation: if the family is not empty, get the id of the person who wants to make the meeting
* then, assuming that person has less then 3 children, ask for the name and id of the new person and connect 
* the parent to the child
******************/
void addFamilyMeeting(Trin_Ari* root)
{
	//checking if the family has not been created yet
	if (root->name == NULL)
	{
		puts("Please create the family first");
		return;
	}
	//this variable will hold the id of the person that makes the appointment
	int idParent;
	puts("Enter the ID of the person who wants to make an appointment?");
	scanf("%d", &idParent);
	//checking if the person that makes the appointment exists
	Trin_Ari* parent = searchById(idParent, root);
	if (parent == NULL)
	{
		printf("There is no ID %d\n", idParent);
		return;
	}
	//now we are making sure the user is being notified in case he tries adding a fourth child
	if (parent->left != NULL && parent->middle != NULL && parent->right != NULL)
	{
		printf("%s ID: %d can't meet more than 3 members!\n", parent->name, parent->id);
		return;
	}
	//idChild holds the id of the upcoming child
	int idChild;
	//MEMORY ALLOCATION WILL BE DONE LATER!
	char name[NAME_SIZE];
	Trin_Ari* child;
	do
	{
		puts("enter name");
		scanf(" %[^\n]s", name);
		puts("enter ID");
		scanf("%d", &idChild);
		//checking if the child's id already exists in the tree system
		child = searchById(idChild, root);
		if (child != NULL)
			printf("ID %d belongs to %s\n", child->id, child->name);
	} while (child != NULL);

	//after reciving the name and id, create the child and connect it to the tree
	child = newTrinAri(idChild, name, parent, root);
	printf("Hello %s, ID: %d\n", child->name, child->id);
}

/******************
* THIS IS THE MAIN FUNCTION FOR SUB-QUESTION 3
* Function Name: printFamilyTree
* Input: the trees root
* Output: prints the printing menu and the family, according to the user input
* Function Operation: 1.print the options menu 2.get the user's choice 3.call one of the 4 functions
* declared in "Utils.h" to take care of the printing
******************/
void printFamilyTree(Trin_Ari* root)
{
	int memoryFailureIndicator;
	char choice;
	//the printing menu contains 4 options
	puts("Please select an operation:");
	puts("\t0. Return to the main menu.");
	puts("\t1. Print Trin-Ari family.");
	puts("\t2. Print Pre-order.");
	puts("\t3. Print Left-order.");
	puts("\t4. Print BFS.");
	//getting the user choice ->and pointing it to a switch case
	scanf(" %c", &choice);

	switch (choice)
	{
	case '0':
	{
		//case 0 -> return the main menu
		return;
	}
	case '1':
	{
		//case 1 -> Print Trin-Ari family. (as a family tree)
		print2DUtil(root, PRINT_SPACES_BETWEEN);
		return;
	}
	case '2':
	{
		//case 2 ->pre-order printing
		printPreOrder(root);
		return;
	}
	case '3':
	{
		//case 3 -> left order
		printLeftOrder(root);
		return;
	}
	case '4':
	{
		//case 4 -> print BFS, we are also creating a variable that will indicate if there was a memory error
		int failSafe;
		//bfs will return MEMORY_FAILURE and stop its proccess in case there was an allocation problem
		failSafe = bfs(root, printNameAndId);
		//if we encountered a memory error, free the allocated tree and exit with code 1
		if (failSafe == MEMORY_FAILURE)
		{
			puts("Malloc Failed!");
			//free all allocated tree and exit with code 1
			freeTrinAri(root, MEMORY_FAILURE);
			exit(1);
		}
		return;
	}
	default:
	{
		//if we reached here it means the user has given an input different from 0-4 which is invalid
		puts("Error: unrecognized operation.");
		//invalid input -> go back to the PRINTING MENU
		printFamilyTree(root);
	}
	}
}

/******************
* Function Name: isolateSus
* Input: the tree's root
* Output: tells the suspected member, his parent and his children to stay at home
* Function Operation: assuming the family isnt empty, ask for the suspected members id, look for him
* using the "searchById" function, and assuming he exists, send all of his connections to home using the
* "isolationPrinting" function (see in utils.h)
******************/
void isolateSus(Trin_Ari* root)
{
	//if the tree is initilized but empty, return
	if (root->name == NULL)
	{
		puts("Please create the family first");
		return;
	}
	//this variable will store the id of the suspected family member
	int susId;
	puts("Enter the ID of the suspected member");
	scanf("%d", &susId);
	Trin_Ari* susMember = searchById(susId, root);
	//if the id inputted does not exist -> print an error massage
	if (susMember == NULL)
	{
		printf("ID %d does not exist\n", susId);
		return;
	}
	//send home every member that came in direct contact with him
	isolationPrinting(susMember);
}

/******************
* Function Name:superSpreader
* Input: the trees root
* Output: sends the superspreader, its parent and the whole subtree of it to home
* Function Operation: assuming the family isnt empty, get the id of the suspected member, search for him,
* tell his parent to stay at home, then tell him and his whole subtree to stay home, with bfs order printing
******************/
void superSpreader(Trin_Ari* root)
{
	//checking if the family is empty
	if (root->name == NULL)
	{
		puts("Please create the family first");
		return;
	}
	//we will store the super spreader's id here
	int id;
	puts("Enter the ID of the suspected Superspreader");
	scanf("%d", &id);
	Trin_Ari* spreader = searchById(id, root);
	if (spreader == NULL)
	{
		printf("ID %d does not exist\n", id);
		return;
	}
	//creating a variable that will indicate if there was a memory error
	int memoryFailSafe;
	//printing the "stay home" massage for the parent
	sendHome(spreader->parent);
	//bfs will return MEMORY_FAILURE and stop its proccess in case there was an allocation problem
	memoryFailSafe = bfs(spreader, sendHome);
	//if we encountered a memory error, free the allocated tree and exit with code 1
	if (memoryFailSafe == MEMORY_FAILURE)
	{
		puts("Malloc Failed!");
		//free all allocated tree and exit with code 1
		freeTrinAri(root, MEMORY_FAILURE);
		exit(1);
	}

}

/******************
* Function Name:vaccine
* Input: the trees root
* Output: the new trees root (after freeing all/some of the members)
* Function Operation: assuming the family isnt empty, get the id of the vaccined person, locate him, and 
* free him and his whole subtree
* if the user attemps to vaccine the root -> and by that freeing the whole tree, we will initilize a new Trin_Ari tree
* and return it
******************/
Trin_Ari* vaccine(Trin_Ari* root)
{
	//if the tree is empty -> print error massage
	if (root->name == NULL)
	{
		puts("Please create the family first");
		return root;
	}
	int id;
	//an indicator weather the root is being vaccined or not
	int isRoot = 0;
	puts("Who got vaccinated (ID)?");
	//getting the id of the vaccined family member
	scanf("%d", &id);
	//searching/locating the pointer to the vaccined person by its id
	Trin_Ari* vaccined = searchById(id, root);
	//if the person does not exist -> print error massage
	if (vaccined == NULL)
	{
		printf("There is no ID %d\n", id);
		return root;
	}
	//free the whole subtree below it with including printing
	if (vaccined->id == root->id)
		isRoot = 1;
	freeTrinAri(vaccined, MEMORY_SECCESS);
	if (isRoot == 1)
	{
		//if the root was vaccined, we released the whole family, so we initilize a new family
		Trin_Ari* newRoot = initFamily();
		//returning the new initilized family root
		return newRoot;
	}
	//returning the remaining family
	return root;
}

/******************
* Function Name: choiceToAction
* Input: a course list
* Output: gets us to the wanted operation (no return value)
* Function Operation: imagine this as the 'information' stand at the university:
* -	first, it understands what operation you want by the assist using the "scanf()" function
* -	then, using a switch case, it dirercts you to the operation you want to do
******************/
void choiceToAction(Trin_Ari* familyRoot)
{
	char choice;
	//the space here is to clean the buffer
	scanf(" %c", &choice);
	switch (choice)
	{
	case '0':
	{
		//free allocated tree and exit, freeing the root is the same as freeing the whole tree
		freeTrinAri(familyRoot, MEMORY_SECCESS);
		//exiting the program with code 0 whitch means the program ran seccesfully
		exit(0);
	}
	case '1':
	{
		//attempting to create the family
		createFamily(familyRoot);
		break;
	}
	case '2':
	{
		//Add family meeting/members
		addFamilyMeeting(familyRoot);
		break;
	}
	case '3':
	{
		//Printing options
		printFamilyTree(familyRoot);
		//after every printing operation we are required to print the full menu
		menu(FULL_MENU);
		choiceToAction(familyRoot);
	}
	case '4':
	{
		//case 4 ->isolate the suspected member, his parent and his children
		isolateSus(familyRoot);
		break;
	}
	case '5':
	{
		//Superspreader -> isolate the suspected member, his parent and his whole subtree
		superSpreader(familyRoot);
		break;
	}
	case '6':
	{
		//vaccine -> free an entire subtree
		Trin_Ari* changedRoot = vaccine(familyRoot);
		menu(SHORT_MENU);
		choiceToAction(changedRoot);
	}
	case '7':
	{
		//case 7-> print the full menu
		menu(FULL_MENU);
		choiceToAction(familyRoot);
	}
	default:
	{
		//if the choice didnt match to any of the options above, the input was invalid
		puts("Error: unrecognized operation.");
		break;
	}
	}
	menu(SHORT_MENU);
	//recalling the function
	choiceToAction(familyRoot);
}

/******************
* Function Name: menu
* Input: int type
* Output: prints a menu to the user (no return value)
* Function Operation:
* type == 1 -> print short menu
* type == 0 -> print full menu
******************/
void menu(int type)
{
	//type "FULL_MENU" print the entire menu
	if (type == FULL_MENU)
	{
		puts("Please select an operation:");
		puts("\t0. Exit.");
		puts("\t1. Create family.");
		puts("\t2. Add family member.");
		puts("\t3. Print Family-Tree.");
		puts("\t4. Bidud.");
		puts("\t5. Superspreader.");
		puts("\t6. Vaccine.");
		puts("\t7. Print the menu.");
		return;
	}
	//otherwize -> print short version of the menu
	puts("Select the next operation (insert 7 for the entire menu):");
}
