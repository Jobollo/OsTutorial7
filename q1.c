#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

typedef struct{
	char name[256];
	int priority,pid,runtime;
}proc;
typedef struct node{
    proc process;
    struct node* next;
}node_t;
node_t * head = NULL;
node_t * tail = NULL;
node_t * new_node;

void push(proc process) {
    node_t * new_node;
    new_node = malloc(sizeof(node_t));

    new_node->process = process;
    new_node->next = NULL;
    if(head == NULL && tail == NULL){
	head = tail = new_node;
	return;
    }
    tail->next = new_node;
    tail = new_node;
}
void print_list() {
    node_t * current = head;

    while (current != NULL) {
        printf("%s, %d, %d, %d\n", current->process.name,current->process.priority,current->process.pid,current->process.runtime);
        current = current->next;
    }
}


int main(void)
{
	char buffer[1024];
	FILE *fp;
	fp = fopen("processes.txt", "r");
	const char s[2] = ", ";
	char *token;
	int i;
	char* data;
	proc process;
	if(fp != NULL)
	{
		while(fgets(buffer, sizeof buffer, fp) != NULL)
		{
		    data = strdup(buffer);
		    token = strtok(data, s);
		    for(i=0;i<4;i++)
		    {
			if(i==0)
			{   
			    strcpy(process.name,token);
			    token = strtok(NULL,s);
			} else if (i==1){
			    process.priority = atoi(token);
			    token = strtok(NULL,s);
			}else if (i==2){
			    process.pid = atoi(token);
			    token = strtok(NULL,s);
			}else if (i==3){
			    process.runtime = atoi(token);
			    token = strtok(NULL,s);
			}                     
		    }
		    push(process);
		}
		fclose(fp);
	} else {
	perror("processes.txt");
	}   
	print_list();
}   







