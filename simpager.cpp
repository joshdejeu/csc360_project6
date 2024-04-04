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
bool simulateAlgorithm(int mapped_algorithm, vector<int> page_refs, int frames);
bool isNumInVector(int num, const vector<int> &vec);
void displayFrame(vector<int> frame);
int simFIFO(vector<int> page_refs, int frame_count);
int simLRU(vector<int> page_refs, int frame_count);
int simOPT(vector<int> page_refs, int frame_count);
int simRAND(vector<int> page_refs, int frame_count);

int generateRandomNumber(int n)
{
    // Created with trial an error using a question from a stack overflow forum
    // link: https://stackoverflow.com/questions/41489979/random-integers-from-a-function-always-return-the-same-number-why
    random_device rd;                           // random hardward number
    mt19937 eng(rd());                          // change randomness seed
    uniform_int_distribution<> distr(0, n - 1); // the range from 0 to n-1

    return distr(eng); // return randomly generated num
}

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

bool isNumInVector(int num, const vector<int> &vec)
{
    for (int n : vec)
    {
        if (n == num)
            return true;
    }
    return false;
}

void displayFrame(vector<int> frame)
{
    cout << endl;
    for (int n : frame)
        cout << n << ", ";
    cout << endl;
}

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

// given an ID run an algoirthm on page refs with a frame
bool simulateAlgorithm(int mapped_algorithm, vector<int> page_refs, int frame_count)
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