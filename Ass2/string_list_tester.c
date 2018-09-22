/* string_list_tester.c
  
   SENG 265 - Summer 2016
   Assignment 2
   
   Template for a tester for the StringList datatype.
   
   Do not change any of the function signatures or the contents
   of main() or your submission may be invalid.
  
   B. Bird - 05/26/2016
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_list.h"

#define TEST_FAILED 0
#define TEST_PASSED 1

/* Each of the test functions below should return TEST_FAILED if the test fails
   and TEST_PASSED if the test is passed.
*/

int test1(){

	StringList tester;
	StringList_Init(&tester);
	printf("After initialize tester has %d item(s)\n",StringList_Size(&tester));
	if(StringList_Size(&tester)!=0)
	return TEST_FAILED;
	
	char* str="hahaha";
	StringList_AddFront(&tester,str);
	printf("After adding tester has %d item(s)\n",StringList_Size(&tester));
	if(StringList_Size(&tester)!=1)
	return TEST_FAILED;
	
	StringList_Init(&tester);
	printf("After initialize tester again it has %d item(s)\n",StringList_Size(&tester));
	if(StringList_Size(&tester)!=0)
	
	return TEST_FAILED;
	return TEST_PASSED;
}

int test2(){

	StringList tester;
	StringList_Init(&tester);
	printf("After initialize tester has %d item(s)\n",StringList_Size(&tester));
	if(StringList_Size(&tester)!=0)
	return TEST_FAILED;
	
	char* str="hahaha";
	StringList_AddFront(&tester,str);
	printf("After adding front tester has %d item(s)\n",StringList_Size(&tester));
	if(StringList_Size(&tester)!=1)
	return TEST_FAILED;
	
	StringList_AddBack(&tester,str);
	printf("After adding back tester has %d item(s)\n",StringList_Size(&tester));
	if(StringList_Size(&tester)!=2)
	return TEST_FAILED;

	StringList_Init(&tester);
	printf("After initialize tester again it has %d item(s)\n",StringList_Size(&tester));
	if(StringList_Size(&tester)!=0)
	return TEST_FAILED;
		
	return TEST_PASSED;
}

int test3(){

	StringList tester;
	StringList_Init(&tester);
	printf("After initialize tester testing the head...\n");
	if(tester.head != NULL){
		printf("failed to intialize head to NULL.\n");
		return TEST_FAILED;
	}
	printf("succeed\n");
	
	printf("testing size\n");
	int size = StringList_Size(&tester);
	if(size != 0){
		printf("Doesn't return the right size: \n%d\n", size);
		return TEST_FAILED;	
	}
	printf("Returns the correct size of %d item(s)\n",StringList_Size(&tester));
	
	printf("testing addfront\n");
	char *str = "aaa";
	StringList_AddFront(&tester,str);
	
	if(tester.head == NULL){
		printf("head = NULL\n");
		return TEST_FAILED;
	}
	printf("succeed\n");
	StringList_Init(&tester);

	printf("testing addBack\n");
	StringList_AddBack(&tester,str);
	if(tester.head == NULL){
		printf("head = NULL\n");
		return TEST_FAILED;
	}
	printf("succeed\n");

	printf("testing size again\n");
	
	size = StringList_Size(&tester);
	if(size != 1){
		printf("Doesn't return the right size: \n%d\n", size);
		return TEST_FAILED;	
	}
	printf("Returns the correct size of %d item(s)\n",StringList_Size(&tester));
	
	return TEST_PASSED;
}

int test4(){
	printf("Creating nodes and linking them together\n");
	char* a="aaa";
	char* b="bbb";
	char* c="ccc";
	char* d="ddd";
	StringList tester;
	StringList_Init(&tester);
	StringList_AddFront(&tester,b);
	StringList_AddFront(&tester,a);
	StringList_AddBack(&tester,c);
	StringList_AddBack(&tester,d);
	
	printf("Trying to find node c at index 2\n");
	StringList_GetIndex(&tester, 2);
	printf("should print 'ccc'\n");
	printf("%s\n",StringList_GetIndex(&tester, 2)->element);
	if(!strstr(StringList_GetIndex(&tester, 2)->element,"ccc"))
	return TEST_FAILED;
	
	return TEST_PASSED;
}

int test5(){
	printf("Creating nodes and linking them together\n");
	char* a="aaa";
	char* b="bbb";
	char* c="ccc";
	char* d="ddd";
	StringList tester;
	StringList_Init(&tester);
	StringList_AddFront(&tester,b);
	StringList_AddFront(&tester,a);
	StringList_AddBack(&tester,c);
	StringList_AddBack(&tester,d);
	
	printf("Trying to find the node contains 'ccc'\n");
	StringList_InList(&tester, c);
	printf("The address of str 'ccc' is %p\n",StringList_GetIndex(&tester, 2));
	printf("The address that the function returns is %p\n",StringList_InList(&tester, c));
	if(StringList_GetIndex(&tester, 2)!=StringList_InList(&tester, c))
	return TEST_FAILED;

	printf("Trying to find a string that doesn't exist\n");
	printf("%p\n",StringList_InList(&tester, "f"));
	
	return TEST_PASSED;
}

int test6(){
	printf("Creating nodes and linking them together\n");
	char* a="aaa";
	char* b="bbb";
	char* c="ccc";
	char* d="ddd";
	StringList tester;
	StringList_Init(&tester);
	StringList_AddFront(&tester,b);
	StringList_AddFront(&tester,a);
	StringList_AddBack(&tester,c);
	StringList_AddBack(&tester,d);
	
	printf("Now the list has %d item(s)",StringList_Size(&tester));	

	printf("Testing String_Remove\n deleting...\n");	
	StringList_Remove(&tester, b);
	printf("Now the list has %d item(s)\n",StringList_Size(&tester));
	if(StringList_Size(&tester) != 3)
	return TEST_FAILED;

	printf("Testing StringList_RemoveNode\n deleting...\n");	
	
	StringList_RemoveNode(&tester, tester.head);
	printf("Now the list has %d item(s)\n",StringList_Size(&tester));
	if(StringList_Size(&tester) != 2)
	return TEST_FAILED;

	return TEST_PASSED;
}

int test7(){
	printf("Creating nodes and linking them together\n");
	char* a="aaa";
	char* b="bbb";
	char* c="ccc";
	char* d="ddd";
	StringList tester;
	StringList_Init(&tester);
	StringList_AddFront(&tester,b);
	StringList_AddFront(&tester,a);
	StringList_AddBack(&tester,c);
	StringList_AddBack(&tester,d);
	
	printf("Now the list has %d item(s)\n",StringList_Size(&tester));	
	
	printf("Deleting all the nodes in list with StringList_remove function\n");

	for(int i=4;i>0;i--){
	printf("head element:%s\n",tester.head->element);
	StringList_Remove(&tester, tester.head->element);
	printf("Now the list has %d item(s)\n",StringList_Size(&tester));
	}	
	if(StringList_Size(&tester)!=0)
	return TEST_FAILED;
	

	printf("\n\n");
	printf("Adding nodes and linking them together again\n");
	StringList_Init(&tester);
	StringList_AddFront(&tester,b);
	StringList_AddFront(&tester,a);
	StringList_AddBack(&tester,c);
	StringList_AddBack(&tester,d);
	printf("Now the list has %d item(s)\n",StringList_Size(&tester));	
	
	printf("Deleting all the nodes in list with StringList_RemoveNode function\n");
	for(int i=4;i>0;i--){
	printf("head element:%s\n",tester.head->element);
	StringList_RemoveNode(&tester, tester.head);
	printf("Now the list has %d item(s)\n",StringList_Size(&tester));
	}	
	if(StringList_Size(&tester)!=0)
	return TEST_FAILED;

	printf("\n\n");
	printf("Adding nodes and linking them together again\n");
	StringList_Init(&tester);
	StringList_AddFront(&tester,b);
	StringList_AddFront(&tester,a);
	StringList_AddBack(&tester,c);
	StringList_AddBack(&tester,d);
	printf("Now the list has %d item(s)\n",StringList_Size(&tester));	
	printf("Deleting all the nodes in list with StringList_Destroy function\n");
	StringList_Destroy(&tester);
	printf("Now the list has %d item(s)\n",StringList_Size(&tester));
	if(StringList_Size(&tester)!=0)
	return TEST_FAILED;
	

	return TEST_PASSED;
}

int test8(){
	printf("Creating nodes and linking them together\n");
	char* a="aaa";
	char* b="bbb";
	char* c="ccc";
	char* d="ddd";
	StringList tester;
	StringList_Init(&tester);
	printf("After initialize the list has %d item(s)\n",StringList_Size(&tester));
	if(StringList_Size(&tester)!=0)
	return TEST_FAILED;
	
	StringList_AddFront(&tester,b);
	StringList_AddFront(&tester,a);
	StringList_AddBack(&tester,c);
	StringList_AddBack(&tester,d);
	printf("After adding 4 nodes list has %d item(s)\n",StringList_Size(&tester));
	if(StringList_Size(&tester)!=4)
	return TEST_FAILED;
	
	printf("\n\n");
	printf("Removing str head str which is 'aaa' with StringList_Remove\n");
	StringList_Remove(&tester, "aaa");
	printf("head element is now:%s\n",tester.head->element);
	printf("Now the list has %d item(s)\n",StringList_Size(&tester));	
	if(strcmp(tester.head->element,"bbb")!=0)
	return TEST_FAILED;

	printf("\n\n");
	printf("Removing str head str which is 'bbb' with StringList_RemoveNode\n");
	StringList_RemoveNode(&tester, tester.head);
	printf("head element is now:%s\n",tester.head->element);
	printf("Now the list has %d item(s)\n",StringList_Size(&tester));
	if(strcmp(tester.head->element,"ccc")!=0)
	return TEST_FAILED;
	
	printf("\n\n");
	printf("Useing StringList_GetIndex to check if the item at index 1 is now the tail which contains 'ddd', it contians:%s",StringList_GetIndex(&tester,1)->element);
	if(!strstr(StringList_GetIndex(&tester, 1)->element,"ddd"))
	return TEST_FAILED;

	printf("\n\n");
	printf("Destroying the list...\n");
	StringList_Destroy(&tester);
	printf("Now the list has %d item(s)\n",StringList_Size(&tester));
	if(StringList_Size(&tester)!=0)
	return TEST_FAILED;








	return TEST_PASSED;
}




/* Do not change any of the code below, to ensure consistency during all vs. all testing */

void show_usage(){
	fprintf(stderr,"Usage: ./string_list_tester <test_number>\n");
	fprintf(stderr,"Where <test_number> is an integer between 1 and 8.\n");
}

int main(int argc, char** argv){
	if (argc < 2){
		show_usage();
		return 0;
	}
	//The atoi function converts a string to an integer (and returns 0 if
	//the conversion fails).
	int test_number = atoi(argv[1]);
	
	if (test_number <= 0 || test_number > 8){
		show_usage();
		return 0;
	}
	
	int result = 1;
	switch(test_number){
		case 1:
			result = test1();
			break;
		case 2:
			result = test2();
			break;
		case 3:
			result = test3();
			break;
		case 4:
			result = test4();
			break;
		case 5:
			result = test5();
			break;
		case 6:
			result = test6();
			break;
		case 7:
			result = test7();
			break;
		case 8:
			result = test8();
			break;
	}
	
	if (result == TEST_PASSED){
		printf("\nTEST PASSED\n");
	}else{
		printf("\nTEST FAILED\n");
	}
	
	return 0;
}
