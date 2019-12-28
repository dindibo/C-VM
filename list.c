#include<stdlib.h>

struct node
{
    void *value;
    struct node *next;
}typedef node;


node *node_initialize(void *value){
    node *temp = (node *)malloc(sizeof(node));
    temp->next = NULL;
    temp->value = value;
    return temp;
}

node *list_initialize(){
    return NULL;
}

node *list_add(node *head, void *value){
    // if list is new
    if (head == NULL)
    {
        head = node_initialize(value);
    }
    else
    {
        node *temp = node_initialize(value);
        temp->next = head;
        head = temp;
    }
    
    return head;
}