#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> numToIndex; // stores number -> index
    for (int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i];
        if (numToIndex.find(complement) != numToIndex.end()) {
            // Found the two numbers
            return {numToIndex[complement], i};
        }
        numToIndex[nums[i]] = i;
    }
    return {}; // Should never reach here since problem guarantees one solution
}

int main() {
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;

    vector<int> result = twoSum(nums, target);
    cout << "[" << result[0] << ", " << result[1] << "]" << endl;

    // Additional test cases
    vector<int> nums2 = {3, 2, 4};
    target = 6;
    result = twoSum(nums2, target);
    cout << "[" << result[0] << ", " << result[1] << "]" << endl;

    vector<int> nums3 = {3, 3};
    target = 6;
    result = twoSum(nums3, target);
    cout << "[" << result[0] << ", " << result[1] << "]" << endl;

    return 0;
}
