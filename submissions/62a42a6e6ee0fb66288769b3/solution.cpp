#include <bits/stdc++.h>

#define N 1000010
#define ff first
#define ss second
#define ll long long
#define pii pair <int, int>
#define mod 1000000007

using namespace std;

int n, m, k;
int v[N];

string longDivision(string number, int divisor)
{
    string ans;
 
    int idx = 0;
    int temp = number[idx] - '0';
    while (temp < divisor)
        temp = temp * 10 + (number[++idx] - '0');
 
    while (number.size() > idx) {
        ans += (temp / divisor) + '0';
 
        temp = (temp % divisor) * 10 + number[++idx] - '0';
    }
 
    if (ans.length() == 0)
        return "0";
 
    return ans;
}

string multiply(string num1, string num2)
{
    int len1 = num1.size();
    int len2 = num2.size();
    if (len1 == 0 || len2 == 0)
    return "0";
 
    vector<int> result(len1 + len2, 0);
 
    int i_n1 = 0;
    int i_n2 = 0;
     
    for (int i=len1-1; i>=0; i--)
    {
        int carry = 0;
        int n1 = num1[i] - '0';
 
        i_n2 = 0;
         
        for (int j=len2-1; j>=0; j--)
        {
            int n2 = num2[j] - '0';
 
            int sum = n1*n2 + result[i_n1 + i_n2] + carry;
 
            carry = sum/10;
 
            result[i_n1 + i_n2] = sum % 10;
 
            i_n2++;
        }
 
        if (carry > 0)
            result[i_n1 + i_n2] += carry;
 
        i_n1++;
    }
 
    int i = result.size() - 1;
    while (i>=0 && result[i] == 0)
    i--;
 
    if (i == -1)
    return "0";
 
    string s = "";
     
    while (i >= 0)
        s += std::to_string(result[i--]);
 
    return s;
}

int main()
{
//	freopen("C:/Fmesele.in", "r", stdin);
	
	cin >> n >> m >> k;
	
	string ans = "1";
	for(int i = 1; i <= n*m; i++) {
		string cur = "";
		int x = i;
		while(x) {
			cur += x % 10 + '0';
			x /= 10;
		}
		
		reverse(cur.begin(), cur.end());
		
		ans = multiply(ans, cur);
	}
	
	int sum = 0;
	for(int i = 1; i <= k; i++) {
		cin >> v[i];
		
		sum += v[i];
		
		for(int j = 2; j <= v[i]; j++)
			ans = longDivision(ans, j);
	}
	
	for(int j = 2; j <= n*m - sum; j++)
		ans = longDivision(ans, j);
	
	cout << ans;
}
/*
10 10
3
5
10
80
*/
