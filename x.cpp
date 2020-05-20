/*
 * let sum [i][j] the number of continuous '1' from s[i][j] , s[i+1][j] , s [i+2][j] .. 
 * let mn [sz][i][j] the minimum from , sum [i][j-sz+1] ,sum [i][j-sz+2] .. sum [i][j] 
 * let mx [sz][i] the max from mn [sz][i][j]
 * we build sparse table on mx [sz][i] for every sz and answer the queries
*/
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <bits/stdc++.h>
using namespace std;
#define sqr 270
//#define mp make_pair
#define mid (l+r)/2
#define pb push_back
#define ppb pop_back
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define ins insert
#define era erase
#define C continue
#define mem(dp,i) memset(dp,i,sizeof(dp))
#define mset multiset
#define all(x) x.begin(), x.end()
#define gc getchar_unlocked
typedef long long ll;
typedef short int si;
typedef long double ld;
typedef pair<int,int> pi;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pi> vpi;
typedef vector<pll> vpll;
const ll inf=1e18;
const ll mod=1e9+7;
const ld pai=acos(-1);
ifstream f("lcdr.in");
ofstream g("lcdr.out");
int n , m , q ;
string s[509];
int a [509][509] , sum [509][509] , mx [509][509] , mn [2][509][509] , sparse [509][509][10] , Log [509] ;
int main () {
	f >> n >> m >> q;
	for ( int i = 0 ; i < n ; i ++ ) f >> s[i] ;
	for ( int i = n-1 ; i >= 0 ; i -- ) {
		for ( int j = 0 ; j < m ; j ++ ) {
			if ( s[i][j] =='0' ) {
				sum [i][j] = 0;
				C ;
			}
			sum [i][j] = 1 ;
			if ( i != n-1 ) sum [i][j] += sum [i+1][j] ;
		}
	}
	for ( int i = 0 ; i < n ; i ++ ) {
		for ( int j = 0 ; j < m ; j ++ ) {
			mn [0][i][j] = sum [i][j] ;
			mx [1][i] = max ( mx [1][i] , sum [i][j] ) ;
		}
		sparse [1][i][0] = mx [1][i] ; 
	}
	for ( int j = 1 ; j < 10 ; j ++ ) {
                for ( int i = 0 ; i < n ; i ++ ) {
                        if ( i + ( 1 << j ) - 1 >= n ) break ;
                        int nxt = i + ( 1 << (j-1) ) ;
                        sparse [1][i][j] = max ( sparse [1][i][j-1] , sparse [1][nxt][j-1] ) ;
                }
        }
	for ( int sz = 2 ; sz <= m ; sz ++ ) {
		for ( int i = 0 ; i < n ; i ++ ) {
			for ( int j = sz - 1 ; j < m ; j ++ ) {
				mn [1][i][j] = min ( mn [0][i][j-1] , sum [i][j] ) ;
				mx [sz][i] = max ( mx [sz][i] , mn [1][i][j] ) ;
			}
			for ( int j = sz - 1 ; j < m ; j ++ ) {
				mn [0][i][j] = mn [1][i][j] ;
				mn [1][i][j] = 0 ;
			}
			sparse [sz][i][0] = mx [sz][i] ;
		}
		for ( int j = 1 ; j < 10 ; j ++ ) {
                        for ( int i = 0 ; i < n ; i ++ ) {
                                if ( i + ( 1 << j ) - 1 >= n ) break ;
                                int nxt = i + ( 1 << (j-1) ) ;
                                sparse [sz][i][j] = max ( sparse [sz][i][j-1] , sparse [sz][nxt][j-1] ) ;
                        }
                }
	}
	for ( int i = 1 ; i <= n ; i ++ ) {
		for ( int j = 0 ; j < 10 ; j ++ ) {
			if ( ( i & ( 1 << j ) ) ) {
				Log [i] = j ;
			}
		}
	}
	while ( q -- ) {
		int need , sz , l , r ;
		f >> need >> sz >> l >> r ; 
		l -- , r -= need ;
		if ( l > r ) { g << 0 << '\n' ;C ;}
		int crnt = l , xxx = r - l + 1 , ans = 0 ;
		ans = max ( ans , sparse [sz][crnt][Log[xxx]] ) ;
		crnt = r - ( 1 << Log [xxx] ) + 1 ;
		ans = max ( ans , sparse [sz][crnt][Log[xxx]] ) ;
		g << ( ans >= need ) << '\n' ;
	}
}
