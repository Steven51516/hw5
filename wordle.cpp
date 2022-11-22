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


// // Add prototypes of helper functions here
// void helper(const std::string& in,
//     std::vector<char>& floating,
//     const std::set<std::string>& dict,
// 		std::set<std::string>& answer, std::string word);

// // Definition of primary wordle function
// std::set<std::string> wordle(
//     const std::string& in,
//     const std::string& floating,
//     const std::set<std::string>& dict)
// {
//     // Add your code here
// 		std::set<std::string> answer;
// 		std::vector<char> remain;
// 		for(int i = 0; i<int(floating.size()); i++) remain.push_back(floating[i]);
// 		helper(in, remain, dict, answer, "");
// 		return answer;
// }

// // Define any helper functions here
// void helper(const std::string& in,
//     std::vector<char>& floating,
//     const std::set<std::string>& dict,
// 		std::set<std::string>& answer, std::string word)
// {
// 	int current = word.size();
// 	if(current==int(in.size()))
// 	{
// 		if(dict.find(word)!=dict.end() && floating.size()==0) answer.insert(word);
// 		return;
// 	}
// 	int num = 0;
// 	for(int i = current; i<int(in.size()); i++)
// 	{
// 		if(in[i]=='-') num++;
// 	}
// 	if(num<int(floating.size())) return;
// 	if(in[current]!='-')
// 	{
// 		helper(in, floating, dict, answer, word+in[current]);
// 		return;
// 	}
// 	std::string atoz = "abcdefghijklmnopqrstuvwxyz";
// 	for(int i = 0; i<int(floating.size()); i++)
// 	{
// 		char c = floating[i];
// 		floating.erase(floating.begin()+i);
// 		helper(in, floating, dict, answer, word+ c);
// 		floating.insert(floating.begin()+i, c);
// 		if(atoz.find(c)!=atoz.npos)	atoz.erase(atoz.begin()+atoz.find(c));
// 	}
// 	for(int i = 0; i<int(atoz.size()); i++) helper(in,floating, dict, answer, word+(atoz[i]));
// }

// Add prototypes of helper functions here
void helper(const std::string& in,
    std::multiset<char>& floating,
    const std::set<std::string>& dict,
		std::set<std::string>& answer, std::string word);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
		std::set<std::string> answer;
		std::multiset<char> remain;
		for(int i = 0; i<int(floating.size()); i++) remain.insert(floating[i]);
		helper(in, remain, dict, answer, "");
		return answer;
}

// Define any helper functions here
void helper(const std::string& in,
    std::multiset<char>& floating,
    const std::set<std::string>& dict,
		std::set<std::string>& answer, std::string word)
{
	int current = word.size();
	if(current==int(in.size()))
	{
		if(dict.find(word)!=dict.end() && floating.size()==0) answer.insert(word); 
		return;
	}
	if(in[current]!='-')
	{
		helper(in, floating, dict, answer, word+in[current]);	return;
	}
  std::string atoz = "abcdefghijklmnopqrstuvwxyz";
	for(std::multiset<char>::iterator it = floating.begin(); it!=floating.end(); ++it)
	{
		char c = *it;
		floating.erase(it);
		helper(in, floating, dict, answer, word+ c);
		floating.insert(*it);
		int a = atoz.find(*it);
		if(a!=atoz.npos)	atoz.erase(atoz.begin()+a);
	}
	int num = 0;
	for(int i = current+1; i<int(in.size()); i++)
	{
		if(in[i]=='-') num++;
	}
	if(num<int(floating.size())) return;
	for(int i = 0; i<int(atoz.size()); i++) helper(in,floating, dict, answer, word+(atoz[i]));
}
