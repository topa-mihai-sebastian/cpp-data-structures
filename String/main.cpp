#include <cstring>
#include <iostream>
#include <utility>

class String {
  public:
    // 1. Constructor Default
    String() {
        data = new char[1];
        size = 0;
        data[0] = '\0';
        std::cout << "-> Default Constructor apelat\n";
    }

    // 2. Constructor parametrizat
    String(const char *text) {
        if (text != nullptr) {
            size = std::strlen(text);
            data = new char[size + 1];
            std::memcpy(data, text, size + 1);
        } else {
            size = 0;
            data = new char[1];
            data[0] = '\0';
        }
        std::cout << "-> Parametrized Constructor apelat (" << data << ")\n";
    }

    // --- REGULA CELOR 5 ---

    // 1. Destructor
    ~String() {
        delete[] data;
        size = 0;
        // Fara cout aici pentru a nu polua output-ul la curatarea memoriei
    }

    // 2. Copy Constructor
    String(const String &a) {
        size = a.size;
        data = new char[size + 1];
        std::memcpy(data, a.data, size + 1);
        std::cout << "-> Copy Constructor apelat (" << data << ")\n";
    }

    // 3. Copy Assignment Operator
    String &operator=(const String &other) {
        if (this == &other) {
            return *this;
        }
        delete[] data;
        size = other.size;
        data = new char[size + 1];
        std::memcpy(data, other.data, size + 1);
        std::cout << "-> Copy Assignment apelat (" << data << ")\n";
        return *this;
    }

    // 4. Move Constructor
    String(String &&other) noexcept {
        size = other.size;
        data = other.data;
        other.size = 0;
        other.data = nullptr;
        std::cout << "-> Move Constructor apelat (" << data << ")\n";
    }

    // 5. Move Assignment Operator
    String &operator=(String &&other) noexcept {
        if (this == &other) {
            return *this;
        }
        delete[] data;
        data = other.data;
        size = other.size;
        other.size = 0;
        other.data = nullptr;
        std::cout << "-> Move Assignment apelat (" << data << ")\n";
        return *this;
    }

    // Metoda utilitara pentru afisare
    void print() const {
        if (data) {
            std::cout << "Data: " << data << " | Size: " << size << "\n";
        } else {
            std::cout << "Data: [GOL/MUTAT] | Size: 0\n";
        }
    }

  private:
    char *data;
    size_t size;
};

int main() {
    std::cout << "=== Test 1: Constructori ===\n";
    String s1;
    String s2("Salutare HFT!");

    std::cout << "\n=== Test 2: Copy Constructor ===\n";
    String s3 = s2; // Apeleaza copy constructor
    s3.print();

    std::cout << "\n=== Test 3: Copy Assignment ===\n";
    String s4("Text initial");
    s4 = s2; // Apeleaza copy assignment (s4 exista deja)
    s4.print();

    std::cout << "\n=== Test 4: Move Constructor ===\n";
    // std::move(s3) transforma lvalue (s3) intr-un rvalue temporar, fortand
    // mutarea
    String s5 = std::move(s3);
    s5.print();
    std::cout << "Dupa mutare, s3 a ramas: ";
    s3.print(); // Ar trebui sa fie gol/null

    std::cout << "\n=== Test 5: Move Assignment ===\n";
    String s6("Alt text");
    s6 = std::move(s4); // Apeleaza move assignment
    s6.print();
    std::cout << "Dupa mutare, s4 a ramas: ";
    s4.print();

    std::cout << "\n=== Sfarsit program (Destructoarele isi fac treaba) ===\n";
}

