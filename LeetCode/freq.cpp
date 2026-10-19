#include <vector>
#include <unordered_map>
using namespace std;

int main()
{
    unordered_map<int, int> freq;
    

    vector<int> nums = {1, 3, 3, 2, 1, 3};

    for (int i = 0; i < nums.size(); i++)
    {
        freq[nums[i]]++;
    }

    int bestValue = nums[0];
    int bestFrequency = 0;

    for (auto entry : freq)
    {
        int value = entry.first;
        int frequency = entry.second;

        if (frequency > bestFrequency || (frequency == bestFrequency && value < bestValue))
        {
            bestValue = value;
            bestFrequency = frequency;
        }
    }
    return bestValue;
}
