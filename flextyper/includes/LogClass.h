////////////////////////////////////////////////////////////////////////
/// \copyright Copyright (c) 2020, Wasserman lab
////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <chrono>

namespace ft {

//class LogClass;
//std::string& operator<<(std::string& in, const LogClass& c);

class LogClass 
{
private:
public:
    LogClass() {
    };
    ~LogClass() {
    };

    static std::fstream Log;

    static void OpenLog(std::string logname) {
        Log.open(logname, std::fstream::out);
        if (!Log.is_open()) {
            std::cout << "Couldn't open " << logname << " file" << std::endl;
        }
        auto start = std::chrono::system_clock::now();
        std::time_t start_time = std::chrono::system_clock::to_time_t(start);
        //std::ostringstream oss;
        Log << "======== " << std::ctime(&start_time);
        //write(oss.str().c_str(), oss.tellp());
    };

    static void CloseLog() {
        Log.close();
    }

    static void ThrowRuntimeError(const std::string& error) {
        Log << "(EE) " << error << std::endl;
        std::cout << "(EE) " << error << std::endl;
        throw std::runtime_error(error);
    }

    ////////////////////////////////////////////////////////////////////////
    /// Benchmark
    ////////////////////////////////////////////////////////////////////////
    class Benchmark {
    public:
        Benchmark() {
           update();
        };
        ~Benchmark() {};
        void update() {_start = std::chrono::steady_clock::now();};
        void now(const std::string& tag) {
            _end = std::chrono::steady_clock::now();
            LogClass::Log << "Benchmark:";
            LogClass::Log << tag << std::chrono::duration_cast<std::chrono::seconds>(_end - _start).count() << " in sec" << std::endl;
            _start = _end;
        };
    private:
        std::chrono::steady_clock::time_point _start;
        std::chrono::steady_clock::time_point _end;
    };

};

}
