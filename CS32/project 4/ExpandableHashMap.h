// ExpandableHashMap.h

// Skeleton for the ExpandableHashMap class template.  You must implement the first six
// member functions.
#include <vector>
using namespace std;

template<typename KeyType, typename ValueType>
class ExpandableHashMap
{
public:
    ExpandableHashMap(double maximumLoadFactor = 0.5);
    ~ExpandableHashMap();
    void reset();
    int size() const;
    void associate(const KeyType& key, const ValueType& value);

      // for a map that can't be modified, return a pointer to const ValueType
    const ValueType* find(const KeyType& key) const;

      // for a modifiable map, return a pointer to modifiable ValueType
    ValueType* find(const KeyType& key)
    {
        return const_cast<ValueType*>(const_cast<const ExpandableHashMap*>(this)->find(key));
    }

      // C++11 syntax for preventing copying and assignment
    ExpandableHashMap(const ExpandableHashMap&) = delete;
    ExpandableHashMap& operator=(const ExpandableHashMap&) = delete;

private:
    struct Bucket{
        KeyType key;
        ValueType val;
    };
    double m_maxLoad;
    vector<Bucket>* m_hash;
    int m_size;
    int m_count;
};

template<typename KeyType, typename ValueType>
ExpandableHashMap<KeyType, ValueType>::ExpandableHashMap(double maximumLoadFactor)
{
    m_maxLoad = maximumLoadFactor;
    m_size = 8;
    m_hash = new vector<Bucket>[m_size];
    m_count = 0;
}
template<typename KeyType, typename ValueType>
ExpandableHashMap<KeyType, ValueType>::~ExpandableHashMap()
{
    delete[] m_hash;
}
template<typename KeyType, typename ValueType>
void ExpandableHashMap<KeyType, ValueType>::reset()
{
    delete[] m_hash;
    m_size = 8;
    m_hash = new vector<Bucket>[m_size];
    m_count = 0;
}
template<typename KeyType, typename ValueType>
int ExpandableHashMap<KeyType, ValueType>::size() const
{
    return m_count;  // Delete this line and implement this function correctly
}

template<typename KeyType, typename ValueType>
void ExpandableHashMap<KeyType, ValueType>::associate(const KeyType& key, const ValueType& value)
{
    unsigned int hasher(const KeyType& k); // prototype
    //update
    int bucket = hasher(key)%m_size;
    for(int i = 0; i < m_hash[bucket].size(); i++){
        if(m_hash[bucket][i].key == key){
            m_hash[bucket][i].val = value;
            return;
        }
    }
    //or add
    Bucket b;
    b.key = key;
    b.val = (value);
    m_hash[bucket].push_back(b);
    m_count++;
    //check if over maxLoad
    if(m_count*1.0/m_size > m_maxLoad){
        //reassign everything
        m_size*=2;
        vector<Bucket>* temp = new vector<Bucket>[m_size];
        for(int i = 0; i< m_size/2; i++){
            vector<Bucket> v = m_hash[i];
            for(int j = 0; j < v.size(); j++){
                Bucket b;
                b.key = v[j].key;
                b.val = v[j].val;
                int newBucket = hasher(b.key)%m_size;
                temp[newBucket].push_back(b);
            }
        }
        delete [] m_hash;
        m_hash = temp;
    }
}

template<typename KeyType, typename ValueType>
const ValueType* ExpandableHashMap<KeyType, ValueType>::find(const KeyType& key) const
{
    unsigned int bucket = hasher(key)%m_size;
    if(m_hash[bucket].empty()){
        return nullptr;
    }
    for(int i = 0; i < m_hash[bucket].size(); i++){
        if(m_hash[bucket][i].key == key){
            return &m_hash[bucket][i].val;
        }
    }
    return nullptr;
}

