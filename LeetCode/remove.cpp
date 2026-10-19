#include <vector>
using namespace std;

// class Solution {
// public:
//     int removeElement(vector<int>& nums, int val) {
//         int size = nums.size();

//         for(int i = 0; i < size; i++)
//         {
//             if(nums[i] == val)
//             {
//                 for(int j = i + 1; j < size; j++)
//                 {
//                     nums[j - 1] = nums[j];
//                 }

//                 i--; // decrement i when an element is removed so that i checks the new spot
//                 size--; // decrease size when an element is removed and elements are shifted so the inner for loop does't access invalid values
//             }
//         }

//         return size;
//     }
// };

// class Solution {
// public:
//     int removeElement(vector<int>& nums, int val) {
//         int k = 0;

//         for (int i = 0; i < nums.size(); i++) {
//             if(nums[i] != val)
//             {
//                 nums[k] = nums[i];
//                 k++;
//             }
//         }

//         return k;
//     }
// };

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int k = 0;

        for(int i = 0; i < nums.size(); i++)
        {
            if(nums[i] != 0)
            {
                nums[k] = nums[i];
                k++;
            }
        }

        for(k; k < nums.size(); k++)
        {
            nums[k] = 0;
        }
    }
};
