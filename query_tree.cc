// Alfredo Morales
// Main file for Part2(a) of Homework 2.
//	I created a parser to read in this database and constructed an AVL tree.
//	For each line of the database	and for each recognition sequence in that line I created
//	a new SequenceMap object that contains the recognition sequence as its recognition_sequence_ 
//	and the enzyme acronym as the only string of its enzyme_acronyms_ and I inserted this object into the tree.	

#include "avl_tree.h"
#include "SequenceMap.h"

#include <iostream>
#include <fstream> 
#include <vector>
#include <sstream>
#include <string>
using namespace std;

namespace {
	// @db_filename: an input filename.
	// @a_tree: an input tree of the type TreeType. It is assumed to be
	//  empty.
	template <typename TreeType>
	void QueryTree(const string &db_filename, TreeType &a_tree) {

		ifstream newFile(db_filename);
		SequenceMap new_sequence_map; 
		string line, skipped_lines,acronym,rec_sequence;
  
   

		for(int i =0; i < 10;i++){				//skips the first ten lines of the text file
			getline(newFile,skipped_lines); 
		} 
		while(getline(newFile, line)){
			stringstream ss(line);
			getline(ss,acronym,'/');				// reads file and stops at the first /   

			while(getline(ss,rec_sequence,'/')){
				SequenceMap new_sequence_map(rec_sequence,acronym);
				a_tree.insert(new_sequence_map);			
			} 
		}
	}
}  // namespace

int main(int argc, char **argv) {			//Here is where I test all the parts of Part2(a).
  string sequence1,sequence2,sequence3;		//Three strings that are going to be searched for (input as well).
  if (argc != 2) {
    cout << "Usage: " << argv[0] << " <databasefilename>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  cout << "Input filename is " << db_filename << endl;
  
  AvlTree<SequenceMap> a_tree;
  QueryTree(db_filename, a_tree);

    cin >> sequence1;						// The user should enter THREE strings (supposed to be recognition sequences).
    cin >> sequence2;
    cin >> sequence3; 

    a_tree.locate(sequence1);				//locates the input and outputs the corresponding acronym
    a_tree.locate(sequence2);
    a_tree.locate(sequence3);

  return 0;
}
