# cmu15-445-project3


## 2021 FALL cmu15-445-project3

实现数据库执行器(Query Executor)，涉及的知识点为ppt9-14章。

通过迭代器模型(iterator model/Volcano model)实现增删改查，连接，排序（这里不需要实现）和聚集函数。

- **Access Methods**: Sequential Scan
- **Modifications**: Insert, Update, Delete
- **Miscellaneous**: Nested Loop Join, Hash Join, Aggregation, Limit, Distinct

#### 排序

面向磁盘的数据库系统，并不能保证查询的结果能够容纳在内存中，因此需要将结果保存到磁盘当中。

![image-20220503195805354](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220503195805354.png)

##### 外部归并排序(External Merge Sort)

![image-20220503200359664](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220503200359664.png)

假设有`N`页数据页，缓冲池中有`B`页容量，遍历一轮数据页(Sort/Merge)称为一轮(1Pass)。可以执行k(k=B-1)路External Merge Sort。经历`i`轮操作之后，每$k^i$页内部有序。`i=0, Sorting`，每1($k^0$)页内部有序，`i=1, Merging`，每k($k^1$)页内部有序...。

+ Pass #0：遍历每一页，排序后写回。
+ Pass #i：每$k^i$页进行合并，直到($k^i>=N$)。

共有$1+log_kN$轮操作(sort：1Pass，Merge：$log_kN$ Pass)，每一轮操作需要读入N页，写入N页。

总共的IO操作：**$2N*(1+log_kN)$**

![image-20220503202011010](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220503202011010.png)

缓冲池中至少需要3页，两页用于输入，一页用于输出，执行2路外部归并排序。

##### B+树索引排序

+ B+树聚簇索引有序，包含所有的数据记录，直接进行遍历即可排序。

![image-20220503203743975](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220503203743975.png)

+ 非聚簇索引回表产生大量的随机IO。

![image-20220503204054855](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220503204054855.png)

#### 聚集函数

聚集函数包括`ORDER BY`,`JOIN`,`GROUP BY`,`AVG`,`LIMIT`,`Distinct`等对某一列进行操作，主要通过哈希和排序进行实现。

**`Distinct`，`GROUP BY`可以通过排序实现，但是如果没有显式地排序地话，哈希将会是一种更好的处理方式。**

##### 外部哈希聚集

###### 动态哈希(Disk)

假设缓冲池中有B页，B-1页用于哈希，1页用于输入数据。

![image-20220503210606639](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220503210606639.png)

###### Rehash(Memory)

通过二次哈希产生中间结果，实现聚集函数。

![image-20220503211144992](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220503211144992.png)

#### 连接算法

##### 连接分类

例子可以参考https://www.jianshu.com/p/c4c43f32b66f。

+ 内连(Inner-Join)：连接相同的两列，用ON表示条件。

+ 外连(Outer-Join)：左连，右连，全连。

![image-20220504150627195](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220504150627195.png)

##### 早物化与晚物化

早物化在连接过程中会产生临时表，最后结果无需再去表中寻找其他的记录。晚物化在连接过程中只会记录结果的RowID，后续如果需要使用该记录需要利用该RowID进行查找。

##### 连接表假设

表R有M页共m行数据，表S有N页共n行数据，计算连接两表需要的IO操作。

![image-20220504151659032](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220504151659032.png)

##### Nested Loop Join（循环）

较小的表做驱动表

###### Simple

对于表R中的每条记录，都要从S中扫描一遍。

Cost：$M+(m*N)$(`M`是从表R中取出每一页，`m*N`是表R中的每一行都需要扫描表S)

![image-20220504152752143](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220504152752143.png)

###### Block

按页进行扫描

Cost：$M + M*N$

![image-20220504153038820](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220504153038820.png)

假设缓冲池可以存放B页，B-2页存放驱动表R，1页存放被驱动表S，1页用于输出。

Cost：$M+\lceil M/(B-2)\rceil * N$

###### Index

遍历R中的每一行，利用S中的索引查找$r_i=s_j$，每次查找的时间为$C$

Cost：$M+(m*C)$

![image-20220504154940771](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220504154940771.png)

##### Sort-Merge Join（排序）

将两表排序后，利用双指针查找有效结果。

![image-20220504155249938](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220504155249938.png)

+ Sort R：$2M*(1+\lceil log_{B-1} \lceil M/b \rceil \rceil)$
+ Sort S：$2N*(1+\lceil log_{B-1} \lceil N/b \rceil \rceil)$
+ Merge：M+N
+ Total：Sort+Merge

如果两个表已经被排序好，或者结果也需要排序，那么通过排序连接将会是十分高效的。

##### Hash Join（哈希）

###### Basic Hash Join

+ 首先对表R建立哈希表$HT_R$（Build），之后对于S中的每一行，查找$HT_R$中是否存在该元素（Probe）。
+ 哈希值子在哈希表中存在两种情况：早物化或者晚物化
+ Basic Hash Join 只能在内存可以完全容纳哈希表时使用

![image-20220504165358231](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220504165358231.png)

在查找过程中可以通过布隆过滤器进行加速，布隆过滤器通过多个哈希函数确定该key是不是一定不在哈希表之中。其主要思想是位图和多个哈希函数。

![image-20220504165736883](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220504165736883.png)

###### Grace Hash Join

分别对R和S进行哈希，之后将有相同哈希值的数据页进行Nest Block Join

Hash：$2(M+N)$

Probe：$M+N$

Total：$3(M+N)$

![image-20220504170626874](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220504170626874.png)

#### 连接算法IO时间对比

Hash Join最优，所以通常使用Hash Join，如果输入数据已经排序那么Sort-Merge Join的效率更高。

![image-20220504165939982](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220504165939982.png)

#### 关系操作符

关系relation就是一个表，关系操作符就是对一个表或两个表之间的操作运算符。

##### 执行计划

所有的关系操作符组成表达式树，通过后序遍历自下而上计算关系运算符得出最后的结果。

![image-20220503192043047](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220503192043047.png)

##### 迭代模型

每一个请求通过`Next`实现：

+ 返回True，得到一行数据。
+ 返回False，请求结束。

![image-20220504172050800](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220504172050800.png)

##### 物化模型

将计算产生的中间结果生成临时表供上层操作符使用

![image-20220504172257025](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220504172257025.png)

##### 矢量化模型

介于物化模型和迭代模型之间，每次迭代产生一定数量的行

![image-20220504184844942](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220504184844942.png)

#### 请求执行

##### 查询请求

###### 顺序扫描

按照顺序访问数据库中的每一页，通过游标(cursor)记录当前访问的页。

常用的优化方式：

+ 预取
+ 增大缓冲池
+ 并行化
+ 堆聚类
+ Zone Map：提前计算聚集函数的参数。
+ 晚物化：最终使用聚集函数可以通过RowID延迟物化。

![image-20220504185909392](C:/Users/shen/AppData/Roaming/Typora/typora-user-images/image-20220504185909392.png)

###### 单个索引

###### 多个索引

##### 修改请求

修改主要包括：插入，删除，更新。修改过程中要同时修改行和索引数据。如果修改后的数据再次被检索到则会产生HALLOWEEN问题。

![image-20220504190122062](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220504190122062.png)

#### 请求并行

并行与分布式的差别在于资源间通信的速度，并行通信的速度远高于分布式。

![image-20220505143448525](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220505143448525.png)

##### 进程模型

![image-20220505144020562](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220505144020562.png)

##### 线程模型

![image-20220505144027313](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220505144027313.png)

##### 多请求并行

##### 单请求并行

水平并行，垂直并行，IO并行(RAID)

#### 请求优化

##### 优化方式

重写请求：按照一定规则重写请求，提高执行效率。

损耗对比：对于所有可行的执行计划，计算其执行损耗，选择损耗最小的计划进行执行。

![image-20220505145245224](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220505145245224.png)

##### 请求重写

###### 关系代数等效

谓词下放：提前进行投影，或者选择减少数据的规模，还可以对选择的语句进行化简。

![image-20220505150125907](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220505150125907.png)

###### 逻辑请求优化

优化方法：分离谓词，谓词下放，替换笛卡尔积，投影下放

![image-20220505150813968](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220505150813968.png)

分离谓词

![image-20220505150921271](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220505150921271.png)谓词下放

![image-20220505151008727](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220505151008727.png)

替换笛卡尔积

![image-20220505150955133](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220505150955133.png)

投影下放：执行过程中只选择参与请求的列。

![image-20220505151044250](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220505151044250.png)

###### 子查询

重写子查询和分解子查询。

###### 表达式重写

##### 执行计划损耗

物理损耗必须要考虑顺序IO和随机IO，顺序IO的访问速度是随机IO的4倍。

![image-20220505153007739](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220505153007739.png)

###### 统计数据

每个表内都会存有关于表，索引，表项的统计数据。这些数据可以用于估计执行查询的代价。

###### 逻辑损耗

选择谓词可以通过选择性(selectivity近似为概率)计算损失，选择性也可以通过采样进行计算。

计算时需要满足以下三个条件：

![image-20220505155505442](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20220505155505442.png)

#### 实验代码

##### 代码框架

###### AbstractPlanNode

AbstractPlanNode是执行计划表达式树中的一个节点（即关系运算符），由它组成一棵多叉的表达式树。所有的关系运算符的实现都需要继承该抽象基类。 

``` cpp
// src/include/execution/plans/abstract_plan.h
/**
 * AbstractPlanNode represents all the possible types of plan nodes in our system.
 * Plan nodes are modeled as trees, so each plan node can have a variable number of children.
 * Per the Volcano model, the plan node receives the tuples of its children.
 * The ordering of the children may matter.
 */
class AbstractPlanNode {
 public:
  /**
   * Create a new AbstractPlanNode with the specified output schema and children.
   * @param output_schema the schema for the output of this plan node
   * @param children the children of this plan node
   */
  AbstractPlanNode(const Schema *output_schema, std::vector<const AbstractPlanNode *> &&children)
      : output_schema_(output_schema), children_(std::move(children)) {}

  /** @return the type of this plan node */
  // 抽象基类
  virtual PlanType GetType() const = 0;

 private:
  /**
   * The schema for the output of this plan node. In the volcano model, every plan node will spit out tuples,
   * and this tells you what schema this plan node's tuples will have.
   */
  const Schema *output_schema_;
  /** The children of this plan node. */
  std::vector<const AbstractPlanNode *> children_;
};
```

###### AbstractExecutor

AbstractExecutor用来计算关系运算符向上的返回值。`AbstractExecutor`是`AbstractPlanNode`对应运算符的具体实现。关系运算符具体的运算过程通过继承该抽象基类实现，`exec_ctx_`中存放了该关系运算符需要的信息。它实现了迭代器模型中的`Next`和`Init`方法。

``` cpp
// src/include/execution/executors/abstract_executor.h
/**
 * The AbstractExecutor implements the Volcano tuple-at-a-time iterator model.
 * This is the base class from which all executors in the BustTub execution
 * engine inherit, and defines the minimal interface that all executors support.
 */
class AbstractExecutor {
 public:
  /**
   * Construct a new AbstractExecutor instance.
   * @param exec_ctx the executor context that the executor runs with
   */
  explicit AbstractExecutor(ExecutorContext *exec_ctx) : exec_ctx_{exec_ctx} {}

  /** Virtual destructor. */
  virtual ~AbstractExecutor() = default;

  /**
   * Initialize the executor.
   * @warning This function must be called before Next() is called!
   */
  virtual void Init() = 0;

  /**
   * Yield the next tuple from this executor.
   * @param[out] tuple The next tuple produced by this executor
   * @param[out] rid The next tuple RID produced by this executor
   * @return `true` if a tuple was produced, `false` if there are no more tuples
   */
  virtual bool Next(Tuple *tuple, RID *rid) = 0;

  /** @return The schema of the tuples that this executor produces */
  virtual const Schema *GetOutputSchema() = 0;

  /** @return The executor context in which this executor runs */
  ExecutorContext *GetExecutorContext() { return exec_ctx_; }

 protected:
  /** The executor context in which the executor runs */
  ExecutorContext *exec_ctx_;
};
```

###### 请求的执行过程

分析测试顺序扫描的测试文件`SimpleSeqScanTest`。通过输出的表头，投影信息，表的oid构造了以`SeqScanPlanNode`，`SeqScanPlanNode`继承了`AbstractPlanNode`。之后通过`ExecutionEngine`的`Execute`方法执行该执行计划。

``` cpp
// SELECT col_a, col_b FROM test_1 WHERE col_a < 500
TEST_F(ExecutorTest, SimpleSeqScanTest) {
  // Construct query plan
  TableInfo *table_info = GetExecutorContext()->GetCatalog()->GetTable("test_1");
  const Schema &schema = table_info->schema_;
  auto *col_a = MakeColumnValueExpression(schema, 0, "colA");
  auto *col_c = MakeColumnValueExpression(schema, 0, "colC");
  auto *const500 = MakeConstantValueExpression(ValueFactory::GetIntegerValue(500));
  auto *predicate = MakeComparisonExpression(col_a, const500, ComparisonType::LessThan);
  auto *out_schema = MakeOutputSchema({{"colA", col_a}, {"colC", col_c}});
  // Create plan node
  SeqScanPlanNode plan{out_schema, predicate, table_info->oid_};

  // Execute
  std::vector<Tuple> result_set{};
  GetExecutionEngine()->Execute(&plan, &result_set, GetTxn(), GetExecutorContext());
}
```

`Execute`方法执行执行计划，通过`ExecutorFactory`工厂函数构造`AbstractPlanNode`对应`AbstractExecutor`完成执行过程。对于`SeqScanPlanNode`则构造了对应的`SeqScanExecutor`进行执行。

``` cpp
  /**
   * Execute a query plan.
   * @param plan The query plan to execute
   * @param result_set The set of tuples produced by executing the plan
   * @param txn The transaction context in which the query executes
   * @param exec_ctx The executor context in which the query executes
   * @return `true` if execution of the query plan succeeds, `false` otherwise
   */
  bool Execute(const AbstractPlanNode *plan, std::vector<Tuple> *result_set, Transaction *txn,
               ExecutorContext *exec_ctx) {
    // Construct and executor for the plan
    auto executor = ExecutorFactory::CreateExecutor(exec_ctx, plan);

    // Prepare the root executor
    executor->Init();

    // Execute the query plan
    try {
      Tuple tuple;
      RID rid;
      while (executor->Next(&tuple, &rid)) {
        if (result_set != nullptr && executor->GetOutputSchema() != nullptr) {
          result_set->push_back(tuple);
        }
      }
    } catch (TransactionAbortException &e) {
      LOG_DEBUG("execute txn abort exception:%s", e.GetInfo().c_str());
      txn_mgr_->Abort(txn);
      return false;
    } catch (Exception &e) {
      LOG_DEBUG("execute exception!");
      txn_mgr_->Abort(txn);
      return false;
    }

    return true;
  }
```

###### 常用API

+ 获取一个表的oid：`oid = plan_->GetTableOid();`
+ 通过oid获取表：`auto table = exec_ctx_->GetCatalog()->GetTable(oid);`
+ 投影过程：

``` cpp
    for (auto &col : output_schma->GetColumns()) {
      values.emplace_back(col.GetExpr()->Evaluate(tuple, schema));
    }
```

+ 判断tuple是否满足过滤条件

``` cpp
    if (predicate != nullptr && !predicate->Evaluate(tuple, schema).GetAs<bool>()) {
      continue;
    }
```

+ 获取索引，更新索引

``` cpp
auto affect_indexes = exec_ctx_->GetCatalog()->GetTableIndexes(table->name_);

// Insert/Update index
for (const auto &table_index : affect_indexes) {
    table_index->index_->InsertEntry(
        row.KeyFromTuple(schema, *table_index->index_->GetKeySchema(), table_index->index_->GetKeyAttrs()), *rid, txn);
}

// delete index
for (const auto &table_index : affect_indexes) {
    txn->GetIndexWriteSet()->emplace_back(
        IndexWriteRecord(*rid, info->oid_, WType::DELETE, *tuple, table_index->index_oid_, exec_ctx_->GetCatalog()));
    table_index->index_->DeleteEntry(
        tuple->KeyFromTuple(info->schema_, *table_index->index_->GetKeySchema(), table_index->index_->GetKeyAttrs()),
        *rid, txn);
}
```

+ 修改表中的行

``` cpp
// 插入
table->table_->InsertTuple(row, rid, txn)

// 更新
table->table_->UpdateTuple(row, rid, txn)
    
// 删除
table->table_->MarkDelete(rid, txn)
```

##### 增删改查

###### SeqScanExecutor

+ Init：初始化表迭代器
+ Next：从表迭代器中拿出一行，知道该行满足过滤条件。

###### InsertExecutor

有两种方法获取插入的行，获得插入的行后。将其插入到表中，插入成功后插入索引。

+ 从原始数据插入
    + Init：初始化下标索引，`index_=0;`
    + Next：`std::vector<Value> raw_values = plan_->RawValuesAt(index_);`
+ 从其他Executor的返回结果插入
    + Init：`child_executor_->Init();`
    + Next：`child_executor_->Next(tuple, rid)`

###### UpdateExecutor

更新表信息，更新索引。

###### DeleteExecutor

标记删除，删除索引。

##### 连接算法

###### Nested Loop Join

Init：初始化左子节点和右子节点，并且获取左子节点的第一行。

Next：

+ 如果左子节点的行数据无效，返回false
+ 如果右子节点的行数据无效，获取左子节点的下一行，重新初始化右子节点。
+ 使用`predicate`判断这左右节点的两行数据是否满足连接条件。

``` cpp
    if (predicate != nullptr &&
        !predicate->EvaluateJoin(&left_tuple_, left_schema, &right_tuple, right_schema).GetAs<bool>()) {
      continue;
    }
```

+ 获取左右两行中的有效数据，构造一行新数据后返回true

``` cpp
    for (auto &col : schema->GetColumns()) {
      values.emplace_back(col.GetExpr()->EvaluateJoin(&left_tuple_, left_schema, &right_tuple, right_schema));
    }

    *tuple = Tuple(values, schema);
    found = true;
```

###### Hash Join

+ 哈希表的实现：只需要实现内存中的哈希表即可，是对`unordered_map`的封装。

`HashJoinKey`是一种数据库可表示的数据类型`Value`，`Value`由`uint64, uint32, uint8, uint32`组成，由于对其问题，一个`Value`占用24字节。

`HashJoinKey`需要定义其构造函数以及比较函数。

`HashJoinValue`表示相同的key的所有的行。

``` cpp
 protected:
  // The actual value item
  union Val {
    int8_t boolean_;
    int8_t tinyint_;
    int16_t smallint_;
    int32_t integer_;
    int64_t bigint_;
    double decimal_;
    uint64_t timestamp_;
    char *varlen_;
    const char *const_varlen_;
  } value_;

  union {
    uint32_t len_;
    TypeId elem_type_id_;
  } size_;

  bool manage_data_;
  // The data type
  TypeId type_id_;
```

``` cpp
namespace bustub {

/** AggregateKey represents a key in an aggregation operation */
struct HashJoinKey {
  Value key_;
  explicit HashJoinKey(const Value &key) : key_(key) {}
  /**
   * Compares two aggregate keys for equality.
   * @param other the other aggregate key to be compared with
   * @return `true` if both aggregate keys have equivalent group-by expressions, `false` otherwise
   */
  // 这里实现的是，所有相同的key。
  // 也可以通过下面实现相同的哈希值的key，与ppt中的相同，但是后面还需进行多余的比较key是否相同。
  bool operator==(const HashJoinKey &other) const { return key_.CompareEquals(other.key_) == CmpBool::CmpTrue; }
  // bool operator==(const HashJoinKey &other) const { return bustub::HashUtil::HashValue(&key_) == bustub::HashUtil::HashValue(&other.key_); }
};

/** HashJoinValue represents a value for each tuple of same key */
struct HashJoinValue {
  /** The tuple values */
  std::vector<Tuple> values_;
};
}  // namespace bustub
```

除此之外，还需要对通过模板函数`hash`的特化实现`HashJoinKey`的哈希函数。

``` cpp
namespace std {

/** Implements std::hash on AggregateKey */
template <>
struct hash<bustub::HashJoinKey> {
  std::size_t operator()(const bustub::HashJoinKey &hash_key) const {
    if (hash_key.key_.IsNull()) {
      return 0;
    }
    return bustub::HashUtil::HashValue(&hash_key.key_);
  }
};
```

最后实现`SimpleJoinHashTable`的插入和查找方法，相当于适配器模式。

``` cpp
/**
 * A simplified hash table that has all the necessary functionality for aggregations.
 */
class SimpleJoinHashTable {
 public:
  void Insert(const HashJoinKey &key, const Tuple &value) { ht_[key].values_.emplace_back(value); }
  HashJoinValue GetValues(const HashJoinKey &key) {
    if (ht_.count(key) != 0) {
      return ht_[key];
    }
    return HashJoinValue{};
  }

 private:
  std::unordered_map<HashJoinKey, HashJoinValue> ht_{};
};
```

+ 连接的实现
    + Build：通过`SimpleJoinHashTable`对左子节点进行哈希。
    + Probe：对右子节点的每一行进行哈希，然后将符合条件左子节点的行逐次返回。如果没有符合的哈希值，那么右子节点的该行无法与左子节点进行连接。

##### 聚集函数

###### GROUP HAVING 实现

+ 根据GROUP的表项建立哈希表`SimpleAggregationHashTable`，在初始化过程中便可以实现MAX，MIN，COUNT，SUM。并且初始化哈希表的迭代器`aht_iterator_`，对哈希表中的每个桶便实现了GROUP。
+ 之后通过迭代器遍历哈希表中的每一项，并且使用having进行判断。

``` cpp
    auto having = plan_->GetHaving();
    ++aht_iterator_;

    if (having != nullptr && !having->EvaluateAggregate(key.group_bys_, value.aggregates_).GetAs<bool>()) {
      continue;
    }
```

##### 其他

###### LIMIT

+ 计数即可。

###### DISTINCT

+ 实现类似的哈希表进行去重。

#### 参考博客

+ https://www.inlighting.org/archives/cmu-15-445-notes/
+ https://www.cnblogs.com/JayL-zxl/category/1919605.html
+ https://15445.courses.cs.cmu.edu/fall2021/
+ https://segmentfault.com/a/1190000015856311
+ https://www.jianshu.com/p/c4e4d55706ff
+ https://www.liaoxuefeng.com/wiki/1177760294764384/1179610888796448
+ https://www.inlighting.org/archives/database-query-processing

