#include<bits/stdc++.h>
using namespace std;

// || GREEDY + HASHING ||

// =========================================================
// MAKE PERMUTATION FROM ARRAY (REDUCE BY HALVING)
// =========================================================
//
// Problem (Codeforces-style):
//   Given an array arr[] of n integers, you may repeatedly
//   REPLACE any element x with floor(x/2). You must convert
//   the array into a PERMUTATION of {1, 2, ..., n}.
//   Determine whether this is possible.
//
//   Output "YES" if a valid permutation can be formed,
//   else "NO".
//
// ---------------------------------------------------------
// KEY IDEA
// ---------------------------------------------------------
//
// We need each value from 1 to n to appear EXACTLY ONCE.
//
// Process each element greedily:
//   - For the current value val, try to fit it into the
//     permutation at the LARGEST available slot it can reach
//     by halving (val, val/2, val/4, ...).
//   - Keep halving while:
//       (a) val > n              -> out of range, must halve
//       (b) formed[val] == true  -> slot already taken
//   - If val becomes 0, no valid slot exists -> "NO".
//
// Why greedy works:
//   - Each number can only map to values <= itself (via
//     halving). Assigning the largest possible unused value
//     preserves smaller slots for smaller numbers, which is
//     optimal.
//
// ---------------------------------------------------------
// "formed" ARRAY
// ---------------------------------------------------------
//
//   formed[v] = true  -> value v in [1..n] is already used
//   Size is n+1 (index 0 unused; 0 means no valid slot).
//
// ---------------------------------------------------------
// COMPLEXITY
// ---------------------------------------------------------
//
//   For each element, halving reduces the value by ~factor 2,
//   so at most O(log n) halvings per element.
//
//   TC: O(N log N) per test case
//   SC: O(N) for arr[] and formed[]
// =========================================================

int main(){
    int t;
    cin >> t;

    while(t--){
        int n;
        cin >> n;

        // read the input array
        vector<int> arr(n);
        for(int i=0; i<n; i++){
            cin >> arr[i];
        }

        // formed[v] = true means value v (1..n) is already
        // assigned in the permutation we're building
        vector<int> formed(n+1, false);
        bool canForm = true;

        for(int i=0; i<n; i++){
            int val = arr[i];

            // keep halving until val lands in [1..n] AND
            // that slot is not already taken
            while(val > n || formed[val] == true){
                val = val/2;
            }

            // val == 0 means we ran out of options:
            // this element cannot occupy any valid slot
            if(val == 0){
                canForm = false;
                break;
            }

            // claim this slot for the current element
            formed[val] = true;
        }

        if(canForm){
            cout << "YES\n";
        }
        else{
            cout << "NO\n";
        }
    }

    return 0;
}