#include <sgtools/log.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#define MAX_LOG_SIZE 4000

static void (*logFunc)(const char *, const char *, int) = NULL;

/**
 * @brief The file that will be written to when logs are put.
 *
 */
static FILE *openDebugFile = NULL;
/**
 * @brief The internal logging function that the others will end up calling.
 * Probably don't call it manually
 *
 * @param level The log level to log this as.
 * @param data_to_write The data to write to the log.
 */
static void logInternal(sgLogLevel level, const char *data_to_write, ...);
/**
 * @brief The log level to log at, this should be sent in via settings.
 */
static sgLogLevel logLevel = sgLog_LDebug;
static const char *logFileName = "errors.log";

int sgInitializeLogSystem(const char *logfileName) {
  sgLogDebug("Opening log file at %s", logfileName);
  openDebugFile = fopen(logfileName, "a");
  if (openDebugFile)
    return true;
  sgLogError("Could not open file %s for logging!", logfileName);
  return false;
}

void sgSetDebugFunction(void (*func)(const char *, const char *, int)) {
  logFunc = func;
}

int sgShutdownLogSystem(void) {
  if (!openDebugFile)
    return true;
  int result = fclose(openDebugFile);
  if (result)
    sgLogError("Couldn't close logging file.");
  return !result;
}

static const char *getTextByLevel(sgLogLevel level) {
  switch (level) {
  case sgLog_LDebug:
    return "Debug";
  case sgLog_LInfo:
    return "Info";
  case sgLog_LWarn:
    return "Warn";
  case sgLog_LError:
    return "Error";
  default:
    return "";
  }
}

static void logInternal(sgLogLevel level, const char *thing_to_write, ...) {
  time_t current_time;
  time(&current_time);
  struct tm *gm_time = gmtime(&current_time);
  char buf[30];
  strftime(buf, sizeof(buf), "%H:%M-%S", gm_time);
  FILE *outStream = level == sgLog_LError ? stderr : stdout;
  fprintf(outStream, "%s-%s> %s -\n", buf, getTextByLevel(level),
          thing_to_write);
  if (logFunc) {
    logFunc(buf, thing_to_write, level);
  }
  if (level == sgLog_LError && openDebugFile) {
    fprintf(openDebugFile, "%s: %s\n", buf, thing_to_write);
  }
}

void sgSetLogLevel(int newLevel) { logLevel = (sgLogLevel)newLevel; }
