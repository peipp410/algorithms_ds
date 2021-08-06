# lower_bound and upper_bound

c++中提供lower_bound()和upper_bound()函数。前者功能为查找数组中第一个大于等于目标值的数所出现的位置，后者功能为查找第一个大于目标值的数所出现的位置。

```c++
int lb(vector<int>& nums, int target, int l, int r){
	int mid;
	while(l < r){
		mid = (l+r)>>1;
		if (nums[mid] >= target) r = mid;
		else l = mid + 1;
	}
	return l;
}
```

```c++
int ub(vector<int>& nums, int target, int l, int r){
    int mid;
    while(l < r){
        mid = (l+r)>>1;
        if (nums[mid] > target) r = mid;
        else l = mid + 1;
    }
    return l;
}
```

