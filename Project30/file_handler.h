#ifndef __FILE_HANDLER_H__
#define __FILE_HANDLER_H__

#include <stdint.h>

#define buffer_size 64

class file_handler_t {
public:
    file_handler_t();
    ~file_handler_t();

    void read(const std::string m_file_name);
    size_t size() const;
    char* get(size_t i) const;

private:
    char *elements;
    uint8_t data_size;
};

#endif
