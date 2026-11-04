/*
Logic: If length of string > 10, abbreviate as first character + count of middle characters (size - 2) + last character.
Time Complexity: O(N * L) where N is number of words and L is length of string.
Space Complexity: O(L) for storing each word.
*/

#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;

    while(n--){
        string s;
        cin >> s;

        int size = s.size();

        if(size > 10){
            cout << s[0] << size - 2 << s[size - 1] << endl;
        }
        else{
            cout << s << endl;
        }
    }

    return 0;
}