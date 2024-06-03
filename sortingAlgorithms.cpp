/*****************************************************************************************************************************
* Name: 	    [Magerl]
* Projekt: 	    [sortingAlgorithms]
* Erstelldatum: [22.01.2024]
* Beschreibung: [es wird ein Vektor Array zufällig befüllt und der User kann sich aussuchen welchen Sortier-Algorithmus
				 er darauf anwenden möchte]
******************************************************************************************************************************/

// test git changes

// zweite Änderung test

// Änderung für TestCommit

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <ctime>

void bubbleSort(std::vector<int> &arr) {
	for (size_t i = 0; i < arr.size() - 1; i++) {
		for (auto it = arr.begin(); it != arr.end() - 1 - i; it++) {
			if (*it > *(it + 1)) {
				std::swap(*it, *(it + 1));
			}
		}
	}
}

auto partition(std::vector<int>::iterator low, std::vector<int>::iterator high) {
	int pivotValue = *(high - 1); // pivot element is always the rightmost element
	std::vector<int>::iterator i = low; // i is for evaluating the correct position for the current pivot element

	for (std::vector<int>::iterator j = low; j != high - 1; ++j) {
		if (*j <= pivotValue) {
			std::swap(*i, *j);
			++i;
		}
	}
	std::swap(*i, *(high - 1)); // swapping the pivot element on its correct position
	return i;
}

void quickSort(std::vector<int> &arr, std::vector<int>::iterator low, std::vector<int>::iterator high) {
	if (low < high) {
		auto pivot = partition(low, high);
		quickSort(arr, low, pivot);
		quickSort(arr, pivot + 1, high);
	}
}

void insertionSort(std::vector<int> &arr) {
	for (auto iterator = std::next(arr.begin()); iterator != arr.end(); ++iterator) {
		std::vector<int>::iterator current = iterator;
		while (current != arr.begin() && *(std::prev(current)) > *current) {
			std::iter_swap(current, std::prev(current));
			--current; // Bewegen Sie den Iterator rückwärts.
		}
	}
}

void shellSort(std::vector<int> &arr) {
	std::vector<int> gapSize = { 4, 2, 1 };

	for (auto cycleIt = gapSize.begin(); cycleIt != gapSize.end(); ++cycleIt) {
		for (auto it = arr.begin() + *cycleIt; it <= arr.end() - *cycleIt; it += *cycleIt) {
			std::vector<int>::iterator current = it;
			while (current >= arr.begin() + *cycleIt && *(current - *cycleIt) > *current){
				std::iter_swap(current, current - *cycleIt);
				current -= *cycleIt;
			}
		}
	}
}

// zusätzlicher Test für Commit leeeeesgoooo

int main() {
	std::vector<int> generatedVectorArray;
	int option;

	std::srand(static_cast<unsigned int>(std::time(nullptr))); // initialising the random generator


	// filling the vector Array with 10 random numbers between 1 and 10
	for (int i = 0; i < 10; i++) {
		generatedVectorArray.push_back(std::rand() % 10 + 1);
	}

	// printing the vector array
	std::cout << "die random generierte & unsortierte Zahlenfolge: ";
	for (int value : generatedVectorArray) {
		std::cout << value << ", ";
	}

	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << ">>1<< Quick Sort \n";
	std::cout << ">>2<< Insertion Sort\n";
	std::cout << ">>3<< Bubble Sort\n";
	std::cout << ">>4<< Shell Sort\n";
	std::cout << "wähle einen der vier Sortier-Algorithmen aus: ";

	std::cin >> option;

	switch (option) {
	case 1:
		quickSort(generatedVectorArray, generatedVectorArray.begin(), generatedVectorArray.end());
		break;
	case 2:
		insertionSort(generatedVectorArray);
		break;
	case 3:
		bubbleSort(generatedVectorArray);
		break;
	case 4:
		shellSort(generatedVectorArray);
		break;
	default:
		std::cout << "\n\nbei der Auswahl des Algorithmus muss dir ein Fehler unterlaufen sein\n";
		break;
	}

	// printing the result
	std::cout << "die sortierte Zahlenfolge: ";
	for (int value : generatedVectorArray) {
		std::cout << value << ", ";
	}
	std::cout << std::endl;

	return 0;
}
