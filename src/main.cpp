#include <iostream>
#include<string>
#include <cstring>
#include <fstream>
#include <algorithm>
using namespace std;

void erase_leading_spaces(string* string_var)
{

    int index = 0;
    while (index < string_var->size() && string_var->at(index) == ' ')
    {
        index++;
    }
    if (index >= string_var->size())
    {
        *string_var = "";
        return;
    }
    *string_var = string_var->substr(index);

}


void erase_trailing_spaces(string* string_var)
{
    int index = string_var->size() - 1;
    while (index  >= 0 && string_var->at(index) == ' ')
    {
        index--;
    }
    if (index == -1)
    {
        *string_var = "";
        return;
    }
    *string_var = string_var->substr(0,index + 1);
}
bool check_filename_is_empty(string* filename)
{
    erase_leading_spaces(filename);
    erase_trailing_spaces(filename);
    return filename->empty();
}
bool check_valid_token_length(string* filename, string* suffix, int length, const char* splitter)
{
    const int _count = static_cast<int>(count(filename->begin(), filename->end(), *splitter));
    return _count == length - 1;
}
bool check_valid_suffix(string* filename, string* suffix, const char* splitter)
{
    string value = "";
    for (int index = filename->size() - 1 ; index >= 0 ; index--)
    {
        if (filename->at(index) == *splitter)break;
        value += filename->at(index);
    }
    reverse(value.begin(), value.end());
    return value == *suffix;
}

bool check_valid_filename(string* filename, const char* splitter ,  string* suffix, int token_length)
{
    //it might be better to return a string of error messages or success
    if (check_filename_is_empty(filename))
    {
        cerr << "Invalid Filename" << endl;
        cerr << "Filename cannot be empty" << endl;
        return false;
    }
    if (!check_valid_token_length(filename, suffix, token_length,splitter))
    {
        cerr << "Invalid Filename" << endl;
        cerr << "Correct Usage: hydro " << "<input_file.hy> ,eg: test.hy" << endl;
        return false;
    }
    if (!check_valid_suffix(filename, suffix, splitter))
    {
        cerr << "Invalid Filename" << endl;
        cerr << "Correct Filename should have the suffix .hy" << endl;
        return false;
    }
    return true;
}

int main(int argc , char* argv[])
{  

    if (argc != 2)
    {
        cerr << "Incorrect number of arguments" << endl;
        cerr << "Correct Usage: hydro " << "<input_file.hy>" << endl;
        return EXIT_FAILURE;
    }
    //erase leading and trailing spaces
    string filename = argv[1];
    const char* splitter = ".";
    const int TOKEN_LENGTH = 2;
    string suffix = "hy";
    if (!check_valid_filename(&filename, splitter,&suffix,TOKEN_LENGTH))
    {
        cerr << "Incorrect number of arguments" << endl;
        cerr << "Correct Usage: hydro " << "<input_file.hy>" << endl;
        return EXIT_FAILURE;
    }
    cout << filename << endl;

    //make sure the file exists

    //read the file

    return EXIT_SUCCESS;
}