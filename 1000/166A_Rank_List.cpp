#include<bits/stdc++.h>
using namespace std;

// || SORTING WITH CUSTOM COMPARATOR ||

// =========================================================
// COUNT TEAMS WITH THE SAME SCORE AS THE K-TH TEAM
// =========================================================
//
// Problem (Codeforces 222A-style / "Ranking"):
//   n teams each submit a pair (problemsSolved, penaltyTime).
//   Teams are ranked by:
//       1. MORE problems solved is better  (descending)
//       2. LESS penalty time is better     (ascending)
//   Given k, find how many teams share the EXACT SAME
//   (problemsSolved, penaltyTime) pair as the team ranked
//   at position k (1-indexed) after sorting.
//
// ---------------------------------------------------------
// APPROACH
// ---------------------------------------------------------
//
// 1. Sort teams with a custom comparator:
//       - primary: descending on problems solved
//       - tie-break: ascending on penalty time
//
// 2. The team at index k-1 in the sorted array is the
//    "reference team" for ranking position k.
//
// 3. Count how many teams in the sorted array are EXACTLY
//    equal (same solved count AND same penalty) to this
//    reference team. That count is the answer.
//
// Why count in the SORTED array?
//   Equal pairs land adjacent after sorting, but since we
//   scan the whole array, adjacency isn't required — we just
//   count exact matches of the pair value.
//
// ---------------------------------------------------------
// COMPLEXITY
// ---------------------------------------------------------
//
//   Sorting : O(N log N)
//   Counting: O(N)
//
//   TC: O(N log N)
//   SC: O(N) for the vector of pairs
// =========================================================

int main(){
    int n, k;
    cin >> n;
    cin >> k;

    // arr[i] = { problemsSolved, penaltyTime } for team i
    vector<pair<int,int>> arr(n);
    for(int i=0; i<n; i++){
        cin >> arr[i].first >> arr[i].second;
    }

    // ---------------------------------------------------
    // CUSTOM SORT: ranking rules
    // ---------------------------------------------------
    //  - primary:   MORE problems solved first (a.first > b.first)
    //  - tie-break: LESS penalty time first    (a.second < b.second)
    sort(arr.begin(), arr.end(), [](auto& a, auto& b){
        if(a.first == b.first){
            // same solved count -> smaller penalty ranks higher
            return a.second < b.second;
        }
        // more solved ranks higher
        return a.first > b.first;
    });

    // ---------------------------------------------------
    // reference team at ranking position k (1-indexed)
    // -> index k-1 in the sorted array
    // ---------------------------------------------------
    auto val = arr[k-1];

    // ---------------------------------------------------
    // count all teams with the exact same (solved, penalty)
    // pair as the reference team
    // ---------------------------------------------------
    int ans = 0;
    for(int i=0; i<n; i++){
        if(arr[i] == val){
            ans++;
        }
    }

    cout << ans << endl;

    return 0;
}