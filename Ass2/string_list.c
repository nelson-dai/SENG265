#include "string_list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* StringList_init(L)
 Initialize the provided StringList instance.
 
 Pre-conditions:
 L is a pointer to a StringList struct.
 Post-conditions:
 The head and tail pointers of L have been
 initialized to NULL.
 */

void StringList_Init(StringList* L){
    L->head = NULL;
    L->tail = NULL;
}

/* StringList_destroy(L)
 Free all storage associated with each node of the StringList
 object and reset all pointers to NULL.
 
 Pre-conditions:
 L is a pointer to a StringList struct which has been
 initialized with StringList_init and has not already
 been destroyed.
 Post-conditions:
 Each node of L, and its associated string, has been freed.
 The head and tail pointers of L have been set to NULL.
 */
void StringList_Destroy(StringList* L){
    StringListNode* curr = L->head; //curr initially points to head
    while(curr != NULL)
    {
        StringListNode* currNext = curr->next;
        free(curr->element);   //safer ?
        free(curr);
        curr = currNext;
    }
    L->head = NULL;
    L->tail = NULL;
    //free(L);  //not really necessary ?
}

/* StringList_size(L)
 Return the number of nodes in the list L
 
 Pre-conditions:
 L is a pointer to an initialized StringList struct.
 Return value:
 The number of nodes in L.
 */
int StringList_Size(StringList* L){
    int count = 1;
    
    if(L->head == NULL){
        
        return 0;
    }
    
    StringListNode* curr = L->head; //curr initially points to head
    while(curr != NULL)
    {
        StringListNode* currNext = curr->next;
        curr = currNext;
	if(curr!=NULL)
        count++;
    }
    return count;
}

/* StringList_AddFront(L, str)
 Create a new list node containing a copy of the string str and
 add the node to the front (head) of the list L.
 
 Note: The created node must not contain a pointer to the string
 str. Instead, it should contain a pointer to a new array containing
 a copy of str.
 
 Pre-conditions:
 L is a pointer to an initialized StringList struct.
 str points to a valid null terminated C string.
 Post-conditions:
 A new node containing a copy of str has been attached
 to the beginning of the list L.
 Return value:
 A pointer to the created node.
 */
StringListNode* StringList_AddFront(StringList* L, char* str){
    StringListNode* NewNode =  (StringListNode* )malloc(sizeof(StringListNode));
    char *copy = (char*)malloc(sizeof(str));
    strcpy(copy,str);
    NewNode->element = copy;
    NewNode->next = NULL;
    NewNode->previous = NULL;
    
    if(L->head == NULL){
    L->head = NewNode;
    L->tail = NewNode;
    NewNode->next = NULL;
    NewNode->previous = NULL;
        return NewNode;
    }
    
    NewNode->next = L->head;
    L->head->previous = NewNode;
    NewNode->previous = NULL;
    L->head = NewNode;
    
    return NewNode;
}


/* StringList_AddBack(L, str)
 Create a new list node containing a copy of the string str and
 add the node to the back (tail) of the list L.
 
 Note: The created node must not contain a pointer to the string
 str. Instead, it should contain a pointer to a new array containing
 a copy of str.
 
 Pre-conditions:
 L is a pointer to an initialized StringList struct.
 str points to a valid null terminated C string.
 Post-conditions:
 A new node containing a copy of str has been attached
 to the end of the list L.
 Return value:
 A pointer to the created node.
 */
StringListNode* StringList_AddBack(StringList* L, char* str){
    
    StringListNode* NewNode =  (StringListNode* )malloc(sizeof(StringListNode));
	
    char *copy = (char*)malloc(sizeof(str)+1);
    
    strcpy(copy,str);

    NewNode->element = copy;
    NewNode->next = NULL;
    NewNode->previous = NULL;
    
    if(L->head == NULL){
    L->head = NewNode;
    L->tail = NewNode;
    NewNode->next = NULL;
    NewNode->previous = NULL;
        return NewNode;
    }
     StringListNode* curr = L->head;
    while(curr->next != NULL){
    	curr = curr->next;
    }
    curr->next = NewNode;
    NewNode->previous = curr;
    L->tail = NewNode;
    L->tail->next = NULL;
    return NewNode;
}

/* StringList_remove(L, str)
 Search the list L for a node containing the provided string str
 and remove the first such node if it is present.
 
 Note that the removal process should free all storage associated
 with the node and the string it contains.
 
 Pre-conditions:
 L is a pointer to an initialized StringList struct.
 str points to a valid null terminated C string.
 Post-conditions:
 If a node containing str was found, it has been removed
 from the list L.
 Return value:
 1 if a node containing str was found.
 0 otherwise.
 */
int StringList_Remove(StringList* L, char* str) {
  StringListNode* temp;
  temp=StringList_InList(L,str);
  if (temp!=NULL) {
    StringList_RemoveNode(L,temp);
    return 1;
  }
  return 0;
}


/* StringList_RemoveNode(L, node)
   Remove the provided node from the list L.
   
   Note that the removal process should free all storage associated
   with the node and the string it contains.
   
   Pre-conditions:
     L is a pointer to an initialized StringList struct.
   node points to a valid node in L.
   Post-conditions:
     node has been removed from L.
*/ 
//add a function, use"free"

void StringList_RemoveNode(StringList* L, StringListNode* node) {
  if (L->head==L->tail) {
   if (node!=NULL) {
    if (node->element!=NULL) {
      free(node->element);
    }
    free(node);
  }
    L->head=NULL;
    L->tail=NULL;
  }else if (node==L->head) {
    L->head=L->head->next;
    if (node!=NULL) {
    if (node->element!=NULL) {
      free(node->element);
    }
    free(node);
  }
    L->head->previous=NULL;
  }else if (node==L->tail) {
    L->tail=L->tail->previous;
    if (node!=NULL) {
    if (node->element!=NULL) {
      free(node->element);
    }
    free(node);
  }
    L->tail->next=NULL;
  }else {
    node->previous->next=node->next;
    node->next->previous=node->previous;
    if (node!=NULL) {
    if (node->element!=NULL) {
      free(node->element);
    }
    free(node);
  }
  }
}

/* StringList_InList(L, str)
 Search the list L for a node containing the provided string str
 and return a pointer to the first node containing str if it is found.
 
 The "first" node, in this context, refers to the first node encountered
 on a forward traversal of the list starting at the head.
 
 Pre-conditions:
 L is a pointer to an initialized StringList struct.
 str points to a valid null terminated C string.
 Return value:
 A pointer to the first node containing str if it was found in the list.
 NULL otherwise.
 */
StringListNode* StringList_InList(StringList* L, char* str){
 	StringListNode *tmp = L->head;
 	if(str == NULL) 
	return NULL;
	
 	while(tmp != NULL){
    	if(strcmp(tmp->element, str) == 0)
      	return tmp;
    	
    	tmp = tmp->next;
  	}
  	return NULL;
}

/* StringList_GetIndex(L, i)
 Return the node at the provided index i (where index 0 is
 the node at the head of the list).
 
 
 Pre-conditions:
 L is a pointer to an initialized StringList struct.
 Return value:
 A pointer to node i if 0 <= i <= size - 1 (where size is the
 number of elements in the list.
 NULL if i is not a valid index into the list.
 */
StringListNode* StringList_GetIndex(StringList* L, int i){
    
    if( i < 0 || i > StringList_Size(L) - 1){
        return NULL;
    }
    
    StringListNode* curr = L->head;
    for(int j =0; j < i ; j++){
        curr = curr->next;
    }
    
    return curr;
}
