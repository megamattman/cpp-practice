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

    logger (string out_file){
        output_stream.open(out_file);
    }    
    ~logger(){
        output_stream.close();
    }
    template <class logType>
    void write_to_stream(logType output_string){
        output_stream << output_string << endl;
    }
};


class logged_class {

    public:
    logger *my_logger;
    logged_class(){};
    logged_class(logger *new_logger){
        set_logger(my_logger);
    }
    void set_logger(logger* my_logger){
        my_logger = my_logger;
    }

};