#pragma once

#include <cstring>
#include <iostream>
#include <utility>

namespace sebi
{
class string
{
public:
    // -1 castat la cel mai mare numar natural
    static const size_t npos = -1;

    string() : data(nullptr), m_size(0), m_capacity(0)
    {
    }
    // string s("hi");

    string(const char *text) : data(nullptr), m_size(0), m_capacity(0)
    {
        size_t size_needed = strlen(text);
        reserve(size_needed); // Aloca cel putin necesarul
        strcpy(data, text);
        m_size = size_needed;
    }

    // copy constr
    //  string s1 = s2;
    // initializezi data cu null pentru functia reserve
    // aceasta verifica daca data este nullptr
    string(const string &other) : data(nullptr), m_size(0), m_capacity(0)
    {
        reserve(other.m_size);
        if (other.data)
        {
            strcpy(data, other.data);
            m_size = other.m_size;
        }
    }

    // move constructor
    // string s = "text";
    // string s1 = std::move(s2)
    string(string &&other)
    {
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        data = other.data;

        other.data = nullptr;
        other.m_capacity = 0;
        other.m_size = 0;
    }

    // copy assignment operator
    // string s2 = "text";
    // s2 = s3
    string &operator=(const string &other)
    {
        // pentru s2 = s2 !!!
        if (this == &other)
        {
            return *this;
        }

        // daca nu avem sufiect spatiu folosim reserve
        if (other.m_size > m_capacity)
        {
            reserve(other.m_size);
        }

        if (other.data)
        {
            strcpy(data, other.data);
            m_size = other.m_size;
        }
        else
        {
            if (data)
                data[0] = '\0';
            m_size = 0;
        }

        return *this;
    }

    string &operator=(string &&other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        data = other.data;

        other.data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;

        return *this;
    }

    char &operator[](size_t index)
    {
        return data[index];
    }

    const char &operator[](size_t index) const
    {
        return data[index];
    }

    char &at(size_t index)
    {
        if (index >= m_size)
        {
            throw std::out_of_range("index is out of bound!");
        }
        return data[index];
    }

    string &operator+=(char c)
    {
        if (m_size == m_capacity)
        {
            // Daca a atins limita, dublam. (Daca initial era 0, punem macar capacitate 1)
            reserve(m_capacity == 0 ? 1 : m_capacity * 2);
        }
        data[m_size] = c;
        m_size++;
        data[m_size] = '\0'; // Mutam mereu '\0' la coada
        return *this;
    }

    string &operator+=(const string &other)
    {
        size_t new_len = m_size + other.m_size;

        if (new_len > m_capacity)
        {
            // Cat spatiu ar fi ideal? Hai sa zicem Dublu... dar daca nici dublul nu e de ajuns pt `other` (e foarte lung)?
            // Atunci dam capacitatea exact `new_len`.
            size_t new_cap = std::max(m_capacity * 2, new_len);
            reserve(new_cap);
        }

        // Acum NICIODATA nu pica/nu e nevoie de `delete` direct aici, doar lipim restul efectiv!
        strcat(data, other.data);
        m_size = new_len;

        return *this;
    }

    string operator+(const string &other) const
    {
        string result;
        size_t needed_size = m_size + other.m_size;

        // Alocam direct cat este nevoie (+1 se adauga intern in reserve)
        result.reserve(needed_size);

        result.data[0] = '\0'; // Pornim ca "string gol" pentru siguranta strcat
        if (data)
            strcat(result.data, data);
        if (other.data)
            strcat(result.data, other.data);

        result.m_size = needed_size;
        return result;
    }

    size_t find(char c)
    {
        for (size_t i = 0; i < m_size; i++)
        {
            if (data[i] == c)
            {
                return i;
            }
        }
        return npos;
    }

    bool operator==(const string &other) const
    {
        if (m_size != other.m_size)
            return false;

        return strcmp(data, other.data) == 0;
    }

    bool operator!=(const string &other) const
    {
        // aici este folosit operatorul == de mai sus
        return !(*this == other);
    }

    bool operator<(const string &other) const
    {
        return strcmp(data, other.data) < 0;
    }

    bool operator>(const string &other) const
    {
        return strcmp(data, other.data) > 0;
    }

    void push_back(char c)
    {
        if (m_size == m_capacity)
        {
            reserve(m_capacity == 0 ? 1 : m_capacity * 2);
        }
        data[m_size++] = c;
    }

    void pop_back()
    {
        m_size--;
        data[m_size] = '\0';
    }

    char &front()
    {
        return data[0];
    }

    const char &front() const
    {
        return data[0];
    }

    char &back()
    {
        return data[m_size - 1];
    }

    const char &back() const
    {
        return data[m_size - 1];
    }

    void reserve(size_t new_cap)
    {
        if (new_cap <= m_capacity)
            return; // Nu facem nimic daca avem deja suficient loc

        // Alocam noul spatiu (mereu cu +1 pentru '\0')
        char *new_data = new char[new_cap + 1];

        // Copiem ce aveam pana acum, daca exista ceva
        if (data != nullptr)
        {
            strcpy(new_data, data);
            delete[] data;
        }
        else
        {
            // Daca data era gol (ex. la un string abia creat), sa fim siguri ca incepe curat
            new_data[0] = '\0';
        }

        data = new_data;
        m_capacity = new_cap;
    }

    const char *c_str() const
    {
        return data ? data : "";
    }

    bool empty()
    {
        return m_size == 0;
    }

    void clear()
    {
        m_size = 0;
        data[0] = '\0';
    }

    size_t size() const
    {
        return m_size;
    }

    size_t capacity() const
    {
        return m_capacity;
    }

    ~string()
    {
        delete[] data;
    }

private:
    char *data;
    size_t m_size;
    size_t m_capacity;
};
} // namespace sebi
