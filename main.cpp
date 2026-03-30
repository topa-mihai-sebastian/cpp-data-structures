#include "String/string.hpp"
#include "Vector/vector.hpp"
#include <iostream>
#include <string>

void test_sebi_string()
{
    std::cout << "\n============================================\n";
    std::cout << "          TESTE PENTRU sebi::string          \n";
    std::cout << "============================================\n\n";

    std::cout << "=== Test 1: Constructori si Afisare (c_str, size) ===" << std::endl;
    sebi::string s1;          // Default
    sebi::string s2("Hello"); // C-string
    sebi::string s3(s2);      // Copy

    sebi::string temp(" World!");
    sebi::string s4(std::move(temp)); // Move

    std::cout << "s1 (default): '" << s1.c_str() << "' (size: " << s1.size() << ")\n";
    std::cout << "s2 (c-string): '" << s2.c_str() << "' (size: " << s2.size() << ")\n";
    std::cout << "s3 (copied): '" << s3.c_str() << "' (size: " << s3.size() << ")\n";
    std::cout << "s4 (moved): '" << s4.c_str() << "' (size: " << s4.size() << ")\n\n";

    std::cout << "=== Test 2: Acces elemente (Operator[], at, front, back) ===" << std::endl;
    std::cout << "s2 front: " << s2.front() << ", back: " << s2.back() << "\n";
    std::cout << "s2[1]: " << s2[1] << ", s2.at(1): " << s2.at(1) << "\n";

    try
    {
        s2.at(100); // Trebuie sa arunce exceptie
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "Exceptie prinsa fix cum trebuia pt s2.at(100): " << e.what() << "\n";
    }
    std::cout << "\n";

    std::cout << "=== Test 3: Modificare (push_back, pop_back, Operator+=) ===" << std::endl;
    sebi::string s5("Salut");
    s5.push_back('r');
    s5.push_back('z');
    std::cout << "Dupa push_back('r') si ('z'): " << s5.c_str() << "\n";

    s5.pop_back(); // Elimina 'z'
    std::cout << "Dupa pop_back(): " << s5.c_str() << "\n";

    s5 += '!'; // Operator+= char
    std::cout << "Dupa += '!': " << s5.c_str() << "\n";

    s5 += s4; // Operator+= string (" World!")
    std::cout << "Dupa += s4: " << s5.c_str() << "\n\n";

    std::cout << "=== Test 4: Concatenare (Operator+) ===" << std::endl;
    sebi::string s_left("Stanga ");
    sebi::string s_right("Dreapta");
    sebi::string s_combined = s_left + s_right;
    std::cout << s_left.c_str() << " + " << s_right.c_str() << " => " << s_combined.c_str() << "\n\n";

    std::cout << "=== Test 5: Cautare (find) ===" << std::endl;
    sebi::string s6("abracadabra");
    std::cout << "String: " << s6.c_str() << "\n";
    std::cout << "find('c'): " << s6.find('c') << " (asteptat 4)\n";
    std::cout << "find('z'): " << s6.find('z');
    if (s6.find('z') == sebi::string::npos)
    {
        std::cout << " (Returneaza npos cum era asteptat)\n";
    }
    std::cout << "\n";

    std::cout << "=== Test 6: Operatori relationali (==, !=, <, >) ===" << std::endl;
    sebi::string a("Mere");
    sebi::string b("Pere");
    sebi::string a2("Mere");

    std::cout << "a: " << a.c_str() << ", b: " << b.c_str() << "\n";
    std::cout << "a == a2 : " << (a == a2 ? "true" : "false") << "\n";
    std::cout << "a != b  : " << (a != b ? "true" : "false") << "\n";
    std::cout << "a < b   : " << (a < b ? "true" : "false") << "\n";
    std::cout << "b > a   : " << (b > a ? "true" : "false") << "\n\n";

    std::cout << "=== Test 7: Metode de baza (empty, clear, capacity) ===" << std::endl;
    sebi::string s7("Test string mare cu multa memorie alocata!");
    std::cout << "s7 size: " << s7.size() << ", capacity: " << s7.capacity() << "\n";
    s7.clear();
    std::cout << "Dupa clear -> isEmpty? " << (s7.empty() ? "Da" : "Nu") << " (size: " << s7.size() << ")\n";
    std::cout << "============================================\n\n";
}
void test_sebi_vector()
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
}

int main()
{
    sebi::string s("TEST TEST");
    sebi::string s1("AL DOILEA");
    s.append("1");
    s.append(s1);
    std::cout << s << "\n\n";
    for (auto c : s)
    {
        std::cout << c << std::endl;
    }
    sebi::string terminal;
    std::cin >> terminal;
    std::cout << "jfshajkf\n";
    std::cout << terminal << std::endl;
    s.push_back('X');
    std::cout << terminal << std::endl;
    s.push_back('X');
    std::cout << terminal << std::endl;
    // test_sebi_vector();
    // test_sebi_string();
    return 0;
}