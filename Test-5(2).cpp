#include <iostream>
#include <random>

void cinClear() {															//Очистка буфера и перевод cin в нормальный режим

	std::cin.clear();
	std::cin.ignore(32767, '\n');
	std::cout << "Something went wrong. Please, try again.\n";

}

bool again() {																//Спрашиваем хочет ли пользователь сыграть ещё раз

	char choice;
	while (true) {

		std::cout << "Whould you like to play again (y/n)? ";

		while (true) {
			std::cin >> choice;

			if (std::cin.fail()) {		//Проверка ввода
				cinClear();
			}else
				std::cin.ignore(32767, '\n');
				break;
		}

		switch (choice) {
		case 'y': return true;
		case 'n': return false;

		}

	}

}

short chooseDifficulty() {

	short difficulty;
	while(true){
		std::cout << "Choose difficulty: 1 -- very easy\t2 -- easy\t3 -- medium\t4 -- high\t5 - expert.\n";							
		std::cin >> difficulty;

		if ( std::cin.fail() || (difficulty != 1 && difficulty != 2 && difficulty != 3 && difficulty != 4 && difficulty != 5) ) {		//Проверка ввода
			cinClear();
		}
		else {
			switch (difficulty) {			//Возвращаю количество попыток в зависимости 
			case 1: return 70;				//от выбранного уровня сложности
			case 2: return 35;
			case 3: return 15;
			case 4: return 10;
			case 5: return 5;
			}

		}

	}

}

int getRandomNumber() {

	std::random_device a;										//Получаем рандомное число
	std::mt19937 gen(a());										//Инициализируем вихрь Мерсенна полученным случайным числом
	std::uniform_int_distribution<> dist(1, 100);				//Задаём диапазон распределения псевдослучайных чисел

	return dist(gen);											//Возвращаем псевдослучайное число из заданного диапазона
}

int inputNumber() {																//Ввод

	int number;

	while (true) {
		
		std::cin >> number;

		if (std::cin.fail()) {					//Проверка ввода
			cinClear();
		}
		else {
			std::cin.ignore(32767, '\n');
			return number;
		}
			
	}

}

void game(int hiddenNumber, short difficulty) {												//Сама игра
	
	bool youWin{ false };	 //Переменная для вывода/не вывода строки, сообщающей о проигрыше
	int userNumber;

	for (int kkk = 1; kkk <= difficulty; ++kkk) {
		std::cout << "Guess #" << kkk << ": ";
		userNumber = inputNumber();
		if (userNumber < hiddenNumber) {
			std::cout << "Your guess iss too low.\n";
		}
		else
			if (userNumber > hiddenNumber) {
				std::cout << "Your guess is too high.\n";
			}
			else
				if (userNumber == hiddenNumber) {
					std::cout << "Correct! You win!\n";
					youWin = true;
					break;
				}
	}
	if (!youWin) {
		std::cout << "Sorry, you lose. The correct number was " << hiddenNumber << "\n\n";
	}

}

int main()
{
	while (true) {

		std::cout << "Let's play a game. I'm thinking of a number. Number is in range [1 ; 100]. You should guess what it is.\n\n";

		short difficulty{ chooseDifficulty() };
		
		std::cout << "Yon have " << difficulty << " tries.\n\n";

		game(getRandomNumber(), difficulty);

		if (!again()) {
			std::cout << "Thanks for playing this game! We look forward to seeing you again!\n";
			break;
		}

	}
	
	system("pause");
	return 0;
}
