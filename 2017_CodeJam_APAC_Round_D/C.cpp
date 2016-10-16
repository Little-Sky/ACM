#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
// const int maxv = 1000+10;
const string ini = "00000000000000000000000000";
const int mod = 1000000007;
string S;
map<string, int> V;  //Vocabulary
int v, s;

long long dp[5000];
long long sol(){
  memset(dp, 0, sizeof(dp));
  cout << "pos 1 " << S.length() << endl;
  dp[0] = 1;  //one way to form empty string
  int len = S.length();
    cout << "pos 2" << endl;
  for (int i=0; i<len; i++){
    cout << "i: " << i << " " << endl;
    string x = ini;
    for (int j=1; j<=20 && i+j < len; j++){
      char tmp = S[i+j];
      x[tmp-'a']++;
      if (V.count(x)){
        cout << "i+j: " <<  i+j << " " << endl;
        dp[i+j] += V[x] * dp[i];
        dp[i+j] %= mod;
      }
    }
  }
  cout << "HERE?\n";
  return dp[len-2];
}

void cast(){
  int len = S.length();
  string x = ini;
  for (int i=0; i<len; i++){
    char tmp = S[i];
    x[tmp-'a']++;
  }
  V[x]++;
  // cout << "check cast: " << S  << " to " << x << endl;
}

int main(){
  ios::sync_with_stdio(false);
  int kase;
  cin >> kase;
  for (int k_i=1; k_i<=kase; k_i++){
    cout << "Case #" << k_i << ":";
    V.clear();
    cin >> v >> s;
// if (k_i == 5)
//   cout << v << " " << s << V.size();
    for (int i=0; i<v; i++){  //Vocabulary
      cin >> S;
      cast();
    }
// if (k_i == 5)
//   cout << V.size();
    for (int i=0; i<s; i++){  //Sentence
      cin >> S;
      cout << S << endl;
      S = " " + S + " ";
      cout << " " << sol();
    } 
    cout << endl;
  }
  return 0;
}