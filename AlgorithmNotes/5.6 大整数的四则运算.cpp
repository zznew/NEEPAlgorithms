/**
* 大整数的四则运算
**/


//高精度加法
bign add(bign a, bign b) {
    bign c;
    int carry = 0; //进位
    //以较长的为界限
    for (int i = 0; i < a.len || i < b.len; i++) {
        int temp = a.d[i] + b.d[i] + carry; //两个对应位与进位相加
        c.d[c.len++] = temp % 10; //个位数为该位结果
        carry = temp / 10; //十位数为新的进位
    }
    if (carry != 0)
        c.d[c.len++] = carry; //如果最后进位不为0，则直接赋给结果的最高位
    return c;
}

//高精度减法
bign sub(bign a, bign b) {
    bign c;
    for (int i = 0; i < a.len || i < b.len; i++) {
        //如果不够减
        if (a.d[i] < b.d[i]) {
            a.d[i + 1]--; //向高位借位
            a.d[i] += 10; //当前位加10
        }
        c.d[c.len++] = a.d[i] - b.d[i]; //减法结果为当前位结果
    }
    while (c.len - 1 >= 1 && c.d[c.len - 1] == 0) {
        c.len--; //去除高位的0，同时至少保留一位最低位
    }
}

//高精度与低精度的乘法
bign multi(bign a, int b) {
    bign c;
    int carry = 0; //进位
    for (int i = 0; i < a.len; i++) {
        int temp = a.d[i] * b + carry;
        c.d[c.len++] = temp % 10; //个位作为该位结果
        carry = temp / 10; //高位部分作为新的进位
    }
    //和加法不一样，乘法的进位可能不止一位，因此用while
    while (carry != 0) {
        c.d[c.len++] = carry % !0;
        carry /= 10;
    }
    return c;
}

//高精度与低精度的除法
bign divide(bign a, int b, int& r) {
    bign c;
    c.len = a.len; //被除数的每一位和商的每一位是一一对应的，因此先令长度相等
    //从高位开始
    for (int i = a.len - 1; i >= 0; i--) {
        r = r * 10 + a.d[i]; //和上一位遗留的余数组合
        if (r < b)
            c.d[i] = 0; //不够除，该位为0
        else {
            c.d[i] = r / b; //商
            r = r % b; //获得新的余数
        }
    }
    while (c.len - 1 >= 1 && c.d[c.len - 1] == 0) {
        c.len--; //去除高位的0，同时至少保留一位最低位
    }
    return c;
}
