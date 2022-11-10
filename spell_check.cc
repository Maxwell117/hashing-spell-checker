//Maxwell Large
#include "quadratic_probing.h"
#include "linear_probing.h"
#include "double_hashing.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
using namespace std;
// SpellCheck document1_short.txt wordsEn.txt
//passes any hash table,dictionary and spelled/mispelled words
//prints correct/incorrect and corrections
template <typename HashTableType>
void spellcheck(HashTableType &hash_table, const string &document_filename, const string &dictionary_filename)
{
 
//   cout << "TestFunctionForHashTables..." << endl;
//   cout << "Document filename: " << document_filename << endl;
//   cout << "Dictionary filename: " << dictionary_filename << endl;

   hash_table.MakeEmpty();
   hash_table.Reset_Collisions();
   
// code to get each word from the your words file;
  ifstream document_file;
  document_file.open(document_filename.c_str());
  if(document_file.fail())
  {
  cerr << "Error opening document file\n";
  }
  
//code to get the word from dictionary file
  ifstream dictionary_file;
  dictionary_file.open(dictionary_filename.c_str());
  if (dictionary_file.fail())
  {
  cerr << "Error opening dictionary file\n";
  }
  
  
  string line;
  // store dictionary
//code to insert the dictionary into hashtable
  while(dictionary_file.good())
  {
  getline(dictionary_file, line);
  hash_table.Insert(line);
  }
  
  //read in document and clean up input
  while(document_file >> line) 
  {
    char letter = ' ';
    string word = "";
    
    //clean input from file to be user friendly
    for (int i=0;i<line.length();i++) 
  	{
         letter=tolower(line[i]);
         word+=letter;
    }
    int len = word.length();
    int start = 0;
    while(start < len && !isalnum(word[start])) {//alpha and numeric
        start++;//catch beginning 
    }
    int end = len - 1;
    while(end >= 0 && !isalnum(word[end])) {
        end--;//catch ending
    }
    if (end < start) {
        continue; //repeart
    }
    word = word.substr(start, end-start+1);
    
    if(hash_table.Contains(word)) //a while would work too
    {
    cout<<word<<" is CORRECT"<<endl;
    continue;//go back up incase more correct words are found
    }
    else
    { 
    cout<<word<<" is INCORRECT"<<endl;
    }
    
    
    
    
    
    
    
    
    
    // END get each word
    // check word, 3 cases
   string correctword=word;
// 1) add one char in each possible position
       	for(int i=0;i<word.length()+1;i++)
         {
         // insert a - z
            for (char c='a';c<='z';c++) 
            {
                correctword=word;		 // reset
                correctword.insert(i,1,c);
                if(hash_table.Contains(correctword)) 
                {
                cout<<"** "<<word<<" -> "<<correctword<<" ** "<<"case A"<<endl;
                }
            }
         }
       correctword=word;
    // 2) remove one character from the word
       for(int i=0;i<word.length();i++) 
       {
            correctword=word;//reset
            // begins at the character position pos and spans len characters
            correctword.erase(i,1);
            if(hash_table.Contains(correctword)) 
            {
            cout<<"** "<<word<<" -> "<<correctword<<" ** "<<"case B"<<endl;
            }
            
       }
       // 3) Swap adjacent characters in the word
       for(int i=0;i<word.length()-1;i++) 
       {
             correctword=word;// reset
            // begins at the character position pos and spans len characters
            swap(correctword[i],correctword[i+1]);
            if(hash_table.Contains(correctword))
 	         {
            cout<<"** "<<word<<" -> "<<correctword<<" ** "<<"case C"<<endl;
            }

       }
  }		 // end while line
  // END check each word in document

document_file.clear();	//safety handling files	
document_file.close();
dictionary_file.clear();
dictionary_file.close();
}
//////////////////////////////////////////////////////////////
//template <typename HashTableType>
int testSpellingWrapper(int argument_count, char** argument_list) 
{

  const string document_filename(argument_list[1]);
  const string dictionary_filename(argument_list[2]);
  //spellcheck(,)
  HashTableDouble<string> hash_table;
  // Call functions implementing the assignment requirements.
  spellcheck(hash_table,document_filename,dictionary_filename);
  return 0;
}
// Sample main for program spell_check
//int main(int argc, char **argv) {
int main(int argc, char **argv) 
{
  if (argc!=4)
   {
    cout << "Usage: " << argv[0] << " <document-file> <dictionary-file> <flag>" << endl;
    return 0;
  }
  
 //  const string document_filename(argv[1]);
//   const string dictionary_filename(argv[2]);
//   
//   cout << "Input document filename is " << document_filename << endl;
//   cout << "Input dictionary filename is " << dictionary_filename << endl;

  // Call functions implementing the assignment requirements.
  testSpellingWrapper(argc,argv);
  return 0;
}