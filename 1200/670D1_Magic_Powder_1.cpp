#include<bits/stdc++.h>
using namespace std;

// || BINARY SEARCH ON ANSWER ||

// =========================================================
// MAXIMUM NUMBER OF COOKIES THAT CAN BE MADE
// =========================================================
//
// Problem (classic "Magic Powder" / Codeforces style):
//   You have n ingredients.
//   need[i] = amount of ingredient i required for ONE cookie.
//   have[i] = amount of ingredient i currently in stock.
//   k       = magic powder available (can substitute for ANY
//             single missing unit of any ingredient).
//
//   Find the MAXIMUM number of cookies you can bake.
//
// ---------------------------------------------------------
// KEY IDEA: BINARY SEARCH ON THE ANSWER
// ---------------------------------------------------------
//
// The answer (number of cookies) is monotonic:
//   If we can bake X cookies, we can also bake any count < X.
//   If we CANNOT bake X cookies, we cannot bake any count > X.
//
// So we binary search the largest feasible cookie count.
//
// Feasibility check for a candidate 'cookies':
//   total powder needed =
//       sum over i of max(0, cookies*need[i] - have[i])
//   Feasible if total powder needed <= k.
//
// ---------------------------------------------------------
// BOUNDS
// ---------------------------------------------------------
//
//   low  = 0
//   high = 2e9  (safe upper bound; answer fits in long long
//                because cookies*need[i] can overflow int)
//
// ---------------------------------------------------------
// COMPLEXITY
// ---------------------------------------------------------
//
//   powderNeeded : O(N)
//   binary search: O(log(2e9)) ≈ O(31)
//
//   TC: O(N * log(MAX))   ~  O(N * 31)
//   SC: O(1) extra (besides input arrays)
// =========================================================

// ---------------------------------------------------------
// FEASIBILITY CHECK
// ---------------------------------------------------------
// Returns true if we can bake 'cookies' cookies using the
// available stock 'have' plus at most k units of magic powder.
//
// For each ingredient:
//   required = cookies * need[i]
//   if required > have[i], we must cover the deficit
//   (required - have[i]) using magic powder.
//
// If at any point the accumulated powder exceeds k, we can
// early-exit with false (the candidate is infeasible).
bool isPossible(long long cookies, vector<int>& need, vector<int>& have, int k){
    int n = need.size();

    long long powder = 0;   // total magic powder consumed so far

    for(int i=0; i<n; i++){
        // amount of ingredient i required for 'cookies' cookies
        // (1LL forces 64-bit multiplication to avoid overflow)
        long long required = 1LL * cookies * need[i];

        // if stock is insufficient, the deficit must come
        // from magic powder
        if(required > have[i]){
            powder += required - have[i];
        }

        // pruning: already over budget -> infeasible
        if(powder > k){
            return false;
        }
    }

    // all ingredients covered within powder budget
    return (powder <= k);
}

// ---------------------------------------------------------
// BINARY SEARCH ON ANSWER
// ---------------------------------------------------------
// Finds the largest 'cookies' such that powderNeeded() is true.
//
// Standard lower/upper-bound style binary search:
//   - if mid is feasible, store it and search the RIGHT half
//     (we want the MAXIMUM feasible value)
//   - else search the LEFT half
long long maxCookies(vector<int>& need, vector<int>& have, int k){
    long long low = 0, high = 2e9;   // search space bounds
    long long ans = 0;               // best feasible answer found

    while(low <= high){
        // overflow-safe midpoint calculation
        long long mid = low + (high - low)/2;

        if(isPossible(mid, need, have, k)){
            // mid cookies are possible -> try for more
            ans = mid;
            low = mid + 1;
        }
        else{
            // mid cookies not possible -> reduce upper bound
            high = mid - 1;
        }
    }

    return ans;
}

int main(){
    int n, k;
    cin >> n >> k;

    // read required amount per cookie for each ingredient
    vector<int> need(n), have(n);
    for(int i=0; i<n; i++){
        cin >> need[i];
    }

    // read current stock for each ingredient
    for(int i=0; i<n; i++){
        cin >> have[i];
    }

    // print maximum cookies that can be baked
    cout << maxCookies(need, have, k) << endl;

    return 0;
}