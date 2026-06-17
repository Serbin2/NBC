#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

long long explored = 0;   // 탐색한 노드 수 (자동 집계 — 건드리지 마세요)

// idx번째 상품부터 "담는다 / 안 담는다"를 결정합니다.
//   sum    = 지금까지 담은 금액의 합
//   target = 정확히 맞춰야 하는 예산
//   반환   = 합을 정확히 target으로 만드는 경우의 수
// ※ prices는 오름차순으로 정렬되어 들어옵니다 (정렬이 가지치기를 돕는다)
long long countWays(const vector<int>& prices, int idx, int sum, int target) {
    explored++;   // 이 함수가 호출될 때마다 노드 1개 탐색

    // [TODO 1] 성공 — 합이 정확히 target이 되었다면 경우의 수 1.
    //          (모든 가격은 양수 → 여기서 더 담으면 반드시 초과합니다)
    if (sum == target) return 1;

    // [TODO 2] 가지치기 — 이미 target을 넘었다면, 더 내려가볼 필요가 있을까요?
    //          (이 한 줄이 없어도 정답은 맞습니다. 하지만 "탐색 노드 수"가 크게 달라져요)
    if (sum > target) return 0;

    // [TODO 3] 실패 — 모든 상품을 다 살펴봤는데 합을 못 맞췄다면 경우의 수 0.
    if (idx == static_cast<int>(prices.size())) return 0;

    // [TODO 4] 선택 — idx번째 상품을 "담는 경우"와 "안 담는 경우", 두 갈래로 재귀.
    long long withItem    = countWays(prices, idx + 1, sum + prices[idx], target);   // idx번째를 담는다
    long long withoutItem = countWays(prices, idx + 1, sum, target);                 // idx번째를 건너뛴다

    return withItem + withoutItem;
}

// ───────────── 채점용 main (수정 금지) ─────────────
int main() {
    int pass = 0, total = 0;

    auto check = [&](vector<int> prices, int target, long long expected, string name) {
        total++;
        sort(prices.begin(), prices.end());   // 정렬은 백트래킹의 동반자
        explored = 0;
        long long got = countWays(prices, 0, 0, target);
        bool ok = (got == expected);
        if (ok) pass++;
        long long maxNodes = (1LL << (prices.size() + 1)) - 1;   // 가지치기 없는 이론상 최대
        cout << (ok ? "[PASS] " : "[FAIL] ") << name
             << " — 기대값 " << expected << ", 내 답 " << got
             << "  (탐색 노드 " << explored << " / 최대 " << maxNodes << ")" << endl;
    };

    check({5, 12, 8, 3, 7},                15, 3,  "테스트 1: 상품 5개, 예산 15");
    check({2, 4, 6, 8},                    10, 2,  "테스트 2: 상품 4개, 예산 10");
    check({3, 3, 3},                        6, 3,  "테스트 3: 같은 가격 3개");
    check({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 10, 10, "테스트 4: 상품 10개, 예산 10");

    cout << endl << pass << " / " << total << " 통과"
         << (pass == total ? " — 수고했습니다, 시험 끝!" : " — TODO를 다시 살펴보세요.") << endl;
    return 0;
}