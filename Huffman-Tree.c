#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#define MAX 500

typedef struct node{
	char letter;
	int frequency;
	struct node *left, *right, *next;
}NODE;

//for scanning input from file
void scanFromFile(char *buffer, FILE *file);
//for creating new node
NODE *createNewNODE(char letter);
//search a node in list if it has already exist return it else return null
NODE *searchInList(NODE *head, char letter);
//add a node at front
void pushFront(NODE **head, NODE *theNODE);
//take input string and create a linked list that its each nodes are letters in text
NODE *putInList(NODE *head, char *text);
//push a node into the proper position
void sortedInsert(NODE **head, NODE *theNODE);
//create a new sorted linked list
void insertionSort(NODE **head);
//convert the linked list to a huffman tree
void huffmanTree(NODE **head);
//calculate height of a tree
int height(NODE* head);
//printf a tree with level order traversal
void printLevelbyLevel(NODE *head);
//prints the number of spaces given
void printSpace(int n);

int main(){
	//Scanning text
	char text[MAX];
	FILE *file;
	printf("If you want to scan from terminal type input directly!!\n");
	printf("If you want to scan input from file type '!file' and press enter!!\n");
	scanf("%[^\n]s",text);
	//If first input is scan from file command this input becomes invalid and scans again from file
	//If firs input is not !file this scanning is valid as input
	if(!strcmp(text,"!file")){
		scanFromFile(text, file);
	}
	
	NODE *head = NULL;
	//Creation Linked List
	head = putInList(head, text);
	//sorting linked list
	insertionSort(&head);
	//Covertion linked list to huffman tree
	huffmanTree(&head);
	//print tree
	printLevelbyLevel(head);

	return 0;
}

void printSpace(int n){
	int i;
	for(i = 0; i < n ; i++){
		printf(" ");
	}
}

void printLevelbyLevel(NODE *head){
	//if tree is empty do nothing
	if(head == NULL){
		return;
	}
	//Create a Queue to print tree with level order
	//I design a simple array based Queue
	NODE *q[MAX];
	//enq for enqueue and deq for dequeue
	int enq = 0, deq = 0;
	//I need space size for printing proper spaces each characters
	int space = pow(2, height(head)-1)-1;
	//calculate height of tree 
	int level = height(head);
	int i, j;
	q[enq++] = head;
	//loop for every level of tree
	for(i = 0; i < level; i++){
		//loop for every elements of that level
		for(j = 0; j < pow(2, i); j++){
			//dequeue from queue and make it current
			NODE *current = q[deq++];
			//enqueue currents left and right children to queue
			if(current != NULL){
				q[enq++] = current->left;
				q[enq++] = current->right;
			}
			//if it has't got any child enqueue NULL to queue
			else{
				q[enq++] = NULL;
				q[enq++] = NULL;
			}
			//if current is not null print it
			//printSpace functions are necessary for formatting
			if(current != NULL){
			printSpace(space);	
			printf("%d%c", current->frequency, current->letter);
			printSpace(space);
			}
			//if current is null print '  ' for proper formatting
			else{
				printSpace(space);
				printf("  ");
				printSpace(space);
			}
		}
		//if this level ends go to next line
		//and set space size space/2 for formatting
		space = space/2;
		printf("\n");
	}
}

void huffmanTree(NODE **head){
	//if list is empty we can not create a tree
	if((*head) == NULL){
		return;
	}
	//create a new node and set 2 nodes as childeren of new node and insert new node to list
	NODE *node1, *tmp;
	for(node1 = (*head); node1->next != NULL; node1 = node1->next->next){
		tmp = createNewNODE(' ');
		tmp->frequency = node1->frequency + node1->next->frequency;
		sortedInsert(head, tmp);
		tmp->left = node1;
		tmp->right = node1->next;
		(*head) = node1->next->next;
	}
}

void insertionSort(NODE **head){
	//create new list and insert sorted
	NODE *sorted = NULL;
	NODE *current = (*head);
	
	//loof for every elements in list
	while(current != NULL){
		NODE *next = current->next;
		sortedInsert(&sorted, current);
		current = next;
	}
	
	//set sorted list as my main list
	(*head) = sorted;
}

void sortedInsert(NODE **head, NODE *theNODE){
	NODE *current = (*head);
	
	//if list is empty or theNODE is less than head
	if((*head) == NULL || theNODE->frequency <= current->frequency){
		theNODE->next = (*head);
		(*head) = theNODE;
	}
	//go ahead until find a grater number and insert it
	else{
		while(current->next != NULL && current->next->frequency <= theNODE->frequency){
			current = current->next;
		}
		theNODE->next = current->next;
		current->next = theNODE;
	}
}

NODE *putInList(NODE *head, char *text){
	//Make a linked list from letters of text
	int i;
	NODE *tmp;
	//iterate until the end of text
	for(i = 0; text[i] != '\0'; i++){
		//Is there the letter before?
		tmp = searchInList(head, text[i]);
		//if no create new node and push front of list
		if(tmp == NULL){
			tmp = createNewNODE(text[i]);
			pushFront(&head, tmp);
		}
		//if yes increase its frequency
		else{
			tmp->frequency++;
		}
	}
	return head;
}

void pushFront(NODE **head, NODE *theNODE){
	//if list is empty make theNODE head
	if((*head) == NULL){
		(*head) = theNODE;
	}else{
		//else set previous head as the next of theNODE and set theNODE as new head
		theNODE->next = (*head);
		(*head) = theNODE;
	}
}

NODE *searchInList(NODE *head, char letter){
	NODE *current = head;
	//it goes until the end or until it found
	while(current != NULL && current->letter != letter){
		current = current->next;
	}
	//if node has already exists it returns node else it returns NULL
	return current;
}

NODE *createNewNODE(char letter){
	NODE *newNODE = (NODE*)malloc(sizeof(NODE));
	if(newNODE == NULL){
		printf("Allocation Error");
		exit(1);
	}
	newNODE->frequency = 1;
	newNODE->letter = letter;
	newNODE->left = NULL;
	newNODE->right = NULL;
	newNODE->next = NULL;
	return newNODE;
}

void scanFromFile(char *buffer, FILE *file){
	char fileName[20];
	printf("Filename: ");
	scanf("%s",fileName);
	file = fopen(fileName, "r");
	if(file == NULL){
		printf("File Error");
		exit(1);
	}
	fgets(buffer, MAX, file);
	printf("Text: ");
	puts(buffer);
}

int height(NODE *head){
	//calculates the height of tree
	if(head == NULL){
		return 0;
	}else{
		int leftHeight = height(head->left);
		int rightHeight = height(head->right);
		
		if(leftHeight > rightHeight){
			return leftHeight+1;
		}else{
			return rightHeight+1;
		}
	}
}


