#include <iostream>
using namespace std;
int main(int argc , char* argv[])
{  

    if (argc != 2)
    {
        cerr << "Incorrect number of arguments" << endl;
        cerr << "Correct Usage: " << argv[0] << " <input_file.hy>" << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}