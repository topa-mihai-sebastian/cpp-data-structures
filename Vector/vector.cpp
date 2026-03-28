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
    std::cout << "=== Test 1: Push Back and Auto-Resize ===" << std::endl;
    sebi::vector<int> v1;
    for (int i = 1; i <= 5; ++i)
    {
        v1.push_back(i * 10);
    }
    for (size_t i = 0; i < v1.size(); ++i)
    {
        std::cout << v1[i] << " ";
    }
    std::cout << "\nSize: " << v1.size() << ", Capacity: " << v1.capacity() << "\n\n";

    std::cout << "=== Test 2: Initializer List and Range-based for ===" << std::endl;
    sebi::vector<std::string> v2 = {"Apple", "Banana", "Cherry"};
    for (const auto &fruit : v2)
    {
        std::cout << fruit << " ";
    }
    std::cout << "\n\n";

    std::cout << "=== Test 3: Copy Constructor and Assignment ===" << std::endl;
    sebi::vector<std::string> v3 = v2; // Copy Constructor
    v3.push_back("Date");
    sebi::vector<std::string> v4;
    v4 = v3; // Copy Assignment
    std::cout << "v4 (copied from v3 + added 'Date'): ";
    for (const auto &f : v4)
        std::cout << f << " ";
    std::cout << "\n\n";

    std::cout << "=== Test 4: Move Constructor and Assignment ===" << std::endl;
    sebi::vector<std::string> v5 = std::move(v3); // Move Constructor
    std::cout << "v5 (moved from v3): ";
    for (const auto &f : v5)
        std::cout << f << " ";
    std::cout << "\nv3 size after move: " << v3.size() << "\n";

    sebi::vector<std::string> v6;
    v6 = std::move(v4); // Move Assignment
    std::cout << "v6 (moved from v4): ";
    for (const auto &f : v6)
        std::cout << f << " ";
    std::cout << "\n\n";

    std::cout << "=== Test 5: Modifiers (pop_back, clear) ===" << std::endl;
    sebi::vector<int> v7 = {1, 2, 3, 4, 5};
    v7.pop_back();
    std::cout << "After pop_back, last element is: " << v7.back() << "\n";
    v7.clear();
    std::cout << "After clear, empty() is: " << (v7.empty() ? "true" : "false") << "\n\n";

    std::cout << "=== Test 6: Math Operators (+ and +=) ===" << std::endl;
    sebi::vector<int> a = {1, 2, 3};
    sebi::vector<int> b = {10, 20, 30};
    a += b;
    std::cout << "a += b -> ";
    for (auto x : a)
        std::cout << x << " "; // expected 11 22 33
    std::cout << "\n";

    try
    {
        sebi::vector<int> c = a + b;
        std::cout << "a + b  -> ";
        for (auto x : c)
            std::cout << x << " "; // expected 21 42 63
        std::cout << "\n";
    }
    catch (const std::exception &e)
    {
        std::cout << "Exception: " << e.what() << "\n";
    }
    std::cout << "\n";

    return 0;
}
