#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "TIMER.h"
#include "CommandInterpreter/CommandInterpreter.h"
#include "banned.h"

#define MAX_TIMERS 256

void TimerStart (char CommandParams[][COMMANDS_MAX_TOKENS_LENGTH], size_t ParamsCount, char *HookParams);
void TimerStop  (char CommandParams[][COMMANDS_MAX_TOKENS_LENGTH], size_t ParamsCount, char *HookParams);
void TimerAdd   (char CommandParams[][COMMANDS_MAX_TOKENS_LENGTH], size_t ParamsCount, char *HookParams);
void TimerDelete(char CommandParams[][COMMANDS_MAX_TOKENS_LENGTH], size_t ParamsCount, char *HookParams);
void TimerShow  (char CommandParams[][COMMANDS_MAX_TOKENS_LENGTH], size_t ParamsCount, char *HookParams);
void TimerHelp  (char CommandParams[][COMMANDS_MAX_TOKENS_LENGTH], size_t ParamsCount, char *HookParams);

void TimerCallBack(void);

typedef struct TimerList {
    char *Name;
    int Interval;
    int RepeatCount;
    char *Command;
    int NextTick;
} TimerList;

TimerList TimersList[MAX_TIMERS];
int FreeTimersList [MAX_TIMERS / sizeof(int) + 1];
#define isTimerFree(i) (FreeTimersList[i / sizeof(int)] & (1 << i % sizeof(int)))
#define setTimerFree(i) (FreeTimersList[i / sizeof(int)] &= ~(1 << i % sizeof(int)))
#define setTimerInUse(i) (FreeTimersList[i / sizeof(int)] |= (1 << i % sizeof(int)))

void TimerModuleInit(void) {
    CommandsRegister("timer.start", &TimerStart, "");
    CommandsRegister("timer.stop", &TimerStop, "");
    CommandsRegister("timer.add", &TimerAdd, "");
    CommandsRegister("timer.delete", &TimerDelete, "");
    CommandsRegister("timer.list", &TimerShow, "");
    CommandsRegister("help.timer", &TimerHelp, "");
}

void _TimerDelete(int i) {
    TimersList[i].Interval = TimersList[i].NextTick = 0;
    setTimerFree(i);
}

void TimerCallBack(void) {
    TimerList *LoopTimer;
    for(int i = 0; i < MAX_TIMERS; i++) {
        if(!isTimerFree(i)) {
            LoopTimer = &TimersList[i];
            if(--LoopTimer->NextTick == 0) {
                LoopTimer->NextTick = LoopTimer->Interval;
                printf("Timer '%s' Triggered!\n", LoopTimer->Name);
                CommandsRun(LoopTimer->Command);
                if(LoopTimer->RepeatCount != 0 && --LoopTimer->RepeatCount == 0) {
                    //delete timer
                    _TimerDelete(i);
                }
            }
        }
    }
}

void TimerStart(char CommandParams[][COMMANDS_MAX_TOKENS_LENGTH], size_t ParamsCount, char *HookParams) {
    EnableTimer1(&TimerCallBack, 1);
}

void TimerStop(char CommandParams[][COMMANDS_MAX_TOKENS_LENGTH], size_t ParamsCount, char *HookParams) {
    DisableTimer1();

    for(int i = 0; i < MAX_TIMERS; i++) {
        if(!isTimerFree(i)) {
            TimersList[i].NextTick = 0;
        }
    }
}

void TimerAdd(char CommandParams[][COMMANDS_MAX_TOKENS_LENGTH], size_t ParamsCount, char *HookParams) {
    TimerList *NewTimer = NULL;
    for(int i = 0; i < MAX_TIMERS; i++) {
        if(isTimerFree(i)) {
            setTimerInUse(i);
            NewTimer = &TimersList[i];
            break;
        }
    }
    if(NewTimer != NULL) {
        NewTimer->Name = *CommandParams;
        NewTimer->Interval = NewTimer->NextTick = atoi(*(CommandParams + 1));
        NewTimer->RepeatCount = atoi(*(CommandParams + 2));
        NewTimer->Command = *(CommandParams + 3);    
        
        printf("Timer Added!\n");
    }
    else {
        printf("Timer Overflow!!!\n");
    }
}

void TimerDelete(char CommandParams[][COMMANDS_MAX_TOKENS_LENGTH], size_t ParamsCount, char *HookParams) {
    for(int i = 0; i < MAX_TIMERS; i++) {
        if(!isTimerFree(i) && strcmp(TimersList[i].Name, *CommandParams) == 0) {
            _TimerDelete(i);
            printf("Timer Deleted!\n");
            return;
        }
    }
}

void TimerShow(char CommandParams[][COMMANDS_MAX_TOKENS_LENGTH], size_t ParamsCount, char *HookParams) {
//    if(FirstTimer == NULL) {
//        printf("No Timer defined!\n");
//        return;
//    }

    TimerList *LoopTimer = NULL;
    for(int i = 0; i < MAX_TIMERS; i++) {
        if(!isTimerFree(i)) {
            LoopTimer = &TimersList[i];
            printf("Name:\t\t\t%s\n", LoopTimer->Name);
            printf("Interval:\t\t%dms\n", LoopTimer->Interval);
            printf("Running Command:\t%s\n", LoopTimer->Command);
            printf("Remained Ticks:\t\t%d\n", LoopTimer->RepeatCount);
            printf("= = = = = = = = = = = = = = = = = = = = =\n");
        }
    }
}

void TimerHelp(char CommandParams[][COMMANDS_MAX_TOKENS_LENGTH], size_t ParamsCount, char *HookParams) {
    printf("Timer help:\n");
    printf("Add Timer: timer.add.[Timer Name].[Interval in ms].[Repeat Count].[Command]\n");
    printf("Note that to type commands use double . instead of single dot!\n");
    printf("Timer help:\n");
    printf("Timer help:\n");
}
