#include "Exceptions.h"

Exceptions::Exceptions(std::string x, int y) {
    error_name = x;
    error_code = y;
}

Exceptions::~Exceptions() = default;

std::string Exceptions::What() {
    return error_name;
}

int Exceptions::Code() {
    return error_code;
}


