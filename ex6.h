/***********
* Roei Cohen
* 325714152
* 01
* ex6
***********/

#ifndef _EX6_H_
#define _EX6_H_

//used in both main and ex6.c
#define FULL_MENU 1
#define SHORT_MENU 0

/*
* Defining the trenary tree structure, each tree has:
* -> An id
* -> A name
* -> Pointers to his parent, and his left, middle and right child
*/
struct Trin_Ari 
{
	int id;
	char* name;
	struct Trin_Ari* parent;
	struct Trin_Ari* left;
	struct Trin_Ari* middle;
	struct Trin_Ari* right;
};

typedef struct Trin_Ari Trin_Ari;
Trin_Ari* initFamily();
void menu(int type);
void choiceToAction(Trin_Ari* family);

#endif
