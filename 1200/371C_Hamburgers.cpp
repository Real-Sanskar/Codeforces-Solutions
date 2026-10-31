#include<bits/stdc++.h>
using namespace std;

// || BINARY SEARCH ON ANSWER ||

// =========================================================
// MAXIMUM NUMBER OF BURGERS THAT CAN BE MADE
// =========================================================
//
// Problem (classic "Hamburgers" / Codeforces style):
//   A burger recipe is given as a string s over {B, S, C}.
//   The string tells how many of each ingredient are needed
//   for ONE burger:
//       need[0] = count of 'B' (Bread)
//       need[1] = count of 'S' (Sausage)
//       need[2] = count of 'C' (Cheese)
//
//   have[i]  = current stock of ingredient i.
//   price[i] = cost to buy ONE unit of ingredient i.
//   r        = total money available.
//
//   Find the MAXIMUM number of burgers that can be made,
//   buying any missing ingredients with the available money.
//
// ---------------------------------------------------------
// KEY IDEA: BINARY SEARCH ON THE ANSWER
// ---------------------------------------------------------
//
// The answer (number of burgers) is monotonic:
//   - If we can make X burgers, we can make any count < X.
//   - If we cannot make X burgers, we cannot make any count > X.
//
// So we binary search the largest feasible burger count.
//
// Feasibility check for a candidate 'burgers':
//   For each ingredient i:
//       required = burgers * need[i]
//       if required > have[i]:
//           missing = required - have[i]
//           money  += price[i] * missing
//   Feasible if total money needed <= r.
//
// ---------------------------------------------------------
// BOUNDS
// ---------------------------------------------------------
//
//   low  = 0
//   high = 2e12
//     - burger count can grow large because the recipe
//       string length can be up to 100, and r up to 1e12,
//       so the answer can exceed 32-bit int range.
//     - 2e12 is a safe upper bound (fits in long long).
//
// ---------------------------------------------------------
// COMPLEXITY
// ---------------------------------------------------------
//
//   isPossible  : O(3) = O(1)   (only 3 ingredients)
//   binary search: O(log(2e12)) ≈ O(41)
//
//   TC: O(log(MAX))      practically O(1) per check
//   SC: O(1) extra
// =========================================================

// ---------------------------------------------------------
// FEASIBILITY CHECK
// ---------------------------------------------------------
// Returns true if we can make 'burgers' burgers using
// current stock 'have' and buying deficits at 'price',
// spending at most r money.
//
// For each of the 3 ingredients:
//   required = burgers * need[i]
//   if required > have[i]:
//       buy (required - have[i]) units at price[i]
//       add that cost to 'money'
//
// Early exit: if money already exceeds r, this candidate
// is infeasible — no need to check the rest.
bool isPossible(long long burgers, vector<int>& need, vector<int>& have, vector<int>& price, long long r){

    long long money = 0;    // total money spent so far

    // only 3 ingredients (B, S, C)
    for(int i=0; i<3; i++){
        // amount of ingredient i required for 'burgers' burgers
        // (multiplication is 64-bit since burgers is long long)
        long long required = burgers * need[i];

        // if stock is insufficient, buy the deficit
        if(required > have[i]){
            money += price[i] * (required - have[i]);
        }

        // pruning: already over budget -> infeasible
        if(money > r){
            return false;
        }
    }

    // all ingredients covered within budget
    return (money <= r);
}

// ---------------------------------------------------------
// BINARY SEARCH ON ANSWER
// ---------------------------------------------------------
// Finds the largest 'burgers' such that isPossible() is true.
//
//   - if mid is feasible, store it and search the RIGHT half
//     (we want the MAXIMUM feasible value)
//   - else search the LEFT half
long long maxBurgers(vector<int>& need, vector<int>& have, vector<int>& price, long long r){
    long long low = 0, high = 2e12;   // search space bounds
    long long ans = 0;                // best feasible answer found

    while(low <= high){
        // overflow-safe midpoint
        long long mid = low + (high - low)/2;

        if(isPossible(mid, need, have, price, r)){
            // mid burgers possible -> try for more
            ans = mid;
            low = mid + 1;
        }
        else{
            // mid burgers not possible -> reduce upper bound
            high = mid - 1;
        }
    }

    return ans;
}

int main(){
    // recipe string, e.g. "BBSSCC" or "BSC"
    string s;
    cin >> s;

    // need[] is derived from s below; have[] and price[]
    // are read from input for the 3 ingredients
    vector<int> need(3), have(3), price(3);

    // read current stock for B, S, C
    for(int i=0; i<3; i++){
        cin >> have[i];
    }

    // read unit price for B, S, C
    for(int i=0; i<3; i++){
        cin >> price[i];
    }

    // total money available
    long long r;
    cin >> r;

    // ---------------------------------------------------
    // Manually form need array from recipe string
    // ---------------------------------------------------
    // 'B' -> need[0]++   (Bread)
    // 'S' -> need[1]++   (Sausage)
    // 'C' -> need[2]++   (Cheese)
    for(char c: s){
        if(c == 'B'){
            need[0]++;
        }
        else if(c == 'S'){
            need[1]++;
        }
        else{
            need[2]++;
        }
    }

    // print the maximum burgers that can be made
    cout << maxBurgers(need, have, price, r) << endl;

    return 0;
}