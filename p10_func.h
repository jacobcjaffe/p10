#ifndef P10_FUNC_H
#define P10_FUNC_H

#include <iostream>
#include <vector>
#include <unordered_map>

//enum for hand values
enum Hand { Highest_Card = 0, One_Pair = 1, Two_Pairs = 2,
	Three_Of_A_Kind = 3, Straight = 4, Flush = 5, Full_House = 6,
	Four_Of_A_Kind = 7, Straight_Flush = 8,
};

// convert the cards into integer values between 0-52
// convertSuit changes from the char representing suit to an int
int convertSuit(char c);
// convertValue changes from the char represnting value to its int value
int convertValue(char c);

// heap sort
void heapify(std::vector<int> &a, int size, int largest);
void heapsort(std::vector<int> &a, int size);

// detects a straight flush
bool straightFlush(std::vector<int> &a);
// detects a straight
bool straight(std::vector<int> &a);

Hand getHand(std::unordered_map<int, int> &suit, std::unordered_map<int, int> &value, std::vector<int> &h);
std::vector<std::vector<int>> NChooseK(std::vector<int> &a, int k);

void debug(std::vector<std::vector<int>> &a);

#endif
