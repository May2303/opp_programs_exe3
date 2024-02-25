#include <stdio.h>
#include "StrList.h"
#include <stdlib.h>
#include <strings.h>
#include <string.h>

// Node & List Data Structures
typedef struct _node {
    char* _data;
    struct _node * _next;
} Node;


struct _StrList{
    Node* _head;
    size_t _size; 
};

//------------------------------------------------
// Node implementation
//------------------------------------------------

Node* Node_alloc(const char* data, Node* next) {
    Node* p = (Node*)malloc(sizeof(Node));
    p->_data = strdup(data);  // Copy the string
    p->_next = next;
    return p;
}

void Node_free(Node* node) {
	free(node);
}
//------------------------------------------------

StrList* StrList_alloc(){
    StrList* p = (StrList*)malloc(sizeof(StrList));
        p->_head = NULL;
        p->_size = 0;
    return p;
}


void StrList_free(StrList* StrList){
    if (StrList==NULL) return;
	Node* p1= StrList->_head;
	Node* p2;
	while(p1) {
		p2= p1;
		p1= p1->_next;
		Node_free(p2);
	}
	free(StrList);
}

size_t StrList_size(const StrList* StrList){
    return StrList->_size;
}

void StrList_insertLast(StrList* StrList, const char* data){

    Node *newNode = Node_alloc(data, NULL);

    if (StrList->_head == NULL) {
        StrList->_head = newNode;
    }

    //check if newNode should be the first elemnt
    else{

        Node *current = StrList->_head;
        if(current->_next == NULL){
            (current->_next)=newNode;
        }
        while (current->_next != NULL) { // Change 2
            if(current->_next == NULL)
            {
                current->_next = newNode;
                printf("added later\n");
                break; // Change 3
            }
            current = current->_next;
        };
    }
}
    
   

void StrList_insertAt(StrList* StrList, const char* data,int index){

    }

char* StrList_firstData(const StrList* StrList) {
    if (StrList == NULL || StrList->_size == 0 || StrList->_head == NULL) {
        return NULL; // Handle the case where the list is empty or invalid
    }
    return StrList->_head->_data;
}

void StrList_print(const StrList* StrList){
    const Node* p = StrList->_head;
    while(p){
        printf("(%s)",p->_data);
        p = p->_next;
    }
}

void StrList_printAt(const StrList* Strlist,int index){

}

int StrList_printLen(const StrList* StrList){
   const Node* p= StrList->_head;
   int totalLength =0 ;

   while (p){ 
    char buffer[32]; // Adjust the size accordingly
        snprintf(buffer, sizeof(buffer), "%s", p->_data);
        totalLength = totalLength+ strlen(buffer);
        p = p->_next;
    }
    return totalLength;
}

int StrList_count(StrList* StrList, const char* data){
   return 0;
}

void StrList_remove(StrList* StrList, const char* data){
char *str = StrList->_head->_data;
	Node* p = StrList->_head;
	Node* prev = NULL;
	while (p!=NULL)
		{
		if(strcmp(str,data) == 0){
			if (prev == NULL) {
					// If the match is in the first node
					StrList->_head = p->_next;
				}
			else {
				// If the match is in a subsequent node
					prev->_next = p->_next;
				}

				// Free the memory allocated for the string
				free(p->_data);
				free(p);
		}
		prev = p;
		p = p->_next;
		str = p->_data;
	}
}


void StrList_removeAt(StrList* StrList, int index){
  	Node* p = StrList->_head;
	Node* prev = NULL;
	for (int i = 0; i<=index; i++){
		if(i==index){
			if (prev == NULL) {
					// If the match is in the first node
					StrList->_head = p->_next;
				}
			else {
				// If the match is in a subsequent node
				prev->_next = p->_next;
				}

				// Free the memory allocated for the string
				free(p->_data);
				free(p);
		}
		prev = p;
		p = p->_next;
	}
}

int StrList_isEqual(const StrList* StrList1, const StrList* StrList2){
    const int eq= 0;
	const int neq= 1;
	
	const Node* p1= StrList1->_head;
	const Node* p2= StrList2->_head;
	while(p1) {
		 if (p2 == NULL || strcmp(p1->_data, p2->_data) != 0)
            return neq;
        p1 = p1->_next;
        p2 = p2->_next;
	}
	if (p2!=NULL) return neq;
	return eq;
}

StrList* StrList_clone(const StrList* StringList){
    StrList* ret = StrList_alloc();
	const Node* old= StringList->_head;
	Node* * copy= &(ret->_head);
	ret->_size= StringList->_size;
	while(old) {
		*copy = Node_alloc(old->_data, NULL);
		old= old->_next;
		copy= &((*copy)->_next);
	}
	return ret;
}


void StrList_reverse( StrList* StrList){
    Node* prev = NULL;
    Node* current = StrList->_head;
    Node* next = NULL;
    while (current != NULL) {
        // Store next
        next = StrList->_head->_next;
 
        // Reverse current node's pointer
        StrList->_head->_next = prev;
 
        // Move pointers one position ahead.
        prev = current;
        current = next;
    }
    StrList->_head = prev;
}

void StrList_sort(StrList* StrList) {
    if (StrList == NULL || StrList->_size <= 1) {
        return;
    }

    for (Node* current = StrList->_head; current && current->_next; current = current->_next) {
        for (Node* next = current->_next; next; next = next->_next) {
            if (strcmp(current->_data, next->_data) > 0) {
                char* temp = current->_data;
                current->_data = next->_data;
                next->_data = temp;
            }
        }
    }
}

int StrList_isSorted(StrList* StrList) {
    if (StrList == NULL || StrList->_size <= 1) {
        return 1;
    }

    for (Node* current = StrList->_head; current && current->_next; current = current->_next) {
        if (strcmp(current->_data, current->_next->_data) > 0) {
            return 0;
        }
    }
    return 1;
}