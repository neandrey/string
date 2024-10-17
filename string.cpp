#include "string.h"
#include <cstring>

String::String() : length(first_size), capacity(0)
{
    rep = new char[length];
}

String::String(size_t _length) : length(_length), capacity(_length)
{
    rep = new char[length];
}

String::String(size_t _length, size_t _capecity)
    : length(_length), capacity(_capecity)
{
    rep = new char[length];
}

String::String(const char *c_str) : String(strlen(c_str))
{
    _copy_arr(c_str, length);
}

String::String(const String &s) : String(s.length, s.capacity)
{
    _copy_arr(s.rep, length);
}

String::String(String &&move) noexcept
{
    capacity = move.capacity;
    length = move.length;
    rep = move.rep;
    move.rep = nullptr;
}

String::~String()
{
    delete[] rep;
}

void String::_resize_mem(size_t len)
{
    if (len < first_size)
        return;

    while (len > length)
    {
        if (len >= max_size)
        {
            length = max_size;
            break;
        }

        length *= factor_resize;
    }

    char *new_mem = new char[length];

    for (size_t i = 0; i < length; ++i)
        new_mem[i] = rep[i];

    delete[] rep;
    rep = new_mem;
}

void String::_copy_arr(const char *ar, size_t length)
{
    for (size_t i = 0; i < length; ++i)
        rep[i] = ar[i];
}

void String::_clear()
{
    capacity = 0;
    length = first_size;
    char *new_mem = new char[length];
    for (size_t i = 0; i < length; ++i)
        new_mem[i] = 0;
    delete[] rep;
    rep = new_mem;
}

void String::push_back(char c)
{
    _resize_mem(capacity + 1);
    if (capacity == max_size)
        throw "Max_size";
    rep[capacity++] = c;
}

String &String::operator=(const String &s)
{
    if (this == &s)
        return *this;

    length = s.length;
    capacity = s.capacity;
    _resize_mem(length);
    return *this;
}

String &String::operator+=(const String &s)
{
    _resize_mem(length + s.length);
    for (size_t i = 0; i < s.capacity; ++i)
        rep[capacity + i] = s.rep[i];

    capacity += s.capacity;

    return *this;
}

static char _lower(char c)
{
    return (c >= 'A' && c <= 'Z') ? c + 32 : c;
}

String operator+(const String &s1, const String &s2)
{
    size_t length = s1.length + s2.length;
    size_t capecity = s1.capacity + s2.capacity;
    String temp(length, capecity);

    size_t h = 0;
    for (size_t i = 0; i < s1.capacity; ++i)
        temp.rep[h++] = s1.rep[i];

    for (size_t i = 0; i < s2.capacity; ++i)
        temp.rep[h++] = s2.rep[i];

    return temp;
}

std::istream &operator>>(std::istream &is, String &s)
{
    char c;
    s._clear();
    while (1)
    {
        c = is.get();
        if (c == '\n' || c == EOF)
            break;
        s.push_back(c);
    }
    return is;
}

std::ostream &operator<<(std::ostream &os, const String &s)
{
    for (size_t i = 0; i < s.capacity; ++i)
        os << s.rep[i];
    return os;
}

bool operator<(const String &_new, const String &_old)
{
    for (size_t i = 0; i < _new.capacity; ++i)
        if (_lower(_new.rep[i]) > _lower(_old.rep[i]))
            return true;

    return false;
}