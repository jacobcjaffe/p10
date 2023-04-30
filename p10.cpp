#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include "p10_func.h"

int main(int argc, char * argv[]) {

	std::ofstream outstream;
	std::ifstream instream;
    if (argc != 3) {
		std::cout << "ERROR: Input and output files must be specified." << std::endl;
        return -1;
    }
    instream.open(argv[1]);
	outstream.open(argv[2]);
	if(!instream.is_open() || !outstream.is_open()) {
		std::cout << "ERROR: input or output file couldn't be opened." << std::endl;
		return -1;
	}

	// hand represents the cards in hand, with each card represented by 0 - 52
	std::vector<int> hand;
	std::vector<int> deck;
	std::string str;
	int cardValue;
	int cardSuit;
	Hand handValue;

	// the map holds information on how many times each value appears
	std::unordered_map<int, int> valueMap;
	std::unordered_map<int, int> suitMap;
	std::unordered_map<int, int>::iterator itr;

	// iterate until you reach the end of file
	while(!instream.eof()) {
		handValue = Highest_Card;
		// get all of the cards for the hand
		outstream << "Hand: ";
		for(int i = 0; i < 5; i++) {

			instream >> str;
			outstream << str << " ";
			cardSuit = convertSuit(str[1]);
			cardValue = convertValue(str[0]);
			if(suitMap.find(cardSuit) == suitMap.end()) {
				suitMap[cardSuit] = 1;
			}
			else {
				suitMap[cardSuit] += 1;
			}
			if(valueMap.find(cardValue) == valueMap.end()) {
				valueMap[cardValue] = 1;
			}
			else {
				valueMap[cardValue] += 1;
			}
			hand.push_back(cardSuit + cardValue);
		}

		// get the current hand value
		heapsort(hand, 5);
		handValue = getHand(suitMap, valueMap, hand);

		// get all of the cards for the deck
		outstream << "Deck: ";
		for(int i = 0; i < 5; i++) {
			instream >> str;
			outstream << str << " ";
			cardSuit = convertSuit(str[1]);
			cardValue = convertValue(str[0]);
			deck.push_back(cardSuit + cardValue);
		}
		suitMap.clear();
		valueMap.clear();
		Hand currentHand;
		std::vector<std::vector<int>> combos;
		
		// get all combinations from the hand of size n, mix with parts of stack
		for(int i = 1; i < 6; i++) {
			combos = NChooseK(hand, 5-i);
			for(int j = 0; j < combos.size(); j++) {

				//use the deck in the combination
				for(int k = 0; k < i; k++) {
					combos[j].push_back(deck[k]);
				}

				// populate maps for the hands
				for(int k = 0; k < 5; k++) {
					cardValue = combos[j][k] & 0xf;
					cardSuit = combos[j][k] & 0x30;
					if(valueMap.find(cardValue) == valueMap.end()) {
						valueMap[cardValue] = 1;
					}
					else {
						valueMap[cardValue] += 1;
					}
					if(suitMap.find(cardSuit) == suitMap.end()) {
						suitMap[cardSuit] = 1;
					}
					else { 
						suitMap[cardSuit] += 1;
					}
				}
				heapsort(combos[j], 5);
				//std::cout << "new hand" << std::endl;
				for(int k = 0; k < 5; k++) {
					//std::cout << combos[j][k] << std::endl;
				}
				currentHand = getHand(suitMap, valueMap, combos[j]);
				if(currentHand > handValue) {
					handValue = currentHand;
				}
				suitMap.clear();
				valueMap.clear();
			}
			combos.clear();
		}
		hand.clear();
		deck.clear();
		suitMap.clear();
		valueMap.clear();
		outstream << "Best hand: ";
		switch (handValue) {
			case 8:
				outstream << "straight_flush" << std::endl;
				break;
			case 7: 
				outstream << "four_of_a_kind" << std::endl;
				break;
			case 6:
				outstream << "full_house" << std::endl;
				break;
			case 5:
				outstream << "flush" << std::endl;
				break;
			case 4:
				outstream << "straight" << std::endl;
				break;
			case 3:
				outstream << "three_of_a_kind" << std::endl;
				break;
			case 2:
				outstream << "two_pairs" << std::endl;
				break;
			case 1:
				outstream << "one_pair" << std::endl;
				break;
			case 0:
				outstream << "highest_card" << std::endl;
		}
	}
	instream.close();
	return 0;
}
