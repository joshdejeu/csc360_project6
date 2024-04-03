using namespace std;

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <unordered_map>

vector<int> convertStringToVectorInt(string refs);
void printPageReference(vector<int> nums);
bool simulateAlgorithm(int mapped_algorithm, vector<int> page_refs, int frames);
bool isNumInVector(int num, vector<int> vec);

int main(int argc, char *argv[])
{
    vector<int> int_page_refs;
    string string_of_refs;
    int frame_count;
    string algorithms;

    string line;

    unordered_map<string, int> algorithmMap = {
        {"FIFO", 1},
        {"LRU", 2},
        {"OPT", 3},
        {"RAND", 4}};

    int input_section{1};
    // Loop through every line in txt file
    while (getline(cin, line))
    {
        // Skip empty lines
        if (line.empty())
            continue;
        switch (input_section++)
        {
        case 1:
            string_of_refs = line;
            int_page_refs = convertStringToVectorInt(string_of_refs);
            printPageReference(int_page_refs);
            break;
        case 2:
            frame_count = stoi(line);
            cout << "Number of frames: " << frame_count << endl;
            break;
        default:
            if (input_section >= 3)
                simulateAlgorithm(algorithmMap[line], int_page_refs, frame_count);
            break;
        }
    }

    for (auto s : algorithms)
    {
        cout << s << ": ";
    }
}

bool isNumInVector(int num, vector<int> vec)
{
    for (int n : vec)
    {
        if (n == num)
            return true;
    }
    return false;
}

// given an ID run an algoirthm on page refs with a frame
bool simulateAlgorithm(int mapped_algorithm, vector<int> page_refs, int frame_count)
{
    // initialize a vect of size 'frame_count' with all values of '-1'
    vector<int> frames(frame_count, -1);

    for (int page_ref : page_refs)
    {
        if (isNumInVector(page_ref, frames))
        {
            cout << "Yes!" << endl;
        }
    }

    switch (mapped_algorithm)
    {
    case 1:
        cout << "FIFO: ";
        break;
    case 2:
        cout << "\nLRU: ";
        break;
    case 3:
        cout << "\nOPT: ";
        break;
    case 4:
        cout << "\nRAND: ";
        break;
    default:
        return false;
        break;
    }
    return true;
}

vector<int> convertStringToVectorInt(string refs)
{
    vector<int> nums;
    stringstream ss(refs);
    int num;
    // Convert page ref string to vector of ints
    while (ss >> num)
    {
        nums.push_back(num);
    }
    return nums;
}

void printPageReference(vector<int> nums)
{
    cout << "\nPage Reference String:" << endl;
    int max_int_per_line = 20;
    int int_on_line_count = 1;
    for (auto num : nums)
    {
        ((int_on_line_count++) % max_int_per_line == 0) ? cout << num << endl : cout << num << " ";
    }
}