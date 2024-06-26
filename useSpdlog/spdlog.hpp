#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <memory>


void  stdoutAndstderr_logger(bool isOpen) {

    if (!isOpen)
        return;
    /*
        标准输出（stdout）：通常用于输出普通信息，如程序的正常运行状态等。
        标准错误（stderr）：通常用于输出错误信息或警告，以便于在大量日志信息中突出显示这些重要信息。

        spdlog 提供了多种日志 sink（即日志输出目标）来实现上述功能。你可以创建一个日志器，将多个 sink 组合在一起，
        使其同时记录到 stdout 和 stderr。
    */
    // 创建 stdout 和 stderr sinks
    auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto stderr_sink = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();

    // 创建一个 logger，组合这两个 sinks
    spdlog::logger logger("multi_sink", { stdout_sink, stderr_sink });

    // 设置日志级别（可选）
    logger.set_level(spdlog::level::debug);

    // 使用 logger 记录日志
    logger.info("This is an info message");
    logger.warn("This is a warning message");
    logger.error("This is an error message");


}


#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
void Basic_file_logger(bool isOpen)
{
    /*包含头文件：需要包含 spdlog 的核心头文件以及用于文件日志器的头文件。
    创建日志器：使用 basic_file_sink_mt 创建一个文件日志器。
    记录日志：使用日志器记录不同级别的日志信息。*/
    if (!isOpen)
        return;
    // 创建一个文件日志器
    auto file_logger = spdlog::basic_logger_mt("basic_logger", "logs/basic-log.txt");

    // 设置日志级别（可选）
    file_logger->set_level(spdlog::level::debug);

    // 设置日志格式（可选）
    file_logger->set_pattern("[%Y-%m-%d %H:%M:%S] [%l] %v");

    // 使用日志器记录日志
    file_logger->debug("This is a debug message");
    file_logger->info("This is an info message");
    file_logger->warn("This is a warning message");
    file_logger->error("This is an error message");
    file_logger->critical("This is a critical message");

}

#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"

void Rotating_files(bool isOpen)
{
    /*
    包含头文件：需要包含 spdlog 的核心头文件以及用于轮转文件日志器的头文件。
    创建轮转文件日志器：使用 rotating_file_sink_mt 创建一个带有轮转功能的文件日志器。
    记录日志：使用日志器记录不同级别的日志信息
    */
    if (!isOpen)
        return;

    // 创建一个轮转文件日志器
    //文件大小限制为 1 MB（1024 * 1024 * 5 字节）
    //最多保留 3 个日志文件。
    /*
    * rotating-log.txt：当前日志文件，大小不超过 5 MB。
      rotating-log.1.txt：上一个日志文件。
      rotating-log.2.txt：再上一个日志文件。
      rotating-log.3.txt：最早的日志文件（在记录更多日志时，这个文件将被删除）。
    */

    auto rotating_logger = spdlog::rotating_logger_mt("rotating_logger", "rotating_logger/rotating-log.txt", 1024 * 1024, 3);

    // 设置日志级别（可选）
    rotating_logger->set_level(spdlog::level::debug);

    // 设置日志格式（可选）
    rotating_logger->set_pattern("[%Y-%m-%d %H:%M:%S] [%l] %v");

    // 使用日志器记录日志
    for (int i = 0; i < 2000000; ++i) {
        rotating_logger->info("This is log message number {}", i);
    }

}

#include "spdlog/spdlog.h"
#include "spdlog/sinks/daily_file_sink.h"
void Daily_files(bool isOpen)
{
    /*
    * 在这个例子中，daily_file_sink 每天都会创建一个名为 my_daily_log.txt 的新日志文件。
    日志消息将被写入此文件。
    */
    if (!isOpen)
        return;
    // 创建名为“my_daily_log”并写入“my_daily_log.txt”的每日记录器
    auto daily_logger = spdlog::daily_logger_st("my_daily_log", "daily_logger/my_daily_log.txt");

    // 将日志级别设置为调试
    daily_logger->set_level(spdlog::level::debug);

    // 记录一些消息
    daily_logger->info("这是一条信息消息");
    daily_logger->debug("这是一条调试消息");


    /*
    您还可以通过向 daily_file_sink 构造函数传递附加参数来自定义每日日志文件名和其他选项。
    例如，以下代码将创建名为 my_daily_log_%Y-%m-%d.txt 的每日日志文件：
    */

    auto daily_logger_ = spdlog::daily_logger_st("my_daily_log_", "daily_logger/my_daily_log_%Y-%m-%d.txt");
    daily_logger_->info("这是一条信息消息");
    daily_logger_->debug("这是一条调试消息");

}

void Backtrace_support(bool isOpen)
{
    if (!isOpen)
        return;
    // Debug messages can be stored in a ring buffer instead of being logged immediately.
// This is useful to display debug logs only when needed (e.g. when an error happens).
// When needed, call dump_backtrace() to dump them to your log.

    spdlog::enable_backtrace(32); // Store the latest 32 messages in a buffer. 
    // or my_logger->enable_backtrace(32)..
    for (int i = 0; i < 100; i++)
    {
        spdlog::debug("Backtrace message {}", i); // not logged yet..
    }
    // e.g. if some error happened:
    spdlog::dump_backtrace(); // log them now! show the last 32 messages
    // or my_logger->dump_backtrace(32)..

}

