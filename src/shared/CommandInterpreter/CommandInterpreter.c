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
    CommandsNode *Node = FindInChildNodes(RootNode, SubCommands, 1, 0);
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
    while(SearchNode != NULL) {
        if(strcmp(SearchNode->CommandText,*SplittedCommandText) == 0) {
            if(((int)*(SplittedCommandText + 1)) == 0) // this is the last part in command text
                return SearchNode;
            else 
                return FindInChildNodes(SearchNode, SplittedCommandText + 1, CreateIfNotFound, ++FoundSteps);
        }

        if(SearchNode->NextNode != NULL)
            SearchNode = SearchNode->NextNode;
        else
            break;
    }

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
        else
            return FindInChildNodes(SearchNode, SplittedCommandText + 1, CreateIfNotFound, ++FoundSteps);
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
    int *ParamStep = 0;
    CommandsNode *Node = FindInChildNodes(RootNode, SubCommands, 0, ParamStep);
    if(Node == NULL || Node->Hook == NULL)
        printf("Command Not  Found!\n");
    else
        (*Node->Hook)("", "");
    free(SubCommands);
}

void CommandsHelp(char** CommandParams, char* HookParams) {
    printf("Help goes here!\n");
}