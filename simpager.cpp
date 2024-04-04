//********************************************************************
//
// Josh Dejeu
// Operating Systems
// Project #6: Simulation of Page Replacement Strategies
// Due 4/3/2024
// Instructor: Dr. Siming Liu
//
//********************************************************************

using namespace std;

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <unordered_map>
#include <queue>  //fifo
#include <stack>  //lru
#include <random> //rand

vector<int> convertStringToVectorInt(string refs);
void printPageReference(vector<int> nums);
bool simulateAlgorithms(int mapped_algorithm, vector<int> page_refs, int frames);
bool isNumInVector(int num, const vector<int> &vec);
int simFIFO(vector<int> page_refs, int frame_count);
int simLRU(vector<int> page_refs, int frame_count);
int simOPT(vector<int> page_refs, int frame_count);
int simRAND(vector<int> page_refs, int frame_count);

//********************************************************************
//
// Generate Random Number
//
// This function generates a random number between 0 and a given number
// n exclusive.
//
// Return Value
// ------------
// int                         Random number between 0 and n-1
//
// Value Parameters
// ----------------
// n		int                 The upper bound of random number
//
//*******************************************************************
int generateRandomNumber(int n)
{
    // Created with trial an error using a question from a stack overflow forum
    // link: https://stackoverflow.com/questions/41489979/random-integers-from-a-function-always-return-the-same-number-why
    random_device rd;                           // random hardward number
    mt19937 eng(rd());                          // change randomness seed
    uniform_int_distribution<> distr(0, n - 1); // the range from 0 to n-1

    return distr(eng); // return randomly generated num
}

//********************************************************************
//
// Main
//
// This function takes in inputs from a text file and runs
// frame swapping algorithms found in the txt file
//
// Return Value
// ------------
// int                         Success/Fail
//
// Value Parameters
// ----------------
// argc		int                Count of cmd line arguments
// *argv    char               Point to 'string' of arguments from cmd line
//
//*******************************************************************
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
                simulateAlgorithms(algorithmMap[line], int_page_refs, frame_count);
            break;
        }
    }

    for (auto s : algorithms)
    {
        cout << s << ": ";
    }
}

//********************************************************************
//
// Is Number In Vector
//
// This function returns true/false if a given number exists within
// a given vector of ints
//
// Return Value
// ------------
// bool                 True if number exists else false
//
// Value Parameters
// ----------------
// num		int             The number to search for
//
// Reference Parameters
// --------------------
// vec     vector<int>      The vector of ints to search
//
//*******************************************************************
bool isNumInVector(int num, const vector<int> &vec)
{
    for (int n : vec)
    {
        if (n == num)
            return true;
    }
    return false;
}

//********************************************************************
//
// Simulate First-In First-Out
//
// This function simulates the FIFO pageswap algorithm given page references
// and frame count. It counts the number of frame misses and returns it.
//
// Return Value
// ------------
// int                            The count of frame misses
//
// Value Parameters
// ----------------
// page_refs		vector<int>   The page reference ints
// frame_count		int           The number of frames to store references in
//
//*******************************************************************
int simFIFO(vector<int> page_refs, int frame_count)
{
    int miss_count = 0;
    int frames_filled = 0;
    queue<int> fifo_queue;

    // initialize a vect of size 'frame_count' with all values of '-1'
    vector<int> frames(frame_count, -1);

    for (int i = 0; i < page_refs.size(); i++)
    {
        bool frame_hit = (isNumInVector(page_refs[i], frames));
        if (frame_hit)
        {
            continue;
        }
        // empty frame exists
        else if (frames_filled < frame_count)
        {
            frames[frames_filled] = page_refs[i];
            fifo_queue.push(frames_filled++);
            miss_count++;
        }
        // frame miss
        else
        {
            int victimn_frame_index = fifo_queue.front();
            fifo_queue.pop();
            frames[victimn_frame_index] = page_refs[i];
            fifo_queue.push(victimn_frame_index++ % 3);
            miss_count++;
        }
    }

    return miss_count;
}

//********************************************************************
//
// Simulate Least Recently Used
//
// This function simulates the LRU pageswap algorithm given page references
// and frame count. It counts the number of frame misses and returns it.
//
// Return Value
// ------------
// int                            The count of frame misses
//
// Value Parameters
// ----------------
// page_refs		vector<int>   The page reference ints
// frame_count		int           The number of frames to store references in
//
//*******************************************************************
int simLRU(vector<int> page_refs, int frame_count)
{
    int miss_count = 0;
    int frames_filled = 0;
    // initialize a vect of size 'frame_count' with all values of '-1'
    vector<int> frames(frame_count, -1);
    stack<int> lru_stack;

    for (int i = 0; i < page_refs.size(); i++)
    {
        bool frame_hit = (isNumInVector(page_refs[i], frames));
        if (frame_hit)
        {
            continue;
        }
        // empty frame exists
        else if (frames_filled < frame_count)
        {
            frames[frames_filled] = page_refs[i];
            lru_stack.push(frames_filled++);
            miss_count++;
        }
        // frame miss
        else
        {
            int victimn_frame_index = lru_stack.top();
            lru_stack.pop();
            frames[victimn_frame_index] = page_refs[i];
            lru_stack.push(victimn_frame_index++ % 3);
            miss_count++;
        }
    }

    return miss_count;
}

//********************************************************************
//
// Simulate Optimal
//
// This function simulates the OPT pageswap algorithm given page references
// and frame count. It counts the number of frame misses and returns it.
//
// Return Value
// ------------
// int                            The count of frame misses
//
// Value Parameters
// ----------------
// page_refs		vector<int>   The page reference ints
// frame_count		int           The number of frames to store references in
//
//*******************************************************************
int simOPT(vector<int> page_refs, int frame_count)
{
    int miss_count = 0;
    int frames_filled = 0;
    // initialize a vect of size 'frame_count' with all values of '-1'
    vector<int> frames(frame_count, -1);

    for (int i = 0; i < page_refs.size(); i++)
    {
        bool frame_hit = (isNumInVector(page_refs[i], frames));
        if (frame_hit)
        {
            continue;
        }
        // empty frame exists
        else if (frames_filled < frame_count)
        {
            frames[frames_filled++] = page_refs[i];
            miss_count++;
        }
        // frame miss
        else
        {
            int max_future_index = -1;
            int victimn_frame_index = -1;

            // check which number appears latest in future
            for (int j = 0; j < frame_count; j++)
            {
                int frame_to_find = frames[j];
                int latest_use_index = 0;

                // remove that number from frame copy
                // the last number to remain will be the latest num used
                for (int k = i + 1; k < page_refs.size(); k++)
                {
                    if (page_refs[k] == frame_to_find)
                    {
                        latest_use_index = k;
                        break;
                    }
                }

                if (latest_use_index == 0)
                {
                    victimn_frame_index = j;
                    break;
                }

                if (latest_use_index > max_future_index)
                {
                    max_future_index = latest_use_index;
                    victimn_frame_index = j;
                }
            }

            frames[victimn_frame_index] = page_refs[i];
            miss_count++;
        }
    }

    return miss_count;
}

//********************************************************************
//
// Simulate Random
//
// This function simulates the RAND pageswap algorithm given page references
// and frame count. It counts the number of frame misses and returns it.
//
// Return Value
// ------------
// int                            The count of frame misses
//
// Value Parameters
// ----------------
// page_refs		vector<int>   The page reference ints
// frame_count		int           The number of frames to store references in
//
//*******************************************************************
int simRAND(vector<int> page_refs, int frame_count)
{
    int miss_count = 0;
    int frames_filled = 0;

    // initialize a vect of size 'frame_count' with all values of '-1'
    vector<int> frames(frame_count, -1);

    for (int i = 0; i < page_refs.size(); i++)
    {
        bool frame_hit = (isNumInVector(page_refs[i], frames));
        if (frame_hit)
        {
            continue;
        }
        // empty frame exists
        else if (frames_filled < frame_count)
        {
            frames[frames_filled++] = page_refs[i];
            miss_count++;
        }
        // frame miss
        else
        {
            int victimn_frame_index = generateRandomNumber(3);
            frames[victimn_frame_index] = page_refs[i];
            miss_count++;
        }
    }
    return miss_count;
}

//********************************************************************
//
// Simulate Algorithms
//
// This function runs any algorithms specified in a txt file on data
// parsed from that same file, given a vector of ints for page references
// and an int for frame count
//
// Return Value
// ------------
// bool                 Success/Fail to turn an algorithm
//
// Value Parameters
// ----------------
// mapped_algorithm		int             Id of frame-swap algorithm mapped to an int
// page_refs		    vector<int>     The page reference numbers
// frame_count		    int             The count of frames
//
//*******************************************************************
bool simulateAlgorithms(int mapped_algorithm, vector<int> page_refs, int frame_count)
{

    switch (mapped_algorithm)
    {
    case 1:
        cout << "FIFO: " << simFIFO(page_refs, frame_count);
        break;
    case 2:
        cout << "LRU: " << simLRU(page_refs, frame_count);
        break;
    case 3:
        cout << "OPT: " << simOPT(page_refs, frame_count);
        break;
    case 4:
        cout << "RAND: " << simRAND(page_refs, frame_count);
        break;
    default:
        return false;
    }

    cout << endl;
    return true;
}

//********************************************************************
//
// Convert String To Vector
//
// This function takes a string of integers seperated by spaces and
// populates a vector with the numbers between each space.
//
// Return Value
// ------------
// vector<int>                 The vector with all the ints
//
// Value Parameters
// ----------------
// refs		string             The string with numbers seperated by spaces
//
//*******************************************************************
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

//********************************************************************
//
// Print Page Reference
//
// This function prints all the ints parsed from the number string
//
// Return Value
// ------------
// void
//
// Value Parameters
// ----------------
// nums		vector<int>         A vector of ints
//
//*******************************************************************
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