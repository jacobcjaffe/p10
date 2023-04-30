#include "p10_func.h"

// fifth and sixth bits are used to represent suit
int convertSuit(char c) {
	if(c == 'C') {
		return 0;
	}
	else if(c == 'S') {
		return 16;
	}
	else if(c == 'D') {
		return 32;
	}
	else {
		return 48;
	}
}

// first four bits are used to represent the value
int convertValue(char c) {
	if (c == 'A') {
		return 1;
	}
	else if (c == 'T') {
		return 10;
	}
	else if (c == 'J') {
		return 11;
	}
	else if (c == 'Q') {
		return 12;
	}
	else if (c == 'K') {
		return 13;
	}
	else {
		return c & 0xf;
	}
}

// heapify for heap sort
void heapify( std::vector<int> &a, int size, int largest ) {
    int temp, temp2; // For swapping
    temp2 = largest;
    int leftchild = (largest << 1) + 1;
    int rightchild = leftchild + 1;

    if ( leftchild < size && (a[leftchild] & 0xf)  > (a[temp2] & 0xf) ) {
        temp2 = leftchild;
    }

    if ( rightchild < size && (a[rightchild] & 0xf) > (a[temp2] & 0xf) ) {
        temp2 = rightchild;
    }
    if (temp2 != largest) {
      temp = a[largest];
      a[largest] = a[temp2];
      a[temp2] = temp;
      heapify(a, size, temp2);
    }

    return;
}

// heap sort
void heapsort( std::vector<int> &a, int size ) {
    // No need to subtract on this one.
    int i, temp;
    for (i = (size >> 1) - 1; i>= 0; i--) {
        heapify( a, size, i );
    }
    for ( i = size - 1; i >= 0; i-- ) {
        temp = a[0];
        a[0] = a[i];
        a[i] = temp;
        heapify( a, i, 0 );
    }
    return;
}

// checks if the hand has a straight flush
bool straightFlush (std::vector<int> &a) {
	bool present1 = true;
	bool present2 = false;
	if((a[0] & 0xf) == 1) {
		present2 = true;
		a.push_back(a[0] + 13);
		for(int i = 2; i < 6; i++) {
			if(a[i] != a[1] + i - 1) {
				present2 = false;
			}
		}
		a.pop_back();
	}
	for(int i = 0; i < 5; i++)  {
		if(a[i] != a[0] + i) {
			present1 = false;
		}
	}
	return (present1 || present2);
}

// checks if the hand has a straight
bool straight(std::vector<int> &a) {
	bool present1 = true;
	bool present2 = false;
	
	std::vector<int> copy;
	for(int i = 0; i < 5; i++) {
		copy.push_back(a[i] & 0xf);
	}
	heapsort(copy, 5);
	for(int i = 1; i < 5; i++) {
		if(copy[i] == 1) {
			present2 = true;
			copy.push_back(a[i] + 13);
			for(int j = 2; j < 6; j++) {
				if(copy[j] !=  (copy[j-1] + 1)) {
					present2 = false;
				}
			}
			copy.pop_back();
		}
		if(copy[i] != (copy[i-1] + 1)) {
			present1 = false;
		}
	}
	return (present1 || present2);
}

Hand getHand(std::unordered_map<int, int> &suit, std::unordered_map<int, int> &value, std::vector<int> &h) {
	Hand hand;
	std::unordered_map<int, int>::iterator itr;
	// check for a straight flush
	if(straightFlush(h)) {
		hand = Straight_Flush;
		return hand;
	}
	// check for a four of a kind
	for(itr = value.begin(); itr != value.end(); itr++) {
		if (itr->second == 4) {
			hand = Four_Of_A_Kind;
			return hand;
		}
	}
	if(value.size() == 2) {
		hand = Full_House;
		return hand;
	}
	if(suit.size() == 1) {
		hand = Flush;
		return hand;
	}

	// check for a straight
	if(straight(h)) {
		hand = Straight;
		return hand;
	}
	int pairs = 0;
	// check for a three of a kind, two pair, one pair
	for(itr = value.begin(); itr != value.end(); itr++) {
		if(itr->second == 3) {
			hand = Three_Of_A_Kind;
			return hand;
		}
		else if(itr->second == 2) {
			pairs++;
		}
	}
	if(pairs == 2) {
		hand = Two_Pairs;
	}
	else if(pairs == 1) {
		hand = One_Pair;
	}
	else {
		hand = Highest_Card;
	}
	return hand;
}

// counts the 1s in a binary representation of a decimal number
int countOnes (int n) {
	int count = 0;
	while(n) {
		n = n & (n-1);
		count ++;
	}
	return count;
}

// returns all combinations n choose k
std::vector<std::vector<int>> NChooseK(std::vector<int> &a, int k) {
	std::vector<std::vector<int>> output;
	std::vector<int> build;
	for(int i = 0; i < (1 << (a.size())); i++) {
		if(countOnes(i) == k) {
			for(int j = 0; j < a.size(); j++) {
				if((1 << j) & i) {
					build.push_back(a[j]);
				}
			}
			output.push_back(build);
			build.clear();
		}
	}
	return output;
}

void debug(std::vector<std::vector<int>> &a) {
	for(int i = 0; i < a.size(); i++) {
		for(int j = 0; j < a[i].size(); j++) {
			std::cout << a[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
	
