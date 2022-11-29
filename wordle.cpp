// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <vector>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void helper(const std::string& in,
    std::string& floating,
    const std::set<std::string>& dict,
		std::set<std::string>& answer, std::string word, int num);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
		std::set<std::string> answer;
		std::string remain = "";
		for(int i = 0; i<int(floating.size()); i++) remain+=floating[i];
		int num = 0;
		//num is the number of the remaining unkown alphabets
		for(int i = 0; i<int(in.size()); i++)
		{
			if(in[i]=='-') num+=1;
		}
		helper(in, remain, dict, answer, "", num);
		return answer;
}

// Define any helper functions here
void helper(const std::string& in,
    std::string& floating,
    const std::set<std::string>& dict,
		std::set<std::string>& answer, std::string word, int num)
{
	int current = word.size();
	if(current==int(in.size()))
	{
		if(dict.find(word)!=dict.end() && floating.size()==0) answer.insert(word);
		return;
	}
	if(in[current]!='-')
	{
		helper(in, floating, dict, answer, word+in[current], num); return;
	}
	std::string atoz = "abcdefghijklmnopqrstuvwxyz";
	for(auto it = floating.begin(); it!=floating.end(); ++it)
	{
		char c = *it;
		floating.erase(it);
		helper(in, floating, dict, answer, word+ c, num-1);
		floating.insert(it, c);
		int f = atoz.find(c);
		//erase all floatings from atoz
		if(f!=atoz.npos)	atoz.erase(atoz.begin()+f);
	}
	//if the remaining places is equal to number of floatings, then only add floatings
	if(num-1<int(floating.size())) return;
	for(int i = 0; i<int(atoz.size()); i++) helper(in,floating, dict, answer, word+(atoz[i]), num-1);
}


