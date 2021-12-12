/***********
* Roei Cohen
* 325714152
* 01
* ex6
***********/

#include "ex6.h"

/******************
* Function Name: main
* Input: none
* Output: void type -> none
* Function Operation: first -> allocate the root in the heap
* secondly -> print the full menu
* then -> call the "choiceToAction" function that will take care of the rest
******************/
int main()
{
	//initilizing the family for the first time
	Trin_Ari* familyRoot = initFamily();
	//print the full menu for the first time
	menu(FULL_MENU);
	//calling the "choice to action" function that will take care of the rest
	choiceToAction(familyRoot);
	//we will never reach here...
	return 0;
}
