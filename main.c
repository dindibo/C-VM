#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include "list.c"
//#include "file.c"
#include "directory.c"


#define newInt(NAME, X) int *NAME = (int *)malloc(sizeof(int));*NAME = X;
#define strEqu(BUFFER, STR) strcmp(BUFFER, STR) == 0


#define  BUFFER_SIZE    1000

#define  COMMAND_EXIT       "exit"
#define  COMMAND_LIST       "ls"
#define  COMMAND_MKDIR      "mkdir"
#define  COMMAND_PWD        "pwd"
#define  COMMAND_CD         "cd"

// TODO: Fix ls duplication
void cmds_ls(directory *dir){
    printf("\033[0;34m");    
    for(node *ptr = dir->listDirectories; ptr != NULL; ptr = ptr->next){
        printf("%s\n", ((directory *)(ptr->value))->name);
    }
    printf("\033[0m");    
    for(node *ptr = dir->listFiles; ptr != NULL; ptr = ptr->next){
        printf("%s\n", ((file *)(ptr->value))->name);
    }
}

//#define TEST_LIST
#define TEST_DIR


// < ------------------------------------------------   <SHELL> ------------------------------------------------ >


struct shell
{
    directory *currentWorkingDirectory;
}typedef shell;

shell *shell_initialize(){
    shell *temp = (shell *)malloc(sizeof(shell));
    temp->currentWorkingDirectory = NULL;
    return temp;
}

void cmd_ls(directory *dir){
    printf("[0;34m");
    for(node *ptr = dir->listDirectories; ptr != NULL; ptr = ptr->next){
        printf("Hello");
    }
}

void shell_cmd_pwd(shell *this){
    printf("%s\n", this->currentWorkingDirectory->path);
}

int shell_cmd_cd(shell *s, char *tempName){
    directory *target = NULL;

    if(strEqu(tempName, ".")){
        return 0;
    }
    else if (strEqu(tempName, "..") || strEqu(tempName, "../"))
    {
        target = s->currentWorkingDirectory->previousDirectory;
    }
    else{
        for(node *ptr = s->currentWorkingDirectory->listDirectories; (ptr != NULL) && (target == NULL); ptr = ptr->next){
            if( strEqu(((directory *)ptr->value)->name, tempName) ){
                target = (directory *)(ptr->value);
            }
        }
    }

    if(target == NULL){
        printf("Directory \"%s\" Does not exists\n", tempName);
        return -1;
    }

    s->currentWorkingDirectory = target;
    return 0;
}

int shell_interpret_cmd(shell *s){

    printf("> ");
    char buffer[BUFFER_SIZE];
    scanf("%s", buffer);

    if(strEqu(buffer, COMMAND_LIST)){
        cmds_ls(s->currentWorkingDirectory);
        return 0;
    }
    else if (strEqu(buffer, COMMAND_MKDIR))
    {
        char tempName[DIRECTORY_NAME_MAX];
        scanf("%s", tempName);

        // allocate new string on heap
        char *dirName = (char *)malloc(strlen(tempName) + 1);
        // copy string, null terminate
        strcpy(dirName, tempName);
        strcat(dirName, "\00");
        
        directory_initialize(s->currentWorkingDirectory, dirName);

        return 0;
    }
    else if (strEqu(buffer, COMMAND_PWD))
    {
        shell_cmd_pwd(s);

        return 0;
    }
    else if (strEqu(buffer, COMMAND_CD))
    {
        char tempName[DIRECTORY_NAME_MAX];
        scanf("%s", tempName);

        shell_cmd_cd(s, tempName);

        return 0;
    }
    else if (strEqu(buffer, COMMAND_EXIT))
    {
        return 1;
    }
    else
    {
        printf("%s : Command not found\n", buffer);
        return -1;
    }

}

int shell_interact(shell *s){
    int result = shell_interpret_cmd(s);

    while (result != 1)
    {
        result = shell_interpret_cmd(s);
    }
    
    return 0;
}


// < ------------------------------------------------   </SHELL>    ------------------------------------------------ >


// < ------------------------------------------------   <GLOBALS">   ------------------------------------------------ >


shell *active_shell;
directory *root;


// < ------------------------------------------------   </GLOBALS>  ------------------------------------------------ >


void file_info(file f){
    printf("{%s : %ld}\n", f.name, f.length);
}

void initialize(){
    root = (directory *)malloc(sizeof(directory));
    root->name = "/";
    root->path = "/";
    root->listDirectories = NULL;
    root->listFiles = NULL;
    root->previousDirectory = root;
    root->size = 0;

    active_shell = shell_initialize();
    active_shell->currentWorkingDirectory = root;
}

void foo(){
    directory_initialize(root, "a");
    directory_initialize(root, "b");
}

int main(){
    /*
    #ifdef TEST_LIST
    node *head = list_initialize();

    newInt(val0, 10)
    newInt(val1, 20)
    newInt(val2, 30)
    newInt(val3, 40)

    head = list_add(head, val0);
    head = list_add(head, val1);
    head = list_add(head, val2);
    head = list_add(head, val3);
    
    for(node *ptr = head; ptr != NULL; ptr = ptr->next){
        printf("%d\n", *((int *)(ptr->value)));
    }
    #endif
    #ifdef TEST_DIR

    file *f1 = file_initialize("note1.txt", "Hello world", 12);
    file *f2 = file_initialize("note2.txt", "very nice", 10);

    directory d;

    // initialize dir
    d.name = "/";
    d.previousDirectory = &d;
    d.listDirectories = list_initialize();
    d.listFiles = list_initialize();
    d.size = 0;
    
    // add files
    directory_add_file(&d, f1);
    directory_add_file(&d, f2); 


    // access files
    //file_info(*((file *)(d.listFiles->next->value)));

    directory d2;
    d2.name = "media";
    d2.previousDirectory = &d;
    d2.size = 0;
    d2.listFiles = NULL;
    d2.listDirectories = NULL;

    d.listDirectories = list_add(d.listDirectories, &d2);

    #endif


    // < ------------------------------------------------ >


    //cmds_ls(&d);

    shell active_shell;
    active_shell.currentWorkingDirectory = &d;

    shell_interact(&active_shell);*/

    initialize();

    //directory *media = directory_initialize(root, "media");
    //directory_initialize(root, "asd");

    //printf("%s\n", ((directory*)((root->listDirectories)->value))->name );
    
    shell_interact(active_shell);

    /*cmds_ls(root);
    shell_cmd_cd(active_shell, "media");

    printf("%d\n", media == active_shell->currentWorkingDirectory->listDirectories);*/

}
