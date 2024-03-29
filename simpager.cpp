using namespace std;

#include <iostream>

string page_refs;
string frames;
string algorithms;

void printStats();

int main(int argc, char *argv[])
{
    string line;

    int input_section{1};
    // Loop through every line in txt file
    while (getline(cin, line))
    {
        // Skip empty lines
        if (line.empty())
            continue;
        switch (input_section++)
        {
        case 1:;
            page_refs = line;
            break;
        case 2:
            frames = line;
            break;
        default:
            if (input_section >= 3)
                algorithms += line + " ";
            break;
        }
    }

    printStats();
}

void printStats()
{
    cout << page_refs << endl;
    cout << "Number of frames: " << frames << endl;
    cout << algorithms << endl;
}