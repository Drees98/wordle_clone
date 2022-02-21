# wordle_clone
A project I took on to freshen up my skills in C++. End project will have a GUI, similar to the one on the website.

words.txt contains a string literal that has been copied to words.h. This literal contains most, if not all, 5 letter words in the english language.

wordle_functions contains all of the functions required to have the wordle application run. 

functions include:
  get_words(string words): Takes a newline delimited string and transfers it to an array of strings. returns said array.
  
  random_word(array<string>word_list): Takes the word_list array and selects a random word from it. Returns the random word in a string.
  
  valid_word(array<string> words, array<string> guesses): Takes the array of words and the array of previously guessed words. User enters a word, if it is not in the word list, 
    or has already been guessed, user will be prompted to enter another word. Once a valid word has been entered, it is returned as a string.
    
  compare(string word, string guess): Takes the word and the users guess and compares them. If the guess is correct, it will immediately return the boolean value true.
    If not, it will compare each char in the guess, to each char in the word. If there is a match, it will let the user know that char in position x is correct.
    If it is not a match, but the char exists in the target word, it will let the user know that the char is in the word, just not that position.
    If the char is not in the target word, it will let the user know that the char is not in the word at all. After this process, the boolean value false is returned.
    
wordle.cpp is the driver file that runs the code for the executable. While the file contains some things for now, most will be removed once the functions get added to an object.

wordle.exe is the executable file for the program. It should run on windows machines, however I have not had the opportunity to try it on other versions of windows

Future plans:
  
  1: Move the functions into an object in the wordle_functions header file
  
  2: Create a gui, similar to the one on the wordle website
  
  3: Have the program create a file to track user games and display them
