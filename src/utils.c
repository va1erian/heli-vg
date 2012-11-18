#include "utils.h"

void LogOpen(void) {
    time_t the_time = time(NULL);
    char timestr[32];
    strftime(timestr, sizeof(timestr), "%x, %X", localtime(&the_time));
    _Log = fopen(DEFAULT_LOG, "a");
    fprintf(_Log, "---Logging started on %s---\n", timestr);
}

void LogWrite(int level, char* format, ...) {
    va_list args;
    time_t the_time = time(NULL);
    char timestr[32];
    va_start(args, format);
    strftime(timestr, sizeof(timestr), "%X", localtime(&the_time));
    fprintf(_Log, timestr);
    switch(level) {
        case LOGLEVEL_NORMAL:
            fprintf(_Log, " :");
        break;
        case LOGLEVEL_INFO:
            fprintf(_Log, " (INFO):");
        break;
        case LOGLEVEL_ERROR:
            fprintf(_Log, " (ERROR):");
        break;
        case LOGLEVEL_FATALERROR:
            fprintf(_Log, " (FUCK):");
        break;
    }
    vfprintf(_Log, format, args);
    fprintf(_Log, "\n");
}

void LogClose() {
    time_t the_time = time(NULL);
    char timestr[32];
    strftime(timestr, sizeof(timestr), "%x, %X", localtime(&the_time));
    fprintf(_Log, "---Logging ended on %s---\n", timestr);
	fclose(_Log);
}

inline void* AllocMem(size_t m) {
	void* mem = malloc(m);
	if(!mem) {
		Crash("Out of memory");
		return NULL;
	} else
		return mem;
}

void Crash(char* why) {
	LogWrite(LOGLEVEL_FATALERROR, why);
	#ifndef _WIN32
		fprintf(stderr, "FATAL ERROR: %s", why);
	#endif
	LogClose();
	abort();
}
