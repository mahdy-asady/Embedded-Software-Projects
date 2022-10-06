#ifndef __DEBUG_H_
#define __DEBUG_H_

#include <stdio.h>

#define NONE                0
#define ERROR_LEVEL         1
#define WARNING_LEVEL       2
#define INFO_LEVEL          3
#define TRACE_LEVEL         4

/*      TRACE   INFO    WARN    ERROR   NONE
TRACE   YES      NO      NO      NO      NO
INFO    YES      YES      NO      NO      NO
WARN    YES      YES      YES      NO      NO
ERROR   YES      YES      YES      YES      NO*/

/* -- Macro Definitions */

#if LOG_LEVEL>= ERROR_LEVEL
    #define log_error(M, ...)           printf("[ERR] (%s:%d) " M "\n", __BASE_FILE__, __LINE__, ##__VA_ARGS__);
#else
    #define log_error(format, ...)      {}
#endif

#if LOG_LEVEL>= WARNING_LEVEL
    #define log_warning(M, ...)         printf("[WARN] (%s:%d) " M "\n", __BASE_FILE__, __LINE__, ##__VA_ARGS__);
#else
    #define log_warning(format, ...)    {}
#endif

#if LOG_LEVEL>= INFO_LEVEL
    #define log_info(M, ...)            printf("[INFO] (%s:%d) " M "\n", __BASE_FILE__, __LINE__, ##__VA_ARGS__);
    #define DebugBlock(x)               do {x} while(0)
#else
    #define log_info(format, ...)       {}
    #define DebugBlock(x)               {}
#endif

#if LOG_LEVEL>= TRACE_LEVEL
    #define log_trace()                 printf("[..] (%s:%d->%s)\n", __BASE_FILE__, __LINE__, __func__);
#else
    #define log_trace()                 {}
#endif

#endif /*__DEBUG_H_*/
