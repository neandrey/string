#ifndef STRING_H
#define STRING_H
#include <stddef.h>
#include <iostream>

class String
{
    friend std::istream &operator>>(std::istream &, String &);
    friend std::ostream &operator<<(std::ostream &, const String &);
    friend String operator+(const String &s1, const String &s2);
    friend bool operator<(const String &lhs, const String &rhs);

    enum
    {
        first_size = 8,
        factor_resize = 2,
        max_size = 4096
    };
    void _resize_mem(size_t length);
    void _copy_arr(const char *ar, size_t length);
    void _clear();
    static char _lower(char);
    char *rep;
    size_t length{0}, capacity{0};

public:
    String();
    String(size_t);
    String(size_t, size_t);
    String(const char *str);
    String(const String &);
    String(String &&) noexcept;
    ~String();
    String &operator=(const String &);
    String &operator+=(const String &);
    size_t get_length() const { return length; }
    size_t get_capecity() const { return capacity; }
    void push_back(char);
};

#endif