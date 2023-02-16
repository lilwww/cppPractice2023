#include <fstream>
#include <limits>
#include <iostream>
using namespace std;
void GotoLine(std::fstream &file, unsigned int num)
{
    file.seekg(std::ios::beg);
    for (int i = 0; i < num - 1; ++i)
    {
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void replace(const string &filename)
{

    fstream fs(filename);
    if (!fs)
    {
        cerr << "ofs open " << filename << " error!" << endl;
        return;
    }
    GotoLine(fs, 8);

    getline(fs,)
    fs.close();
}

]
int main()
{
    using namespace std;
    fstream file("bla.txt");
    GotoLine(file, 8);
    string line8;
    file >> line8;
    cout << line8;
    cin.get();
    return 0;
}
