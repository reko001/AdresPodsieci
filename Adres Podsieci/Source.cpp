#include <iostream>
#include <string>
#include <bitset>

//funkcja sprawdzajaca czy na wejscie zostaly podane  4 maksymalnie trzycyfrowe liczby oddzielone kropkami
bool ValidateFormat(std::string input) { 
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
	if (countDots == 0) {
		return false;
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

bool ValidateRange(int* numbers){ //funkcja sprawdzajaca zakres danych liczb
	for (int i = 0; i < 4; i++) {
		if (numbers[i] < 0 || numbers[i]>255)
			return false;
	}
	return true;
}

bool ValidateMask(int* mask) {
	int n = 128;
	bool zero = false;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++, n /= 2) {
			if ((mask[i] & n) == n) {
				if (zero)
					return false;
			}
			else {
				zero = true;
			}
		}
		n = 128;
	}
	return true;
}

int main() {
	//std::bitset<8> IPv4[4];
	int IPv4[4];
	int subnetMask[4];
	std::string input;
	std::cout << "Wpisz adres IPv4" << std::endl;
	while (std::cin >> input) {
		if (ValidateFormat(input)) {
			ParseInput(input, IPv4);
			if (ValidateRange(IPv4)) {	
				break;
			}
		}
		std::cout << "Podany adres IPv4 jest nieprawidlowy." << std::endl << "Wpisz jeszcze raz" << std::endl;
	}
	std::cout << "Wpisz maske podsieci" << std::endl;
	while (std::cin >> input) {
		if (ValidateFormat(input)) {
			ParseInput(input, subnetMask);
			if (ValidateRange(subnetMask)) {
				if (ValidateMask(subnetMask)) {
					break;
				}
			}
		}
		std::cout << "Podana maska podsieci jest nieprawidlowa." << std::endl << "Wpisz jeszcze raz" << std::endl;
	}
}