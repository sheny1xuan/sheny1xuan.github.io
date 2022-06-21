# cmu15-445-project0,1


## 2021 FALL cmu15-445-project0,1

### 写在前面

过去也看了一些公开课了，但是从来没有完整的做完一个课程的实验，cmu15-445也相当于我第一个完整做完的课程实验。~~由于2021FALL的课程并不是[ Andy Pavlo](http://www.cs.cmu.edu/~pavlo)主讲的，少了点意思~~（是我时间不够，并且不想看公开课了），我并没看公开课，而是通过ppt和书进行学习的（主要是PPT）。虽然都能够通过gradescope上所有的测试，但是很多东西都是面向测试用例编程的，并没有自己的理解。我的感觉与[沧海月明](https://www.inlighting.org/)大佬一样，如果只是面向测试用例编程，以通过gradescope为目的的话，是远远不够的，后期还需要仔细对着PPT和《数据库系统概念 第七版》进行理解与复习。这篇博客是我以实验为中心，通过PPT学习的一个简单的总结，大部分内容都是我从PPT中拿出来认为比较重要的部分，或者是对实验的梳理。

2021年的实验主要由[四个小实验构成](https://15445.courses.cs.cmu.edu/fall2021/assignments.html)，每个实验都有详细的实验介绍。每个实验开始前，通读实验。的基础要求，然后去补对应的知识点（一般都忘记了），之后去看对应文件的代码，最后就是实现和测试了。

下面是一些注意事项

+ 每一个实验的要求和介绍都需要详细的阅读。除此之外，对于每一个需要实现的方法，它的注释都是很关键的。
+ 实验不需要特别多的c++的知识。但是最困难的是c++编译和设置调试的过程，如果没有c++和cmake开发的基础，还是最好使用clion之类的集成编译环境会更省心一点。~~我是通过vscode进行调试的，利用自己写vscode的task进行编译的。配置文件很麻烦，感觉没什么用。~~

### project0

project0是一个用来熟悉代码环境的准备性的实验。这个实验至少要实现一下几个目标，这个也是开头最困难的地方。

1. 创建你的私有仓库，并且初始化开发环境，学习编译测试与格式化代码。这些内容在project0的介绍里都有详细的教程。
2. 学会使用LOG，这个对于后续调试有很重要的作用。我没有成功通过环境变量修改或者编译选项过这日志等级，是通过修改[这一行](https://github.com/cmu-db/bustub/blob/ed3fdb6a71e23051d91d1c14dad6385d3e44f213/src/include/common/logger.h#L75)实现的。
3. 学会在线测试，本地测试都是比较基础的简单测试，真的困难的测试需要在gradescope上，上传代码到gradesocpe并且进行测试。困难的测试是**推荐自己写**（我不会写，太菜了），没有测试用例很难找出来问题。如果有需要测试用例，也可以来找我，我当时找了好久。gradescope可以通过压缩文件包上传文件，也可以直接通过github的分支直接上传，这里推荐使用第二种，更方便管理。可以通过简单的脚本来实现。project0只能通过打包文件实现。

可参考的代码提交测试脚本 `./script labname commitmsg`或者是通过`./script check`进行代码format。

``` bash
# !/usr/bin/bash

lab="$1"
msg="$2"

check(){
    if [ $? -ne 0 ]; then
        echo "command error."
        exit 10
    else
        echo "ok"
    fi
}

if [ "$lab" = "check" ] ; then
    cd build
    make format
    make check-lint
    make check-clang-tidy
    cd ..
    exit 0
fi

if [ "$lab" = "" ] || [ "$msg" == "" ] ; then
    echo "lab or msg error."
    exit 10
fi

cd build
make format
cd ..

check

git add .
git commit -m "$msg"
git push origin dev

check

lab0File="test/primer/starter_test.cpp"
lab1File="src/include/buffer/lru_replacer.h \
        src/buffer/lru_replacer.cpp \
        src/include/buffer/buffer_pool_manager_instance.h \
        src/buffer/buffer_pool_manager_instance.cpp \
        src/include/buffer/parallel_buffer_pool_manager.h \
        src/buffer/parallel_buffer_pool_manager.cpp\
        src/include/common/logger.h"
lab2File="$lab1File src/include/storage/page/hash_table_directory_page.h \
        src/storage/page/hash_table_directory_page.cpp \
        src/include/storage/page/hash_table_bucket_page.h \
        src/storage/page/hash_table_bucket_page.cpp \
        src/include/container/hash/extendible_hash_table.h \
        src/container/hash/extendible_hash_table.cpp \
        src/include/storage/page/tmp_tuple_page.h"
lab3File="$lab2File src/include/execution/execution_engine.h \
        src/include/execution/executors/seq_scan_executor.h \
        src/include/execution/executors/insert_executor.h \
        src/include/execution/executors/update_executor.h \
        src/include/execution/executors/delete_executor.h \
        src/include/execution/executors/nested_loop_join_executor.h \
        src/include/execution/executors/hash_join_executor.h \
        src/include/execution/executors/aggregation_executor.h \
        src/include/execution/executors/limit_executor.h \
        src/include/execution/executors/distinct_executor.h \
        src/execution/seq_scan_executor.cpp \
        src/execution/insert_executor.cpp \
        src/execution/update_executor.cpp \
        src/execution/delete_executor.cpp \
        src/execution/nested_loop_join_executor.cpp \
        src/execution/hash_join_executor.cpp \
        src/execution/aggregation_executor.cpp \
        src/execution/limit_executor.cpp \
        src/execution/distinct_executor.cpp"
lab4File="$lab3File src/concurrency/lock_manager.cpp\
        src/include/concurrency/lock_manager.h"

if [ "$lab" = "l0" ] ; then
    labFile = lab0File
elif [ "$lab" = "l1" ] ; then
    labFile = lab1File
elif [ "$lab" = "l2" ] ; then
    labFile = lab2File
elif [ "$lab" = "l3" ] ; then
    labFile = lab3File
elif [ "$lab" = "l4" ] ; then
    labFile = lab4File
fi

if [ "$msg" != "" ] ; then
    git checkout -b "$lab"
    git reset --hard dev
    git rm -r --cached .
    git add $labFile
    git commit -m "$msg"
    git push -f origin "$lab"
    git checkout dev -f
fi
```

### project1

实现一个线程安全的缓冲池，涉及的的知识点为ppt1-5章。

#### 缓冲池理论

各级存储的访问时间是有显著差异的，磁盘即使是SSD的访问时间(ms)也是内存DRAM(us)的访问时间的1000倍。对于磁盘而言，磁盘的随机访问的效率也远低于顺序访问。因此，对于磁盘的访问，需要最大化顺序IO，减少对磁盘的随机访问。

![image-20220428205830968](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220428205830968.png)

##### 为什么需要缓冲池与磁盘直接进行交互而不用操作系统的普通文件系统：

数据库系统需要做根据数据库系统的IO操作特点进行优化，**尽可能多地减少IO的读写**

+ 按照顺序IO写入磁盘
+ 预读
+ 页面置换策略
+ 线程切换

![image-20220430195409319](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220430195409319.png)

##### IO分类：

+ 无缓冲IO：内存中的数据->内核缓冲区->磁盘
+ 缓冲IO：内存中的数据->用户缓冲区->内核缓冲区->磁盘
+ DIO/CIO：内存中的数据->数据库地缓冲池->磁盘
+ 直接IO减少了数据的拷贝，操作系统使用mmap直接将文件映射到数据库程序当中的虚拟地址空间中。而虚拟地址空间中的页与实际物理地址映射与换入换出仍通过操作系统管理。

![image-20220430195012745](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220430195012745.png)

##### 缓冲池总体架构

![image-20220430194844125](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220430194844125.png)

![image-20220430205102536](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220430205102536.png)

##### 单一缓冲池主要由两部分组成：

1. PageTable：将全局页号(page_id)映射为该页在缓冲池中的位置索引(frame_id)。
2. BufferPool：存储每一页的内存，以及对应页的元信息。这两使用双锁机制，缓冲池的锁保护每一页的元信息，数据页的锁保护每一页数据读写。

操作过程：

1. 拿出一页需要Pin，引用计数加一，不允许被换入换出。
2. 不需要使用某一页时，需要Unpin，引用计数减一，当引用计数为0时，允许换入换出。

**唯一性：**缓冲池中同一个页号只能对应一份内存。

![image-20220428204717614](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220428204717614.png)

##### 组相联缓冲池，与缓存组相联类似：

+ 减少锁的竞争
+ 提升局部性，防止遍历导致的缓存污染。

![image-20220430205453587](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220430205453587.png)

##### 页面置换算法

时钟算法

+ 被访问到，标志位置为1。
+ 当需要置换时，如果标志位为1，置为0；如果标志位为0，则将其置换。

![image-20220430205712851](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220430205712851.png)

顺序淘汰：RoundRobin

LRU：https://leetcode-cn.com/problems/lru-cache/，通过哈希表和双向链表实现。

LRU-K：防止遍历导致的缓存污染。访问k次后才加入缓存，淘汰过时的页面。

#### 数据库系统中的页

+ 数据库系统中的每一页有固定的大小，不同于操作系统中的页(4KB)，数据库系统中的页通常为(4-16KB)。

![image-20220430222801590](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220430222801590.png)

这些页被分配在堆内存中，而这些页可以通过链表或者目录项的方式组织起来。

![image-20220430223422575](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220430223422575.png)

每一页由页头和页数据组成。

![image-20220430223620546](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220430223620546.png)

数据页中的行数据(tuple)由行ID唯一的表示，访问该行通过页号和页内偏移进行访问。![image-20220430223926464](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220430223926464.png)

##### 每一行数据的组成

![image-20220430224132868](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220430224132868.png)

##### 每一行数据的表示

![image-20220430224323580](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220430224323580.png)

##### 两种不同的事务类型

![image-20220430224517751](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220430224517751.png)

#### 实验代码

##### 实现LRU换页

参考https://leetcode-cn.com/problems/lru-cache/。主要由哈希表，链表以及保证线程安全的锁组成。

+ Pin：该页正在被使用，从LRU队列中取出不允许被换入换出。
+ Unpin：该页不需要使用，放入LRU队列中准备换入换出。
+ Victim：LRU队列中队尾的页，返回true。如果队列为空，返回false。

##### 单个缓冲池

`BufferPoolManagerInstance()`继承了`BufferPoolManager`，其成员主要由下面的成员构成

``` cpp
    // src/include/buffer/buffer_pool_manager_instance.h
	
	/** Array of buffer pool pages. */
	// 堆内存
    Page *pages_;
    /** Pointer to the disk manager. */
    // 没有实现wal，只是简单的文件读写
    DiskManager *disk_manager_ __attribute__((__unused__));
    /** Pointer to the log manager. */
    LogManager *log_manager_ __attribute__((__unused__));
    /** Page table for keeping track of buffer pool pages. */
    std::unordered_map<page_id_t, frame_id_t> page_table_;
    /** Replacer to find unpinned pages for replacement. */
    Replacer *replacer_;
    /** List of free pages. */
    std::list<frame_id_t> free_list_;
    /** This latch protects shared data structures. We recommend updating this comment to describe what it protects. */
    /** Protect free_list_, page_table_*/
    std::mutex latch_;
```

缓冲池中的每一页`page`包含了控制信息和页内数据，控制信息包括PIN该页的次数，页号，脏页标志位，以及一个读写锁。

``` cpp
  // src/include/storage/page/page.h
  /** Zeroes out the data that is held within the page. */
  inline void ResetMemory() { memset(data_, OFFSET_PAGE_START, PAGE_SIZE); }

  /** The actual data that is stored within a page. */
  char data_[PAGE_SIZE]{};
  /** The ID of this page. */
  page_id_t page_id_ = INVALID_PAGE_ID;
  /** The pin count of this page. */
  int pin_count_ = 0;
  /** True if the page is dirty, i.e. it is different from its corresponding page on disk. */
  bool is_dirty_ = false;
  /** Page latch. */
  ReaderWriterLatch rwlatch_;
```

对于堆内存中的每一页其存在的位置只有在空闲链表，lru队列，正在使用(PIN)三种状态。因此空闲的页都存在于空闲链表或者lru队列中，对于lru队列中被换出的页需要检查其是否是脏页，如果是脏页的化需要利用`disk_manager_`写回到磁盘当中。寻找空闲的frame的逻辑可以进行简单的封装`bool FindFrame(frame_id_t *frame_id)`。需要注意的是，`page_table_`中映射的页不一定都是被PIN的状态，有些可能正处于LRU队列中。主要需要实现一下方法，其中最主要的是FetchPgImp，UnpinPgImp（需要详细阅读注释）：

+ FetchPgImp：寻找该页，如果该页不在`page_table_`中，需要找到合适的空闲页，利用`disk_manager_`读出该页。之后将该页引用计数加一，从LRU队列中取出。
+ UnpinPgImp：这里需要注意注释里的`*false if the page pin count is <= 0 before this call, true otherwise*`，只有`pin_count <=0`时才返回false，其余情况下都返回true。除此之外，即使该页`pin_count<=0`，不需要将该页从`page_table_`中删除，否则FetchPage时，该页在lru队列中不能被拿出，**导致不唯一**。脏页也只需要进行标记即可后续被换出时写回磁盘即可。内存中的页只会存在三个位置：空闲链表，缓冲池，LRU队列。
+ FlushPgImp：利用`disk_manager_`写回。
+ NewPgImp：先找到空闲的页，之后`AllocatePage()`申请`page_id`。
+ DeletePgImp：删除该页，需要注意只有`pin_count_ <= 0`才能删除，感觉应该还需要在磁盘中删除该页，这部分不是很确定。

##### 线程安全组相联缓冲池

`ParallelBufferPoolManager`包含多个`BufferPoolManagerInstance`，对于每一页需要通过取余找到合适的`BufferPoolManagerInstance`，之后调用单个缓冲池的api即可。

NewPgImp比较复杂一些，需要轮询所有的缓冲池，直到成功拿到一页，或者是失败。

#### 参考博客

实验主要参考的博客，后面不在一一列出。

+ https://www.inlighting.org/archives/cmu-15-445-notes/
+ https://www.cnblogs.com/JayL-zxl/category/1919605.html
+ https://15445.courses.cs.cmu.edu/fall2021/
+ https://segmentfault.com/a/1190000015856311
+ https://www.jianshu.com/p/c4e4d55706ff

