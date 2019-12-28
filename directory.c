#include "file.c"
#include "list.c"
#define strEqu(BUFFER, STR) strcmp(BUFFER, STR) == 0
#define TRUE    1
#define FALSE   0

#define DIRECTORY_NAME_MAX  100

// TODO: . and ..

struct directory
{
    char *name;
    char *path;
    struct directory *previousDirectory;
    struct node *listFiles;
    struct node *listDirectories;
    long int size;
}typedef directory;

// Returns 0 if name doesn't exists, else 1
int directory_is_name_exists(directory *dir, char *str){
    for(node *ptr = dir->listDirectories; ptr != NULL; ptr = ptr->next){
        if(strEqu(((directory *)(ptr->value))->name, str))
            return TRUE;
    }

    for(node *ptr = dir->listFiles; ptr != NULL; ptr = ptr->next){
        if(strEqu(((file *)(ptr->value))->name, str))
            return TRUE;
    }
    
    return FALSE;
}

// returns 0 on sucsess, else 1
int directory_add_file(directory *dir, file *f){
    if (directory_is_name_exists(dir, f->name) == 0)
    {
        dir->listFiles = list_add(dir->listFiles, f);
        dir->size += f->length;
        return 0;
    }
    return 1;
}

// returns 0 on sucsess, else 1
int directory_add_directory(directory *dir, directory *d){
    if (directory_is_name_exists(dir, d->name) == 0)
    {
        // TODO: TEST
        dir->listDirectories = list_add(dir->listDirectories, d);
        return 0;
    }
    return 1;
}

directory *directory_initialize(directory *parent, char *name){
    // TODO: assert user's not trying to add / directory
    // TODO: assert name is valid

    directory *temp = (directory *)malloc(sizeof(directory));
    
    char *newName = (char *)malloc(strlen(name) + 1);
    strcat(newName, name);
    strcat(newName, "\00");
    temp->name = newName;

    temp->previousDirectory = parent;
    temp->listDirectories = NULL;
    temp->listFiles = NULL;
    temp->size = 0;

    // parent/name
    // TODO: optimize
    temp->path = (char *)malloc(strlen(parent->name) + strlen(name) + 2);
    strcat(temp->path, parent->path);
    if(!(strEqu(parent->name, "/"))){
        strcat(temp->path, "/");
    }
    strcat(temp->path, name);
    strcat(temp->path, "\00");

    directory_add_directory(parent, temp);

    return temp;
}
