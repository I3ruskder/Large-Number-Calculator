#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Creating nodes that hold numbers */
struct multiplier1{
	int number;
	int index;
	struct multiplier1 *next;
};
struct multiplier2{
	int number;
	int index;
	struct multiplier2 *next;
};
struct product{
	int number;
	int index;
	struct product *next;
	struct product *prev;
};
struct multiplier1 *head1 = NULL;
struct multiplier1 *current1 = NULL;

struct multiplier2 *head2 = NULL;
struct multiplier2 *current2 = NULL;

struct product *head3 = NULL;
struct product *current3 = NULL;
struct product *last = NULL;
/*             ****************************************************************                           */

bool isEmpty() {
   return head3 == NULL;
}

void insertMultiplier1(int index, int number) {
   struct multiplier1 *connect = (struct multiplier1*) malloc(sizeof(struct multiplier1));
	
   connect->index = index;
   connect->number = number;
   

   connect->next = head1;
	

   head1 = connect;
}

void insertMultiplier2(int index, int number) {
   struct multiplier2 *connect = (struct multiplier2*) malloc(sizeof(struct multiplier2));
	
   connect->index = index;
   connect->number = number;
	

   connect->next = head2;
	

   head2 = connect;
}


void insertProduct(int index, int number) {
   struct product *connect = (struct product*) malloc(sizeof(struct product));
   
   connect->index = index;
   connect->number = number;
	
   if(isEmpty()) {
   	
      last = connect;
   } else {

      head3->prev = connect;
   }


   connect->next = head3;
	

   head3 = connect;
}

struct product* deleteFirst() {
   struct product *tempLink = head3;
	
   while(head3->number==0){
	if(head3->next == NULL){
      last = NULL;
   } else {
      head3->next->prev = NULL;
   }
	
   head3 = head3->next;
	}
   return;
}


void add(int index,int number) {
   struct product* current3 = head3;
   struct product* previous = NULL;
	

   if(head3 == NULL) {
   		return;
   }


   while(current3->index != index) {

 
      if(current3->next == NULL) {
         return;
      } else {
    
         previous = current3;
        
         current3 = current3->next;
      }
   }

   	current3->number+= number;
   	
	if(current3->number >= 10){
		
		add(index+1, current3->number /10);
		current3->number = current3->number %10;
		
	}
	
}
void printList() {
   FILE *op = fopen("output.txt","a");
   
   struct product *ptr = head3;
	 fprintf(op,"\n");

   while(ptr != NULL) {
   		if(ptr->number || ptr->number == 0){
   			fprintf(op,"%d",ptr->number);
		   }  			
        ptr = ptr->next;
   }
   fclose(op);
}

void multiply(){
	struct multiplier1 *current1;
  	struct multiplier2 *current2;
	struct product *current3;
	
	int i,j=0;
	
	
	for(current2 = head2; current2 != NULL; current2 = current2->next) {
		
      	for(current1 = head1; current1 != NULL; current1 = current1->next) {
      		
      		i++; 
      		add(i+j,current1->number * current2->number);
		}
		
		i=0;
		j++;
   }
   
}

int main(int argc, char *argv[]) {
	FILE *fp,*op;
	char holder;
    int i,j=1;
    int line = 0;
    
    fp=fopen("input.txt", "r");
    op=fopen("output.txt", "w");
    
    
    while((holder=fgetc(fp)) != EOF) {
    	
        if(holder == '\n') 
			line++;
			
        if(line == 1){
        	fprintf(op,"\n");
        	break;
		} 
		
    	insertMultiplier1(i,(int)(holder - '0'));
    	
    	fprintf(op,"%d",(int)(holder - '0'));
    	
    	insertProduct(i+j,0);
    	i++;
    }      
    while((holder=fgetc(fp)) != EOF && (holder != '\n' )) { 
    
        insertMultiplier2(j,(int)(holder - '0'));
        
        fprintf(op,"%d",(int)(holder - '0'));
        
        insertProduct(i+j,0);
        j++;
    }
    
    fclose(fp);
    fclose(op);
		
	multiply();
	
	deleteFirst();
	
    printList();
    
	return 0;
}
