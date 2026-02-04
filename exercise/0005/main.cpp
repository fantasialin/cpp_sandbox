#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <iomanip>
#include <cmath>
#include <limits>
#include <chrono>

using namespace std;
using namespace chrono;

#if 0
#define JOE_TIME_PROFILE_INIT()
#define JOE_TIME_PROFILE_START()
#define JOE_TIME_PROFILE_COUNT(message)
#else

#define JOE_TIME_PROFILE_INIT() \
  std::chrono::microseconds delta;\
  std::chrono::microseconds start_;\
  std::chrono::microseconds now_;

#define JOE_TIME_PROFILE_START() start_ = duration_cast<microseconds>(system_clock::now().time_since_epoch());

#define JOE_TIME_PROFILE_COUNT(message) \
  now_ = duration_cast<microseconds>(system_clock::now().time_since_epoch());\
  delta = (now_ - start_);\
  start_ = now_;\
  std::cout << message << " : " << (delta.count() / 1.0f) << " us\n";
  //std::cout << message << " : " << (delta.count() / 1000.0f) << " ms\n";
#endif

bool debug_log = false;

typedef vector<vector<int>> Array_2D;

int maxSubArray_BF(vector<int>& nums){
    int n = nums.size();
    Array_2D sum(n, vector<int>(n,0));
    // -int_max
    int maximum = -2147483648; 
    // designate start position
    for (int start = 0; start < n; start++){
        // designate region
        for (int finish = start ; finish < n; finish++){
            sum[start][finish] = 0;
            // calculate region sum
            for (int k = start; k <= finish; k++){
                sum[start][finish] += nums[k];
            }
            if (sum[start][finish] > maximum){
                maximum = sum[start][finish];
                if(debug_log)
                    std::cout << "[ " << start << ", " << finish << " ] ==> result " << maximum << "\n";
            }
        }
    }
    return maximum;
}

int maxSubArray_BF_improve(vector<int>& nums){
    int n = nums.size();
    // 儲存每個從開頭開始的區間的和
    vector<int>sum_1_to_n(n,0);
    // 儲存所有區間的和
        Array_2D sum(n, vector<int>(n,0));
    int maximum = -2147483648; // -int_max
    // 先計算每個從開頭開始的區間的元素和，複雜度 O(n)
    for (int i = 0; i < n; i++){
        if (i == 0)
            sum_1_to_n[i] = nums[0];
        else
            sum_1_to_n[i] = sum_1_to_n[i - 1] + nums[i];
    }
    // 利用 [0, finish] 和 [0, start-1] 兩個區間和的差
    // 計算其他區間的元素和，複雜度降到 O(n^2)
    for (int start = 0; start < n; start++){
        for (int finish = start ; finish < n ; finish++){
            // start!=0
            if (start){
                // 這層的複雜度從 O(n) 優化成 O(1)
                sum[start][finish] = sum_1_to_n[finish] - sum_1_to_n[start - 1];
            }
            // start==0
            else{
                sum[start][finish] = sum_1_to_n[finish];
            }
            if (sum[start][finish] > maximum){
                maximum = sum[start][finish];
                if(debug_log)
                    std::cout << "[ " << start << ", " << finish << " ] ==> result " << maximum << "\n";
            }
        }
    }
    return maximum;
}

int maxCrossArray(vector<int>& nums){
    int len = nums.size();
    int middle = (len - 1) / 2;
    int max_center = nums[middle];
    int index_left = -1, index_right = 1;
    int left_sum = 0, right_sum = 0;
    int max = -2147483648;

    while(middle + index_left >= 0){
        left_sum += nums[middle + index_left];
        if (left_sum > max)
            max = left_sum;
        index_left--;
    }

    // 如果往左會變大，就累加
    if(max > 0)
        max_center += max;
    max = -2147483648;

    while(middle + index_right < len){
        right_sum += nums[middle + index_right];
        if(right_sum > max)
            max = right_sum;
        index_right++;
    }

    // 如果往右會變大，就累加
    if(max > 0)
        max_center += max;

    return max_center;
} // end of maxCrossArray

int maxSubArray_divide_conquer(vector<int>& nums){
    // 取得整數陣列 nums 的長度
    int len = nums.size();

    // 例外處理：陣列中沒有資料，回傳整數最小值
    if (len == 0)
        return -2147483648;
    // 例外處理：陣列中只有一筆資料，回傳該筆資料
    if (len == 1)
        return nums[0];

    // 一般情況
    // 訂出 data_left 和 data_right 的範圍
    // 中間元素的迭代器
    auto middle = nums.begin() + len / 2;
    vector<int> data_left(nums.begin(), middle);
    vector<int> data_right(middle, nums.end());

    // 分成三個子問題處理
    int max_left = maxSubArray_divide_conquer(data_left);
    int max_right = maxSubArray_divide_conquer(data_right);
    int max_center = maxCrossArray(nums);

    // 回傳最大值
    if (max_left >= max_center &&
        max_left >= max_right)
        return max_left;
    else if (max_right >= max_center &&
                max_right >= max_left)
        return max_right;
    else
        return max_center;
} // end of maxSubArray



// max sub-array
int main(int argc, char **argv){
    cout << "exercise - 0005" << endl;
    // debug_log = true; //if output debug log

    std::vector<int> data = {8, -5, -1, 4, -3, 6, 2, -2, 3, 4};
    JOE_TIME_PROFILE_INIT()

    cout << "Brute Force" << endl;
    JOE_TIME_PROFILE_START()
    int result = maxSubArray_BF(data);
    std::string str = std::string("max sub-array BF => ") + to_string(result);
    JOE_TIME_PROFILE_COUNT(str)
    cout << endl;

    cout << "Brute Force improve" << endl;
    JOE_TIME_PROFILE_START()
    result = maxSubArray_BF_improve(data);
    str = std::string("max sub-array BF improve => ") + to_string(result);
    JOE_TIME_PROFILE_COUNT(str)
    cout << endl;


    cout << "divide and conquer" << endl;
    JOE_TIME_PROFILE_START()
    result = maxSubArray_divide_conquer(data);
    str = std::string("max sub-array divide and conquer => ") + to_string(result);
    JOE_TIME_PROFILE_COUNT(str)
    cout << endl;

    return 0;
};
