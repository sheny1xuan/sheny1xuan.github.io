# Valgrind使用




### 安装Valgrind

+ `sudo apt-get install valgrind`

### Memcheck

#### 通常使用

+ `valgrid --log-file=output.log --tool=memcheck --leak-check=full --show-leak-kinds=all your_binary_file`
+ `--log-file`设置输出信息路径
+ `--leak-check=full`检测所有的内存使用问题，不仅仅包含内存泄露，还包含其他各种错误使用内存问题。
+ `show-leak-kinds=all`显示所有内存泄露的类型。

### 内存使用错误

+ 错误配对malloc/free,new/delete

```
Mismatched free() / delete / delete []
```

#### 内存泄露的类型

``` 
     Pointer chain            AAA Leak Case   BBB Leak Case
     -------------            -------------   -------------
(1)  RRR ------------> BBB                    DR
(2)  RRR ---> AAA ---> BBB    DR              IR
(3)  RRR               BBB                    DL
(4)  RRR      AAA ---> BBB    DL              IL
(5)  RRR ------?-----> BBB                    (y)DR, (n)DL
(6)  RRR ---> AAA -?-> BBB    DR              (y)IR, (n)DL
(7)  RRR -?-> AAA ---> BBB    (y)DR, (n)DL    (y)IR, (n)IL
(8)  RRR -?-> AAA -?-> BBB    (y)DR, (n)DL    (y,y)IR, (n,y)IL, (_,n)DL
(9)  RRR      AAA -?-> BBB    DL              (y)IL, (n)DL

Pointer chain legend:
- RRR: a root set node or DR block
- AAA, BBB: heap blocks
- --->: a start-pointer
- -?->: an interior-pointer

Leak Case legend:
- DR: Directly reachable
- IR: Indirectly reachable
- DL: Directly lost
- IL: Indirectly lost
- (y)XY: it's XY if the interior-pointer is a real pointer
- (n)XY: it's XY if the interior-pointer is not a real pointer
- (_)XY: it's XY in either case
```

+ 主要有两种Directly lost和Indirectly lost，主要是情况3和情况4。
+ Possible lost主要针对后面几种情况。

#### Indirectly lost

``` c
#include <malloc.h>
#include <stdlib.h>
#include <stdint.h>
void *RRR;
void *AAA;
void *BBB;
int main()
{
    RRR = malloc(8);
    AAA = malloc(8);
    BBB = malloc(8);

    *(uint64_t*)RRR = (uint64_t)(uint64_t*)AAA; // 将RRR指向的块指向AAA指向的块
    *(uint64_t*)AAA = (uint64_t)(uint64_t*)BBB; // 将AAA指向的块指向BBB指向的块
    AAA = NULL;
    BBB = NULL;
    *(uint64_t*)RRR = 0;
    return 0;
}

==6007== HEAP SUMMARY:
==6007==     in use at exit: 24 bytes in 3 blocks
==6007==   total heap usage: 3 allocs, 0 frees, 24 bytes allocated
==6007==
==6007== LEAK SUMMARY:
==6007==    definitely lost: 8 bytes in 1 blocks  (AAA)
==6007==    indirectly lost: 8 bytes in 1 blocks  (BBB)
==6007==      possibly lost: 0 bytes in 0 blocks
==6007==    still reachable: 8 bytes in 1 blocks
==6007==         suppressed: 0 bytes in 0 blocks
==6007== Rerun with --leak-check=full to see details of leaked memory
==6007==
==6007== For counts of detected and suppressed errors, rerun with: -v
==6007== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

#### interior-pointer

+ 指针指向了申请的块，但是并不在该块开始的地方，会产生possible loss。

``` c
#include <malloc.h>
#include <stdlib.h>
#include <stdint.h>
void *RRR;
void *AAA;
void *BBB;
int main()
{
    RRR = malloc(8);

    *(uint64_t*)RRR = 0;
    RRR = (char*)RRR + 2;
    
    return 0;
}

==6429== HEAP SUMMARY:
==6429==     in use at exit: 8 bytes in 1 blocks
==6429==   total heap usage: 1 allocs, 0 frees, 8 bytes allocated
==6429==
==6429== LEAK SUMMARY:
==6429==    definitely lost: 0 bytes in 0 blocks
==6429==    indirectly lost: 0 bytes in 0 blocks
==6429==      possibly lost: 8 bytes in 1 blocks  (pointer not in block begin)
==6429==    still reachable: 0 bytes in 0 blocks
==6429==         suppressed: 0 bytes in 0 blocks
==6429== Rerun with --leak-check=full to see details of leaked memory
==6429==
==6429== For counts of detected and suppressed errors, rerun with: -v
==6429== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

### callgrind

#### profile

+ `valgrind --tool=callgrind --callgrind-out-file=callgrind.out ./prog `之后会生成相应的profile文件`callgrind.out.<pid>`
+ 之后可以通过`kcachegrind `可视化查看profile的结果`kcachegrind callgrind.out.*`。
+ 也可以通过`gprof2dot.py`脚本生成svg可视化图片`./gprof2dot.py -f callgrind callgrind.out.x | dot -Tsvg -o output.svg`。

### 参考

+ https://zhuanlan.zhihu.com/p/92074597?utm_source=wechat_session&utm_medium=social&utm_oi=792314251669823488
+ https://stackoverflow.com/questions/375913/how-can-i-profile-c-code-running-on-linux
+ https://stackoverflow.com/questions/35881610/what-is-a-real-pointer-in-valgrind-when-detecting-memory-leak/48683154




