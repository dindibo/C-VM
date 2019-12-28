#include <stdlib.h>

struct file
{
    char *name;
    long int length;
    char *data;
}typedef file;

// initializes a file in the Heap, caller's responsible for freeing space
file *file_initialize(char *name, char *data, int length){
    file *temp = (file *)malloc(sizeof(file));
    temp->data = data;
    temp->length = length;
    temp->name = name;
    return temp;
}