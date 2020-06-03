#include <iostream>
#include <windows.h>
#include <string>
#include <ctime>
#include <conio.h>
#include <fstream>
#include "sha1.h"

using namespace std;

fstream DataBasePassword;
unsigned long long int time_start = 0;
unsigned long long int time1 = 0;
unsigned long long int time2 = 0;
unsigned long long int about_time_work = 0;
const int time_delay = 10;						//Время задержки- через сколько времени выводить информацию на экран
//Используемые символы
char using_simbol[] = {
	//numer & simbol
	'1','2','3','4','5','6','7','8','9','0','-','=',
	'!','@','#','$','%','^','&','*','(',')','_','+',
	'~','\'',';','{','}',':','\"',',','.','/','<','>',
	'?','[',']',/*38*/
	//English
	'q','w','e','r','t','y','u','i','o','p',
	'Q','W','E','R','T','Y','U','I','O','P',
	'a','s','d','f','g','h','j','k','l',
	'A','S','D','F','G','H','J','K','L',
	'z','x','c','v','b','n','m',
	'Z','X','C','V','B','N','M',/*99*/
	//RUSSIAN
	'й','ц','у','к','е','н','г','ш','щ','з','х','ъ',
	'Й','Ц','У','К','Е','Н','Г','Ш','Щ','З','Х','Ъ',
	'ф','ы','в','а','п','р','о','л','д','ж','э',
	'Ф','Ы','В','А','П','Р','О','Л','Д','Ж','Э',
	'я','ч','с','м','и','т','ь','б','ю',
	'Я','Ч','С','М','И','Т','Ь','Б','Ю',
	'ё','Ё'/*156*/
};
const int start_char = 0,				//С какого 
	end_char = sizeof(using_simbol);	//По какой символ использовать
string password,						//Строка хранящая исходный пароль
buffer_brutforce;						//Строка в которой хранятся промежуточные варианты

void Performance_calculation(long long int itteration, long long int max);		// Высчитывает время ожидания

void switch_menu();		//Меню

void sound_signal();	//Звуковой сигнал

void combination_menu();	//брутфорс-меню функция

void input_password();		//Ввод пароля

void func_brut(int i);		//Брут функция

int return_number_simbol(char k);	//Возвращение символа из массива используемых символов

bool check_input(char k);			//Проверка на ввод символов

void find_in_Data_Base();			//Поиск в БД

void add_in_Data_Base(int mode, int time);	//Запись результатов

;int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	switch_menu();
	
}

void switch_menu() {
	short int user_choise = 0;
	bool open_menu = FALSE;
	buffer_brutforce = "";
	while (user_choise != 9)
	{
		time_start = time(NULL);
		time1 = time(NULL);
		time2 = time(NULL);
		system("cls");
		cout << " Выберите меню:\n";
		cout << "1.\t Ввести пароль:";
		if (!password.empty())
		{
			open_menu = TRUE;
			cout << password << '\n';
			cout << "\t2. Поиск в БД" << '\n';
			cout << "\t3. Перебор всех комбинаций" << '\n';
		};
		cout << "\n9. Выход из прогграммы\n";
		cin >> user_choise;
		switch (user_choise)
		{
		case 1:	//Ввод пароля
			input_password();
			break;
			if (open_menu) {
		case 2: // Поиск в БД
			if (open_menu)
			{
				find_in_Data_Base();
			}
			else 
			{
				cout << "Ошибка, вы ввели неверное значение\n";
				Sleep(1000);
			};
			break;
		case 3: // Перебор комбинаций
			if (open_menu)
			{
				combination_menu();
			}
			else
			{
				cout << "Ошибка, вы ввели неверное значение\n";
				Sleep(1000);
			};
			break;


		}
		case 9:
			cout << "Вы вышли из программы\n";
			break;
		default:
			cout << "Ошибка, вы ввели неверное значение\n";
			Sleep(1000);
			break;
		}
	}
}

void input_password() {
	cout << "Введите пароль: ";
	getline(cin, password);
INPUT_ERROR:;
	getline(cin, password);
	for (int i = 0; i < password.size(); i++)
	{
		if (!check_input(password[i]))
		{
			system("cls");
			cout << "Вы ввели неиспользуемый символ! проверьте ввод и введите заного!\n\t\t" << password[i] << "\n\n\t";
			goto INPUT_ERROR;
		}
	}
}


void combination_menu(){
	time_start = time(NULL);
	about_time_work = 0;
	int i = 0;
	time1 = time(NULL);
	long long int year = 0;
	long long int day = 0;
	long long int hour = 0;
	long long int minuts = 0;
	long long int secund = 0;
	//Для быстроты начинаем сразу с определенным количеством символов.
	for (int i = 0; i < password.size(); i++)
	{
		buffer_brutforce.push_back(using_simbol[start_char]);
	}
	char press_button = ' ';
	while ((buffer_brutforce != password))
	{
		time2 = time(NULL);
		if ((time2 - time1) >= time_delay) {
			if (about_time_work == 0)
			{
				long long int max = pow(end_char - start_char, password.size());
				Performance_calculation(i, max );
				year = about_time_work / 31536000;
				day = about_time_work / 86400 - year * 365;
				hour = about_time_work / 3600 - day * 24 - year * 8760;
				minuts = about_time_work / 60 - hour * 60 - day * 1440 - year * 525600;
				secund = about_time_work - minuts * 60 - hour * 3600 - day * 86400 - year * 31536000;
			}
			system("cls");
			cout << "Введите пароль: " << password << "\n\n\t\t" << buffer_brutforce << '\n';
			cout << "Время ожидания:" << year << " лет " << day << " дней " << hour << " часов " << minuts << " минут " << secund << " секунд" << endl;
			cout << "\t\t\t\t Общее время в секундах: " << about_time_work << '\n';
			cout << "Прошло: " << time(NULL) - time_start << 'c' << '\n';
			time1 = time(NULL);
		};
		func_brut(buffer_brutforce.size() - 1);
		if (_kbhit())
		{
			press_button = _getch();
			if (press_button == 27)
			{
				switch_menu();
			}
		};
		i++;
	}
	add_in_Data_Base(0, (time(NULL) - time_start));
	cout << "\n\nПароли совпали!!! " << buffer_brutforce << "\n\tВремя подбора: " << time(NULL) - time_start << 'c';
	sound_signal();
}

void func_brut(int i) {
	if (i < 0)
	{
		buffer_brutforce.insert(0,1,using_simbol[start_char]);
		i = (buffer_brutforce.size() - 1);
	}
	int z = return_number_simbol(buffer_brutforce[i]);
	//cout << "\nz " << buffer_brutforce << ':' << z << '\n';
	//Sleep(100);
	if ( (z + 1) > end_char)
	{
		buffer_brutforce[i] = using_simbol[start_char];
		func_brut(i - 1);
	}
	else {
		buffer_brutforce[i] = using_simbol[z+1];
	}
}

int return_number_simbol(char k) {
	for (int i = 0; i < end_char; i++)
	{
		if (k == char(using_simbol[i])) return i;
	}
}

bool check_input(char k) {
	bool flag = false;
	{
		for (int j = start_char; (j < end_char) && (!flag); j++)
		{
			flag = k == char(using_simbol[j]);
			//cout << flag << ':' << k << "==" << using_simbol[j];
		};
		return flag;
	};
};

void add_in_Data_Base(int mode, int time) {
	DataBasePassword.open("Password.txt", ios::app);
	DataBasePassword << password << "    ";
	switch (mode)
	{
	case 0:
		DataBasePassword << buffer_brutforce << "    " << sha1(password) << "В режиме подбора примерно время ожидания было:" << about_time_work << "    Фактическое время подбора: " << time;
		break;
	case 1:
		DataBasePassword << buffer_brutforce << "    " << sha1(password) << "    " << "В режиме поиска в БД примерное время ожидания было:" << about_time_work << "    Фактическое время подбора: " << time;
		break;
	default:
		break;
	}
	DataBasePassword << '\n';
	DataBasePassword.close();
}

void find_in_Data_Base() {
	about_time_work = 0;
	time_start = time(NULL);
	DataBasePassword.open("DataBasePassword.txt", ios::in);						//Вместо "DataBasePassword.txt" Указать имя файла.
	if (!DataBasePassword.is_open())
	{
		cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
		cout << "!Файл не может быть открыт!" << endl;
		cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
		Sleep(1500);
		system("cls");
	}
	else
	{
		cout << "Файл читается: " << endl;
		char x[41];
		int i = 0;
		long long int year = 0;
		long long int day = 0;
		long long int hour = 0;
		long long int minuts = 0;
		long long int secund = 0;
		string password_upper = sha1(password);
		for (int i = 0; i < password_upper.size(); i++)
		{
			password_upper[i] = toupper(password_upper[i]);
		};
		char press_button = ' ';
		while (DataBasePassword.getline(x,41))
		{
			time2 = time(NULL);
			if ((time2 - time1) >= time_delay) {
				system("cls"); 
				if (about_time_work == 0)
				{
					Performance_calculation(i, 320000000);
					year = about_time_work / 31536000;
					day = about_time_work / 86400 - year * 365;
					hour = about_time_work / 3600 - day * 24 - year * 8760;
					minuts = about_time_work / 60 - hour * 60 - day * 1440 - year * 525600;
					secund = about_time_work - minuts * 60 - hour * 3600 - day * 86400 - year * 31536000;
				}
				cout << "Введите пароль: " << password << "\n Смотрим в БД: " << password_upper << "\n\n\t\t" << x << '\n';
				cout << "Пройдено записей: " << i << '\n';
				cout << "Время ожидания:" << year << "лет" << day << "дней" << hour << " часов " << minuts << " минут " << secund << " секунд" << endl;
				cout << "\tПрошло: " << time(NULL) - time_start << 'c' << '\n';
				time1 = time(NULL);
			}
			if (x == password_upper)
			{
				system("cls");
				buffer_brutforce = x;
				DataBasePassword.close();
				cout << "УСПЕХ!" << '\t' << password << '\t' << buffer_brutforce << '\n';
				add_in_Data_Base(1, (time(NULL) - time_start));
				sound_signal();
			}
			if (_kbhit())
			{
				press_button = _getch();
				if (press_button == 27)
				{
					switch_menu();
				}
			};
			i++;
		}
	}
	cout << "Результатов нет\n";
	DataBasePassword.close();
}

void Performance_calculation(long long int itteration, long long int max) {
	about_time_work = (max / itteration) * time_delay;
}

void sound_signal() {
	cout << "\n\n\n";
	cout << "Нажмите ENTER для продолжения";
	char c = ' ';
	long long time1 = time(NULL);
	long long time2 = time(NULL);
	const int dot_time = 100,
		frequency = 1000;
	while (c != 13)
	{
		time1 = time(NULL);
		if ((time1 - time2) >= time_delay)
		{
			cout << "\r АУ! ВЫ ТУТ?                 ";
			Beep(frequency, dot_time);
			Sleep(dot_time);
			Beep(frequency, dot_time*3);
			Sleep(dot_time * 1.5);

			Beep(frequency, dot_time * 3);
			Sleep(dot_time * 1.5);

			Beep(frequency, dot_time * 3);
			Sleep(dot_time * 1.5);

			Beep(frequency, dot_time);
			Sleep(dot_time * 1.5);

			Beep(frequency, dot_time * 3);
			Sleep(dot_time);
			Beep(frequency, dot_time);
			Sleep(dot_time * 1.5);

			Beep(frequency, dot_time * 3);
			Sleep(dot_time * 1.5);

			Beep(frequency, dot_time);
			Sleep(dot_time);
			Beep(frequency, dot_time);
			Sleep(dot_time * 1.5);

			Beep(frequency, dot_time * 3);
			Sleep(dot_time);
			Beep(frequency, dot_time * 3);
			Sleep(dot_time);
			Beep(frequency, dot_time * 3);
			Sleep(dot_time);

			Beep(frequency, dot_time * 3);
			Sleep(dot_time);
			Beep(frequency, dot_time);
			time2 = time(NULL);
		}
		cout << "\rНажмите ENTER для продолжения";
		if (_kbhit())
		{
			c = _getch();
		}
	}
}