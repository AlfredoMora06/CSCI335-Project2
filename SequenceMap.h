//Alfredo Morales
#pragma once

#ifndef SEQUENCE_MAP_H
#define SEQUENCE_MAP_H

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class SequenceMap
{
	public:
	//big 5
		SequenceMap() = default;
		~SequenceMap() = default;
		SequenceMap(const SequenceMap& rhs) = default; //copy-constructor
		SequenceMap(SequenceMap&& rhs) = default; //move constructor
		SequenceMap& operator=(SequenceMap&& rhs) = default; // move - assignment
		SequenceMap& operator=(const SequenceMap& rhs) = default; //copy - assignment
		//end of big 5
		
		/*	This constructs	a SequenceMap from two strings (note that now the vector enzyme_acronyms_	
			will contain just one element, the an_enz_acro).
		*/
		SequenceMap(const string& a_rec_seq, const string& an_enz_acro):
			recognition_sequence_(a_rec_seq), enzyme_acronyms_{an_enz_acro} {}


		/*	Operates based on the regular string comparison between the 
			recognition_sequence_ strings (this will be a one line function).
		*/
		string get_sequence() const{
			return recognition_sequence_;
		}

		void list_acronyms() {
			for (unsigned int i = 0; i < enzyme_acronyms_.size(); i++) {
				cout << enzyme_acronyms_[i] << " ";
			}
			cout << endl;
		}
		/*	Operates based on the regular string comparison	
			between	the	recognition_sequence_ strings 
		*/
		bool operator < (const SequenceMap& rhs) const{
			return recognition_sequence_ < rhs.recognition_sequence_;
		}

		/*	The	function Merge() merges	the	
			other_sequence.enzyme_acronym_ with the	object’s enzyme_acronym_.
		*/
		void Merge(const SequenceMap& other_sequence) {
			for (unsigned int i = 0; i < other_sequence.enzyme_acronyms_.size(); i++) {
				enzyme_acronyms_.push_back(other_sequence.enzyme_acronyms_[i]);
			}
		}

		//overloading << operator
		friend std::ostream& operator<<(std::ostream& out, const SequenceMap& a_map) {
			out << a_map.recognition_sequence_ << " ";
			for (unsigned int i = 0; i < a_map.enzyme_acronyms_.size(); i++) {
				out << a_map.enzyme_acronyms_[i] << " ";
			}
			out << endl;

			return out;
		}

	private:
		string recognition_sequence_;
		vector<string>	enzyme_acronyms_;

};
#endif
