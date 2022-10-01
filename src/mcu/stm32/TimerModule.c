#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "TIMER.h"
#include "CommandInterpreter/CommandInterpreter.h"

void TimerStart(char **CommandParams, char *HookParams);
void TimerStop(char **CommandParams, char *HookParams);
void TimerAdd(char **CommandParams, char *HookParams);
void TimerDelete(char **CommandParams, char *HookParams);
void TimerShow(char **CommandParams, char *HookParams);
void TimerHelp(char **CommandParams, char *HookParams);

void TimerCallBack(void);

typedef struct TimerList {
    char *Name;
    int Interval;
    int RepeatCount;
    char *Command;
    int NextTick;
    struct TimerList *NextTimer;
    struct TimerList *PrevTimer;
} TimerList;

TimerList *Timers, *LastTimer;


void TimerModuleInit(void) {
    Timers = LastTimer = NULL;
    CommandsRegister("timer.start", &TimerStart, "");
    CommandsRegister("timer.stop", &TimerStop, "");
    CommandsRegister("timer.add", &TimerAdd, "");
    CommandsRegister("timer.delete", &TimerDelete, "");
    CommandsRegister("timer.list", &TimerShow, "");
    CommandsRegister("help.timer", &TimerHelp, "");
}

void _TimerDelete(TimerList *TheTimer) {
    if(LastTimer == TheTimer)
        LastTimer = TheTimer->PrevTimer;

    if(Timers == TheTimer) {
        Timers = TheTimer->NextTimer;
        if(Timers != NULL)
            Timers->PrevTimer = NULL;
    }
    else
        TheTimer->PrevTimer->NextTimer = TheTimer->NextTimer;
    free(TheTimer);
}

void TimerCallBack(void) {
    if(Timers == NULL)
        return;
    
    TimerList *LoopTimer = Timers;
    while(LoopTimer != NULL) {
        if(--LoopTimer->NextTick == 0) {
            LoopTimer->NextTick = LoopTimer->Interval;
            printf("Timer '%s' Triggered!\n", LoopTimer->Name);
            CommandsRun(LoopTimer->Command);
            if(LoopTimer->RepeatCount != 0 && --LoopTimer->RepeatCount == 0) {
                //delete timer
                TimerList *NextTimer = LoopTimer->NextTimer;
                _TimerDelete(LoopTimer);
                LoopTimer = NextTimer;
                continue;
            }
        }
        LoopTimer = LoopTimer->NextTimer;
    }
}

void TimerStart(char **CommandParams, char *HookParams) {
    EnableTimer1(&TimerCallBack, 1);
}

void TimerStop(char **CommandParams, char *HookParams) {
    DisableTimer1();

    TimerList *LoopTimer = Timers;
    while(LoopTimer != NULL) {
        LoopTimer->NextTick = 0;
        LoopTimer = LoopTimer->NextTimer;
    }
}

void TimerAdd(char **CommandParams, char *HookParams) {
    TimerList *NewTimer = (TimerList *)malloc(sizeof(TimerList));
    NewTimer->Name = *CommandParams;
    NewTimer->Interval = NewTimer->NextTick = atoi(*(CommandParams + 1));
    NewTimer->RepeatCount = atoi(*(CommandParams + 2));
    NewTimer->Command = *(CommandParams + 3);    
    NewTimer->NextTimer = NULL;
    
    if(LastTimer == NULL) {//no timer defined yet
        NewTimer->PrevTimer = NULL;
        Timers = LastTimer = NewTimer;
    }
    else {
        NewTimer->PrevTimer = LastTimer;
        LastTimer->NextTimer = NewTimer;
        LastTimer = NewTimer;
    }
    printf("Timer Added!\n");
}

void TimerDelete(char **CommandParams, char *HookParams) {
    if(Timers == NULL) {
        printf("No Timer to Delete!\n");
        return;
    }
        
    
    TimerList *LoopTimer = Timers;
    while(LoopTimer != NULL) {
        if(strcmp(LoopTimer->Name, *CommandParams) == 0) {
            _TimerDelete(LoopTimer);
            printf("Timer Deleted!\n");
            return;
        }
        LoopTimer = LoopTimer->NextTimer;
    }
}

void TimerShow(char **CommandParams, char *HookParams) {
    if(Timers == NULL) {
        printf("No Timer defined!\n");
        return;
    }

    TimerList *LoopTimer = Timers;
    while(LoopTimer != NULL) {
        printf("Name:\t\t\t%s\n", LoopTimer->Name);
        printf("Interval:\t\t%dms\n", LoopTimer->Interval);
        printf("Running Command:\t%s\n", LoopTimer->Command);
        printf("Remained Ticks:\t\t%d\n", LoopTimer->RepeatCount);

        LoopTimer = LoopTimer->NextTimer;
        if(LoopTimer != NULL)
        printf("= = = = = = = = = = = = = = = = = = = = =\n");
    }
}

void TimerHelp(char **CommandParams, char *HookParams) {
    printf("Timer help:\n");
    printf("Add Timer: timer.add.[Timer Name].[Interval in ms].[Repeat Count].[Command]\n");
    printf("Note that to type commands use double . instead of single dot!\n");
    printf("Timer help:\n");
    printf("Timer help:\n");
}
