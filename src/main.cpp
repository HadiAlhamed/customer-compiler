#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <sstream>
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
    clog << "string after erasing leading spaces: " << endl;
    clog << *string_var << endl;

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
    clog << "string after erasing trailing spaces: " << endl;
    clog << *string_var << endl;
}
bool check_filename_is_empty(string* filename)
{
    erase_leading_spaces(filename);
    erase_trailing_spaces(filename);
    return filename->empty();
}
bool check_valid_token_count(string* filename, int token_count, const char* splitter)
{
    //handle this case: ./test.hy
    //handle this case: ../../../test.hy
    //handle this case : ../../../dir1/dir2/test.hy
    string same_dir = "./";
    string backward_dir = "../";
    char DOT = '.';
    char SLASH = '/';
    int count_dots{} , count_slashes{};
    int filename_index_start = 0;
    for (int index = 0 ; index < filename->size() ; index ++)
    {
        filename_index_start = index + 1;
        if (count_dots >= 3)
        {
            return false;//file directory cannot have .../
        }
        if (count_slashes >= 2)
        {
            return false;//file directory cannot have .//, let's be strict for now
            //later we can collapse them into one: ..////// becomes ../
        }
        if (filename->at(index) == DOT)
        {
            count_dots++;
        }else if (filename->at(index) == SLASH)
        {
            //check if we have ../ or ./
            if (count_dots == 1)
            {
                //we reached ./ so after it must have a valid filename, if not, later checks will figure it out.
                break;
            }else if (count_dots == 2)
            {
                //prepare for the next possible ../ or ./
                count_dots = 0;
                count_slashes = 0;
            }
        }else
        {
            filename_index_start = index;
            break;
        }
    }

    string real_filename = filename->substr(filename_index_start);
    int count_splits = count(real_filename.begin() , real_filename.end() ,  DOT);
    return count_splits + 1 == token_count;
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

bool check_valid_filename(string* filename, const char* splitter ,  string* suffix, int token_count)
{
    //it might be better to return a string of error messages or success
    if (check_filename_is_empty(filename))
    {
        cerr << "Invalid Filename" << endl;
        cerr << "Filename cannot be empty" << endl;
        return false;
    }
    if (!check_valid_token_count(filename, token_count,splitter))
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
    const int TOKEN_COUNT = 2;
    string suffix = "hy";
    if (!check_valid_filename(&filename, splitter,&suffix,TOKEN_COUNT))
    {
        cerr << "Incorrect number of arguments" << endl;
        cerr << "Correct Usage: hydro " << "<input_file.hy>" << endl;
        return EXIT_FAILURE;
    }
    cout << filename << endl;

    //make sure the file exists
    //read the file
    string file_contents = "";
    {
        stringstream file_contents_stream;
        fstream input(filename, ios::in);//we are only reading from it
        file_contents_stream << input.rdbuf();
        file_contents = file_contents_stream.str();
    }

    cout << "file contents:" << endl;
    cout << file_contents << endl;

    return EXIT_SUCCESS;
}