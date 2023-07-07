//Von Thore Brehmer und Jon Lam
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#define MEM_SIZE 1024

char memory[MEM_SIZE];
struct node *head;
struct node *last;

struct node 
{
    size_t size;
    struct node *next;
};


void memory_init()
{
    puts("init memory...");
    head = (struct node*) &memory[0];
    last = ((struct node*) &memory[MEM_SIZE]) - 1;
    
    head->size=0;
    head->next=last;
    last->next=NULL;
}


void* memory_allocate(size_t byte_count)
{
    printf("allocate memory...(%lu bytes)\n",byte_count); 
    struct node *current = head;
    byte_count = (size_t)(16*ceil(byte_count /16.0));   // Nimmt für byte_count ein vielfaches von 16
    
    
    while(current->next!=NULL)
    {
        if( ( (((current->next - current)-1)*sizeof(struct node)) >= byte_count && current->size==0 ))
        {
            if ((((current->next - current)-1)*sizeof(struct node)) == byte_count)
            {
                current->size= byte_count;
                return current + 1;           
            }
            
            struct node *new = (current + 1) + byte_count/16; 
            new->next=current->next;
            new->size=0;
            
            current->next=new;
            current->size= byte_count;
            
            return current + 1;
        }
        
        
        current=current->next;
    }
    fprintf(stdout,"Fehler, Speicher ist zu groß\n");
    return NULL;
}


void memory_free(void *pointer)
{
    puts("free memory...");  
    if ((head+1)==pointer)
    {
        head->size=0;
        if (head->next->size==0){head->next=head->next->next;}
        return;
    }
     
    struct node *prev = head;
    while((prev->next + 1) != pointer)
    {
        if (prev->next==NULL){fprintf(stdout,"Fehler, diesen Pointer gibt es nicht\n"); return;}
        prev=prev->next;   
    }
    
    struct node *current=prev->next;
    
    current->size=0;
    
    if (current->next->size==0){current->next=current->next->next;}
    if (prev->size==0){prev->next=prev->next->next;}
    
}


void memory_print()
{
    struct node *current = head;
    while(current->next!=NULL)
        {
        if (current->size==0){printf (" |   %ld   | ",((current->next-current)-1) * sizeof(struct node));}
        else {printf (" |xxx %ld xxx| ",current->size);}
        
        current=current->next;
        }
        puts("\n");
}


int main (void)
{
    memory_init();
    memory_print();   
    
    void *pointer = memory_allocate(30);
    memory_print();
     
    void *pointer2 = memory_allocate(100);
    memory_print();
        
    memory_free(pointer);
    memory_print();
        
    //Fall, Speicher genau so groß wie Lücke zwischen zwei Nodes
    void *pointer3 = memory_allocate(32);   
    memory_print();
       
    memory_free(pointer3);
    memory_print();  
     
    //Fall, Speicher kleiner als die Lücke zwischen zwei Nodes
    void *pointer4 = memory_allocate(16);   
    memory_print();   

    //Fall, Werden alle Nodes "gelöscht?"
    void *pointer5 = memory_allocate(16);   
    memory_print();  
    
    memory_free(pointer2);
    memory_print();
    
    memory_free(pointer5);
    memory_print();
    
    memory_free(pointer4);
    memory_print();
      
}