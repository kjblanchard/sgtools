#include <sgtools/log.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define sMaxLogSize 4000
static void (*sLogFunc)(const char*, const char*, int) = NULL;
static FILE* sFptr = NULL;
static sgLogLevel sLogLevel = sgLogLevelDebug;

int sgInitializeLogSystem(const char* logfileName) {
	sgLogDebug("Opening log file at %s", logfileName);
	sFptr = fopen(logfileName, "a");
	if (sFptr)
		return true;
	sgLogError("Could not open file %s for logging!", logfileName);
	return false;
}

void sgSetDebugFunction(void (*func)(const char*, const char*, int)) {
	sLogFunc = func;
}

int sgShutdownLogSystem(void) {
	if (!sFptr)
		return true;
	int result = fclose(sFptr);
	if (result)
		sgLogError("Couldn't close logging file.");
	return !result;
}

static const char* getTextByLevel(sgLogLevel level) {
	switch (level) {
		case sgLogLevelDebug:
			return "Debug";
		case sgLogLevelInfo:
			return "Info";
		case sgLogLevelWarn:
			return "Warn";
		case sgLogLevelError:
			return "Error";
		default:
			return "";
	}
}

void sgLogInternal(sgLogLevel level, const char* fmt, ...) {
	if (level < sLogLevel) {
		return;
	}
	// Write all vaargs to buffer using vsnprintf
	char msgbuf[sMaxLogSize];
	va_list args;
	va_start(args, fmt);
	vsnprintf(msgbuf, sizeof(msgbuf), fmt, args);
	va_end(args);
	// Get time stamp buffer
	time_t current_time;
	time(&current_time);
	struct tm* gm_time = gmtime(&current_time);
	char tmbuf[30];
	strftime(tmbuf, sizeof(tmbuf), "%H:%M-%S", gm_time);
	FILE* outStream = level == sgLogLevelError ? stderr : stdout;
	fprintf(outStream, "%s-%s> %s -\n", tmbuf, getTextByLevel(level), msgbuf);
	if (sLogFunc) sLogFunc(tmbuf, fmt, level);
	bool logToFile = (level == sgLogLevelCritical || level == sgLogLevelError) && sFptr;
	if (logToFile) fprintf(sFptr, "%s: %s\n", tmbuf, msgbuf);
	if (level == sgLogLevelCritical) exit(1);
}

void sgSetLogLevel(int newLevel) { sLogLevel = (sgLogLevel)newLevel; }
