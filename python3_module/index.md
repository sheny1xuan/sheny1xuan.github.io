# Python3_Module




## Python模块的位置

### 查看python模块的位置

+ `python3 -m site` 
+ 或者在`python3`命令行中利用`sys`包查看路径

``` python
import sys

print(sys.path)
```

### `dist-packages`和`site-packages`

+ `dist-packages`路径中安装的是`pip`安装的官方模块
+ `site-packages`路径中安装的是第三方模块

### 参考

+ https://www.cnblogs.com/andylhc/p/9673709.html




