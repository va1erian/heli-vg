#include "main.h"

#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#define DEFAULT_LOG "helichallenge.log"
#define LOGLEVEL_NORMAL     0
#define LOGLEVEL_INFO       1
#define LOGLEVEL_ERROR      2
#define LOGLEVEL_FATALERROR 3

FILE* _Log;

void 		 LogOpen(void);
void 		 LogWrite(int level, char* format, ...);
inline void* AllocMem(size_t m);
void  		 Crash(char* why);
void 		 LogClose(void);

#endif // UTILS_H_INCLUDED
