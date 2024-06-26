#include "spdlog.hpp"

int main()
{
    /*
    Create stdout/stderr logger object
    */
    stdoutAndstderr_logger(false);


    /*
    * Basic file logger 
    */
    Basic_file_logger(false);


    /*
    * Rotating files 
    */
    Rotating_files(false);

    /*
      * Dailyfiles
    */
    Daily_files(false);

    /*
    * Backtrace support
    */
    Backtrace_support(true);

}