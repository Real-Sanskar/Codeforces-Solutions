/*
Logic: A watermelon of weight W can be split into two even numbers if and only if W is even and W > 2 (since 2 = 1+1, which are odd).
Time Complexity: O(1)
Space Complexity: O(1)
*/

#include<bits/stdc++.h>
using namespace std;

int main(){
    int w;
    cin >> w;

    if(w > 2 && w % 2 == 0){
        cout << "YES" << endl;
    }
    else{
        cout << "NO" << endl;
    }

    return 0;
}