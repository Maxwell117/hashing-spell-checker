//Maxwell Large
#ifndef DOUBLE_PROBING_H
#define DOUBLE_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <string>

//namespace
//{




//}  // namespace

 

// Quadratic probing implementation.
template <typename HashedObj>
class HashTableDouble {
private:
 int r_val;
 mutable int probes;//counts probes 
 mutable int collision_counter;//counts collisions or use static 
 ///bool flag;
 public:
  enum EntryType {ACTIVE, EMPTY, DELETED};
  //passes r value via command line and starts everything at 0
  explicit HashTableDouble(size_t size = 101,int r=7) : array_(NextPrime(size))
  { 
  r_val=r;
  current_size_=0;
  MakeEmpty(); 
  //flag=false;
  collision_counter=0;
  }
  
  //tweaked to add collesion counter
  bool Contains(const HashedObj & x) const
  {
  ++collision_counter;//cell/index is occupied
  return IsActive(FindPos(x));
  }
  
 //bool getflag()
//   {
//   return flag;
//   }
  
  
  //unchanged
  void MakeEmpty() {
    current_size_ = 0;
    for (auto &entry : array_)
      entry.info_ = EMPTY;
  }
  
  //unchanged
  bool Insert(const HashedObj & x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;

    //++collision_counter;
    array_[current_pos].element_ = x;
    array_[current_pos].info_ = ACTIVE;
    
    // Rehash; see Section 5.5
    if(++current_size_ > array_.size() / 2)
    {
    Rehash();    
    return true;
    }
  }
  
  //unchanged
  bool Insert(HashedObj && x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;
      
    //++collision_counter;
    array_[current_pos] = std::move(x);
    array_[current_pos].info_ = ACTIVE;

    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
    {
    Rehash();
    return true;
    }
  }
  
  //unchanged
  bool Remove(const HashedObj & x) {
    size_t current_pos = FindPos(x);
    if (!IsActive(current_pos))
      return false;

    array_[current_pos].info_ = DELETED;
    return true;
  }
  
   ////modifed components are below this line
/////////////////////////////////////////////////////////////
   public:
  //passes nothing
  //returns # of elements in table 
  size_t GetNumOfElements()
  {
  return current_size_;
  }
  //passes nothing
  //returns size of hash table(vector size)
  size_t GetVectorSize()
  {
  return array_.size();
  }
  
  // std::string PrintMessage()
//   {
//   return "I will run the double Hashing code";
//   }
  
  void Reset_Collisions()//probably not needed but better safe than sorry
  { 
  collision_counter=0; 
  }
  
  
 //  int Get_R_val()
//   {
//   return r_val;
//   }
  
  //passes nothing
  //returns # of collisions(element tried landing in a filled cell)
  int CollisionCount()
  {
  return collision_counter;
  }
  
  //passes hashobject(template) by const reference
  //returns # of probes(visited cells until an empty cell)
  //  int GetProbes(const HashedObj & x)
//    {
//    //int probes = 0;
//    //FindPos(x, probes);
//    return probes;
//    }

 private:        
  struct HashEntry {
    HashedObj element_;
    EntryType info_;
    
    HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY)
    :element_{e}, info_{i} { }
    
    HashEntry(HashedObj && e, EntryType i = EMPTY)
    :element_{std::move(e)}, info_{ i } {}
  };
    

  std::vector<HashEntry> array_;
  size_t current_size_;
 //modified to handle double hash
 size_t FindPos(const HashedObj & x) const
 {
    size_t offset = SecondHash(x);//2nd hash
    size_t current_pos = InternalHash(x);//1st hash
    while (array_[current_pos].info_ != EMPTY &&
	   array_[current_pos].element_ != x) {
  collision_counter++;//cell occupied means collesion
  current_pos += offset; //add by offset
  if (current_pos >= array_.size())
  current_pos -= array_.size();
    }
    return current_pos;
  }

  //modifed to expand 2x
  void Rehash() 
  {
    std::vector<HashEntry> old_array(current_size_);//pass old size
    std::copy_if(array_.begin(),array_.end(),old_array.begin(),[](const HashEntry& dummy) { return dummy.info_ == EntryType::ACTIVE; });
    //had to look up for something a command http://www.cplusplus.com/reference/algorithm/copy_if/
    int limit=array_.size();
    array_.clear();//start fresh 
    array_.resize(NextPrime(2*limit));//youtube said resize should be 2x 
        
    // Copy table over.
    current_size_ = 0;
    for (auto & entry :old_array)
     //if (entry.info_ == ACTIVE) might be overcomplicating things
	Insert(std::move(entry.element_));
  }
  
  size_t InternalHash(const HashedObj & x) const 
  {
    static std::hash<HashedObj> hf;
    return hf(x) % array_.size( );
  }
  //passes hashobject(template) and offset/i/j
  //returns x mod R
  size_t SecondHash(const HashedObj & x) const 
  {
    static std::hash<HashedObj> hf;
    return (r_val - ( hf(x) )  % r_val) % array_.size();
   //return r_val - current_pos % r_val;//R is 7, R must be prime<table.size()
  }
   
  // Internal method to test if a positive number is prime.
bool IsPrime(size_t n) //maybe make this friend so other classes can use? im trying to avoid to redefintion errors from having it in every prob/hash class
{ 
  if( n == 2 || n == 3 )
    return true;
  
  if( n == 1 || n % 2 == 0 )
    return false;
  
  for( int i = 3; i * i <= n; i += 2 )
    if( n % i == 0 )
      return false;
  
  return true;
}

// Internal method to return a prime number at least as large as n.
int NextPrime(size_t n) 
{
  if (n % 2 == 0)
    ++n;  
  while (!IsPrime(n)) n += 2;  
  return n;
}

//helper functions for Enums, might not used
////////////////////////////////////////////////
bool IsActive(size_t current_pos) const
{
return array_[current_pos].info_ == EntryType::ACTIVE; 
}
bool IsEmpty(size_t current_pos) const 
{ 
return array_[current_pos].info_ == EntryType::EMPTY; 
}
bool IsMatch(size_t current_pos, const HashedObj& x) const 
{ 
return array_[current_pos].element_ == x; 
}
 
  
  
};

#endif  // DOUBLE_PROBING_H