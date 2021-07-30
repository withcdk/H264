#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

#include <fstream>

#define TRACE_CONFIG_CONSOLE 1   //是否向控制台中写入数据
#define TRACE_CONFIG_LOGOUT  1   //是否允许向日志文件中写入数据

extern std::ofstream g_traceFile;


#endif // !_CONFIGURATION_H_

