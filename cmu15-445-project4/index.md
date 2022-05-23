# cmu15-445-project4


## 2021 FALL cmu15-445-project4

实现基于抢占的读写锁(lock manager)，涉及的知识点为ppt15-18章。

#### 事务

事务是一系列数据库请求，这些请求的执行要么全部成功，要么全部失败。

事务的四大特性：ACID

##### 原子性

事务的执行要么全部成功，要么全部失败。

原子性的保证：UndoLog（回滚未提交的操作），RedoLog（执行已经提交的操作）。

##### 一致性

数据库一致性：数据库中的数据是对现实世界中的模拟，并且满足约束的规则。

事务一致性：事务执行前后数据库均满足一致性。

无论事务如何执行，最终应该满足总额为2120的一致性

<img src="https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220507151857380.png" alt="image-20220507151857380" style="zoom:50%;" />



##### 隔离性

多个事务并发执行就像事务单独执行一样并不会相互影响。

###### 并发控制协议

为了达到事务并发执行的目的，需要并发控制协议来进行协调。

+ 悲观锁：事务执行时获取需要的锁，不会导致冲突的发生。
+ 乐观锁：假设事务间冲突是罕见的，遇到冲突后再处理。

###### 正确性

为了保证结果正确（一致性），并发执行的顺序必须等同于某种串行执行的顺序。

<img src="https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220507152154916.png" alt="image-20220507152154916" style="zoom: 33%;" /><img src="https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220507152205777.png" alt="image-20220507152205777" style="zoom: 33%;" />

###### 事务冲突

两个事务不同的事务，如果至少有一个事务对对象有写的操作便会产生冲突。

读写冲突：不可重复读

写读冲突：读未提交（脏读）

写写冲突：覆盖写（更新丢失）

<img src="https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220507152851072.png" alt="image-20220507152851072" style="zoom: 50%;" /><img src="https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220507152953084.png" alt="image-20220507152953084" style="zoom:50%;" /><img src="https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220507153123811.png" alt="image-20220507153123811" style="zoom:50%;" />

###### 串行化分类

冲突的串行化：冲突的串行化执行可以通过一定的转换为某种串行化的结果。

判断是否可转化未串行化的方法：

1. 移动不冲突的操作
2. 通过资源依赖图：如果有环存在则不可转换。

<img src="https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220507153557376.png" alt="image-20220507153557376" style="zoom:67%;" />

视图串行化：允许一定的冲突但是不影响正确性，如覆盖写。

<img src="https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220507153813297.png" alt="image-20220507153813297" style="zoom:50%;" />

##### 持久性

所有已经提交的事务必须是持久的，通过LOG日志实现持久性，这是一个复杂的话题。

#### 2PL

##### 锁的类型

<img src="https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220507154739208.png" alt="image-20220507154739208" style="zoom:50%;" />

##### 两阶段锁

分为Growing和Shrinking两阶段。只有在Growing阶段才能获取锁，释放过锁后进入Shrinking阶段。

<img src="https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220507154825599.png" alt="image-20220507154825599" style="zoom: 50%;" /><img src="https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220507155020086.png" alt="image-20220507155020086" style="zoom:50%;" />

缺点：

+ 级联回滚：由于脏读，当一个事务取消时，其他与只有关的事务也需要回滚。

T1执行失败时，T2读到了A的脏数据，也需要回滚，这种连锁反应就叫级联回滚。

<img src="https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220507155432485.png" alt="image-20220507155432485" style="zoom:50%;" />

##### 严格两阶段锁

只有在事务执行完之后才允许释放所有相关的锁。

<img src="https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220507155851198.png" alt="image-20220507155851198" style="zoom:67%;" />

##### 两阶段锁对比

普通两阶段锁并不满足串行化的要求，只有严格两阶段锁满足串行化要求。

<img src="https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220507160002491.png" alt="image-20220507160002491" style="zoom:67%;" />

#### 死锁

解决方法有两种：死锁检测和死锁避免。

##### 死锁检测

通过依赖图检测死锁，如果出现了环那么就为出现了死锁。当出现死锁后，按照一定的规则挑选出需要回滚的事务进行回滚。

##### 死锁避免

利用事务唯一的id避免死锁，较小的时间戳有更高的优先级。（T1>T2）

Wait-Die：只有较高优先级的事务才能等待锁，否则直接回滚。

Wound-Wait（抢占）：较高优先级的事务会抢占低优先级的事务的锁，低优先级事务直接回滚。低优先级的事务会等待其释放锁。

<img src="https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220507162028425.png" alt="image-20220507162028425" style="zoom:67%;" />

##### 意向锁

意向锁是为了解决多层级加锁中隐式加锁的问题。在意向锁使用的情况下，向根节点加锁无需遍历所有的儿孙节点的锁使用情况。

读意向锁(IS)：该节点的儿孙节点中有加读锁。

写意向锁(IX)：该节点的儿孙节点中有加写锁。

读写意向锁(SIX)：该节点加读锁并且获得其儿子节点写锁。

对一个节点加S锁，IS锁之前，首先要获得其父节点的IS锁。

对一个节点加X锁，IX锁之前，首先要获得其父节点的IX锁。

<img src="https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220507162740978.png" alt="image-20220507162740978" style="zoom:67%;" />

#### 基于时间戳的并发控制

##### 概念

每个事务维护一个事务的时间戳TS(T)，数据库中的每个资源xX维护其最后被读写(W-TS(X)或R-TS(X))的时间戳。

+ 读取：如果事务的TS(T) < W-TS(X)，回滚T。否则允许T读取该记录，并且更新R-TS(X)，为T维护一份X的副本。

+ 写入：如果事务的TS(T)<W-TS(X)或TS(T)<R-TS(X)，回滚T。否则允许T更新X并且个更新W-TS(X)

##### THOMAS写规则

+ TS(T)<R-TS(X)：回滚T。
+ TS(T)<W-TS(X)：当前写入无效，忽略这次写入，并且继续执行T。
+ 否则允许T更新X并且个更新W-TS(X)。

##### 乐观并发控制OCC

如果事务持续时间很短，获取锁的损耗会很大。数据库系统为每个事务维护一份资源的工作区：

+ 读取时将数据放入工作区，修改也是应用到工作区。
+ 当事务提交时，对比当前工作区与数据库是否存在冲突。

###### OCC执行的阶段

+ 读写阶段：将数据放入工作区，修改也是应用到工作区。
+ 验证阶段：当事务提交时，对比当前工作区与数据库是否存在冲突。
+ 写阶段：如果不存在冲突，将其写入数据库。

只有在验证写入阶段才会为该事务分配事务时间戳。

![image-20220507170557570](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220507170557570.png)

###### 验证方法

验证阶段需要保证事务的串行化，验证执行的事务是否存在读写冲突。

反向验证：验证是否与已经提交的事务存在冲突。

前向验证：验证是否与未提交的事务存在冲突。

###### 使用场景：

+ 事务间冲突较少：读多写少，事务间访问数据无交集。
+ 拷贝数据存在性能损耗，验证和写入阶段是性能的瓶颈，重新执行该事务损耗更大。

##### 事务隔离级别

<img src="https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220507171426729.png" alt="image-20220507171426729" style="zoom:67%;" />

2PL实现不同事务隔离级别的方法：对索引加锁可以解决幻读问题。

<img src="https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220507171459463.png" alt="image-20220507171459463" style="zoom:67%;" />

#### MVCC

##### 概念

对同一行数据，MVCC有多个版本，形成版本链。读写不会相互阻塞，但是写写之间会阻塞。写操作会创建一个新的版本，读操作会通过快照的可见性进行读取。

![image-20220507201536928](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220507201536928.png)

##### MVCC设计思想

###### 并发控制协议

MVCC并不是一种并发控制协议，可以通过不同的并发控制协议实现，涉及整个数据库系统。MV-2PL：版本链决定版本是否可见，而该版本的可读可写由2PL实现。

![img](https://picture-table.oss-cn-beijing.aliyuncs.com/img/v2-81a01b066f7fce6f2b0f37fff7103cff_720w.jpg)

###### 版本链设计

对于逻辑上的一行，创建一个版本链。

APPEND：新产生的版本连接到旧版本的后面，在同一表中。

![image-20220507202943480](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220507202943480.png)

TIME-TRAVEL TABLE：新产生的版本不在同一个表中，而是存储在其他区域。

![image-20220507203102400](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220507203102400.png)

DELTA Storage：版本链表中存储的不是具体表的数据，而是表的变化。

![image-20220507203129521](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220507203129521.png)

###### 垃圾清理

###### 索引管理

主键索引指向版本链的头部，版本链从新到旧，更新主键相当于先删除后增加一个新的主键。二级索引有两种方式指向版本链，一种直接指向版本链，另一种是通过主键查询版本链。

<img src="C:/Users/shen/AppData/Roaming/Typora/typora-user-images/image-20220507204337215.png" alt="image-20220507204337215" style="zoom: 33%;" /><img src="https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220507204356316.png" alt="image-20220507204356316" style="zoom:33%;" />

#### 实验代码

##### Lock Manager

###### 代码框架

`LockRequest`是一个读写请求，主要有两个字段，一个是tid，另一个是加锁方式(X/S)，以及是否获得了锁。

``` cpp
  class LockRequest {
   public:
    LockRequest(txn_id_t txn_id, LockMode lock_mode) : txn_id_(txn_id), lock_mode_(lock_mode), granted_(false) {}

    txn_id_t txn_id_;
    LockMode lock_mode_;
    bool granted_;
  };
```

`LockRequestQueue`是请求队列的管理，它包含一个请求队列，以及一个条件变量用来唤醒正在队列中等待的线程。可以通过`Print`函数打印当前队列获得锁的情况进行基础的Debug。

``` cpp
  class LockRequestQueue {
   public:
    std::list<LockRequest> request_queue_;
    // for notifying blocked transactions on this rid
    std::condition_variable cv_;
      
    void Print() {
      std::string out_string;

      for (auto &req : request_queue_) {
        std::string info;
        info += req.lock_mode_ == LockMode::EXCLUSIVE ? "X(" : "S(";
        info += std::to_string(req.txn_id_);
        info += req.granted_ ? ",true)" : ",false)";
        info += " ";
        out_string += info;
      }

      LOG_DEBUG("%s", out_string.c_str());
    }
 }
```

`LockManager`通过2PL实现了对每一行数据读写锁的管理，通过哈希表管理每一行的读写队列，以及mutex实现对互斥量的保护。

``` cpp
  /*
   * [LOCK_NOTE]: For all locking functions, we:
   * 1. return false if the transaction is aborted; and
   * 2. block on wait, return true when the lock request is granted; and
   * 3. it is undefined behavior to try locking an already locked RID in the
   * same transaction, i.e. the transaction is responsible for keeping track of
   * its current locks.
   */

  /**
   * Acquire a lock on RID in shared mode. See [LOCK_NOTE] in header file.
   * @param txn the transaction requesting the shared lock
   * @param rid the RID to be locked in shared mode
   * @return true if the lock is granted, false otherwise
   */
  bool LockShared(Transaction *txn, const RID &rid);

  /**
   * Acquire a lock on RID in exclusive mode. See [LOCK_NOTE] in header file.
   * @param txn the transaction requesting the exclusive lock
   * @param rid the RID to be locked in exclusive mode
   * @return true if the lock is granted, false otherwise
   */
  bool LockExclusive(Transaction *txn, const RID &rid);

  /**
   * Upgrade a lock from a shared lock to an exclusive lock.
   * @param txn the transaction requesting the lock upgrade
   * @param rid the RID that should already be locked in shared mode by the
   * requesting transaction
   * @return true if the upgrade is successful, false otherwise
   */
  bool LockUpgrade(Transaction *txn, const RID &rid);

  /**
   * Release the lock held by the transaction.
   * @param txn the transaction releasing the lock, it should actually hold the
   * lock
   * @param rid the RID that is locked by the transaction
   * @return true if the unlock is successful, false otherwise
   */
  bool Unlock(Transaction *txn, const RID &rid);

 private:
  std::mutex latch_;

  /** Lock table for lock requests. */
  std::unordered_map<RID, LockRequestQueue> lock_table_;

```

###### LockShared/LockExclusive

+ 检查当前事务状态是否为`abort`，如果是返回false。

+ 检查是否满足2PL，只有在Growing阶段才能获取锁。

+ 检查事务隔离级别，`Read uncommited`无需获取S锁。

+ 检查是否重复加锁，已经获得锁直接返回true。

+ 获取LockManager中的latch_，并将等待的读写请求插入到`lock_table_`中。

+ 检查条件变量是否满足获得读写锁的条件（这一步可以封装到GetLatch中）。

    + `LockManager::GetLatch(Transaction *txn, LockRequestQueue *lock_queue)`：txn请求从lock_queue中获得锁。

    + 不满足的话，等待被唤醒再次检查是否可以获得锁。在检查之前需要先检查当前事务是否为`abort`。

+ 获得锁，修改请求中的`granted_`变量，将rid添加到事务获得锁的集合当中。

###### 获得锁的实现

+ **检查是否可以获得锁`TryGetLatch(txn, lock_queue)`**
    1. 该请求在等待队列的队头，无论是X锁还是S锁都可以直接获得。
    2. 该请求为S锁，其之前所有的请求均为S锁。
+ **抢占的条件`Would wait`：**
    1. 该请求为X锁，其之前所有低优先级txn均应该abort
    2. 该请求为S锁，其之前低优先级txn的X锁应该abort

+ **`GetLatch`的流程：**

1. `TryGetLatch`尝试直接获取锁。
2. 尝试抢占锁，首先abort满足抢占条件的txn，之后通过`TryGetLatch`再次获得锁。

+ **注意事项**
    1. 如果可以获得S锁，那么需要唤醒其他等待的锁，唤醒在队列中该S锁之后的的S锁。存在`S S S S`的情况。
    2. 如果在抢占过程中存在被abort的txn，需要唤醒其他等待的txn获得锁。

###### UpdateLatch

+ 检查当前事务状态是否为`abort`，如果是返回false。
+ 检查是否满足2PL，只有在Growing阶段才能获取锁。
+ 如果没有获得S锁返回false，如果已经获得了X锁返回true。
+ 检查是否满足升级锁的条件
    + 首先将队列中该txn的S锁删除，之后插入新的X锁。然后通过`GetLatch`检查是否可以获得锁。
+ 将该txn中rid从读锁集合中删除，插入到写锁的集合中。

###### Unlock

+ 如果隔离级别为可重复读，进入Shrinking状态。
+ 删除rid所有的锁，并且从读写锁的集合中删除。

##### Concurrent Query Execution

###### 不同隔离级别加锁情况

+ 串行化：Strict 2PL，索引锁。
+ 可重复读：Strict 2PL。
+ 读已提交：Strict 2PL但是S锁使用完后可以立即释放。
+ 读未提交：Strict 2PL但是无S锁，允许脏读。

#### 参考博客

+ https://www.inlighting.org/archives/cmu-15-445-notes/
+ https://www.cnblogs.com/JayL-zxl/category/1919605.html
+ https://15445.courses.cs.cmu.edu/fall2021/
+ https://juejin.cn/post/6844904096378404872
+ https://zhuanlan.zhihu.com/p/127274032
+ https://www.modb.pro/db/41656

