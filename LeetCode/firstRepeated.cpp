
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int firstRepeated(vector<int>& nums) {
        unordered_set<int> seen;

        for(int i = 0; i < nums.size(); i++)
        {
            if(seen.count(nums[i]))
            {
                return nums[i];
            }

            seen.insert(nums[i]);
        }

        return -1;
    }
};
