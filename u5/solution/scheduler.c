//Von Thore Brehmer und Jonny Lam
#include <stdlib.h>

#include "scheduler.h"

struct Process* rr(struct Process* head, struct Process* current) {

	if (head->next==head){return NULL;}					//Falls leere Liste
	else if (current == NULL){return head->next;}		//Falls es kein current gibt, Der erste Process ist head->next
	
    //Sonst: Sucht nach einem Process neben sich, 
    //geht die Liste maximal einmal durch
    //solange es ein Prozess cycles_todo>0 gibt
    struct Process* stop = current;
    while ((current = current->next) != stop || stop->cycles_todo>0) 
    {
        if (current->cycles_todo>0) {return current;}
    }
    return NULL;
    
	
}

struct Process* fcfs(struct Process* head, struct Process* current) {
	if (head->next==head){return NULL;}					//Falls leere Liste
    else if (current == NULL){return head->next;}		//Falls es kein current gibt, Der erste Process ist head->next
    
	//Sonst: finde den nächsten Prozess am Dummy,
	//welcher noch ausgeführt werden muss
    current = head;                                     
    while ( (current=current->next) != head )            
    {
        if (current->cycles_todo > 0) {return current;}
    }
    return NULL;
	
}

struct Process* spn(struct Process* head, struct Process* current) {
	if (head->next==head){return NULL;}					//Falls leere Liste
	else if (current == NULL){return head->next;}		//Falls es kein current gibt, Der erste Process ist head->next
   
    else if (current->cycles_todo>0){return current;}   //Derzeitiger Process wird bis zum Ende ausgeführt

   // Sonst: Sucht nach dem Process mit dem kleinsten cycles_todo Wert
   // Geht maximal einmal die Liste durch
    current = head;
    long unsigned int min_cycles_Int = (2^31) - 1;
    struct Process* min_cycles = NULL;
    while ((current = current->next) != head) 
    {
        if (current->cycles_todo > 0 && current->cycles_todo < min_cycles_Int) 
        {
            min_cycles_Int = current->cycles_todo; 
            min_cycles=current;
        }
    }

    return min_cycles;
    
}

struct Process* srt(struct Process* head, struct Process* current) {
    head = head;
    current = current;
	return NULL;
}

struct Process* hrrnPreemptive(struct Process* head, struct Process* current) {
	head = head;
    current = current;
	return NULL;
}

struct Process* hrrnNonPreemptive(struct Process* head, struct Process* current) {
    head = head;
    current = current;
	return NULL;
}

