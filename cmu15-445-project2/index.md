# cmu15-445-project2


## 2021 FALL cmu15-445-project2

实现哈希索引，涉及的的知识点为ppt6-8章。

#### 哈希索引

##### 哈希表关键问题

+ 哈希函数
+ 哈希冲突处理

![image-20220502151738784](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220502151738784.png)

##### 常用哈希函数

![image-20220502151900612](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220502151900612.png)

##### 哈希分类

**静态哈希**：散列函数不随数据规模而改变(1,2,3,4)

**动态哈希**：散列函数随数据规模动态变化，可以动态适应数据规模的变化，性能不随数据规模增大而降低。方法(5)

###### 1. 线性探查

需要注意删除过程中：需要墓碑或者移动后面多余的键使其连续

![](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220502152104038.png)

###### 2. ROBIN HOOD哈希

线性探查的变种，对于产生哈希冲突的键会赋予一个移动的位置次数。尽量减少所有键的移动次数。

![image-20220502152444989](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220502152444989.png)

###### 3. CUCKOO哈希

使用多个哈希函数，多个哈希表。如果产生哈希冲突，尝试在其他哈希表上重新进行哈希解决冲突问题。

![image-20220502153135301](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220502153135301.png)

###### 4. 开链表哈希

将所有产生相同哈希值的key通过链表连接到该哈希值。

![image-20220502153400030](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220502153400030.png)

###### 5. 可扩充散列

这也是这个实验实现的重点，这里可扩充的意思就是无需关注该哈希中哈希冲突的数量，会随数据规模的变化自动处理哈希冲突。这里只做简单介绍，重点参考`《数据库系统概念》11.7动态散列`。

可扩充散列本质上相当于在静态散列的基础上加了一个中间层。首先通过散列函数得到散列值，b位的二进制数，通常为32位。在这基础上，需要维护散列目录页和散列数据页(桶)。散列目录页维护全局的散列位数，前缀到数据页的映射以及每个数据页的局部位数。

![image-20220502155019582](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220502155019582.png)

关键点在于如何处理扩容和缩容：

**扩容操作**：当某个桶的容量已满时，提升当前桶的局部深度$h_i$。需要将当前桶中所有的key按照哈希值的$h_i$分为两类，一类与当前桶的索引相同，一类与当前桶的索引最高位不同。如下图中插入C，可以将10桶中的key分为(100)和(101)前缀两类。之后修改散列目录页对应桶的指针。

通过与散列目录页的深度$h_g$对比，可以分为两种条件：

+ 需要全局扩容：$h_g==h_i$，需要重新定位新产生的指针对应的桶
+ 不需要全局扩容：$h_g > h_i$，仅需要修改这两类前缀的指针。

![image-20220502160020300](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220502160020300.png)

考虑一种特殊的情况，如果需要分裂的页所有的key的哈希值在局部深度$h_i$都相同，这时无法分裂，需要附加桶来解决，该实验中无需考虑这种特殊情况。

**缩容操作**：

局部缩容：如果删除key后，该桶为空则可以尝试与对称的桶进行合并，如上图删除`10011...`后，100和101可以进行合并。并且降低非空的桶的深度$h_i$。

全局缩容：如果所有的局部深度$h_i$都小于全局深度$h_g$的话，可以进行全局缩容。

#### B+树索引

##### B+树结构

+ 完全平衡
+ 左节点小于key，右节点大于等于key
+ 除根结点外所有节点半满
+ 叶子节点通过双向链表连接

![image-20220502164305470](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220502164305470.png)

![image-20220502164406313](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220502164406313.png)

插入：从下往上插入

![](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220502164930161.png)

删除：如果不满足半满的条件，需要合并节点

![image-20220502165102693](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220502165102693.png)

##### 聚簇索引

利用主键作为key创建索引存储数据库的所有行(行在叶子节点中)。

![image-20220502165209464](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220502165209464.png)

利用聚簇索引排序是高效的。非聚簇索引通过回表进行排序，会产生大量的随机IO。越慢的存储介质，需要越大的B+树节点，减少IO操作。

![image-20220502165434083](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220502165434083.png)

#### 并发控制

![image-20220502171352080](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220502171352080.png)

Latch保证数据结构物理性正确，Lock属于事务中逻辑性正确。latch不支持死锁检测与死锁避免。

Latch分类

+ Mutex：pthread通过futex实现。
+ SpinLock：自旋锁
+ 读写锁

![image-20220502171401194](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220502171401194.png)

##### B+树并发控制

从根节点向下依次获取锁，先拿到父节点的锁，之后获取子节点的锁，确认父节点安全后，释放该锁。

![image-20220502172556133](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220502172556133.png)

![image-20220502172645771](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220502172645771.png)

写的次数多的情况下，根节点的写锁将成为性能瓶颈。

![image-20220502172858293](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220502172858293.png)

假设所有写操作都是安全的，从上到下获取读锁，只有目标节点获取写锁。如果发现需要分离，则执行上述的操作流程。

![image-20220502173006982](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220502173006982.png)

#### 哈希索引与B+树索引对比

+ B+树索引有序，支持部分键的查找。
+ 哈希索引只支持等值比较。

#### 实验代码

##### 实现目录页和数据页

目录页`HashTableDirectoryPage`的结构，后续通过将缓冲池中的一页`Page`强转为`HashTableDirectoryPage`进行使用，该对象无虚函数表，所以该对象开始的地址即为该类成员的起始地址。Directory Page: - GetGlobalDepth - IncrGlobalDepth - SetLocalDepth - SetBucketPageId - GetBucketPageId。

``` cpp
// src/include/storage/page/hash_table_directory_page.h 
/**
 *
 * Directory Page for extendible hash table.
 *
 * Directory format (size in byte):
 * --------------------------------------------------------------------------------------------
 * | LSN (4) | PageId(4) | GlobalDepth(4) | LocalDepths(512) | BucketPageIds(2048) | Free(1524)
 * --------------------------------------------------------------------------------------------
 */
private:
  page_id_t page_id_;  // 目录页的页号
  lsn_t lsn_;  // 本实验没用到
  uint32_t global_depth_{0};  // 全局的位数
  uint8_t local_depths_[DIRECTORY_ARRAY_SIZE]; // 数据页的局部位数
  page_id_t bucket_page_ids_[DIRECTORY_ARRAY_SIZE]; // 数据页的页号映射
```

数据页`HashTableBucketPage`，实现数据页的增删改查。`Bucket Page: - Insert - Remove - IsOccupied - IsReadable - KeyAt - ValueAt`。这里需要理解`occupied_`和`readable_`，相当于该页中数据的位图，数据段中下标为`bucket_idx`的状态由`occupied_`和`readable_`中的第`bucket_idx/8`个字符中第`bucket%8`位决定。`occupied_`意思为被占用过，但是在这里我觉得并没有多大用处，并不能提高检索的速度，`readable_`表示当前下标是可读的，有效的。初始所有的下标都是`occupied_`和`readable_`都是0，当`bucket_idx`被写入时，为`occupied_`和`readable_`对应位置位。当`bucket_idx`被删除时，将`readable_`对应位复位为0。

``` cpp
// src/include/storage/page/hash_table_bucket_page.h
/**
 * Store indexed key and and value together within bucket page. Supports
 * non-unique keys.
 *
 * Bucket page format (keys are stored in order):
 *  ----------------------------------------------------------------
 * | KEY(1) + VALUE(1) | KEY(2) + VALUE(2) | ... | KEY(n) + VALUE(n)
 *  ----------------------------------------------------------------
 *
 *  Here '+' means concatenation.
 *  The above format omits the space required for the occupied_ and
 *  readable_ arrays. More information is in storage/page/hash_table_page_defs.h.
 *
 */
  private:
      //  For more on BUCKET_ARRAY_SIZE see storage/page/hash_table_page_defs.h
	  // 00010001 -> bucket_idx occupied are [0, 4].
      char occupied_[(BUCKET_ARRAY_SIZE - 1) / 8 + 1];
      // 0 if tombstone/brand new (never occupied), 1 otherwise.
      char readable_[(BUCKET_ARRAY_SIZE - 1) / 8 + 1];
      MappingType array_[0];
```

首先实现`IsOccupied `,`IsReadable `以及`KeyAt `,`KeyAt `，同时建议实现`SetOccupied`和`SetReadable`，方便插入和删除时使用。插入和删除逻辑一定要检查绝对正确，否则后续出问题，很难定位。

实现插入Insert，两种情况下插入失败：当前页已满或键值对重复。找到一个未被使用或者不可读的下标进行插入。

实现删除Remove，设置标志位即可。

##### 实现哈希表

`ExtendibleHashTable`位于`src/container/hash/extendible_hash_table.cpp`主要实现构造函数，插入`Insert`，删除`Remove`，查找`GetValue`。

###### 构造函数以及辅助函数

`ExtendibleHashTable`，传入缓冲池，key的比较函数以及key的哈希函数。创建两页初始页，一页作为目录页，一页作为数据页，初始化目录页对应的位数和页面指针。目录页使用通过缓冲池中的页构造方式

``` cpp
  auto page = buffer_pool_manager_->NewPage(&directory_page_id_);

  if (directory_page_id_ == INVALID_PAGE_ID) {
    throw Exception(ExceptionType::OUT_OF_MEMORY, "Can't get page from BFP for HashTable.");
  }

  auto dir_page = reinterpret_cast<HashTableDirectoryPage *>(page->GetData());
  buffer_pool_manager_->UnpinPage(directory_page_id_, true);
```

通过`buffer_pool_manager_`拿出的页，在使用结束后一定要`Unpin`。

``` cpp
template <typename KeyType, typename ValueType, typename KeyComparator>
inline uint32_t HASH_TABLE_TYPE::KeyToDirectoryIndex(KeyType key, HashTableDirectoryPage *dir_page) {
  return Hash(key) & dir_page->GetGlobalDepthMask();
}

template <typename KeyType, typename ValueType, typename KeyComparator>
inline uint32_t HASH_TABLE_TYPE::KeyToPageId(KeyType key, HashTableDirectoryPage *dir_page) {
  uint32_t bucket_index = KeyToDirectoryIndex(key, dir_page);
  return dir_page->GetBucketPageId(bucket_index);
}
```

`KeyToDirectoryIndex`，`KeyToPageId`：通过key拿到对应桶在目录页中的下标和页指针，这里使用的是哈希值的后缀，方便取掩码。

``` cpp
template <typename KeyType, typename ValueType, typename KeyComparator>
HashTableDirectoryPage *HASH_TABLE_TYPE::FetchDirectoryPage() {
  // No virtual table, so the page and page_data_ have same pointer address.
  Page *page = buffer_pool_manager_->FetchPage(directory_page_id_);
  return reinterpret_cast<HashTableDirectoryPage *>(page->GetData());
}

template <typename KeyType, typename ValueType, typename KeyComparator>
HASH_TABLE_BUCKET_TYPE *HASH_TABLE_TYPE::FetchBucketPage(page_id_t bucket_page_id) {
  if (bucket_page_id == INVALID_PAGE_ID) {
    throw Exception(ExceptionType::OUT_OF_MEMORY, "Invalild page id to get");
  }
  // No virtual table, so the page and page_data_ have same pointer address.
  Page *page = buffer_pool_manager_->FetchPage(bucket_page_id);
  assert(page != nullptr);
  return reinterpret_cast<HASH_TABLE_BUCKET_TYPE *>(page->GetData());
}
```

从缓冲池中拿出目录页和数据页，并且转换为对应的页表示形式，通过`reinterpret_cast`进行指针的重新解释。

###### 插入以及删除

插入和删除建议先不考虑split和merge的情况，先简化问题，完成最基础的插入和删除。

在当前页已满的条件下进行split_insert，插入逻辑如下。

``` cpp
// 1. Update local depth, get a new page from buffer poll.
// 2. Separate bucket_idx same with new_bucket_idx, and remove them from previous bucket.
// 3. Insert these keys same with new_bucket_idx to new bucket.
// 4. Insert new k,v to corresponding bucket.
// 5. The bucket haven't been influenced, don't need change the bucket.
//    But if grow global depths, need to point new hash code to correct bucket.

//  Global depth need't update.
//  Eg:
//  Global: 1                                                      local depth
//    00 -> (data1(00), data2(10)) -----> same bucket with 10           1
//    01 -> (data3(01), data4(01))                                      2
//    10 -> (data1(00), data2(10)) -----> same bucket with 00           1
//    11 -> (data5(11))                                                 2
//  After insert data6(00): 00' bucket split                       local depth
//    00 -> (data1(00), data6(00))                                      2
//    01 -> (data3(01), data4(01))                                      2
//    10 -> (data2(10))                                                 2
//    11 -> (data5(11))                                                 2
// Global depth need update.
//  Eg:
//     0 -> (data1(00), data2(10))
//     1 -> (data3(11))
//  After insert data4(00):                        local depth
//    00 -> (data1(00), data4(00))                      2
//    01 -> (data3(11))  -----> same with 11            1
//    10 -> (data2(10))                                 2
//    11 -> (data3(11))  -----> same with 01            1
```

在split和merge的过程中最重要的就是查找当前数据页哈希值对称的页的下标，如10(2)在进行split过程中，提升局部位数为3后变为010(3)，其对称页为110(3)。

``` cpp
template <typename KeyType, typename ValueType, typename KeyComparator>
uint32_t HASH_TABLE_TYPE::GetSymmetryBucketIndex(uint32_t bucket_index, uint32_t mask_depth) {
  if (mask_depth == 0) {
    return 0;
  }
  uint32_t new_bucket_index = bucket_index ^ (1 << (mask_depth - 1));
  return new_bucket_index;
}
```

当删除元素后，该页为空时，进行merge操作：删除空页，将目录页的指针指向非空页，非空页的局部深度减1。

``` cpp
//  Eg:
//  Global: 1                                                      local depth
//    00 -> (data1(00), data2(10)) -----> same bucket with 10           1
//    01 -> (data3(01), data4(01))                                      2
//    10 -> (data1(00), data2(10)) -----> same bucket with 00           1
//    11 -> (data5(11))                                                 2
//  After delete data5(11):                                        local depth
//    00 -> (data1(00), data2(10)) -----> same bucket with 10           1
//    01 -> (data3(01), data4(01))                                      2
//    10 -> (data1(00), data2(10)) -----> same bucket with 00           1
//    11 -> ()                                                          2
//  Merge 01 and 11                                                local depth
//    00 -> (data1(00), data2(10)) -----> same bucket with 10           1
//    01 -> (data3(01), data4(01)) -----> same bucket with 01           1
//    10 -> (data1(00), data2(10)) -----> same bucket with 00           1
//    11 -> (data3(01), data4(01)) -----> same bucket with 11           1
//  Shrink                                                         local depth
//    0 -> (data1(00), data2(10))                                       1
//    1 -> (data3(01), data4(01))                                       1
```

之后需要尝试持续进行shrink，可以shrink的条件是，所有数据页的局部深度都小于全局深度。这其中调试很恼火，需要多打一些类似下图中的日志。

``` cpp
  while (dir_page->CanShrink()) {
    // 多打log
    LOG_TRACE("HashTable Shrink: From (%u) to (%u) ", dir_page->GetGlobalDepth(), dir_page->GetGlobalDepth() - 1);
    dir_page->DecrGlobalDepth();

    for (uint32_t bucket_index = 0; bucket_index <= dir_page->GetGlobalDepthMask(); bucket_index++) {
      MergeEmptyBucket(dir_page, bucket_index);
    }
  }
```

调试哈希表打印哈希表的信息，调试过程中最困难的还是需要官方的测试用例进行调试，要不然很难定位到问题。

``` cpp
template <typename KeyType, typename ValueType, typename KeyComparator>
void HASH_TABLE_TYPE::PrintHashTable() {
  HashTableDirectoryPage *dir_page = FetchDirectoryPage();
  dir_page->PrintDirectory();

  for (uint32_t i = 0; i <= dir_page->GetGlobalDepthMask(); i++) {
    auto page_id = dir_page->GetBucketPageId(i);
    auto page = FetchBucketPage(page_id);
    LOG_INFO("Bucket Info: %u, Full: %u, Empty: %u.", i, page->IsFull(), page->IsEmpty());
    page->PrintBucket();

    buffer_pool_manager_->UnpinPage(page_id, false, nullptr);
  }

  assert(buffer_pool_manager_->UnpinPage(directory_page_id_, false, nullptr));
}
```

###### 读取

``` cpp
HASH_TABLE_TYPE::GetValue(Transaction *transaction, const KeyType &key, std::vector<ValueType> *result)

调用数据页的api，注意不能清空传入的result数组。
```

##### 并发哈希表

``` cpp
  // Responsible for dirpage
  // Bucket page use page's lock.
  std::shared_mutex table_latch_;
```

+ 首先要不考虑性能，通过加全局的`table_latch_`通过所有测试用例。
+ 考虑使用读写锁
    + 读取：`table_latch_`读锁，`bucket_page`读锁
    + 插入：`table_latch_`读锁，`bucket_page`写锁。如果需要进行split，依次释放对应的锁`table_latch_`升级为写锁，`bucket_page`写锁，需要重新检查是否还需要split。
    + 删除：与插入同理。

#### 参考博客

+ https://www.inlighting.org/archives/cmu-15-445-notes/
+ https://www.cnblogs.com/JayL-zxl/category/1919605.html
+ https://15445.courses.cs.cmu.edu/fall2021/
+ https://segmentfault.com/a/1190000015856311
+ https://www.jianshu.com/p/c4e4d55706ff

