首先是生成一个 200 个 随机数的 int （32位） data 文件。

```bash
$ od -An -tu4 -N800 /dev/urandom > data
```

解释： od 是一个 linux  command line  的小程序， 它按格式读出文件并打印到 stdout。

/dev/urandom  是一个linux 的系统虚拟硬件， 任务就是生成一个 随机无符号byte。比库自带的 random 函数可靠一些。

-A[ d = 十进制 |o = 八进制 | x = 16进制 | n = 无设置 ]   所以 -An 就是不设置输出进制；

-t[ ] 是设置按什么 format 组合成数。 因为 /dev/urandom 输出8位的 unsigned char, 所以 -tu4 就是生成4个 uint8_t 然后拼成一个 uint32_t;

-N 是限制输出的个数。 我们要200个 uint32_t, 所以需要限制 urandom 输出 4 * 200 = 800 个；

\> data 属于 command line 的 pipe， 把 stdout 转成文件，文件名是 data.



