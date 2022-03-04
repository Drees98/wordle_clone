# wordle_clone
A project I took on to freshen up my skills in C++. End project will have a GUI, similar to the one on the website.

words.txt contains a string literal that has been copied to words.h. This literal contains most, if not all, 5 letter words in the english language.

wordle_clone contains all of the functions and object required to have the wordle application run. 

Default Constructor: Automatically calls the get_words and random_word functions to set the word_list and word object variables

Object Variables: 
  word_list: List of all valid words
  word: target word for the user to guess 

functions include:
  get_word: Returns word variable value

  get_words_list: Returns array of all valid words

  get_words(string words): Takes a newline delimited string and transfers it to an array of strings. returns said array.
  
  random_word(array<string>word_list): Takes the word_list array and selects a random word from it. Returns the random word in a string.
  
  valid_word(array<string> words, array<string> guesses): Takes the array of words and the array of previously guessed words. User enters a word, if it is not in the word list, 
    or has already been guessed, user will be prompted to enter another word. Once a valid word has been entered, it is returned as a string.
    
  compare(string word, string guess): Takes the word and the users guess and compares them. If the guess is correct, it will immediately return the boolean value true.
    If not, it will compare each char in the guess, to each char in the word. If there is a match, it will let the user know that char in position x is correct.
    If it is not a match, but the char exists in the target word, it will let the user know that the char is in the word, just not that position.
    If the char is not in the target word, it will let the user know that the char is not in the word at all. After this process, the boolean value false is returned.

 start_game(string word, array<string> word_list): Starts the gameplay loop where a user will be prompted to enter the words using the valid_word function and then have the word
    compared to the target using the compare function. This will happen until the user guesses the correct word, or six failed attempts have happened. The outcome will affect the message displayed at the end of the gameplay loop
    
wordle.cpp is the driver file that runs the code for the executable. While the file contains some things for now, most will be removed once the functions get added to an object.

wordle.exe is the executable file for the program. It should run on windows machines, however I have not had the opportunity to try it on other versions of windows

Future plans:
  
  1: Create a gui, similar to the one on the wordle website
  
  2: Have the program create a file to track user games and display them
