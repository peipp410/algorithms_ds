# 找第K大元素

虽然这个不算什么高级的内容，也不应该出现在这，但是本菜鸡还是得复习一下。

原题链接：https://leetcode-cn.com/problems/kth-largest-element-in-an-array/

**法一：基于快排**

```c++
class Solution {
public:
    int partition(vector<int>&nums, int l, int r){
        int randIndex = l + rand()%(r-l+1);
        swap(nums[l], nums[randIndex]);
        int pivot = nums[l];
        while(l < r){
            while(l < r && nums[r] > pivot) r--;
            if (l < r){
                nums[l] = nums[r];
                l++;
            }
            while(l < r && nums[l] < pivot) l++;
            if (l < r){
                nums[r] = nums[l];
                r--;
            }
        }
        nums[l] = pivot;
        return l;
    }
    int find(vector<int> nums, int k, int l, int r){
        int mid = partition(nums, l, r);
        if (mid == nums.size() - k) return nums[mid];
        else if (mid < nums.size() - k) return find(nums, k, mid+1, r);
        else return find(nums, k, l, mid-1);
    }
    int findKthLargest(vector<int>& nums, int k) {
        return find(nums, k, 0, nums.size()-1);
    }
};
```

为了避免毒瘤数据，在划分前得随机选取pivot，接下来的操作和标准快排没太大区别。

**法二：基于堆**

```c
void percolateUp(int* nums, int i){
    while(i > 0 && nums[(i-1)/2] > nums[i]){
        int tmp = nums[(i-1)/2];
        nums[(i-1)/2] = nums[i];
        nums[i] = tmp;
        i = (i-1)/2;
    }
}
void percolateDown(int* nums, int i, int n){
    while (i*2+1 <= n){
        int j = i*2+1;
        if (j+1 <= n && nums[j+1] < nums[j]) j++;
        if (nums[i] <= nums[j]) break;
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
        i = j;
    }
}
int findKthLargest(int* nums, int numsSize, int k){
    for (int i = 0; i < k; i++){
        percolateUp(nums, i);
    }
    for (int i = k; i < numsSize; i++){
        if (nums[i] > nums[0]){
            nums[0] = nums[i];
            percolateDown(nums, 0, k-1);
        }
    }
    return nums[0];
}
```

