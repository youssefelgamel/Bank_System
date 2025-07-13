#pragma once

#include <iostream>
using namespace std;

namespace MyLib {

	int readNumber(string message) {
		cout << message << "\n";
		int number = 0;
		cin >> number;
		return number;
	}

	int readPositiveNumber(string message) {
		cout << message << "\n";
		int number;
		cin >> number;
		return number > 0 ? number : readPositiveNumber(message);
	}

	enum enPrimeNotPrime { Prime = 1, NotPrime = 2 };

	enum enCharType { smallLetter = 1, capitalLetter = 2, specialChar = 3, digit = 4 };

	enPrimeNotPrime checkPrime(int number) {
		int m = round(number / 2);
		if (number == 2) return enPrimeNotPrime::Prime;
		if (number == 1) return enPrimeNotPrime::NotPrime;
		for (int i = 2; i <= m; i++) {
			if (number % i == 0) return enPrimeNotPrime::NotPrime;
		}
		return enPrimeNotPrime::Prime;
	}

	int randomNumber(int from, int to) {
		int randNum = rand() % (to - from + 1) + from;
		return randNum;
	}

	char randomCharacter(int from, int to) {
		int randChar = rand() % (to - from + 1) + from;
		return char(randChar);
	}

	void printArray(int arr[100], int arrLength) {
		cout << "{";
		for (int i = 0; i < arrLength; i++) {
			if (i == arrLength - 1) {
				cout << arr[i];
				break;
			}
			cout << arr[i] << ", ";
		}
		cout << "}" << endl;
	}

	void fillArrayWithOrderedNumbers(int arr[100], int& arrLength) {
		arrLength = readPositiveNumber("Enter how many elements: ");
		for (int i = 1; i <= arrLength; i++) {
			arr[i - 1] = i;
		}
	}

	void fillArrayWithRandomNumbers(int arr[100], int& arrLength) {
		arrLength = readPositiveNumber("Enter how many elements: ");
		for (int i = 0; i < arrLength; i++) {
			arr[i] = randomNumber(-100, 100);
		}
	}

	char getRandomChar(enCharType charType) {
		switch (charType) {
		case enCharType::smallLetter: {
			return char(randomNumber(97, 122));
			break;
		}
		case enCharType::capitalLetter: {
			return char(randomNumber(65, 90));
			break;
		}
		case enCharType::specialChar: {
			return char(randomNumber(33, 47));
			break;
		}
		case enCharType::digit: {
			return char(randomNumber(48, 57));
			break;
		}
		}
		return '\0'; // return a null character!
	}

	string generateWord(enCharType charType, short length) {
		string word;
		for (int i = 1; i <= length; i++) {
			word += getRandomChar(charType);
		}
		return word;
	}

	string generateKey() {
		string key = "";
		key = generateWord(enCharType::capitalLetter, 4) + "-";
		key += generateWord(enCharType::capitalLetter, 4) + "-";
		key += generateWord(enCharType::capitalLetter, 4) + "-";
		key += generateWord(enCharType::capitalLetter, 4);
		return key;
	}

	void fillArrayWithKeys(string arr[100], int arrLength) {
		for (int i = 0; i < arrLength; i++) {
			arr[i] = generateKey();
		}
	}

	void printStringArray(string arr[100], int arrLength)
	{
		cout << "\nArray elements:\n\n";
		for (int i = 0; i < arrLength; i++)
		{
			cout << "Array[" << i << "] : ";
			cout << arr[i] << "\n";
		}
		cout << "\n";
	}

	int searchNumberInArray(int arr[100], int arrLength, int number) {
		for (int i = 0; i < arrLength; i++) {
			if (arr[i] == number)
				return i;
		}
		return -1;
	}

	int dynamicArray(int arr[100]) {
		int counter = -1, number = 0, choice;
		do {
			counter++;
			cout << "Please enter a number: \n";
			cin >> number;
			arr[counter] = number;
			cout << "Do you want to add more? [0]:No, [1]:Yes\n";
			cin >> choice;
		} while (choice != 0);
		cout << "Array elements: \n";
		printArray(arr, counter + 1);
		return(counter + 1);
	}

	bool isPalindromeArray(int arr[100], int length) {
		for (int i = 0; i < length; i++) {
			if (arr[i] != arr[length - 1 - i]) {
				return false;
			}
		}
		return true;
	}

	int absNum(int num) {
		if (num < 0) {
			return num * -1;
		}
		return num;
	}

	int sqrtNum(int num) {
		for (int i = 1; i < num / 2; i++) {
			if ((i * i) == num)
				return i;
		}
		return -1;
	}

	void fillRandomMatrix3x3Matrix(int matrix[3][3], short row, short colomn) {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < colomn; j++) {
				matrix[i][j] = MyLib::randomNumber(1, 100);
			}
		}
	}

	void transposeMatrix(int matrix[3][3], int transposedM[3][3], short row, short colomn) {
		for (short i = 0; i < row; i++) {
			for (int j = 0; j < colomn; j++) {
				transposedM[i][j] = matrix[j][i];
			}
		}
	}

	void printMatrix(int matrix[3][3], short row, short colomn) {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < colomn; j++) {
				printf("%0*d\t", 2, matrix[i][j]);
			}
			cout << endl;
		}
	}

	int sumMatrixRow(int matrix[3][3], short row, short colomn) {
		int sum = 0;
		for (int j = 0; j < colomn; j++) {
			sum += matrix[row][j];
		}
		return sum;
	}

	int sumMatrixColomn(int matrix[3][3], short row, short colomn) {
		int sum = 0;
		for (int j = 0; j < row; j++) {
			sum += matrix[j][colomn];
		}
		return sum;
	}

	void printSumColomn(int matrix[3][3], short row, short colomn) {
		cout << "The following are the sum of the matrix colomns: \n";
		for (short i = 0; i < colomn; i++) {
			cout << "Colomn " << i + 1 << ": " << sumMatrixColomn(matrix, row, i) << endl;
		}
	}

	void rowSumToArr(int matrix[3][3], short row, short colomn, int arr[3]) {
		cout << "The following are the sum of each row sum: \n";
		for (short i = 0; i < row; i++) {
			arr[i] = sumMatrixRow(matrix, i, colomn);
			cout << "Row " << i + 1 << ": " << arr[i] << endl;
		}

	}

	void colomnSumToArr(int matrix[3][3], short row, short colomn, int arr[3]) {
		cout << "The following are the sum of each row sum: \n";
		for (short i = 0; i < row; i++) {
			arr[i] = sumMatrixColomn(matrix, row, i);
			cout << "Row " << i + 1 << ": " << arr[i] << endl;
		}

	}

	void multiply2Matrices(int matrex1[3][3], int matrix2[3][3]) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				printf("%0*d", 2, matrex1[i][j] * matrix2[i][j]);
				cout << '\t';
			}
			cout << '\n';
		}
	}

	void printMidRWMatrix(int matrix[3][3], short row, short colomn) {

		int midR = row / 2;
		int midC = colomn / 2;

		cout << "Middle Row :\n";

		for (int j = 0; j < colomn; j++) {
			printf("%0*d  ", 2, matrix[midR][j]);
		}

		cout << endl;
		cout << "Middle Colomn: \n";
		for (int i = 0; i < row; i++) {
			printf("%0*d  ", 2, matrix[i][midC]);
		}
	}

	int sumMatrix(int matrix[3][3]) {
		int sum = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				sum += matrix[i][j];
			}
		}
		return sum;
	}

	bool check2MatricesEquality(int matrix1[3][3], int matrix2[3][3]) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (matrix1[i][j] != matrix2[i][j]) {
					return false;
				}
			}
		}
		return true;
	}

	bool checkMatrixIdentity(int matrix[3][3], int rows, int colomns) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (i == j) {
					if (matrix[i][j] != 1) return false;
				}
				else {
					if (matrix[i][j] != 0) return false;
				}
			}
		}
		return true;
	}

	bool checkMatrixIsScalar(int matrix[3][3], int rows, int colomns) {
		int firstDiagElement = matrix[0][0];
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (i == j) {
					if (matrix[i][j] != firstDiagElement) return false;
				}
				else {
					if (matrix[i][j] != 0) return false;
				}
			}
		}
		return true;
	}

	int countGivenNumberInMatrix(int matrix[3][3], int number) {
		int count = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (matrix[i][j] == number)
					count++;
			}
		}
		return count;
	}

	bool checkSparceMatrix(int matrix[3][3], int rows, int colomns) {
		int MatrixSize = rows * colomns;
		return (countGivenNumberInMatrix(matrix, 0) >= ceil(MatrixSize / 2));
	}

	bool checkNumberInMatrix(int matrix[3][3], int number) {
		int count = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (matrix[i][j] == number)
					return true;
			}
		}
		return false;
	}

	void IntersectedNumbers(int matrix1[3][3], int matrix2[3][3]) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (checkNumberInMatrix(matrix1, matrix2[i][j]))
					cout << matrix2[i][j] << "\t";
			}
		}
	}

	void MinMaxInMatrix(int matrix[3][3]) {
		int min = matrix[0][0];
		int max = matrix[0][0];
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (min > matrix[i][j]) swap(min, matrix[i][j]);
				if (max < matrix[i][j]) swap(max, matrix[i][j]);
			}
		}
		cout << "Min number = " << min << endl;
		cout << "Max number = " << max << endl;
	}

	bool isPalindromeMatrix(int matrix[3][3]) {
		for (int i = 0; i < 3; i++) {
			if (matrix[i][0] != matrix[i][2])  return false;
		}
		return true;
	}

	void fibonacciSeriesUsingLoop(int end) {
		int febNumber = 0;
		int prev2 = 0, prev1 = 1;
		cout << "0 1 ";
		for (int i = 2; i <= end; i++) {
			febNumber = prev1 + prev2;
			cout << febNumber << " ";
			prev2 = prev1;
			prev1 = febNumber;
		}

	}

	void fibonacci(int end, int a, int b) {
		if (end > 0) {
			cout << a << ' ';
			fibonacci(end - 1, b, a + b);
		}
	}

	string lowerCase1stLetterOfEachWord(string s1) {
		bool isFirstLetter = true;
		for (int i = 0; i < s1.length(); i++) {
			if (s1[i] != ' ' && isFirstLetter == true) {
				s1[i] = tolower(s1[i]);
			}

			isFirstLetter = (s1[i] == ' ' ? true : false); // ternary 
		}
		return s1;
	}

	void upperAndLowerAllLetters(string s1) {
		for (int i = 0; i < s1.length(); i++) {
			s1[i] = toupper(s1[i]);
		}
		cout << "\n" << s1;

		for (int i = 0; i < s1.length(); i++) {
			s1[i] = tolower(s1[i]);
		}
		cout << "\n" << s1;
	}

	char InvertCharCase(char c) {
		return islower(c) ? toupper(c) : tolower(c);
	}

	string InvertLetterCase(string s) {
		for (short i = 0; i < s.length(); i++) {
			s[i] = InvertCharCase(s[i]);
		}
		return s;
	}

	void stringDetails(string s) {
		int CapCount = 0;
		int smallCount = 0;
		for (short i = 0; i < s.length(); i++) {
			if (islower(s[i])) smallCount++;
			else if (isupper(s[i])) CapCount++;
		}
		cout << "String Length: " << s.length() << endl;
		cout << "Capital letters count: " << CapCount << endl;
		cout << "Small letters count: " << smallCount << endl;
	}

	bool isVowelChar(char c) {
		return (tolower(c) == 'a') || (tolower(c) == 'e') || (tolower(c) == 'i') || (tolower(c) == 'o') || (tolower(c) == 'u');
	}

	void countVowel(string s) {
		int counter = 0;
		for (short i = 0; i < s.length(); i++) {
			if (isVowelChar(s[i])) cout << s[i] << "\t";
		}
	}

	void printEachWordInString(string s) {
		string delim = " ";//delimiter
		cout << "\nYour string words are: \n\n";
		short pos = 0;
		string sWord;

		while ((pos = s.find(delim)) != std::string::npos)
		{
			sWord = s.substr(0, pos);
			if (sWord != " ") {
				cout << sWord << endl;
			}
			s.erase(0, pos + delim.length());
		}
		if (s != " ") {
			cout << s << endl;
		}
	}

	int countEachWordInString(string s) {
		int counter = 0;
		string delim = " ";//delimiter
		short pos = 0;
		string sWord;

		while ((pos = s.find(delim)) != std::string::npos)
		{
			sWord = s.substr(0, pos);
			if (sWord != "") {
				counter++;
			}
			s.erase(0, pos + delim.length());
		}
		if (s != "") {
			counter++;
		}
		return counter;
	}

}
