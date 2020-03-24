# 前言

秋招面阿里的时候被问到一个这样的问题：

> 平时你使用过map么？是并发安全的么？如何实现一个并发安全的map? 考虑过效率么？

相信大家平时使用最多的结构就是各种hash map了，无论哪种语言都有自身提供的实现，比如Java当中的HashMap,Golang当中的Sync.Map等等。在技术面试当中，对于hash Map实现的考察非常频繁。本文将从阿里的面试真题切入，结合相关代码简要的介绍几种实现并发安全的map的方法。

# 阿里面试真题再现：

### 1.普通的map是并发安全的么？

答：不是并发安全的，在并发访问的过程当中会出现竞争，导致数据不一致。

### 2.unordered_map 和 map的区别?

答：unordered_map是基于哈希实现的，查找和插入开销都是O(1)，而map是基于红黑树实现的，查找和插入的开销都是O(logn)。

### 3.如何实现一个并发安全的map?

答：1.封装读写锁实现；

​    2.分段锁实现；

​    3.读写分离实现；

解析：

#### **方法1**：通过将读写锁和非并发安全的map封装在一起，实现一个并发安全的map结构。

如下面go语言的一个简单的实现，将一个并发不安全的map和一个读写锁结合，对于读写操作的接口进行封装。

```go
type MyMap struct {
    sync.RWMutex
    mp map[interface{}]interface{}
  ...
}

func (m *MyMap) Read(key interface{}) interface{} {
    m.RLock()
    value := m.mp[key]
    m.RUnlock()
    return value
}

func (m *MyMap) Write(key, value interface{}) {
    m.Lock()
    m.mp[key] = value
    m.Unlock()
}
```

优势：

1. 实现简单，几行代码就可以实现。
2. 并发量很小，或者竞争使用map的情况较少时对性能的影响并不大。

缺点：

锁的粒度太大。举例来说，线程A调用Write方法写key1的时候锁住了map，此时线程B调用Read方法，读取和key1不相关的key2时就会被阻塞。当并发量增大时，该方案带来的线程阻塞等待的开销会很大，在高并发情况下就需要进行优化。

#### **方法2：** **锁分段技术**

  相比方法1使用全局锁的方式，锁分段技术将数据分段存储，给每一段数据配一把锁。实现思路：当线程需要读取map当中某个key的时候，线程不会对整个map进行加锁操作，而是先通过hash取模来找到该key存放在哪一个分段中，然后对这个分段进行加锁，因为每一段数据使用不同的锁，所以对该分段加锁不会阻塞其他分段的读写。分段锁的设计目的是细化锁的粒度，减少线程间锁竞争的次数，从而可以有效的提高并发访问效率。

举例来说，分段锁实现的map的主要逻辑如下：

```go
type MyConcurrentMap []*Shard

// 分片Shard
type Shard struct {
    items map[string]interface{}
    mu sync.RWMutex    
}

//根据给定的key获取其对应的段
func (m MyConcurrentMap) GetShard(key string) *Shared {
    h := hash(key) //对key求hash code
    return m[h%SHARD_COUNT]//SHARD_COUNT为预设的Shard的个数

}

//Set方法
func (m MyConcurrentMap) Set(key string, value interface{}) {
    shard := m.GetShard(key) 
    shard.mu.Lock()              
    shard.items[key] = value 
    shard.Unlock()              
}

//Get方法
func (m MyConcurrentMap) Get(key string) (interface{}, bool) {
    shard := m.GetShard(key)
    shard.mu.RLock()
    val, ok := shard.items[key]
    shard.mu.RUnlock()
    return val, ok
}
```

优势：

相比方法1，并发访问效率有很大提升。

缺点：

对于map扩缩容时比较麻烦，因为shard的个数需要预先设定。

#### **方法3**：**读写分离+原子操作**

sync.Map是Golang1.9引入的并发安全的map，以下代码节选自sync.Map的实现：

```go
//sync.Map的实现
type Map struct {
    mu Mutex
    read atomic.Value // readOnly 
    dirty map[interface{}]*entry 
    misses int
}
```

上述结构当中，read 只提供读，dirty 负责写。read 主要用于实现无锁操作，而 dirty 的操作是由 Mutex来保护。简单来说就是，当从map当中读取数据时会先从read当中读取数据，如果read当中可以获取该数据则无锁读取，当无法从read当中读取到时则从dirty当中加锁读取。该方案也是为了减少加锁操作，提升并发访问的效率，具体的实现可以看sync.Map的源码，这里篇幅有限不再赘述。

优势：

1. 通过冗余的两个数据结构(read、dirty),减少频繁加锁对性能的影响。**典型的空间换时间的做法。**
2. 将锁的粒度更加的细小到数据的状态上，减少锁操作。
3. 更好的拓展性，没有分段锁在扩缩容时的烦恼。

缺点：

sync.Map的实现方式并不适用于大量写出现的场景，原因：

- 大量的写会导致read当中读取不到数据，从而加锁读dirty，性能退化。
- 大量写会导致read的miss不断提升，**导致dirty不断提升为read，导致性能下降
  **

###  

### 4.如何考虑并发读写map的效率？

答：具体的场景需要具体分析，一般来说需要先分析对于map的使用场景，是读多写少还是更新多但是创建少，可以对不同的场景进行特殊的优化。一般常用的技巧就是减小锁的粒度，使用无锁操作代替加锁的方式，使用读写分离的方式等等。