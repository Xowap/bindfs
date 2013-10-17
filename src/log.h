#ifndef INC_BINDFS_LOG_H
#define INC_BINDFS_LOG_H

/**
 * Call this when the fd has been modified, it will mark it for flush
 * to logs when the file is closed.
 */
void log_touch(const int fd);

/**
 * When a file is closed, call this function. If the file was
 * previously modified, it will be flushed to the logfile.
 *
 * The log file is opened each time, in append mode.
 */
void log_close(const char *logfile, const int fd, const char *path);

/**
 * Manually add an entry to the log
 */
void log_write_entry(const char *logfile, const char *operation, const char *path);

#endif
