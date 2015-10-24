/**
 * Конвертируем текстовый файл простых чисел с сайта https://primes.utm.edu/lists/small/millions/
 */
#include <fstream>
#include <iostream>
#include <sstream>
#include <cerrno>
using namespace std;
int main(int argc, char **argv) {

    if (argc != 3)
    {
            cout << "USE: " << argv[0] << " <input_file> <output_file>" << endl;
            return 1;
    }

    ios_base::sync_with_stdio(false);
    std::ifstream in(argv[1], ios::in);

    if (!in) {
        cout << "File " << argv[1] << " doesn't open";
    }

    std::ofstream out(argv[2], ios::out|ios::binary|ios::trunc);

    if (!out) {
        cout << "File " << argv[1] << " doesn't open";
    }

    unsigned int number;
    int count = 0;

    while (!in.eof()) {
        in >> number;
        out.write(reinterpret_cast<char *>(&number), sizeof(number));
        count++;
    }

    out.close();
    in.close();

    cout << count << " numbers";

}
