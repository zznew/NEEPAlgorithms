/**
* 问题一：如何计算C(n,m)
**/

//法一：通过定义式直接计算（n≤20）
long long C(long long n, long long m) {
    long long ans = 1;
    for (long long i = 1; i <= n; i++)
        ans *= i;
    for (long long i = 1; i <= m; i++)
        ans /= i;
    for (long long i = 1; i <= n - m; i++)
        ans /= i;
    return ans;
}

//法二：通过递推公式计算（O(n^2)）
long long C(long long n, long long m) {
    if (m == 0 || m == n)
        return 1;
    return C(n - 1, m) + C(n - 1, m - 1);
}

//法三：通过定义式的变形来计算（O(m)）
long long C(long long n, long long m) {
    long long ans = 1;
    for (long long i = 1; i <= m; i++) {
        ans = ans * (n - m + i) / i; //注意一定要先乘再除
    }
    return ans;
}


/**
* 问题二：如何计算C(n,m)%p
**/

//法一：通过递推公式计算
//递归
int res[1010][1010] = { 0 };
int C(int n, int m, int p) {
    if (m == 0 || m == n)
        return 1; //C(n,0)=C(n,n)=1
    if (res[n][m] != 0)
        return res[n][m]; //已经有值
    return res[n][m] = (C(n - 1, m) + C(n - 1, m - 1)) % p; //赋值并返回
}
//递推
void calC() {
    for (int i = 0; i <= n; i++)
        res[i][0] = res[i][i] = 1; //初始化边界
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= i / 2; j++) {
            res[i][j] = (res[i - 1][j] + res[i - 1][j - 1]) % p; //递推计算C(i,j)
            res[i][i - j] = res[i][j]; //C(i,i-j)=C(i,j)
        }
    }
}

//法二：根据定义式计算
//使用筛法得到素数表prime，注意表中最大素数不得小于n
int prime[maxn];
//计算C(n,m)%p
int C(int n, int m, int p) {
    int ans = 1;
    //遍历不超过n的所有质数
    for (int i = 0; prime[i] <= n; i++) {
        //计算C(n,m)中prime[i]的指数c，cal(n,k)为n!中含质因子k的个数
        int c = cal(n, prime[i]) - cal(m, prime[i]) - cal(n - m, prime[i]);
        //快速幂计算prime[i]^c%p
        ans = ans * binaryPow(prime[i], c, p) % p;
    }
    return ans;
}

//法三：通过定义式的变形来计算
//① m < p，且p是素数
int C(int n, int m, int p) {
    int ans = 1;
    for (int i = 1; i <= m; i++) {
        ans = ans * (n - m + i) % p;
        ans = ans * inverse(i, p) % p; //求i模p的逆元
    }
    return ans;
}
//② m任意，且p是素数
int C(int n, int m, int p) {
    //ans存放计算结果，numP统计分子中的p比分母中的p多几个
    int ans = 1, numP = 0;
    for (int i = 1; i <= m; i++) {
        int temp = n - m + i; //分子
        //去除分子中的所有p，同时累计numP
        while (temp % p == 0) {
            numP++;
            temp /= p;
        }
        ans = ans * temp % p; //乘以分子中除了p以外的部分
        temp = i; //分母
        //去除分母中的所有p，同时减少numP
        while (temp % p == 0) {
            numP--;
            temp /= p;
        }
        ans = ans * inverse(temp, p) % p; //除以分母中除了p以外的部分
    }
    if (numP > 0)
        return 0; //分子中p的个数多于分母，直接返回0
    else
        return ans; //分子中p的个数等于分母，返回计算的结果
}
//③ m任意，p可能不是素数

//法四：Lucas定理
int Lucas(int n, int m) {
    if (m == 0)
        return 1;
    return C(n % p, m % p) * Lucas(n / p, m / p) % p;
}
