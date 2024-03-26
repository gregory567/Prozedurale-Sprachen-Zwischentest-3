#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
LEEROY DER LISTENRECHNER

Programmieren Sie einen einfachen Rechner, der zuerst einen Reihe von Operationen, Klammern und Werte einliest,
diese in einer verketteten Liste speichert und sie dann auswertet!
*/

/*
AUFGABE

Ihr Rechenprogramm liest zeilenweise Zahlen, Operatoren und Klammern ein,
speichert diese in einer verketteten Liste und wertet diese dann als einen einzigen Ausdruck aus.
*/

/*
EINGABE

Als Eingabe kommen Integer-Zahlen, Operatoren und Klammern ('+', '-', '*', '/', '(', ')').

Sie können mit der Funktion inputToNode, die bereits implementiert ist, Eingaben in entsprechende Knoten umwandeln,
implementieren Sie dazu noch die fehlenden Funktionen createParenthesisNode, createOperatorNode und createNumberNode (siehe auch Vorausfüllung in Antwort).

Die Eingaben sollen in einer verketteten Liste gespeichert werden.

Jeder Knoten der Liste kann sowohl einen char für den Operator als auch einen Integer für eine Zahl speichern.

Zusätzlich enthält der Knoten einen enum-Typen der angibt, ob es sich um einen Operator oder eine Zahl handelt.

Jeder neue Knoten wird am Ende der Liste eingefügt und nach jedem Einfügen soll die Liste ausgegeben werden.

Die Eingabe wird durch ein '=' beendet.

Dieser Operator wird nicht mehr in die Liste eingefügt.
*/

/*
AUSWERTUNG

Wurde die Eingabe beendet soll die Liste in drei Schritten ausgewertet werden.

Dabei wird sie vom Anfang zum Ende hin ausgewertet.

Es gelten folgende Regeln:

- Es werden nur Integerrechnungen durchgeführt.
- Divisionen durch 0 werden zu Divisionen durch 1.
- Im ersten Schritt werden Klammern aufgelöst und berechnet (Hinweis: Suchen Sie nach der letzten öffnenden Klammer und lösen Sie diese zuerst auf)
- Im zweiten Schritt werden nur Punktoperationen durchgeführt (Multiplikation und Division).
- Im dritten Schritt werden nur Strichoperationen durchgeführt (Addition und Subtraktion).
- Immer wenn ein Operator ausgewertet wird und eine Berechnung stattfindet soll die Liste danach neu ausgegeben werden.
Zum Beispiel:
(2 + 8) / 5 * 4 - 3
(10) / 5 * 4 - 3
2 * 4 - 3
8 - 3
5

Bei jedem Zwischenergebnis reduziert sich somit die Anzahl der Knoten und am Ende der Auswertung sollte die Liste nur noch einen Knoten enthalten - der mit dem Endergebnis (siehe vorhergehendes Beispiel).


Die Struktur der Knoten ist bereits definiert:

struct node {
    char operator;
    int number;
    enum node_type type;
    struct node* next;
};

Das enum type bestimmt dabei ob es sich um einen Knoten für einen Operator, eine Zahl oder eine Klammer handelt.

Das entsprechende Enum ist ebenfalls bereits definiert.

Wurde eine Zahl eingegeben wird also ein Knoten erstellt, bei dem dann number gesetzt wird und der type auf number_type.

Wurde ein Operator eingegeben wird nur operator gesetzt und der type auf operator_type.

Wurde eine Klammer eingegeben wird operator gesetzt und der type auf parenthesis_type.

Es werden nie beide Felder belegt (also number und operator).


Folgende Funktionen könnten hilfreich sein, sind aber nicht vorgeschrieben:

Das Einfügen eines Knotens am Ende der Liste:
struct node *addLast(struct node *head, struct node *newNode);

Das Finden des Knotens der die letzte öffnende Klammer enthält '(', um von dort aus die Klammer auswerten zu können (bis zu ')'):
struct node *findLastParenthesisOpen(struct node *head);

Das Finden des Knotens, der den nächsten Operator enthält (Achtung: Punkt vor Strich!):
struct node *findFirstPointOperator(struct node *startNode);
struct node *findFirstDashOperator(struct node *startNode);

Das Finden des Knotens, der in der Liste vor einem bestimmten Knoten liegt (um den ersten/linken Operanden zu erhalten):
struct node *findPrevious(struct node *head, struct node *node);

Das Löschen eines bestimmten Knotens innerhalb der Liste (um bereits verarbeitete Knoten zu entfernen).

*/


//declaration of enum for node type:
enum node_type{
  number_type = 1, operator_type, parenthesis_type
};

//declaration of struct (node) for list elements:
struct node {
    char Operator;
    int number;
    enum node_type type;
    struct node* next;
};

//function pre-declarations:
struct node* inputToNode(const char* input);

struct node* createParenthesisNode(char Operator);
struct node* createOperatorNode(char Operator);
struct node* createNumberNode(int number);

void addLast(struct node** head, struct node* newNode);
void printList(struct node* head);
void deleteParticularNode(struct node** head, struct node* Node_to_delete);

struct node* findFirstPointOperator(struct node* startNode);
struct node* findFirstDashOperator(struct node* startNode);
struct node* findPrevious(struct node* head, struct node* node);
struct node* findLastParenthesisOpen(struct node* head);


//function declarations:
//function to decide what type of node should be created based on the user's input from main
struct node *inputToNode(const char *input){
    //transform input string into integer format
    int number = atoi(input);
    //if the integer input is not equal to 0, create node with integer as input
    if(number != 0){
        return createNumberNode(number);
    }
    //if the integer input is equal to 0, create node with 0 as input
    if(input[0] == '0'){
        return createNumberNode(0);
    }
    //if the input character is an opening or a closing parenthesis, create node with parenthesis character as input
    if(strcmp(input, "(") == 0 ||
        strcmp(input, ")") == 0){
        return createParenthesisNode(input[0]);
    }
    //if the input character is an operator, create node with operator character as input
    if(strcmp(input, "+") == 0 ||
        strcmp(input, "-") == 0 ||
        strcmp(input, "*") == 0 ||
        strcmp(input, "/") == 0){
        return createOperatorNode(input[0]);
    }
    return NULL;
}

//function to create node, which stores a number
struct node* createNumberNode(int number){
    //allocate memory on the heap for new struct node
    struct node* newNumberNode = (struct node*)malloc(sizeof(struct node));
    newNumberNode -> number = number;
    newNumberNode -> type = number_type;
    //next must be set to NULL, because we want to append each node at the end of the list
    newNumberNode -> next = NULL;
    return newNumberNode;
}

//function to create node, which stores an operator
struct node* createOperatorNode(char Operator){
    //allocate memory on the heap for new struct node
    struct node* newOperatorNode = (struct node*)malloc(sizeof(struct node));
    newOperatorNode -> Operator = Operator;
    newOperatorNode -> type = operator_type;
    //next must be set to NULL, because we want to append each node at the end of the list
    newOperatorNode -> next = NULL;
    return newOperatorNode;
}

//function to create node, which stores a parenthesis
struct node* createParenthesisNode(char Operator){
    //allocate memory on the heap for new struct node
    struct node* newParenthesisNode = (struct node*)malloc(sizeof(struct node));
    newParenthesisNode -> Operator = Operator;
    newParenthesisNode -> type = parenthesis_type;
    //next must be set to NULL, because we want to append each node at the end of the list
    newParenthesisNode -> next = NULL;
    return newParenthesisNode;
}

//function to append a node at the end of a list
//directly manipulating head in the main using triple ref pointer
void addLast(struct node** head, struct node* newNode){
    //if head is NULL, it is an empty list
    //therefore, head will be set as the first node
    if(*head == NULL){
        *head = newNode;
    }else{
        //pointer to iterate through the entire list (initially set to head)
        struct node* ptr = *head;
        //iterate the entire linked list and append the new node at the end
        while(ptr -> next != NULL){
            ptr = ptr -> next;
        }
        ptr -> next = newNode;
    }
    return;
}

//function to print the entire list
void printList(struct node* head){
    //if head is NULL, it is an empty list
    if(head == NULL){
        printf("\nList is empty.");
    }else{
        //pointer to iterate through the entire list (initially set to head)
        struct node* ptr = head;
        //iterate the entire linked list and print the data (numbers, operators and parentheses)
        while(ptr != NULL){
            //we have to differentiate between types of nodes (numbers and operators)
            if(ptr -> type == number_type){
                printf("%d", ptr -> number);
            }else{
                printf("%c", ptr -> Operator);
            }
            ptr = ptr->next;
        }
    }
    return;
}

//function to find the first "point operator" starting from a particular pointer to a node
struct node* findFirstPointOperator(struct node* startNode){
    //pointer to start iteration with
    //we use this pointer to iterate through the remainder of the list
    struct node* ptr = startNode;
    //iterate through the remaining part of the list and find the pointer to the node with the first "point operator"
    while(ptr != NULL){
        if(ptr -> type == operator_type && (ptr -> Operator == '*' || ptr -> Operator == '/')){
            return ptr;
        }
        //checking for closing parentheses
        //if we encounter a closing parenthesis on our way to the end of the list, we stop and return NULL
        if(ptr -> type == parenthesis_type && (ptr -> Operator == ')')){
            ptr = NULL;
            return ptr;
        }
        ptr = ptr -> next;
    }
    //if not found until the end, return NULL
    return ptr;
}

//function to find the first "dash operator" starting from a particular pointer to a node
struct node* findFirstDashOperator(struct node* startNode){
    //pointer to start iteration with
    //we use this pointer to iterate through the remainder of the list
    struct node* ptr = startNode;
    //iterate through the remaining part of the list and find the pointer to the node with the first "dash operator"
    while(ptr != NULL){
        if(ptr -> type == operator_type && (ptr -> Operator == '+' || ptr -> Operator == '-')){
            return ptr;
        }
        //checking for closing parentheses
        //if we encounter a closing parenthesis on our way to the end of the list, we stop and return NULL
        if(ptr -> type == parenthesis_type && (ptr -> Operator == ')')){
            ptr = NULL;
            return ptr;
        }
        ptr = ptr -> next;
    }
    //if not found until the end, return NULL
    return ptr;
}

//function to find the previous node relative to the input node
struct node* findPrevious(struct node* head, struct node* node){
    //pointer to iterate through the entire list (initially set to head)
    struct node* ptr = head;
    //iterate through the entire linked list and find the node previous to the node that was given to the function as input
    while(ptr != NULL){
        if(ptr -> next == node){
            return ptr;
        }
        ptr = ptr -> next;
    }
    //if not found until the end, return NULL
    return ptr;
}

//function to find the last opening parenthesis starting from the head of the list
struct node* findLastParenthesisOpen(struct node* head){
    //pointer to traverse the entire list (initially set to head)
    struct node* ptr = head;
    //temporary pointer to remember the last occurrence of the opening parenthesis
    struct node* tmp = NULL;
    //traverse the entire linked list and if you find a node with an opening parenthesis, point at its address with the temporary pointer
    //overwrite temporary pointer every time a new opening parenthesis is found
    while(ptr != NULL){
        if(ptr -> type == parenthesis_type && ptr -> Operator == '('){
            tmp = ptr;
        }
        ptr = ptr -> next;
    }
    //return the last occurrence of a node with an opening parenthesis
    return tmp;
}

//function to delete a particular node of the list
//directly manipulating head in the main using triple ref pointer
void deleteParticularNode(struct node** head, struct node* Node_to_delete){
    //pointer pointing at current node while traversing the entire list (initially set to head)
    struct node* current = *head;
    //pointer pointing at previous node while traversing the entire list (initially set to head)
    struct node* previous = *head;
    //if head is NULL, it is an empty list
    if(*head == NULL){
        printf("List is empty.");
    //if the node that we have to delete is the first node in the list
    }else if(Node_to_delete == *head){
        *head = current -> next;
        free(current);
        current = NULL;
    //if the node that we have to delete is any other node in the list
    }else{
        //traverse the list until current points at the node we have to delete
        while(current != Node_to_delete){
            previous = current;
            current = current -> next;
        }
        //pointer of previous node points at the node after the node we have to delete
        previous -> next = current -> next;
        free(current);
        current = NULL;
    }
    return;
}


int main(){

    //declare and initialize head with NULL
    struct node* head = NULL;
    //declare a string of length 10 for the user input (enough space for long inputs)
    char input[10];

    do{
        //ask the user for input and read in
        printf("\nInput: ");
        scanf("%s", input);
        //put the input into a node and add the node to the end of the list
        addLast(&head, inputToNode(input));
        //print the entire list after every input from the user
        if(strcmp(input, "=") != 0){
            printf("\nTerm: ");
            printList(head);
        }
    //terminate the input with "="
    }while(strcmp(input, "=") != 0);

    //Evaluation of the list:
    //run the loop until there are no more parentheses
    while(findLastParenthesisOpen(head) != NULL){
        //run the loop until there are no more "point operators" inside the parentheses
        while(findFirstPointOperator(findLastParenthesisOpen(head)) != NULL){
            //if a multiplication operator is found, multiply preceding number by the next number
            if(findFirstPointOperator(findLastParenthesisOpen(head)) -> Operator == '*'){
                findPrevious(head, findFirstPointOperator(findLastParenthesisOpen(head))) -> number *= findFirstPointOperator(findLastParenthesisOpen(head)) -> next -> number;
            //if a division operator is found, divide preceding number by the next number
            }else{
                //if next number is 0, divide by 1 instead
                if(findFirstPointOperator(findLastParenthesisOpen(head)) -> next -> number == 0){
                    findPrevious(head, findFirstPointOperator(findLastParenthesisOpen(head))) -> number /= 1;
                }else{
                    findPrevious(head, findFirstPointOperator(findLastParenthesisOpen(head))) -> number /= findFirstPointOperator(findLastParenthesisOpen(head)) -> next -> number;
                }
            }
            //delete next number and point operator
            deleteParticularNode(&head, findFirstPointOperator(findLastParenthesisOpen(head)) -> next);
            deleteParticularNode(&head, findFirstPointOperator(findLastParenthesisOpen(head)));

            //print the new list
            printf("\nResulting term: ");
            printList(head);
        }

        //run the loop until there are no more "dash operators" inside the parentheses
        while(findFirstDashOperator(findLastParenthesisOpen(head)) != NULL){
            //if an addition operator is found, add next number to the preceding number
            if(findFirstDashOperator(findLastParenthesisOpen(head)) -> Operator == '+'){
                findPrevious(head, findFirstDashOperator(findLastParenthesisOpen(head))) -> number += findFirstDashOperator(findLastParenthesisOpen(head)) -> next -> number;
            //if a subtraction operator is found, subtract next number from the preceding number
            }else{
                findPrevious(head, findFirstDashOperator(findLastParenthesisOpen(head))) -> number -= findFirstDashOperator(findLastParenthesisOpen(head)) -> next -> number;
            }
            //delete next number and dash operator
            deleteParticularNode(&head, findFirstDashOperator(findLastParenthesisOpen(head)) -> next);
            deleteParticularNode(&head, findFirstDashOperator(findLastParenthesisOpen(head)));

            //print the new list
            printf("\nResulting term: ");
            printList(head);
        }
        //once there is no more point or dash operator inside the parentheses, only a single number is inside the parentheses
        //we can eliminate the parentheses, by deleting the nodes before and after the number
        deleteParticularNode(&head, findLastParenthesisOpen(head) -> next -> next);
        deleteParticularNode(&head, findLastParenthesisOpen(head));
    }

    //once all parentheses got eliminated, we can search for point operators between the remaining numbers
    while(findFirstPointOperator(head) != NULL){
        if(findFirstPointOperator(head) != NULL && findFirstPointOperator(head) -> Operator == '*'){
            findPrevious(head, findFirstPointOperator(head)) -> number *= findFirstPointOperator(head) -> next -> number;
        }else{
            if(findFirstPointOperator(head) -> next -> number == 0){
                findPrevious(head, findFirstPointOperator(head)) -> number /= 1;
            }else{
                findPrevious(head, findFirstPointOperator(head)) -> number /= findFirstPointOperator(head) -> next -> number;
            }
        }
        deleteParticularNode(&head, findFirstPointOperator(head) -> next);
        deleteParticularNode(&head, findFirstPointOperator(head));

        printf("\nResulting term: ");
        printList(head);
    }

    //once all point operators got eliminated between the remaining numbers, we can look for dash operators
    while(findFirstDashOperator(head) != NULL){
        if(findFirstDashOperator(head) != NULL && findFirstDashOperator(head) -> Operator == '+'){
            findPrevious(head, findFirstDashOperator(head)) -> number += findFirstDashOperator(head) -> next -> number;
        }else{
            findPrevious(head, findFirstDashOperator(head)) -> number -= findFirstDashOperator(head) -> next -> number;
        }
        deleteParticularNode(&head, findFirstDashOperator(head) -> next);
        deleteParticularNode(&head, findFirstDashOperator(head));

        printf("\nResulting term: ");
        printList(head);
    }

    //finally, we will delete the result of the operation, the only remaining node from the list
    deleteParticularNode(&head, head);
    /*
    printList(head);
    if(head == NULL){
        printf("\nList deleted successfully!");
        printf("\nEnd of program!");
    }
    */
    return 0;
}
