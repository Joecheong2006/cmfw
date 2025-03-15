#include "log.h"
#include "core/assert.h"
#include "platform/platform.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

static char* level_str[] = {
	[LogLevelInfo] = "[INFO]",
	[LogLevelWarn] = "[WARN]",
	[LogLevelDebug] = "[DEBUG]",
	[LogLevelTrace] = "[TRACE]",
	[LogLevelError] = "[ERROR]",
	[LogLevelFatal] = "[FATAL]",
};

static ConsoleTextColor level_colors_map[] = {
	[LogLevelInfo] = ConsoleTextColorMagenta,
	[LogLevelWarn] = ConsoleTextColorYellow,
	[LogLevelDebug] = ConsoleTextColorGreen,
	[LogLevelTrace] = ConsoleTextColorCyan,
	[LogLevelError] = ConsoleTextColorRed,
	[LogLevelFatal] = ConsoleTextColorRed,
};

void log_msg(log_level level, const char* msg, ...) {
	ASSERT_MSG(level >= 0 && level <= LogLevelFatal, "invalid log level");
	char out_msg[1024];
	memset(out_msg, 0, sizeof(out_msg));

	__builtin_va_list arg_ptr;
	va_start(arg_ptr, msg);
	vsnprintf(out_msg, sizeof(out_msg), msg, arg_ptr);
	va_end(arg_ptr);

	char log_out[1024 + 7];
	sprintf(log_out, "%s%s", level_str[level], out_msg);

	platform_console_log(log_out, level_colors_map[level]);
}
