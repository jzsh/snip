class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> nums_map;// nums[i] <-> i

        for(int i=0; i < nums.size(); i++) {
            int toFind = target - nums[i];
            if(nums_map.find(toFind) != nums_map.end()) {
                return { nums_map[toFind], i};
            }
            nums_map[nums[i]] = i;
        }
        return {};
    }
};
