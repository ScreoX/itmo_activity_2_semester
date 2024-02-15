#ifndef LAB_5_OP_2SEM_EXCEPTIONS_H
#define LAB_5_OP_2SEM_EXCEPTIONS_H
#include <string>

class Exceptions {
private:

    std::string error_name;
    int error_code;

public:

    Exceptions(std::string, int);
    ~Exceptions();

    int Code();
    std::string What();

};


#endif
