#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "FunctionPointers.h"

typedef struct CommandsNode {
    char* CommandText;
    voidFnPtr2ParamCharPPCharP Hook;
    char* HookParams;
    struct CommandsNode *ChildNode;
    struct CommandsNode *NextNode;
}CommandsNode;

void CommandsRun(char*);
CommandsNode *FindInChildNodes(CommandsNode *BaseNode, char **SplittedCommandText, int CreateIfNotFound, int *FoundSteps);
char **SplitByDot(char *CommandText);
void CommandsHelp(char** CommandParams, char* HookParams);
void CreateRootNode(void);

CommandsNode *RootNode;





void CommandsRegister(char *CommandText, voidFnPtr2ParamCharPPCharP CommandHook, char *HookParams) {
    char **SubCommands = SplitByDot(CommandText);
    int step = 0;
    CommandsNode *Node = FindInChildNodes(RootNode, SubCommands, 1, &step);
    Node->Hook = CommandHook;
    Node->HookParams = HookParams;
}

voidFnPtr1ParamCharP CommandsInit(void) {
    CreateRootNode();
    CommandsRegister("help", &CommandsHelp, "");
    return &CommandsRun;
}





void CreateRootNode(void) {
    RootNode = (CommandsNode*)malloc(sizeof(CommandsNode));
    RootNode->CommandText = "";
    RootNode->ChildNode = RootNode->NextNode = NULL;
    RootNode->Hook = NULL;
}

CommandsNode *FindInChildNodes(CommandsNode *BaseNode, char **SplittedCommandText, int CreateIfNotFound, int *FoundSteps) {
    CommandsNode *SearchNode = BaseNode->ChildNode;
    //search within childern of BaseNode
    while(SearchNode != NULL) {
        if(strcmp(SearchNode->CommandText,*SplittedCommandText) == 0) {
            if(((int)*(SplittedCommandText + 1)) == 0){ // this is the last part in command text
                if(SearchNode->Hook != NULL || CreateIfNotFound)
                    return SearchNode;
                else
                    return NULL;
            }
            else {
                int tmpFoundStep = *FoundSteps;
                (*FoundSteps)++;
                CommandsNode *ChildResult = FindInChildNodes(SearchNode, SplittedCommandText + 1, CreateIfNotFound, FoundSteps);
                if(ChildResult != NULL || CreateIfNotFound)
                    return ChildResult;
                else {
                    *FoundSteps = tmpFoundStep;
                    if(SearchNode->Hook != NULL)
                        return SearchNode;
                    else
                        return NULL;
                }
            }
        }

        if(SearchNode->NextNode != NULL)
            SearchNode = SearchNode->NextNode;
        else
            break;
    }
    //Node Not Found
    if(CreateIfNotFound) {
        if(SearchNode == NULL) {
            BaseNode->ChildNode = (CommandsNode*)malloc(sizeof(CommandsNode));
            SearchNode = BaseNode->ChildNode;
        }
        else {
            SearchNode->NextNode = (CommandsNode*)malloc(sizeof(CommandsNode));
            SearchNode = SearchNode->NextNode;
        }
        SearchNode->CommandText = *SplittedCommandText;
        SearchNode->ChildNode = SearchNode->NextNode = NULL;
        SearchNode->Hook = NULL;

        if(((int)*(SplittedCommandText + 1)) == 0) // this is the last part in command text
            return SearchNode;
        else {
            (*FoundSteps)++;
            return FindInChildNodes(SearchNode, SplittedCommandText + 1, CreateIfNotFound, FoundSteps);
        }
    }
    else {
        return NULL;
    }

    return BaseNode;
}

char **SplitByDot(char *CommandText) {
    if(*CommandText == 0) return 0;

    char *Start = CommandText;
    int CommandSections = 1;
    while(*Start != 0) {
        if(*Start == '.') CommandSections++;
        Start++;
    }

    Start = CommandText;
    char *End = CommandText;
    char **SubCommands = (char**)calloc(CommandSections + 1, sizeof(char*));
    char **CommandIndex = SubCommands;
    do {
        End++;
        if(*End == '.' || *End == '\0') {
            int strSize = End - Start;
            *CommandIndex = (char*)calloc(strSize + 1, sizeof(char));
            strncpy(*CommandIndex, Start, strSize);
            Start = End + 1;
            CommandIndex++;
        }
    } while(*End != 0);
    *CommandIndex = 0;//??????????????????????
    return SubCommands;
}


void CommandsRun(char *Command) {
    char **SubCommands = SplitByDot(Command);
    int ParamStep = 0;
    CommandsNode *Node = FindInChildNodes(RootNode, SubCommands, 0, &ParamStep);
    if(Node == NULL || Node->Hook == NULL)
        printf("Command Not  Found!\n");
    else {
        (*Node->Hook)((SubCommands + ParamStep + 1), Node->HookParams);
    }
    free(SubCommands);
}


void printAvailableCommands(CommandsNode *BaseNode, char *PrependText) {
    while(BaseNode) {
        if(BaseNode->Hook != NULL)
            printf("\t* %s%s%s\n", PrependText, (strcmp(PrependText, "")? "." : ""), BaseNode->CommandText);
        if(strcasecmp(BaseNode->CommandText, "help") != 0 && BaseNode->ChildNode != NULL) {
            char tmpPrepend[strlen(PrependText) + strlen(BaseNode->CommandText) + 1];
            sprintf(tmpPrepend, "%s%s%s", PrependText, (strcmp(PrependText, "")? "." : ""), BaseNode->CommandText);
            printAvailableCommands(BaseNode->ChildNode, tmpPrepend);
        }
        BaseNode = BaseNode->NextNode;
    }
}

void CommandsHelp(char** CommandParams, char* HookParams) {
    printf("Available Commands:\n");
    printAvailableCommands(RootNode->ChildNode, "");
    printf("\nYou can get help for each command by typing help.[Command Name]\n");
}