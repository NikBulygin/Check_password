# Check_password
 Проверяет надежность вашего пароля методом брутфорса

Главный файл main.cpp В этом файле указать в using_simbol[] (line 18) массив используемых символов.
start_char и end_char - с какого по какой символ использовать. Так же можно изменить задержку между выводом информамции, для этого
нужно изменить time_delay (line 16).

Программа имеет два режима работы:
1) Полный перебор. Для скорости перебора программа начинает перебирать с определенного количества символов,
т.е. если у вас 10-ти символьный пароль, то и перебор начнется с 10-ти символов.

2) Перебор в БД. Для этого использовалась база данных с ресурса pwned? Ссылка на скачивание: https://downloads.pwnedpasswords.com/passwords/pwned-passwords-1.0.txt.7z
В строке 266 нужно указать имя файла. Т.к. в скачанном файле все пароли хранятся в хешах SHA1, была подключена функция по хешированию паролей
(sha1.h и sha1.cpp соответсвенно). Так же в функции find_in_Data_Base(), в строке 298 нужно указать количество паролей в БД. Я поставил значение 320000000.

Так же программа подсчитывает примерное время ожидания. Для этого подсчитывается количество иттераций за time_delay, а так же примерное количество необходимых иттераций(при переборе это (количество_символов^длину_пароля), а для поиска в бд это количество записей)
Возврат в меню выбора осуществляется нажатием клавиши ESC.
После завершения программы раз в time_delay секунд будет звуковое оповещение. Для этого решено было использовать слово ATTENTION которая 
была зашифрована в азбуку морзе.

По завершению программы результат выводится в файл Password.txt
