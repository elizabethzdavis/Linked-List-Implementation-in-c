#include <stdio.h>
#include <stdlib.h>
#include "llist.h"

// Creates and returns an new node
struct LNode *create_new_node(struct LData *data) {
	struct LNode *node;
	node = malloc(sizeof(struct LNode));
	node -> data = data;
	node -> next = NULL;
	return node;

}

// Creates and returns an empty list
struct LList *create_empty_list()  {
	struct LList *list;
	list = malloc(sizeof(struct LList));
	//struct LNode *node = malloc(sizeof(struct LNode)); //creates a new node to set root and sentinal node to - 
	/* --------------------------//otherwise there would be nothing for the root and sentinal to point to */
	/*node -> data = NULL;
	list -> root = node;
	list -> sentinal = node;*/
	list -> root = NULL;
	list -> sentinal = NULL;
	list -> size = 0;
	return list;
	
}

// Clears (empties) the specified list
void clear_list(struct LList *list) {
	list -> size = 0.0;
	list -> root = NULL;
	list -> sentinal = NULL;
}

// Swaps the elements of a list
void swap_elems(struct LList *list, int idx1, int idx2) {
	struct LNode* Node1 = (struct LNode*)malloc(sizeof(struct LNode));
	struct LNode* Node2 = (struct LNode*)malloc(sizeof(struct LNode));

	if(idx1 == idx2) {
		return;
	}

	if(idx1 < idx2) {
		Node1 -> data = get_elem(list, idx1);
		add_elem(list, Node1 -> data, idx2);
		Node2 -> data = get_elem(list, idx2+1);
		add_elem(list, Node2 -> data, idx1);
		rem_elem(list, idx1 +1);
		rem_elem(list, idx2 +1);
	}

	if(idx2 < idx1) {
		Node1 -> data = get_elem(list, idx2);
		add_elem(list, Node1 -> data, idx1);
		Node2 -> data = get_elem(list, idx1+1);
		add_elem(list, Node2 -> data, idx2);
		rem_elem(list, idx2 +1);
		rem_elem(list, idx1 +1);
	}
	
}

// Prints the list to standard output in the form [elem_1 elem_2 ... elem_n]
void print_list(struct LList *list) {
	
	struct LNode *node = (struct LNode*)malloc(sizeof(struct LNode));

	if (list -> root != NULL) {
		node = list -> root;
		printf("[");
		while( node -> next != NULL) {
			printf("(%s, %.1f, %.1f)",
			node -> data->city,
			node -> data->lat,
			node -> data->lon);
			printf(" ");
			node = node -> next;
		} 
		printf("(%s, %.1f, %.1f)",
			node -> data->city,
			node -> data->lat,
			node -> data->lon);
		printf("] ");		
	}
	else {
		printf("[ ]");
	}
}

// ==============================================================
// Query functions (no side effects)
// ==============================================================

// Checks if the list is empty //1 true, 0 fase
int is_empty(struct LList *list) {
	if(list -> size == 0) {
		return 1;
	}

	return 0;
}

// Returns the size of the list
int size(struct LList *list) {
	return list -> size;
}

// Checks of the list contains the specified data
// Uses the are_equal operation of LData
int contains(struct LList *list, struct LData *data) {
	struct LNode* temp = (struct LNode*)malloc(sizeof(struct LNode)); 
	temp = list -> root;
	int i = 0;
	for(i = 0; i < list -> size; i++) {
		if(are_equal(temp -> data, data)) {
			return 1;
		}

		temp = temp -> next;
	}
	return 0;
}

// ==============================================================
// Add operations
// ==============================================================

// Adds the specified element to the specified position
void add_elem(struct LList *list, struct LData *data, int idx) {
		struct LNode* addingElem = (struct LNode*)malloc(sizeof(struct LNode)); 
		struct LNode* counter = (struct LNode*)malloc(sizeof(struct LNode)); //The one before the replace to point to the next node 
		struct LNode* newNext = (struct LNode*)malloc(sizeof(struct LNode)); 
		addingElem -> data = data;
		counter = list -> root;

		if(idx < 0 || idx > (list -> size)) {
			return;
		}

		if(idx == 0) {
			add_first(list, data);
		}

		else { 
			int i = 0;
			for (i = 0; i < idx -1; i ++) { 
				counter = counter -> next;
			}

			newNext = counter -> next;
			counter -> next = addingElem; //The throwaway is now the number replace is at 
			addingElem -> next = newNext;
			
			list -> size ++;
		}			
}

// Adds the specified data to the front of the list
void add_first(struct LList *list, struct LData *data) {
	//create a new node and set that new node as the root
	//Has to remember the second node 
	//printf("\n In Print_List = Size: %d\n", list -> size);
	struct LNode* temp = (struct LNode*)malloc(sizeof(struct LNode)); // creating the temp 
	temp -> data = data;
	temp -> next = list -> root; //setting the second node in the linkedlist back to the original root
	list -> root = temp; //setting the first node to the temp which is the node being inserted
	//printf("\n In Print_List = Size: %d\n", list -> size);
	list -> size = list -> size + 1;  //Want to increase the size in order keep in track of the size 
	//printf("\n In Print_List = Size: %d\n", list -> size);
}

// Adds the specified data to the end of the list
void add_last(struct LList *list, struct LData *data) {
	struct LNode* temp = (struct LNode*)malloc(sizeof(struct LNode)); 	//temporary node to hold new data
	struct LNode* placeholder = (struct LNode*)malloc(sizeof(struct LNode));
	placeholder = list -> root;
	//printf("\n In Print_List = Size: %d\n", list -> size); 							//The node to hold the spot through the loop //start it off as the root
	temp -> data = data;  
	//printf("\n In Print_List = Size: %d\n", list -> size); 		
	 																	//THat's putting the right data into the node to insert
																		//We want to add this node in before the sentinal but after the last 
																		//We need to get the last linked list 
	int i = 0;
	for(i = 0; i <= list -> size-2; i++) { 								//we want it size minus one in order to have it the one before the sentinal
		placeholder = placeholder -> next; 								//This puts the new node in the placeholder node it started off as the root
	} 																	//loop is over and placeholder is the node before the new node is added

	placeholder -> next = temp; 										//inserting the temp node after the last node before the sentinal 
	temp -> next =  list -> sentinal; 
	list -> size = list -> size +1; 
	//printf("\n In Print_List = Size: %d\n", list -> size);								    //resetting it to the sentinal to point to it 
}

// ==============================================================
// Get operation
// ==============================================================

// Returns a handle (pointer) to the element of the list at the specified position
struct LData *get_elem(struct LList *list, int idx) {
	struct LNode* toReturn = (struct LNode*)malloc(sizeof(struct LNode));
	toReturn = list -> root; //to move along the list 

	if(idx < 0 || idx > (list -> size -1)) {
		return NULL;
	}
	int i = 0;
	for (i = 0; i < idx; i ++) {
		toReturn = toReturn -> next;
	}
	return toReturn -> data; 	
}

// ==============================================================
// Remove operations
// ==============================================================

// Removes and returns the specified element from the specified position
struct LData *rem_elem(struct LList *list, int idx) {
	//printf("\n In Print_List = Size: %d\n", list -> size);
	struct LNode* throwaway = (struct LNode*)malloc(sizeof(struct LNode));
	throwaway = list -> root; //to move along the list 
	struct LNode* replace = (struct LNode*)malloc(sizeof(struct LNode)); 
	struct LNode* prior = (struct LNode*)malloc(sizeof(struct LNode)); //The one before the replace to point to the next node 
	/* ----- Loop throught the linked list with throw away. When get to index, the throwaway is the linked list
		that is needed to get rid of. From there point the replace array to the new array -----*/

	if(idx < 0 || idx > (list -> size -1)) {
		return NULL;
	}

	int i = 0;
	for (i = 0; i < idx; i ++) {
		prior = throwaway; 
		throwaway = throwaway -> next;
	}

	replace = throwaway; //The throwaway is now the number replace is at 

	//Now we need to point the replace to the new one
	if(replace -> next != NULL) { //make sure not at end 
		replace = replace -> next; //Point to the new one
		prior -> next = replace; 
	}

	else {
		prior -> next = list -> sentinal;
	}
	list -> size --;
	return throwaway -> data; 
	
}

// Removes and returns the first element in the list
// Assumes that the list is not empty
struct LData *rem_first(struct LList *list) {
	struct LNode* throwaway = (struct LNode*)malloc(sizeof(struct LNode)); //To take the first node and throw away
	struct LNode* newFirst = (struct LNode*)malloc(sizeof(struct LNode)); //The second node to now point to the beginning
	//printf("\n In Print_List = Size: %d\n", list -> size);
	throwaway = list -> root; //First node is the throwaway
	newFirst = throwaway;
	
	if(newFirst != NULL) {
		newFirst = newFirst -> next;
		list -> root = newFirst;
	}

	else{
		newFirst -> next = list -> sentinal;
	}
	//printf("\n In Print_List = Size: %d\n", list -> size);

	list -> size--;
	//printf("\n In Print_List = Size: %d\n", list -> size);
	return throwaway -> data;
	
}

// Removes and returns the last element in the list
// Assumes that the list is not empty
struct LData *rem_last(struct LList *list) {
	struct LNode* temp = (struct LNode*)malloc(sizeof(struct LNode));
	temp = list -> root;
	struct LNode* throwaway = (struct LNode*)malloc(sizeof(struct LNode)); //to iterate through with
	//printf("\n In Print_List = Size: %d\n", list -> size);
	int i = 0;
	for (i = 0; i < list -> size -2; i++) { //We want this to point to the second to last node in order to repoint 
		//the node before it to the sentinal after it
		temp = temp -> next;
	}
	//printf("\n In Print_List = Size: %d\n", list -> size);

	throwaway = temp -> next; //setting the throwawy 
	temp -> next = list -> sentinal; 
	list -> size--;
	//printf("\n In Print_List = Size: %d\n", list -> size);
	return throwaway -> data;
}

// ==============================================================
// Sort operations
// ==============================================================

// Sorts the list according to the are_ordered operation of LData
void insertion_sort(struct LList *list) {
	struct LNode* temp = (struct LNode*)malloc(sizeof(struct LNode));
	struct LNode* iterator = (struct LNode*)malloc(sizeof(struct LNode));
	temp = list -> root;
	iterator = temp -> next;
	int i = 0;
	for (i = 0; i < (list -> size) -1; i++) {
		if(are_ordered(temp -> data, iterator -> data)) {
			temp = temp -> next;
			iterator = iterator -> next;
		}

		else {
			swap_elems(list, i, i+1);
			temp = temp -> next;
			iterator = iterator -> next;
		}
	}

}
// NOTE: Use the pseudocode at Wikipedia as a template for your insertion sort:
// for i â† 1 to length(A) - 1
//     j â† i
//     while j > 0 and A[j-1] > A[j]
//         swap A[j] and A[j-1]
//         j â† j - 1
