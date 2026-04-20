#include <vector>
#include <string>
#include <climits>
#include <iostream>
using namespace std;

#include <iostream>
#include <memory.h>
using namespace std;

int main() {
char star[201];
memset(star, '*', sizeof(star));

int n;
cin >> n;

for(int i = 0; i < n; i++)
{
    char str[201];
    memset(str, ' ', i);
    memcpy(str + i, star, 2 * n - 1 - (i * 2));
    str[2 * n - 2 - i] = '\n';
    cout << str;
}

    return 0;
}

int test()
{
    char str[100];
    memset(str, '*', sizeof(str));
    
    char out[100];
    memcpy(out, str, strlen(str));
}


int solution1(vector<string> arr) 
{
    vector<int> nums;
    vector<char> ops;

    // 1. 분리
    for (int i = 0; i < arr.size(); i++)
    {
        if (i % 2 == 0)
            nums.push_back(stoi(arr[i]));
        else
            ops.push_back(arr[i][0]);
    }

    int n = nums.size();

    vector<vector<int>> maxDP(n, vector<int>(n, INT_MIN));
    vector<vector<int>> minDP(n, vector<int>(n, INT_MAX));

    // 2. 초기값
    for (int i = 0; i < n; i++)
    {
        maxDP[i][i] = nums[i];
        minDP[i][i] = nums[i];
    }

    // 3. 구간 DP
    for (int len = 2; len <= n; len++)
    {
        for (int i = 0; i <= n - len; i++)
        {
            int j = i + len - 1;

            for (int k = i; k < j; k++)
            {
                if (ops[k] == '+')
                {
                    maxDP[i][j] = max(maxDP[i][j],
                                      maxDP[i][k] + maxDP[k + 1][j]);

                    minDP[i][j] = min(minDP[i][j],
                                      minDP[i][k] + minDP[k + 1][j]);
                }
                else // '-'
                {
                    maxDP[i][j] = max(maxDP[i][j],
                                      maxDP[i][k] - minDP[k + 1][j]);

                    minDP[i][j] = min(minDP[i][j],
                                      minDP[i][k] - maxDP[k + 1][j]);
                }
            }
        }
    }

    return maxDP[0][n - 1];
}

int solution(vector<string> arr)
{
    int answer = -1;
    int n = (arr.size() + 1 )/ 2;
    vector<vector<int>> dpMax(n, vector<int>(n, INT_MIN));
    vector<vector<int>> dpMin(n, vector<int>(n, INT_MAX));
    vector<char> signs;
    for (int i = 0; i < arr.size(); i++)
    {
        if (i % 2 == 0)
        {
            dpMin[i / 2][i / 2] = stoi(arr[i]);
            dpMax[i / 2][i / 2] = dpMin[i / 2][i / 2];
        }
        else
        {
            signs.push_back(arr[i][0]);
        }
    }
    
    // 구간 길이 2부터 시작 (숫자 2개 = 연산자 1개)
    for (int length = 2; length <= n; length++)  // in range(2, n+1):          # 구간 길이
    {
        for (int i = 0; i <= n - length; i++)   // 시작 인덱스
        {
            int j = i + length - 1;            // 끝 인덱스
        
            //# i ~ j 사이의 모든 "마지막 연산자 위치 k" 시도
            for (int k = i; k < j; k++)          //# k = 마지막으로 계산할 연산자 위치
            {
                // 여기서 op에 따라 dp[i][j] 갱신!
                if (signs[k] == '+')
                {
                    dpMin[i][j] = min(dpMin[i][j], dpMin[i][k] + dpMin[k+1][j]);
                    dpMax[i][j] = max(dpMax[i][j], dpMax[i][k] + dpMax[k+1][j]);
                }
                else
                {
                    dpMin[i][j] = min(dpMin[i][j], dpMin[i][k] - dpMax[k+1][j]);
                    dpMax[i][j] = max(dpMax[i][j], dpMax[i][k] - dpMin[k+1][j]);
                }
            }
        }
    }       
    
    answer = dpMax[0][n - 1];
    return answer;
}

int main()
{
    vector<string> arr({"5", "-", "3", "+", "1", "+", "2", "-", "4"});
    
    int ret = solution(arr);
    cout << ret << endl;
    
    return 0;
}