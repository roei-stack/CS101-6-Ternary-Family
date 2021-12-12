/***********
* Roei Cohen
* 325714152
* 01
* ex6
***********/

#include "ex6.h"

#ifndef _UTILS_H
#define _UTILS_H

//i added here all of the other printing operations
void printNameAndId(Trin_Ari* t);
void sendHome(Trin_Ari* t);
void isolationPrinting(Trin_Ari* susMember);
void print2DUtil(Trin_Ari *root, int space);
void printPreOrder(Trin_Ari* root);
void printLeftOrder(Trin_Ari* root);
typedef void(*printFunc)(Trin_Ari*);
int bfs(Trin_Ari* root, printFunc print);

#endif // !_UTILS_H
