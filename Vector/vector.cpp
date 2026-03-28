#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>

namespace sebi
{
template <typename T>
class vector
{
  public:
    // ==========================================
    // 1. ALIAS-URI SI TIPURI
    // ==========================================
    using iterator = T *;
    using const_iterator = const T *;

    // ==========================================
    // 2. CONSTRUCTORI & DESTRUCTOR
    // ==========================================
    // constructor default
    vector()
    {
        std::cout << "constructor default fara parametrii" << std::endl;
        data = nullptr;
        m_size = 0;
        m_capacity = 0;
    }

    vector(size_t _capacity) : m_size(0), m_capacity(_capacity)
    {
        if (m_capacity > 0)
        {
            data = new T[m_capacity];
        }
        else
        {
            data = nullptr;
        }
    }

    // copy constr
    vector(const vector<T> &other) : m_size(other.m_size), m_capacity(other.m_capacity)
    {
        if (m_capacity > 0)
        {
            data = new T[m_capacity];
            for (size_t i = 0; i < other.m_size; i++)
            {
                data[i] = other.data[i];
            }
        }
        else
        {
            data = nullptr;
        }
    }

    // move constructor
    vector(vector<T> &&other) noexcept : data(other.data), m_size(other.m_size), m_capacity(other.m_capacity)
    {
        other.data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    // constructor pentru initializari de tipul: vector<int> v = {1, 2, 3};
    vector(std::initializer_list<T> list) : m_size(list.size()), m_capacity(list.size())
    {
        if (m_capacity > 0)
        {
            data = new T[m_capacity];
            size_t i = 0;
            for (const T &element : list)
            {
                data[i++] = element;
            }
        }
        else
        {
            data = nullptr;
        }
    }

    ~vector()
    {
        delete[] data;
    }

    // ==========================================
    // 3. OPERATORI DE ATRIBUIRE (=)
    // ==========================================
    // copy assign operator
    vector &operator=(const vector<T> &other)
    {
        if (this == &other)
        {
            return *this;
        }
        T *new_data = nullptr;
        if (other.m_capacity > 0)
        {
            new_data = new T[other.m_capacity];

            for (size_t i = 0; i < other.m_size; i++)
            {
                new_data[i] = other.data[i];
            }
        }
        delete[] data;

        data = new_data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;

        return *this;
    }

    // move assign operator
    vector &operator=(vector<T> &&other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }
        delete[] data;

        data = other.data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;

        other.data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;

        return *this;
    }

    // ==========================================
    // 4. ACCES LA ELEMENTE
    // ==========================================
    // pentru a modifica elementele : v[10] = 5;
    T &operator[](size_t index)
    {
        return data[index];
    }

    // std::cout<<v[5];
    const T &operator[](size_t index) const
    {
        return data[index];
    }

    T &back()
    {
        // este bine sa gestionăm cazul in care vectorul e gol
        if (m_size == 0)
        {
            throw std::out_of_range("Vector is empty");
        }
        return data[m_size - 1];
    }

    // ==========================================
    // 5. ITERATORI
    // ==========================================
    iterator begin()
    {
        return data; // returnam pointerul la inceputul array-ului
    }

    iterator end()
    {
        return data + m_size; // pointer dupa ultimul element valabil (exclusiv)
    }

    // varianta constanta - read only
    const_iterator begin() const
    {
        return data;
    }

    const_iterator end() const
    {
        return data + m_size;
    }

    // ==========================================
    // 6. CAPACITATE ȘI DIMENSIUNE
    // ==========================================
    size_t size() const
    {
        return m_size;
    }

    size_t capacity() const
    {
        return m_capacity;
    }

    bool empty() const
    {
        return m_size == 0;
    }

    void reserve(size_t new_cap)
    {
        // pentru a nu face vectorul sa fie mai mic
        // ai vector(50) => sa nu poti sa dai reserve(10)
        if (new_cap > m_capacity)
        {
            T *new_data = new T[new_cap];
            for (size_t i = 0; i < m_size; i++)
            {
                new_data[i] = std::move(data[i]);
            }
            delete[] data;
            data = new_data;
            m_capacity = new_cap;
        }
    }

    // ==========================================
    // 7. MODIFICATORI
    // ==========================================
    void push_back(const T &element)
    {
        if (m_size == m_capacity)
        {
            std::cout << "index curent: " << m_size << ", capacitate curenta: " << m_capacity << std::endl;
            std::cout << "se face o realocare de momorie" << std::endl;
            reserve(m_capacity == 0 ? 1 : m_capacity * 2);
        }
        data[m_size++] = element;
    }

    void pop_back()
    {
        // ne asiguram ca avem ce sterge
        if (m_size > 0)
        {
            m_size--;
        }
    }

    // acesta este un free logic
    // nu necesita delete[]
    void clear()
    {
        m_size = 0;
    }

    // ==========================================
    // 8. OPERATORI EXTRA
    // ==========================================
    vector &operator+=(const vector<T> &other)
    {
        if (m_size != other.m_size)
        {
            throw std::invalid_argument("vectorii nu au aceeasi dimensiune!");
        }
        for (size_t i = 0; i < m_size; i++)
        {
            data[i] += other.data[i];
        }
        return *this;
    }

    vector operator+(const vector<T> &other) const
    {
        if (m_size != other.m_size)
        {
            throw std::invalid_argument("Vectorii nu au aceeași dimensiune!");
        }
        // facem o copie a vectorului curent (folosind copy constructor-ul)
        vector<T> result(*this);
        // se foloseste de operatorul += implementat mai sus
        result += other;

        return result;
    }

  private:
    T *data;
    size_t m_size;
    size_t m_capacity;
};
} // namespace sebi
int main()
{
    sebi::vector<int> v;
    v.push_back(5);
    v.push_back(5);
    v.push_back(5);
    v.push_back(5);
    v.push_back(5);
    for (size_t i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
    sebi::vector<int> test = v;
    test += v;

    for (size_t i = 0; i < test.size(); i++)
    {
        std::cout << test[i] << " ";
    }
    std::cout << std::endl;

    sebi::vector<std::string> nume = {"john", "maria", "alex"};
    // folosind iteratori
    for (auto &element : nume)
    {
        std::cout << element << std::endl;
    }
    return 0;
}
