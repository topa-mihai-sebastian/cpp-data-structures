#include "String/string.hpp"
#include "Vector/vector.hpp"
#include <iostream>
#include <string>

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
        {
            std::cout << x << " "; // expected 21 42 63
        }
        std::cout << "\n";
    }
    catch (const std::exception &e)
    {
        std::cout << "Exception: " << e.what() << "\n";
    }
    std::cout << "\n";
    std::string s = "afasfas";
    s.find('c');
    return 0;
}