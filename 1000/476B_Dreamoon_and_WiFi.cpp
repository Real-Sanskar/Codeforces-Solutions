#include<bits/stdc++.h>
using namespace std;

// || RECURSION / BACKTRACKING (BRUTE FORCE ENUMERATION) ||

// =========================================================
// DREAMOON AND WIFI — PROBABILITY OF CORRECT POSITION
// =========================================================
//
// Problem (Codeforces 476B):
//   s1 = the actual command string of '+' and '-' moves.
//   s2 = the remembered command string, but some positions
//        may be '?' (forgotten / ambiguous).
//
//   '+' -> move +1
//   '-' -> move -1
//
//   Starting from position 0, compute the PROBABILITY that
//   the final position reached using s2 equals the final
//   position reached using s1.
//
//   Equivalent:
//       P = (number of '?' assignments of s2 that reach the
//            same final position) / (total assignments)
//
// ---------------------------------------------------------
// APPROACH: BRUTE-FORCE RECURSIVE ENUMERATION
// ---------------------------------------------------------
//
// We DFS over every character of s2:
//   - if s2[i] == '+', move +1
//   - if s2[i] == '-', move -1
//   - if s2[i] == '?', branch into BOTH '+' and '-'
//
// At the leaf (i == n):
//   - if currPosi == originalPosi, increment correctCase
//   - always increment totalCase (every full assignment)
//
// The probability = correctCase / totalCase.
//
// ---------------------------------------------------------
// WHY THIS WORKS
// ---------------------------------------------------------
//
// '?' positions are independent coin flips (each can be '+' or
// '-'), so enumerating all 2^(#?) possibilities gives exactly
// the sample space of equally likely assignments.
//
// ---------------------------------------------------------
// COMPLEXITY
// ---------------------------------------------------------
//
//   Let q = number of '?' in s2 (q <= n).
//   Number of leaves = 2^q.
//
//   TC: O(2^q)  (exponential — fine since n <= 10)
//   SC: O(n)    recursion stack
// =========================================================

// ---------------------------------------------------------
// DFS OVER s2
// ---------------------------------------------------------
// i            : current index in s2
// n            : length of s2 (== length of s1)
// s2           : the remembered command string (has '?')
// correctCase  : passed by reference — count of assignments
//                that reach the target position
// totalCase    : passed by reference — count of ALL
//                possible assignments (2^q)
// originalPosi : final position obtained from s1 (target)
// currPosi     : position after applying s2[0..i-1]
void dfs(int i, int n, string s2, int& correctCase, int& totalCase, int originalPosi, int currPosi){

    // base case: all characters of s2 have been processed
    if(i == n){
        // this full assignment reaches the target position
        if(currPosi == originalPosi){
            correctCase++;
        }

        // every leaf counts as one possible assignment
        totalCase++;
        return;
    }

    if(s2[i] == '+'){
        // forced move: +1
        dfs(i+1, n, s2, correctCase, totalCase, originalPosi, currPosi+1);
    }
    else if(s2[i] == '-'){
        // forced move: -1
        dfs(i+1, n, s2, correctCase, totalCase, originalPosi, currPosi-1);
    }
    else{
        // '?' -> branch into both possibilities
        // (each represents one equally-likely outcome)

        // assume '?' means '+'
        dfs(i+1, n, s2, correctCase, totalCase, originalPosi, currPosi+1);

        // assume '?' means '-'
        dfs(i+1, n, s2, correctCase, totalCase, originalPosi, currPosi-1);
    }
}

int main(){
    string s1, s2;
    cin >> s1;   // actual commands
    cin >> s2;   // remembered commands (may contain '?')

    int n = s1.size();

    // ---------------------------------------------------
    // compute the TARGET final position from s1
    // ---------------------------------------------------
    int originalPosi = 0;
    for(char c: s1){
        if(c == '+'){
            originalPosi++;
        }
        else{
            originalPosi--;
        }
    }

    // counters for the DFS
    int correctCase = 0, totalCase = 0;

    // ---------------------------------------------------
    // enumerate every assignment of s2 ('?' -> '+' or '-')
    // starting from index 0, current position 0
    // ---------------------------------------------------
    dfs(0, n, s2, correctCase, totalCase, originalPosi, 0);

    // ---------------------------------------------------
    // probability = favourable outcomes / total outcomes
    // (cast to double before division)
    // ---------------------------------------------------
    double probability = (double) correctCase / totalCase;

    // print with 12 decimal places (as required by the problem)
    cout << fixed << setprecision(12) << probability << endl;

    return 0;
}