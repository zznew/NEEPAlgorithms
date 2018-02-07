#include <stdio.h>

int main() {
    int n;
    //输入判断增加对n是否等于零进行判断
    while (scanf("%d", &n) != EOF && n != 0) {
        int Hash[101] = { 0 }; //建立一个初始为0的Hash数组用来记录各种分数出现的次数
        for (int i = 0; i < n; i++) {
            int x;
            scanf("%d", &x);
            Hash[x]++; //统计分数出现次数
        }
        int x;
        scanf("%d", &x);
        printf("%d\n", Hash[x]); //查询目标分数统计的数量
    }
    return 0;
}
