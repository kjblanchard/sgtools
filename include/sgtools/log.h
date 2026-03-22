#pragma once
/**
 * @file debug.h
 * @author Kevin Blanchard (kevin@supergoon.com)
 * @brief Logging functions used for logging at specific levels, log to a file,
 * etc.
 * @version 0.3
 * @date 2023-07-15
 * @copyright Copyright (c) 2023-2026
 */
#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief The level that we should show debug events at.
 *
 */
typedef enum sgLogLevel {
  sgLog_LDefault = 0,
  sgLog_LDebug = 1,
  sgLog_LInfo = 2,
  sgLog_LWarn = 3,
  sgLog_LError = 4,
  sgLog_LCritical = 5,
} sgLogLevel;
/**
 * @brief Opens and/or creates a file for debug logging.
 * @param logfileName The file to open to write error logs to during runtime.
 * @return 1 if successful, 0 if failed.
 */
int sgInitializeLogSystem(const char *logfileName);
/**
 * @brief Closes the open file for logging.
 *
 * @return
 */
int sgShutdownLogSystem(void);
#define LOG_ENABLED(level) ((level) >= logLevel)
#define LOG(level, fmt, ...)                                                   \
  do {                                                                         \
    if (LOG_ENABLED(level))                                                    \
      logInternal(level, fmt, ##__VA_ARGS__);                                  \
  } while (0)

#define sgLogDebug(fmt, ...) LOG(sgLog_LDebug, fmt, ##__VA_ARGS__)
#define sgLogInfo(fmt, ...) LOG(sgLog_LInfo, fmt, ##__VA_ARGS__)
#define sgLogWarn(fmt, ...) LOG(sgLog_LWarn, fmt, ##__VA_ARGS__)
#define sgLogError(fmt, ...) LOG(sgLog_LError, fmt, ##__VA_ARGS__)

void sgSetDebugFunction(void (*)(const char *, const char *, int));
/**
 * @brief Sets the log level that we should use throughout the program.  If a
 * log is this level or higher, it will be shown, defaults to Debug
 * @param newLevel
 */
void sgSetLogLevel(int newLevel);
#ifdef __cplusplus
}
#endif
