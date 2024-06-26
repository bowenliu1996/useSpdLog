#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <memory>


void  stdoutAndstderr_logger(bool isOpen) {

    if (!isOpen)
        return;
    /*
        ��׼�����stdout����ͨ�����������ͨ��Ϣ����������������״̬�ȡ�
        ��׼����stderr����ͨ���������������Ϣ�򾯸棬�Ա����ڴ�����־��Ϣ��ͻ����ʾ��Щ��Ҫ��Ϣ��

        spdlog �ṩ�˶�����־ sink������־���Ŀ�꣩��ʵ���������ܡ�����Դ���һ����־��������� sink �����һ��
        ʹ��ͬʱ��¼�� stdout �� stderr��
    */
    // ���� stdout �� stderr sinks
    auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto stderr_sink = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();

    // ����һ�� logger����������� sinks
    spdlog::logger logger("multi_sink", { stdout_sink, stderr_sink });

    // ������־���𣨿�ѡ��
    logger.set_level(spdlog::level::debug);

    // ʹ�� logger ��¼��־
    logger.info("This is an info message");
    logger.warn("This is a warning message");
    logger.error("This is an error message");


}


#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
void Basic_file_logger(bool isOpen)
{
    /*����ͷ�ļ�����Ҫ���� spdlog �ĺ���ͷ�ļ��Լ������ļ���־����ͷ�ļ���
    ������־����ʹ�� basic_file_sink_mt ����һ���ļ���־����
    ��¼��־��ʹ����־����¼��ͬ�������־��Ϣ��*/
    if (!isOpen)
        return;
    // ����һ���ļ���־��
    auto file_logger = spdlog::basic_logger_mt("basic_logger", "logs/basic-log.txt");

    // ������־���𣨿�ѡ��
    file_logger->set_level(spdlog::level::debug);

    // ������־��ʽ����ѡ��
    file_logger->set_pattern("[%Y-%m-%d %H:%M:%S] [%l] %v");

    // ʹ����־����¼��־
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
    ����ͷ�ļ�����Ҫ���� spdlog �ĺ���ͷ�ļ��Լ�������ת�ļ���־����ͷ�ļ���
    ������ת�ļ���־����ʹ�� rotating_file_sink_mt ����һ��������ת���ܵ��ļ���־����
    ��¼��־��ʹ����־����¼��ͬ�������־��Ϣ
    */
    if (!isOpen)
        return;

    // ����һ����ת�ļ���־��
    //�ļ���С����Ϊ 1 MB��1024 * 1024 * 5 �ֽڣ�
    //��ౣ�� 3 ����־�ļ���
    /*
    * rotating-log.txt����ǰ��־�ļ�����С������ 5 MB��
      rotating-log.1.txt����һ����־�ļ���
      rotating-log.2.txt������һ����־�ļ���
      rotating-log.3.txt���������־�ļ����ڼ�¼������־ʱ������ļ�����ɾ������
    */

    auto rotating_logger = spdlog::rotating_logger_mt("rotating_logger", "rotating_logger/rotating-log.txt", 1024 * 1024, 3);

    // ������־���𣨿�ѡ��
    rotating_logger->set_level(spdlog::level::debug);

    // ������־��ʽ����ѡ��
    rotating_logger->set_pattern("[%Y-%m-%d %H:%M:%S] [%l] %v");

    // ʹ����־����¼��־
    for (int i = 0; i < 2000000; ++i) {
        rotating_logger->info("This is log message number {}", i);
    }

}

#include "spdlog/spdlog.h"
#include "spdlog/sinks/daily_file_sink.h"
void Daily_files(bool isOpen)
{
    /*
    * ����������У�daily_file_sink ÿ�춼�ᴴ��һ����Ϊ my_daily_log.txt ������־�ļ���
    ��־��Ϣ����д����ļ���
    */
    if (!isOpen)
        return;
    // ������Ϊ��my_daily_log����д�롰my_daily_log.txt����ÿ�ռ�¼��
    auto daily_logger = spdlog::daily_logger_st("my_daily_log", "daily_logger/my_daily_log.txt");

    // ����־��������Ϊ����
    daily_logger->set_level(spdlog::level::debug);

    // ��¼һЩ��Ϣ
    daily_logger->info("����һ����Ϣ��Ϣ");
    daily_logger->debug("����һ��������Ϣ");


    /*
    ��������ͨ���� daily_file_sink ���캯�����ݸ��Ӳ������Զ���ÿ����־�ļ���������ѡ�
    ���磬���´��뽫������Ϊ my_daily_log_%Y-%m-%d.txt ��ÿ����־�ļ���
    */

    auto daily_logger_ = spdlog::daily_logger_st("my_daily_log_", "daily_logger/my_daily_log_%Y-%m-%d.txt");
    daily_logger_->info("����һ����Ϣ��Ϣ");
    daily_logger_->debug("����һ��������Ϣ");

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

