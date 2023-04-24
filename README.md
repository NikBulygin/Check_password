Brute-force password strength tester

The main file is main.cpp. Modify the using_simbol[] array (line 18) to specify the symbols to be used. Set start_char and end_char to indicate the range of symbols. You can also change the information output delay by adjusting time_delay (line 16).

The program has two operation modes:

Full brute-force: For faster processing, the program starts with a specified number of characters. For example, if your password has 10 characters, the search will begin with 10 characters.

Database search: The program uses the pwned? database available for download at https://downloads.pwnedpasswords.com/passwords/pwned-passwords-1.0.txt.7z. Specify the file name on line 266. As the downloaded file contains SHA1 hashes of passwords, hashing functions are included (sha1.h and sha1.cpp). In the find_in_Data_Base() function, indicate the number of passwords in the database on line 298. The default value is 320,000,000.

The program estimates the waiting time by calculating the number of iterations per time_delay and the approximate number of necessary iterations (for brute-force, it's the number of symbols to the power of password length; for database search, it's the number of entries). Press ESC to return to the menu. Upon completion, the program will sound an alert every time_delay seconds. The word "ATTENTION" encoded in Morse code was chosen for this purpose.

The result is saved to the Password.txt file upon program completion.
