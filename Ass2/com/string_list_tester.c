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

int test1() {
	//First test case: Basic functionality I
	//Test only the StringList_Init, StringList_Size,
	//and StringList_AddFront functions.
	//(Note that since you cannot use StringList_Destroy, this function
	// will produce a memory leak. However, this is acceptable in a testing
	// context).
  //int result;
  //result=TEST_PASSED;
  StringList Lvalue,*L;
  L=&Lvalue;
  StringList_Init(L);
  if (L->head || L->tail) {
    return TEST_FAILED;
  }
  int n;
  n=StringList_Size(L);
  if (n!=0) {
    return TEST_FAILED;
  }
  char * s = "abc";
  StringList_AddFront(L,s);
  if (!(L->head) || strcmp(L->head->element,s)) {
    return TEST_FAILED;
  }
  n=StringList_Size(L);
  if (n!=1) {
    return TEST_FAILED;
  }
	return TEST_PASSED;
}


int test2(){
	//Second test case: Basic functionality II
	//Test only the StringList_Init, StringList_Size,
	//StringList_AddFront and StringList_AddBack functions.
  StringList Lvalue,*L;
  L=&Lvalue;
  StringList_Init(L);
	printf("...");
  if (L->head || L->tail) {
    return TEST_FAILED;
  }
  int n;
  n=StringList_Size(L);
	printf("...");
  if (n!=0) {
    return TEST_FAILED;
  }
  char * s1 = "abc";
  StringList_AddFront(L,s1);
  char * s2 = "def";
  StringList_AddBack(L,s2);
	printf("...");
  if (!(L->head) || strcmp(L->head->element,s1)) {
    return TEST_FAILED;
  }
	printf("...");
  if (!(L->tail) || strcmp(L->tail->element,s2)) {
    return TEST_FAILED;
  }
	printf("...");
  n=StringList_Size(L);
  if (n!=2) {
    return TEST_FAILED;
  }
	return TEST_PASSED;
}

int test3(){
	//Third test case: Basic functionality III
	//Test only the StringList_Init, StringList_Size,
	//StringList_AddFront and StringList_AddBack functions.
	//Use a different methodology for this test than test 2.
  StringList Lvalue,*L;
  L=&Lvalue;
  StringList_Init(L);
  if (L->head || L->tail) {
    return TEST_FAILED;
  }
  int n;
  n=StringList_Size(L);
  if (n!=0) {
    return TEST_FAILED;
  }
  char * s1 = "abc";
  StringList_AddFront(L,s1);
  char * s2 = "def";
  StringList_AddBack(L,s2);
  StringList_AddFront(L,s2);
  StringList_AddBack(L,s1);
  if (!(L->head) || strcmp(L->head->element,s2)) {
    return TEST_FAILED;
  }
  if (!(L->tail) || strcmp(L->tail->element,s1)) {
    return TEST_FAILED;
  }
  n=StringList_Size(L);
  if (n!=4) {
    return TEST_FAILED;
  }
	return TEST_PASSED;
}

int test4(){
	//Fourth test case: List membership I
	//Test the StringList_GetIndex function, using any of the functions
	//tested in previous test cases if necessary.
  StringList Lvalue,*L;
  L=&Lvalue;
  StringList_Init(L);
  if (L->head || L->tail) {
    return TEST_FAILED;
  }
  int n,i;
  StringListNode * node;
  n=StringList_Size(L);
  if (n!=0) {
    return TEST_FAILED;
  }
  char * s1 = "abc";
  StringList_AddFront(L,s1);
  char * s2 = "def";
  StringList_AddBack(L,s2);
  StringList_AddFront(L,s2);
  StringList_AddBack(L,s1);
  char * s3 = "hello";
  StringList_AddBack(L,s3);
  if (!(L->head) || strcmp(L->head->element,s2)) {
    return TEST_FAILED;
  }
  if (!(L->tail) || strcmp(L->tail->element,s3)) {
    return TEST_FAILED;
  }
  n=StringList_Size(L);
  if (n!=5) {
    return TEST_FAILED;
  }
  char * list[]= {s2,s1,s2,s1,s3};
  for (i=0;i<n;i++) {
    node = StringList_GetIndex(L,i);
    if (!node || strcmp(list[i],node->element)) {
      return TEST_FAILED;
    }
  }
	return TEST_PASSED;
}

int test5(){
	//Fifth test case: List membership II
	//Test the StringList_InList function, using any of the functions
	//tested in previous test cases if necessary.
  StringList Lvalue,*L;
  L=&Lvalue;
  StringList_Init(L);
printf("...\n");
  if (L->head || L->tail) {
    return TEST_FAILED;
  }
  int n,i;
  StringListNode * node;
  n=StringList_Size(L);
printf("...\n");
  if (n!=0) {
    return TEST_FAILED;
  }
  char * s1 = "abc";
  StringList_AddFront(L,s1);
  char * s2 = "def";
  StringList_AddBack(L,s2);
  StringList_AddFront(L,s2);
  StringList_AddBack(L,s1);
  char * s3 = "hello";
  StringList_AddBack(L,s3);
  char * s4= "not there";
printf("...\n");
  if (!(L->head) || strcmp(L->head->element,s2)) {
    return TEST_FAILED;
  }
printf("...\n");
  if (!(L->tail) || strcmp(L->tail->element,s3)) {
    return TEST_FAILED;
  }
printf("...\n");
  n=StringList_Size(L);
  if (n!=5) {
    return TEST_FAILED;
  }
  char * list[]= {s1,s2,s3,s4};
  int inlist[] = {1,1,1,0};
printf("...\n");
  for (i=0;i<4;i++) {
    node = StringList_InList(L,list[i]);
    if ((node? 1:0)!=inlist[i]) {
     return TEST_FAILED;
    }
  }
	return TEST_PASSED;
}

int test6(){
	//Sixth test case: Deletion I
	//Test the StringList_Remove and StringList_RemoveNode functions,
	//using any of the functions tested in previous test cases if necessary.
  StringList Lvalue,*L;
  L=&Lvalue;
  StringList_Init(L);
  if (L->head || L->tail) {
    return TEST_FAILED;
  }
  int n;
  //StringListNode * node;
  n=StringList_Size(L);
  if (n!=0) {
    return TEST_FAILED;
  }
  char * s1 = "abc";
  StringList_AddFront(L,s1);
  char * s2 = "def";
  StringList_AddBack(L,s2);
  char * s3 = "hello";
  StringList_AddFront(L,s3);
  //char * s4= "not there";
  if (! StringList_InList(L,s3)) {
    return TEST_FAILED;
  }
  StringList_RemoveNode(L,L->head);
  if (StringList_InList(L,s3)) {
    return TEST_FAILED;
  }

  if (!StringList_Remove(L,s2) || StringList_InList(L,s2)) {
    return TEST_FAILED;
  }
	return TEST_PASSED;
}

int test7(){
	//Seventh test case: Deletion II
	//Test the StringList_Remove, StringList_RemoveNode and StringList_Destroy functions,
	//using any of the functions tested in previous test cases if necessary.
	//Use a different methodology for this test than test 6.
  StringList Lvalue,*L;
  L=&Lvalue;
  StringList_Init(L);
  if (L->head || L->tail) {
    return TEST_FAILED;
  }
  int n;
  //StringListNode * node;
  n=StringList_Size(L);
  if (n!=0) {
    return TEST_FAILED;
  }
  char * s1 = "abc";
  StringList_AddFront(L,s1);
  char * s2 = "def";
  StringList_AddBack(L,s2);
  char * s3 = "hello";
  StringList_AddFront(L,s3);
  StringList_AddBack(L,s1);
  //char * s4= "not there";
  if (! StringList_InList(L,s2)) {
    return TEST_FAILED;
  }
  StringList_RemoveNode(L,L->tail->previous);
  if (StringList_InList(L,s2)) {
    return TEST_FAILED;
  }

  if (!StringList_Remove(L,s1) || !StringList_InList(L,s1)) {
    return TEST_FAILED;
  }
  if (!StringList_Remove(L,s1) || StringList_InList(L,s1)) {
    return TEST_FAILED;
  }
	return TEST_PASSED;
}


void swap(int i, int j,char* str) {
  char temp=*(str+i);
  *(str+i)=*(str+j);
  *(str+j)=temp;
}


void combgen(StringList* L, char *str, int pos, int len) {
  //printf("%d\n",strlen(str));
  if (pos==len) {
    //printf("%s\n",str);
    StringList_AddBack(L,str);
    return;
  }
  int i;
  //printf("ok");
  for (i=pos;i<len;i++) {
    //printf("%d %d",pos,i);
    swap(pos,i,str);
    combgen(L,str,pos+1,len);
    swap(pos,i,str);
  }
}



int test8(){
	//Eighth test case: Stress Test
	//Test all of the methods of the StringList, in an attempt to simulate the
	//actual use of the data structure in practice. For logistical reasons,
	//keep in mind that your test must complete within 30 seconds for the
	//automated system, so some types of exhaustive testing are not practical
	//here.
  StringList Lvalue,*L;
  L=&Lvalue;
  StringList_Init(L);
  if (L->head || L->tail) {
    return TEST_FAILED;
  }
  int n,i;
  //StringListNode * node;
  n=StringList_Size(L);
  if (n!=0) {
    return TEST_FAILED;
  }
  char s[]="abcdefghijk";
  combgen(L,s,0,strlen(s));
  combgen(L,s,0,strlen(s));
  char * check[] = {"abcdefghijk","abcfedkgjih","bcadfgekhji","kjihgfedcba"};
  for (i=0;i<4;i++) {
    if (!StringList_InList(L,check[i])) {
      return TEST_FAILED;
    }
    if (!StringList_Remove(L,check[i]) || !StringList_InList(L,check[i])) {
      return TEST_FAILED;
    }
    if (!StringList_Remove(L,check[i]) || StringList_InList(L,check[i])) {
      return TEST_FAILED;
    }
  }
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
