#ifndef __BANNED_H__
#define __BANNED_H__

#define BANNED(func) sorry_##func##_is_a_banned_function

#undef strcpy
#define strcpy(x,y) BANNED(strcpy)
#undef strcat
#define strcat(x,y) BANNED(strcat)
#undef strncpy
#define strncpy(x,y,n) BANNED(strncpy)
#undef strncat
#define strncat(x,y,n) BANNED(strncat)

#undef sprintf
#undef vsprintf
#define sprintf(...) BANNED(sprintf)
#define vsprintf(...) BANNED(vsprintf)

#undef gmtime
#define gmtime(t) BANNED(gmtime)
#undef localtime
#define localtime(t) BANNED(localtime)
#undef ctime
#define ctime(t) BANNED(ctime)
#undef ctime_r
#define ctime_r(t, buf) BANNED(ctime_r)
#undef asctime
#define asctime(t) BANNED(asctime)
#undef asctime_r
#define asctime_r(t, buf) BANNED(asctime_r)

#undef malloc
#define malloc(s) BANNED(malloc)
#undef calloc
#define calloc(s, c) BANNED(calloc)
#undef free
#define free(p) BANNED(free)

#endif /* __BANNED_H__ */