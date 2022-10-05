#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "FunctionPointers.h"
#include "CommandInterpreter.h"
#include "banned.h"

#define MAX_NODES 256

typedef struct CommandsNode {
    char CommandText[COMMANDS_MAX_TOKENS_LENGTH];
    voidFnPtr3ParamCharPArrIntCharP Hook;
    char* HookParams;
    struct CommandsNode *ChildNode;
    struct CommandsNode *NextNode;
}CommandsNode;

CommandsNode *FindInChildNodes(CommandsNode *BaseNode, char Tokens[][COMMANDS_MAX_TOKENS_LENGTH], size_t TokensCount, int CreateIfNotFound, int *FoundSteps);
size_t getCommandTokensCount (char *CommandText);
void SplitByDot(char Tokens[][COMMANDS_MAX_TOKENS_LENGTH], char *CommandText);
void CommandsHelp(char CommandParams[][COMMANDS_MAX_TOKENS_LENGTH], size_t ParamsCount, char* HookParams);
void CreateRootNode(void);

CommandsNode *RootNode;
CommandsNode NodesList[MAX_NODES];
int FirstFreeNodeIndex = 0;





void CommandsRegister(char *CommandText, voidFnPtr3ParamCharPArrIntCharP CommandHook, char *HookParams) {
    size_t TokensCount = getCommandTokensCount(CommandText);
    char Tokens[TokensCount][COMMANDS_MAX_TOKENS_LENGTH];
    SplitByDot(Tokens, CommandText);
    int step = 0;
    CommandsNode *Node = FindInChildNodes(RootNode, Tokens, TokensCount, 1, &step);
    Node->Hook = CommandHook;
    Node->HookParams = HookParams;
}

voidFnPtr1ParamCharP CommandsInit(void) {
    CreateRootNode();
    CommandsRegister("help", &CommandsHelp, "");
    return &CommandsRun;
}


CommandsNode *RegisterNewNode(void) {
    //find first free node
    if(FirstFreeNodeIndex < MAX_NODES)
        return &NodesList[FirstFreeNodeIndex++];
    else
        return NULL;
}



void CreateRootNode(void) {
    RootNode = RegisterNewNode();
    RootNode->CommandText[0] = 0;
    RootNode->ChildNode = RootNode->NextNode = NULL;
    RootNode->Hook = NULL;
}

CommandsNode *FindInChildNodes(CommandsNode *BaseNode, char Tokens[][COMMANDS_MAX_TOKENS_LENGTH], size_t TokensCount, int CreateIfNotFound, int *FoundSteps) {
    CommandsNode *SearchNode = BaseNode->ChildNode;
    //search within childern of BaseNode
    while(SearchNode != NULL) {
        if(strcmp(SearchNode->CommandText,*Tokens) == 0) {
            if(TokensCount == 1){ // this is the last part in command text
                if(SearchNode->Hook != NULL || CreateIfNotFound)
                    return SearchNode;
                else
                    return NULL;
            }
            else {
                int tmpFoundStep = *FoundSteps;
                (*FoundSteps)++;
                CommandsNode *ChildResult = FindInChildNodes(SearchNode, Tokens + 1, TokensCount - 1, CreateIfNotFound, FoundSteps);
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
            BaseNode->ChildNode = RegisterNewNode();
            SearchNode = BaseNode->ChildNode;
        }
        else {
            SearchNode->NextNode = RegisterNewNode();
            SearchNode = SearchNode->NextNode;
        }
        strlcpy(SearchNode->CommandText, *Tokens, strlen(*Tokens) + 1);
        SearchNode->ChildNode = SearchNode->NextNode = NULL;
        SearchNode->Hook = NULL;

        if(TokensCount == 1) // this is the last part in command text
            return SearchNode;
        else {
            (*FoundSteps)++;
            return FindInChildNodes(SearchNode, Tokens + 1, TokensCount - 1, CreateIfNotFound, FoundSteps);
        }
    }
    else {
        return NULL;
    }

    return BaseNode;
}

void RemoveDoubleDot(char *String) {
    while(*String != 0) {
        if(*String == '.' && *(String + 1) == '.') {
            char *Pointer = String + 1;
            while(*Pointer != 0) {
                *Pointer = *(Pointer + 1);
                Pointer++;
            }
        }
        String++;
    }
}

size_t getCommandTokensCount (char *CommandText) {
    if(*CommandText == 0) return 0;

    size_t TokensCount = 1;
    while(*CommandText != 0) {
        if(*CommandText == '.') {
            if(*(CommandText + 1) == '.')
                CommandText++;
            else
                TokensCount++;
        } 
        CommandText++;
    }
    return TokensCount;
}

void SplitByDot(char Tokens[][COMMANDS_MAX_TOKENS_LENGTH], char *CommandText) {
    if(*CommandText == 0) return ;

    char *IndexPointer = CommandText;
    char *End = CommandText;
    int CommandIndex = 0;
    do {
        End++;
        if(*End == '.' || *End == '\0') {
            if(*End == '.' && *(End+1) == '.')
              End++;
            else {  
                int strSize = End - IndexPointer + 1;
                if(strSize > COMMANDS_MAX_TOKENS_LENGTH) strSize = COMMANDS_MAX_TOKENS_LENGTH;
                strlcpy(Tokens[CommandIndex], IndexPointer, strSize);
                RemoveDoubleDot(Tokens[CommandIndex]);
                IndexPointer = End + 1;
                CommandIndex++;
            }
        }
    } while(*End != 0);
}


void CommandsRun(char *Command) {
    size_t TokensCount = getCommandTokensCount(Command);
    char Tokens[TokensCount][COMMANDS_MAX_TOKENS_LENGTH];
    SplitByDot(Tokens, Command);
    int ParamStep = 0;
    CommandsNode *Node = FindInChildNodes(RootNode, Tokens, TokensCount, 0, &ParamStep);
    if(Node == NULL || Node->Hook == NULL)
        printf("Command Not  Found!\n");
    else {
        (*Node->Hook)((Tokens + ParamStep + 1), TokensCount - (ParamStep + 1), Node->HookParams);
    }
}


void printAvailableCommands(CommandsNode *BaseNode, char *PrependText) {
    while(BaseNode) {
        if(BaseNode->Hook != NULL)
            printf("\t* %s%s%s\n", PrependText, (strcmp(PrependText, "")? "." : ""), BaseNode->CommandText);
        if(strcasecmp(BaseNode->CommandText, "help") != 0 && BaseNode->ChildNode != NULL) {
            int NewPrependSize = strlen(PrependText) + strlen(BaseNode->CommandText);
            char tmpPrepend[ NewPrependSize + 1];
            snprintf(tmpPrepend, NewPrependSize, "%s%s%s", PrependText, (strcmp(PrependText, "")? "." : ""), BaseNode->CommandText);
            printAvailableCommands(BaseNode->ChildNode, tmpPrepend);
        }
        BaseNode = BaseNode->NextNode;
    }
}

void CommandsHelp(char CommandParams[][COMMANDS_MAX_TOKENS_LENGTH], size_t ParamsCount, char* HookParams) {
    printf("Available Commands:\n");
    printAvailableCommands(RootNode->ChildNode, "");
    printf("\nYou can get help for each command by typing help.[Command Name]\n");
}