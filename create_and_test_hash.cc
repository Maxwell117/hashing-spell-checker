//Maxwell Large
#include <iostream>
#include <fstream>
#include "quadratic_probing.h"
#include "linear_probing.h"
#include "double_hashing.h"
#include <typeinfo>
#include <string>
using namespace std;

//passes hashtable template and 2 files
template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename)
{
 // cout<<"Input words file is words.txt, and query file is query_words.txt"<<endl;
 // cout<<hash_table.PrintMessage()<<endl;
 // cout << "TestFunctionForHashTables..." << endl;
  //cout << "Words filename: " << words_filename << endl;
  //cout << "Query filename: " << query_filename << endl;
  hash_table.MakeEmpty();  
  //..Insert your own code
  std::ifstream infile;
  infile.open(words_filename);//open file
  string ignore;
  string line;
  


     //insert first file to table
     while(infile>>line)
     {
     hash_table.Insert(line);
     //hash_table.GetNumOfElements();
     }
   
     


  //gets values from functions
  int N=hash_table.GetNumOfElements();
  int T=hash_table.GetVectorSize();
  float load_factor=float(N)/T;
  
  //add the following two lines also;
  
  //cout<<"Statistics for this Hash Table: "<<endl;
  cout<<"number_of_elements: "<<N<<endl;
  cout<<"size_of_table: "<<T<<endl;
  cout<< "load_factor: "<<(float)(N)/T<< endl;//casting
  cout<< "collisions: "<<hash_table.CollisionCount()<< endl;
  int C=hash_table.CollisionCount();
  float avg_collisons=(float)(C)/N;
  cout<< "avg_collisions: "<<(float)avg_collisons<< endl;
  
  cout<<" "<<endl;  
  string line2;
  std::ifstream infile2;
  infile2.open(query_filename);
  
  //reads in 2nd file and prints found or not 
  while(infile2>>line2)
  {
    cout<<line2<<" ";
    hash_table.Reset_Collisions();//seems odd but this is considered probing
    if(!hash_table.Contains(line2))
    { 
    cout<<"Not_";
    }
    cout<<"Found "<<hash_table.CollisionCount()<<endl;//print probes
   }
}
//dont touch under the /// or gradescope will .....
////////////////////////////////////////////////////////////////////////////////
int testFunctionWrapper(int argument_count, char **argument_list)
{
const string words_filename(argument_list[1]);
const string query_filename(argument_list[2]);
const string param_flag(argument_list[3]);

  if (param_flag == "linear") {
    HashTableLinear<string> linear_probing_table;
    TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);    
  } else if (param_flag == "quadratic") {
    HashTable<string> quadratic_probing_table;
    TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);    
  } else if (param_flag == "double") {
    // read R from argument_list[4]
    int r_val  = atoi(argument_list[4]); 
    cout << "r_value: " << r_val << endl;
    HashTableDouble<string> double_probing_table {101,r_val};
    TestFunctionForHashTable(double_probing_table, words_filename, query_filename);    
  } else {
    cout << "Unknown tree type " << param_flag << " (User should provide linear, quadratic, or double)" << endl;
  }
  return 0;
}


// Sample main for program create_and_test_hash.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE MAIN.
// WE WILL DIRECTLY CALL testFunctionWrapper. ALL FUNCTIONALITY SHOULD BE THERE.
// This main is only here for your own testing purposes.
int main(int argc, char **argv) {

  if (argc == 4) {
    cout << "Usage: " << argv[0] << " <wordsfilename> <queryfilename> <flag>" << endl;
    return 0;
  }
  
  testFunctionWrapper(argc, argv);
  return 0;
}
