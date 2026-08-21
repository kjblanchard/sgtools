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
 */
typedef enum sgLogLevel {
	sgLogLevelDefault = 0,
	sgLogLevelDebug = 1,
	sgLogLevelInfo = 2,
	sgLogLevelWarn = 3,
	sgLogLevelError = 4,
	sgLogLevelCritical = 5,
} sgLogLevel;
/**
 * @brief Opens and/or creates a file for debug logging.
 * @param logfileName The file to open to write error logs to during runtime.
 * @return 1 if successful, 0 if failed.
 */
int sgInitializeLogSystem(const char* logfileName);
/**
 * @brief Closes the open file for logging.
 *
 * @return
 */
int sgShutdownLogSystem(void);
/**
 * @brief The internal logging function that the others will end up calling.
 * Probably don't call it manually
 *
 * @param level The log level to log this as.
 * @param fmt The data to pass to printf.
 */
void sgLogInternal(sgLogLevel level, const char* fmt, ...);
// Do not log except errors and critical in release, and push errors to critical
// for debugging
#ifdef NDEBUG
#define sgLogDebug(fmt, ...) ((void)0)
#define sgLogInfo(fmt, ...) ((void)0)
#define sgLogWarn(fmt, ...) ((void)0)
#define sgLogError(fmt, ...) sgLogInternal(sgLogLevelError, fmt, ##__VA_ARGS__)
#define sgLogCritical(fmt, ...) sgLogInternal(sgLogLevelCritical, fmt, ##__VA_ARGS__)
#else
#define sgLogDebug(fmt, ...) sgLogInternal(sgLogLevelDebug, fmt, ##__VA_ARGS__)
#define sgLogInfo(fmt, ...) sgLogInternal(sgLogLevelInfo, fmt, ##__VA_ARGS__)
#define sgLogWarn(fmt, ...) sgLogInternal(sgLogLevelWarn, fmt, ##__VA_ARGS__)
#define sgLogError(fmt, ...) sgLogInternal(sgLogLevelError, fmt, ##__VA_ARGS__)
#define sgLogCritical(fmt, ...) sgLogInternal(sgLogLevelCritical, fmt, ##__VA_ARGS__)
#endif
/**
 * @brief Sets a function to call when the logger is triggered, used by engine
 * @param func function to be called
 */
void sgSetDebugFunction(void (*func)(const char*, const char*, int));
/**
 * @brief Sets the log level that we should use throughout the program.  If a
 * log is this level or higher, it will be shown, defaults to Debug
 * @param newLevel
 */
void sgSetLogLevel(int newLevel);
/**
 * @brief Sets the log level that we should Pipe to a file.  If a
 * log is this level or higher, it will be shown, defaults to Error
 * @param newLevel
 */
void sgSetFileLogLevel(int newLevel);
#ifdef __cplusplus
}
#endif
