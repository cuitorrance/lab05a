// WordCount.cpp
// Written by Richert Wang for CS 32, F18.

#include "WordCount.h"
#include <stdio.h>
#include <ctype.h>
#include <cctype>
#include <queue>
#include <functional>
#include <vector>
#include <bits/stdc++.h>
//testpurposes
#include <iostream>
#include <fstream>

// Default constructor
WordCount::WordCount() {
  for ( unsigned i =0; i < CAPACITY; i++)
    {
      table[i].clear();
    }
}

// Simple hash function. Do not modify.
size_t WordCount::hash(std::string word) const {
	size_t accumulator = 0;
	for (size_t i = 0; i < word.size(); i++) {
		accumulator += word.at(i);
	}
	return accumulator % CAPACITY;
}

int WordCount::getTotalWords() const {
  int counter = 0;
  for (unsigned i = 0; i < CAPACITY; i++)
    {
      for (unsigned j = 0; j < table[i].size(); j++)
	{
	  counter += static_cast<int>( (table[i].at(j)).second );
	}
    }
  return counter;
}

int WordCount::getNumUniqueWords() const {
  int counter = 0;
  for (unsigned i = 0; i < CAPACITY; i++)
    {
      for (unsigned j = 0; j < table[i].size(); j++)
	{
	  counter++;
	}
    }
  return counter;
}
/* std::string WordCount::toUp(std::string word){
  std::string ans = "";
  for (unsigned i = 0; i < word.length();i++)
    {
      ans += toupper(word[i]);
    }
  return ans;
  } */
int WordCount::getWordCount(std::string word) const { 
  std::string lword = stripWord(word);
  std::string fword = "";
  for (unsigned i = 0; i < lword.length();i++)
    {
      fword += toupper(lword[i]);
    }
  if (fword.compare("") == 0) return 0;
  size_t i = hash(fword);
  for ( unsigned j = 0; j < table[i].size();j++)
    {
      if ( ((table[i].at(j)).first).compare(fword) == 0)
         {
	   return static_cast<int>( (table[i].at(j)).second );
	 }
    }
  return 0;
}
	

int WordCount::incrWordCount(std::string word) {
  std::string lword = stripWord(word);
  std::string fword = "";
  for (unsigned i = 0; i < lword.length();i++)
    {
      fword += toupper(lword[i]);
    }
  if (fword.compare("") == 0) return 0;
  size_t i = hash(fword);
  int index = 0;
  if ( getWordCount(fword) == 0)
    {
      std::pair<std::string,size_t> nword;
      nword.first = fword;
      nword.second = 1;
      table[i].push_back(nword);
      //std::cout << nword.first << std::endl;
      return 1;
    }
  else
    {
      for (unsigned j = 0; j <table[i].size();j++)
	{
	  if ( ((table[i].at(j)).first).compare(fword) == 0)
	    {
	      index = j;
	    }
	}
      (table[i].at(index)).second++;
      //std::cout << (table[i].at(index)).first << std::endl;
      return (table[i].at(index)).second;
    }     
}


bool WordCount::isWordChar(char c) {
  if (isalpha(c))
    {
      return true;
    }
  else
    {
      return false;
    }
}


std::string WordCount::stripWord(std::string word) {
  std::string ans = "";
  
  for ( unsigned i = 0; i < word.length(); i++)
    {
      if ( isalpha(word[i]) )
	{
	  ans += word[i];
	}
      else if ( word[i] == '-' || word[i] == '\'')
	{
	  if ( i == 0 || i == word.length()-1)
	    {
	      //do nothing
	    }
	  else if ( !isalpha(word[i-1]) || !isalpha(word[i+1]) ) 
	    {
	        //do nothing
	    }
	  else
	    {
	      ans += word[i];
	    }
	}
    }
  return ans;
}

//for min priority queue
struct compare
{
  bool operator()(const std::pair<std::string,size_t> &l, const std::pair<std::string, size_t> &r)
  {
    return l.first > r.first;
  }
};
struct compare1
{
  bool operator()(const std::pair<size_t, std::string> &l, const std::pair<size_t, std::string> &r)
  {
    if (l.first == r.first)
      {
	return l.second > r.second;
      }
    else
      {
	return l.first < r.first;
      }
  }
};

void WordCount::dumpWordsSortedByWord(std::ostream &out) const {
  std::priority_queue<std::pair<std::string,size_t> , std::vector<std::pair<std::string,size_t>> , compare>  q;

  for ( unsigned i = 0; i <CAPACITY; i++)
    {
      for (unsigned j = 0; j < table[i].size();j++)
	{
	  q.push(table[i].at(j));
	}
    }
  while (!q.empty())
    {
      out << q.top().first << "," << q.top().second << std::endl;
      q.pop();
    }
    return;
}

void WordCount::dumpWordsSortedByOccurence(std::ostream &out) const {
  std::priority_queue<std::pair<size_t, std::string> , std::vector<std::pair<size_t, std::string>> , compare1>  q;

  std::pair<size_t, std::string> p;
  
  for ( unsigned i = 0; i <CAPACITY; i++)
    {
      for (unsigned j = 0; j < table[i].size();j++)
	{
	  p.first = (table[i].at(j)).second;
	  p.second =( table[i].at(j)).first;
	  q.push(p);
	}
    }
  while (!q.empty())
    {
      out << q.top().second << "," << q.top().first << std::endl;
      q.pop();
    }
	return;
}

void WordCount::addAllWords(std::string text) {
  int i = 0;
  std::string word = ""; 
   for (auto x : text) 
   {
     if ( i > -1)
       {
	 if (x == ' ' || x == '\n') 
	   { 
	     i = incrWordCount(stripWord(word));    
	     word = ""; 
	   } 
	 else
	   { 
	     word = word + x; 
	   }
       }
   }
   i = incrWordCount(stripWord(word));
   return;
}
