#ifndef MYHASH_INCLUDED
#define MYHASH_INCLUDED


template<typename KeyType, typename ValueType>
class MyHash
{
public:
    MyHash(double maxLoadFactor=0.5);
    ~MyHash();
    void reset();
    void associate(const KeyType& key, const ValueType& value);
    const ValueType* find(const KeyType& key) const;
    ValueType* find(const KeyType& key)
    {
        return const_cast<ValueType*>(const_cast<const MyHash*>(this)->find(key));
    }
    
    int getNumItems() const;
    double getLoadFactor() const;
    
    // C++11 syntax for preventing copying and assignment
    MyHash(const MyHash<KeyType, ValueType>&) = delete;
    MyHash<KeyType, ValueType>& operator=(const MyHash<KeyType, ValueType>&) = delete;
    
    
    
private:
    unsigned int bucketNumber(const KeyType& key) const;
    void doubleSize();
    void insert(const KeyType& key, const ValueType& value);
    
    struct Bucket
    {
        KeyType m_key;
        ValueType m_value;
        Bucket* m_next;
    };
    
    Bucket** chart;
    double m_loadfactor;
    int m_numBuckets;
    int m_nItem;
};







template<typename KeyType, typename ValueType>
inline
MyHash<KeyType, ValueType>::MyHash(double maxLoadFactor)
:m_numBuckets(100), m_nItem(0)
{
    if(maxLoadFactor <= 0.0)
    {
        m_loadfactor = 0.5;
    }
    
    else if(maxLoadFactor > 2.0)
    {
        m_loadfactor = 2.0;
    }
    
    else
    {
        m_loadfactor = maxLoadFactor;
    }
    
    chart = new Bucket* [m_numBuckets];
    
    for(int i = 0; i < m_numBuckets; i++)
    {
        chart[i] = nullptr;
    }
}



template<typename KeyType, typename ValueType>
inline
MyHash<KeyType, ValueType>::~MyHash()
{
    
    for(int i = 0; i < m_numBuckets; i++)
    {
        if(chart != nullptr)
        {
            Bucket* currBucket = chart[i];
            while(currBucket != nullptr)
            {
                chart[i] = currBucket->m_next;
                
                delete currBucket;
                currBucket = nullptr;
                currBucket = chart[i];
            }
        }
        delete[] chart;
        
        chart = nullptr;
    }
}



template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::reset()
{
    if(chart == nullptr)
    {
        return;
    }
    
    //only afd if you want to destruct
    
    //
    for (int i=0; i < m_numBuckets; i++)
    {
        if (chart[i] != nullptr)
        {
            Bucket* currBucket = chart[i];
            while(currBucket != nullptr)
            {
                chart[i] = currBucket->m_next;
                delete currBucket;
                currBucket = chart[i];
            }
        }
    }
    
    
    delete [] chart;
    
    
    
    // possibly construction maybe
    m_numBuckets = 100;
    
    m_nItem = 0;
    chart = new Bucket* [m_numBuckets];
    for (int i = 0; i < m_numBuckets; i++)
    {
        chart[i] = nullptr;
    }
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::associate(const KeyType& key, const ValueType& value)
{
    ValueType* vptr = find(key);
    if(vptr != nullptr)
    {
        *vptr = value;
    }
    
    else
    {
        insert(key, value);
    }

    if((double)m_nItem/(double)m_numBuckets >= m_loadfactor)
    {
        doubleSize();
    }
}

template<typename KeyType, typename ValueType>
int MyHash<KeyType, ValueType>::getNumItems() const
{
    return m_nItem;
}

template<typename KeyType, typename ValueType>
double MyHash<KeyType, ValueType>::getLoadFactor() const
{
    double stuff=(double)m_nItem/(double)m_numBuckets;
    
    return stuff;
}


template<typename KeyType, typename ValueType>
unsigned int MyHash<KeyType, ValueType>::bucketNumber(const KeyType& key) const
{
    unsigned int hash(const KeyType& k);
    //need to include this shit bc spec says to do so
    
    unsigned int h = hash(key);
    
    return (h % m_numBuckets);
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::doubleSize()
{
    // create a new hash table
    
    int prev_numBuckets = m_numBuckets;
    
    m_numBuckets = m_numBuckets * 2;
    
    Bucket** oldChart = chart;
    
    chart = new Bucket*[m_numBuckets];
    
    m_nItem = 0;
    
    for(int i = 0; i < m_numBuckets; i++)
    {
        chart[i] = nullptr;
    }
    
    // delete an old hash table
    for(int i = 0; i < prev_numBuckets; i++)
    {
        if(oldChart[i] != nullptr)
        {
            Bucket* prevBucket;
            Bucket* currBucket = oldChart[i];
            while(currBucket != nullptr)
            {
                // move all of the items from the old array to the new array
                insert(currBucket->m_key, currBucket->m_value);
                prevBucket = currBucket;
                currBucket = currBucket->m_next;
                delete prevBucket;
            }
        }
    }
    
    delete[] oldChart;
}

template<typename KeyType, typename ValueType>
inline
void MyHash<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value)
{
    // get the bucket number of where to insert
    unsigned int idx = bucketNumber(key);
    Bucket* newBucket = new Bucket;
    newBucket->m_key = key;
    newBucket->m_value = value;
    newBucket->m_next = nullptr;
    if (chart[idx] == nullptr)
    {
        chart[idx] = newBucket;
        m_nItem++;
    }
    
    else
    {
        m_nItem++;
        Bucket* currBucket = chart[idx];
        newBucket->m_next = currBucket;
        chart[idx] = newBucket;
    }
}

template<typename KeyType, typename ValueType>
const ValueType* MyHash<KeyType, ValueType>::find(const KeyType& key) const
{
    unsigned int idx = bucketNumber(key);
    Bucket* currBucket = chart[idx];
    while (currBucket != nullptr)
    {
        if (currBucket->m_key == key)
        {
            ValueType* value = &(currBucket->m_value);
            if(value != nullptr)
                return value;
        }
        currBucket = currBucket->m_next;
    }
    return nullptr;
}

#endif // MYHASH_INCLUDED
