#include <string>
#include <unordered_map>
using namespace std;

// class Solution {
// public:

//     int firstUniqChar(string s) {

//         unordered_map<char, int> freq;

//         for(int i = 0; i < s.length(); i++)
//         {
//             freq[s[i]]++;
//         }

//         for(int j = 0; j < s.length(); j++)
//         {
//             if(freq[s[j]] == 1)
//             {
//                 return j;
//             }
//         }

//         return -1;

//     }

// };

class Solution {
public:
        int firstUniqChar(string s) {
            int freq[26] = {0};

            // Pass 1: Count each character
            for(int i = 0; i < s.length(); i++)
            {
                freq[s[i] - 'a']++;
            }


            // Pass 2: Find the first unique character
            for(int j = 0; j < s.length(); j++)
            {
                if(freq[s[j] - 'a'] == 1)
                {
                    return j;
                }
            }


            return -1;
        }
};