#include <iostream>
#include  <fstream>
#include <string>

#define HEREISMYNAME my_logger->write_to_stream(__PRETTY_FUNCTION__);
#define HEREISMYNUMBER my_logger->write_to_stream(__LINE__);
#define HEREIAM my_logger->write_to_stream(__PRETTY_FUNCTION__);

using namespace std;
class logger {
    ofstream output_stream;    
    public:
    string log_file_name = "test_log";

    logger (string out_file){
        output_stream.open(out_file);
    }
    template <class logType>
    void write_to_stream(logType output_string){
        output_stream << output_string << endl;
    }
};


class logged_class {

    public:
    logger *my_logger;
    logged_class(logger *new_logger){
        my_logger = new_logger;
    }

};

int main (void) {
    logger new_logger("test_outputfile");
    logged_class my_logged_class(&new_logger);
}