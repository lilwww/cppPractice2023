#include <iostream>
#include <string>
#include <log4cpp/SimpleLayout.hh>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>

using namespace std;
using namespace log4cpp; // 引出log4cpp的命名空间

#define logWarn(msg)\ 
do{\
  Mylogger *plog = Mylogger::getInstance();\
    string fl = __FILE__;\
    string fc = __FUNCTION__;\
    int ln = __LINE__;\
    string log = "File:" + fl + " "+ "Func:" + fc + " " + "Line:" + to_string(ln) +"    "+msg+"\n";\
    plog->warn(log.c_str());\
    Mylogger::destroy();\
}while(0)\

#define logError(msg)\ 
do{\
  Mylogger *plog = Mylogger::getInstance();\
    string fl = __FILE__;\
    string fc = __FUNCTION__;\
    int ln = __LINE__;\
    string log = "File:" + fl + " "+ "Func:" + fc + " " + "Line:" + to_string(ln) +"    "+msg+"\n";\
    plog->error(log.c_str());\
    Mylogger::destroy();\
}while(0)\


#define logDebug(msg)\ 
do{\
  Mylogger *plog = Mylogger::getInstance();\
    string fl = __FILE__;\
    string fc = __FUNCTION__;\
    int ln = __LINE__;\
    string log = "File:" + fl + " "+ "Func:" + fc + " " + "Line:" + to_string(ln) +"    "+msg+"\n";\
    plog->debug(log.c_str());\
    Mylogger::destroy();\
}while(0)\


#define logInfo(msg)\ 
do{\
  Mylogger *plog = Mylogger::getInstance();\
    string fl = __FILE__;\
    string fc = __FUNCTION__;\
    int ln = __LINE__;\
    string log = "File:" + fl + " "+ "Func:" + fc + " " + "Line:" + to_string(ln) +"    "+msg+"\n";\
    plog->info(log.c_str());\
    Mylogger::destroy();\
}while(0)\

// 使用单例模式
class Mylogger
{
public:
    void warn(const char *msg);
    void error(const char *msg);
    void debug(const char *msg);
    void info(const char *msg);
    static Mylogger *getInstance()
    {
        {
            if (nullptr == log)
            {
                log = new Mylogger();
            }
            return log;
        }
    }
    static void destroy()
    {
        {
            if (log) // log != nullptr
            {
                delete log;
                log = nullptr;
            }
        }
    }

private:
    Mylogger(){}
    ~Mylogger(){}

private:
    static Mylogger *log;
};

/*提示：在记录日志的时候，可以把文件名、函数名、行号与最终需要打印的信息拼接起来，这其实就是字符串的拼接，可以使用string进行操作。但是每次使用log->info，log->error的时候，都要使用对象，这样的使用也是比较麻烦，所以可以吧log->info("The log is info message");一些信息再去进行封装即可，例如使用宏定义。

*/

void Mylogger::warn(const char *msg)
{
    PatternLayout *ppl1 = new PatternLayout();
    // 日期%d  Catagory名字%c  等级%p 字符串%m  换行%n
    ppl1->setConversionPattern("%d %c [%p] %m%n");

    PatternLayout *ppl2 = new PatternLayout();
    // 日期%d  Catagory名字%c  等级%p 字符串%m  换行%n
    ppl2->setConversionPattern("%d %c [%p] %m%n");

    // 日志的目的地
    // 每一个appender对应一个Layout，不要共用,否则会报错
    OstreamAppender *poa =
        new OstreamAppender("OstreamAppender123", &cout);
    poa->setLayout(ppl1);

    FileAppender *pfa =
        new FileAppender("FileAppender1", "myLogger.log");
    pfa->setLayout(ppl2);

    // 日志的记录器
    Category &root = Category::getRoot();
    root.addAppender(poa);
    root.addAppender(pfa);

    // 日志的过滤器
    root.setPriority(Priority::WARN);

    // 日志的优先级一定要大于等于Catatory的优先级
    // root.emerg("This is an emerg message");
    // root.fatal("This is an fatal message");
    // root.alert("This is an alert message");
    // root.crit("This is an crit message");
    // root.error("This is an error message");
    root.warn(msg);

    // 空间回收
    Category::shutdown();
}


void Mylogger::error(const char *msg)
{
    PatternLayout *ppl1 = new PatternLayout();
    // 日期%d  Catagory名字%c  等级%p 字符串%m  换行%n
    ppl1->setConversionPattern("%d %c [%p] %m%n");

    PatternLayout *ppl2 = new PatternLayout();
    ppl2->setConversionPattern("%d %c [%p] %m%n");

    OstreamAppender *poa =
        new OstreamAppender("OstreamAppender123", &cout);
    poa->setLayout(ppl1);

    FileAppender *pfa =
        new FileAppender("FileAppender1", "myLogger.log");
    pfa->setLayout(ppl2);

    // 日志的记录器
    Category &root = Category::getRoot();
    root.addAppender(poa);
    root.addAppender(pfa);

    // 日志的过滤器
    root.setPriority(Priority::ERROR);

    // 日志的优先级一定要大于等于Catatory的优先级
    root.error(msg);

    // 空间回收
    Category::shutdown();
}
void Mylogger::debug(const char *msg)
{
    PatternLayout *ppl1 = new PatternLayout();
    // 日期%d  Catagory名字%c  等级%p 字符串%m  换行%n
    ppl1->setConversionPattern("%d %c [%p] %m%n");

    PatternLayout *ppl2 = new PatternLayout();
    ppl2->setConversionPattern("%d %c [%p] %m%n");

    OstreamAppender *poa =
        new OstreamAppender("OstreamAppender123", &cout);
    poa->setLayout(ppl1);

    FileAppender *pfa =
        new FileAppender("FileAppender1", "myLogger.log");
    pfa->setLayout(ppl2);

    // 日志的记录器
    Category &root = Category::getRoot();
    root.addAppender(poa);
    root.addAppender(pfa);

    // 日志的过滤器
    root.setPriority(Priority::DEBUG);

    // 日志的优先级一定要大于等于Catatory的优先级
    root.debug(msg);

    // 空间回收
    Category::shutdown();
}
void Mylogger::info(const char *msg)
{
    PatternLayout *ppl1 = new PatternLayout();
    // 日期%d  Catagory名字%c  等级%p 字符串%m  换行%n
    ppl1->setConversionPattern("%d %c [%p] %m%n");

    PatternLayout *ppl2 = new PatternLayout();
    ppl2->setConversionPattern("%d %c [%p] %m%n");

    OstreamAppender *poa =
        new OstreamAppender("OstreamAppender123", &cout);
    poa->setLayout(ppl1);

    FileAppender *pfa =
        new FileAppender("FileAppender1", "myLogger.log");
    pfa->setLayout(ppl2);

    // 日志的记录器
    Category &root = Category::getRoot();
    root.addAppender(poa);
    root.addAppender(pfa);

    // 日志的过滤器
    root.setPriority(Priority::INFO);

    // 日志的优先级一定要大于等于Catatory的优先级
    root.info(msg);

    // 空间回收
    Category::shutdown();
}

Mylogger *Mylogger::log = getInstance();

int main(int argc, char **argv)
{
    cout << "hello,world" << endl;
    logWarn("The log is a warn message");   
    logError("The log is an error message");
    logDebug("The log is a debug message");
    logInfo("The log is info message");
    return 0;
}


