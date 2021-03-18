#include <iostream>
#include <string>
#include <bitset>

//funkcja sprawdzajaca czy na wejscie zostaly podane  4 maksymalnie trzycyfrowe liczby oddzielone kropkami
bool Validate1(std::string input) { 
	int countDigits = 0; //licznik cyfr
	int countDots = 0; //licznik kropek
	for (int i = 0; i < input.length(); i++) {
		if (input[i] < '0' && input[i]>'9' && input[i] != '.') //falsz dla nie cyfr  i nie kropek
			return false;
		else if (input[i] >= '0' && input[i] <= '9'){ //zwiekszenie licznika cyfr
			countDigits++;
			if (countDigits > 3) //jesli licznik cyfr jest wiekszy od 3 to dane sa zle
				return false;
		}
		else if (input[i] == '.') {
			if (countDigits == 0) //jesli licznik cyfr jest 0 to dane sa zle
				return false;
			countDots++; //zwiekszenie licznika kropek
			countDigits = 0; //wyzerowanie licznika cyfr
			if (countDots > 3) //falsz jesli kropek bylo wiecej niz trzy
				return false;
		}
	}
	return true;
}

void ParseInput(std::string input, int* numbers) { //funkcja wpisujaca do tablicy dane liczby
	std::string temp = ""; //tymczasowa liczba
	int part = 0; //indeks tablicy
	for (int i = 0; i < input.length(); i++) {
		if (input[i] != '.') {
			temp += input[i];
		}
		else {
			numbers[part] = stoi(temp); //zamienienie tymczasowej liczby na inta i wpisanie do tablicy
			part++;
			temp = "";
		}
	}
	numbers[part] = stoi(temp); //wpisanie ostatniej liczby
}

int main() {
	int IPv4;
	int numbers[4];
	int SubnetMask;
	std::string input;
	std::cin >> input;
	if (Validate1(input)) {
		ParseInput(input, numbers);
		for (int i = 0; i < 4; i++) {
			std::cout << numbers[i] << " ";
		}
	}
}