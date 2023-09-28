#ifndef ERROR_HPP_FILE
#define ERROR_HPP_FILE

#include <iostream>

#define ERROR(type,info) std::cerr << "[ERROR][" << type << "]file:" << __FILE__ << ";line:" << __LINE__ << "|info:" << info << std::endl;
#define ERRORINFO(info) std::cerr << "[ERROR]other:" << info << std::endl;
#define WARNING(type,info) std::cerr << "[WARNING][" << type << "]file:" << __FILE__ << ";line:" << __LINE__ << "|info:" << info << std::endl;
#define WARNINGINFO(info) std::cerr << "[WARNING]other:" << info << std::endl;
#define INFO(type,info) std::cout << "[INFO][" << type << "]file:" << __FILE__ << ";line:" << __LINE__ << "|info:" << info << std::endl;
#define INFODATA(info) std::cout << "[INFO]other:" << info << std::endl;

#endif //!ERROR_HPP_FILE