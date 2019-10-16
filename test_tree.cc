// Alfredo Morales
// Main file for Part2(b) of Homework 2.


#include "avl_tree.h"
#include "SequenceMap.h"

#include <fstream> 
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;

namespace {

	// @db_filename: an input database filename.
	// @seq_filename: an input sequences filename.
	// @a_tree: an input tree of the type TreeType. It is assumed to be
	//  empty.
	template <typename TreeType>
	void TestTree(const string& db_filename, const string& seq_filename, TreeType& a_tree) {	//Same concept as queryTree to create new tree out of the file

		ifstream inFile(db_filename);
		SequenceMap new_sequence_map;
		string db_line, skipped_lines, acro, rec_seq;
		for (int i = 0; i < 10; i++) {
			getline(inFile, skipped_lines); //skips the first 10 lines
		}
		while (getline(inFile, db_line)) {
			stringstream ss(db_line);
			getline(ss, acro, '/'); //reads file and stops at the first '/'

			while (getline(ss, rec_seq, '/')) {
				if (rec_seq.length() > 0) {
					SequenceMap new_sequence_map(rec_seq, acro);
					a_tree.insert(new_sequence_map);
				}
			}
		}
	}
	
	template <typename TreeType>
	void averageRecCalls(const string& db_filename, const string& seq_filename, TreeType& a_tree) {
		float averageOfRecCalls = 0;
		int counter = 0, recur_count = 0, recur_calls;
		string line;
		ifstream new_file(seq_filename);
		while (getline(new_file, line)) {
			counter++;
			if (a_tree.find(line, recur_calls)) {
				recur_count++;
			}
			recur_count += recur_calls;
		}
		averageOfRecCalls = (float)recur_count / counter;		
		cout << counter << endl;							// Prints the total number of successful queries (number of strings found)
		cout << averageOfRecCalls << endl;					// Prints the average number of recursion calls, i.e. #total number of recursion calls / number of queries.
	}

	template <typename TreeType>
	void removeEveryOther(const string& seq_filename, TreeType& a_tree) {		
		string line;
		ifstream my_file(seq_filename);
		int no_of_strings = 0, total_lines = 0, remover_lines = 0;
		while (getline(my_file, line)) {
			total_lines++;
			if (remover_lines % 2 == 0) {			//To make sure you're removing every other string
				SequenceMap new_seq_map(line, "");
				if (a_tree.contains(new_seq_map)) {	//check if the Sequence Map is in there
					a_tree.remove(new_seq_map);		//remove sequencemap
					if (!a_tree.contains(new_seq_map)) {
						no_of_strings++;
					}
				}
			}
			remover_lines++;
		}
		cout << no_of_strings << endl;		//Prints number of removed strings
	}

	template <typename TreeType>
	void avgRecurCalls(const string& seq_filename, TreeType& a_tree) {

		string line;
		ifstream my_file(seq_filename);
		int every_other = 0, delete_count = 0, recursion_calls = 0, sum_of_recursion_calls = 0;
		int total_calls = 0;
		while (getline(my_file, line)) {
			
			if (every_other % 2 == 0) {
				total_calls++;
				if (a_tree.sequence_remover(line, recursion_calls)) {
					delete_count++;
				}
					sum_of_recursion_calls += recursion_calls;			
			}
			every_other++;
		}	
		float avg_recursion_calls = (float)sum_of_recursion_calls / total_calls;
		cout << avg_recursion_calls << endl;

		int new_total = a_tree.nodeCount();
		cout << new_total << endl;
		float new_depth = a_tree.average_depth();
		cout << new_depth << endl;
		float new_ratio = a_tree.ratioOfDepth();
		cout << new_ratio << endl;
	}
}  // namespace

int
main(int argc, char **argv) {	//Here is where I test all the parts of Part(b).
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string seq_filename(argv[2]);
  cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
  
  AvlTree<SequenceMap> a_tree;
  TestTree(db_filename, seq_filename, a_tree);

  cout << a_tree.nodeCount() << endl;		// Prints the number of nodes in my tree 𝑛.

  cout << a_tree.average_depth() << endl;	// Prints the average depth
  cout << a_tree.ratioOfDepth() << endl;	// Prints the ratio of the average depth to log2(n).

  averageRecCalls(db_filename, seq_filename, a_tree); // Prints	the	total number of successful queries (number of strings found)
													  // Also prints the average number of recursion calls, i.e. #total number of recursion calls / number of queries.
  removeEveryOther(seq_filename, a_tree);	// Removes every other sequence in sequences.txt from the tree and counts the total number of recursion calls for all executions of remove().

  avgRecurCalls(seq_filename, a_tree);		// Prints the average number of recursion calls, total number of recursion calls / number of remove calls.	
											// a. Prints number of nodes in your tree. 
											// b. Prints the average depth.	
											//c. Prints	the	ratio of the average depth to log2(𝑛).	

  return 0;
}