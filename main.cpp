/**************************************************************************
 *   Author    :  John Chen
 *   Assn #6   :  Hangman
 *   CLASS     :  CS 002
 *   SECTION   :  MTRF: 7a - 12p
 *   Due Date  :  7/7/19
 *************************************************************************/
#include <iostream>
#include <cctype>
using namespace std;
/**************************************************************************
 *
 * HANGMAN
 * ________________________________________________________________________
 * This program accepts a word to be guessed later on and replaces it with
 * dashes which upon being guessed will be filled with the original letter.
 * The program ends when the user guesses the word or when the user inputs
 * seven incorrect gueses.
 * ________________________________________________________________________
 * INPUT:
 *   word: The word to be guessed by the user -> input from user
 *   guess: The different guesses from the user for the word
 *          -> input from user
 *
 * OUTPUT:
 *   Will output a remark based on whether the user succeeded or failed
 *************************************************************************/

/**************************************************************************
 * setupUnsolved
 *  This function receives a phrase and replaces all the letters with
 * dashes as output.
 *   - returns string -> This will be one of strings and spaces
 * ***********************************************************************/
string setupUnsolved(string phrase); //IN - phrase to be replaced

/**************************************************************************
* updateUnsolved
*  This function receives an unsolved string and replaces all instances
*  of the guessed character within the unsolved string by comparing it to
*  the phrase.
*   - returns string -> This will be dashes with replaced letters
* ***********************************************************************/
string updateUnsolved(string phrase,   //IN - the actual phrase inputted
                      string unsolved, //IN - the updated guessed string
                      char guess);     //IN - the guessed letter

/**************************************************************************
 * getGuessed
 *  This function receives a guess for a letter and a string of previous
 *  guesses and will only output a valid guess that is in the alphabet and
 *  not in the previous guesses
 *   - returns char -> This will be a valid guess
 * ***********************************************************************/
char getGuess(string prevGuesses); //IN - previous guesses

int main()
{
    //INPUT     : A description of what is being input.
    //PROCESSING: Detail of what is being processed.
    //OUTPUT    : Details of what is being output.

    //constants
    string word;      //INPUT - Word that is inputted and to be guessed
    string puzzle;    //CALC - String with dashes that is continually
                      //       updated with lettesr
    string guesses;   //OUPUT - Previous guesses for the word
    int incorrect;    //OUTPUT - the amount of incorrect guesses allowed
                      //         left
    bool val;

    //Users are allowed seven guesses at the word
    incorrect = 7;

    //INPUT & OUTPUT: prompt for a phrase to used for the game
    cout << "Enter phrase: ";
    getline(cin, word);
    cout << endl;

    //OUTPUT: Display the word with its letters replaced with dashes
    cout << "Phrase: " << setupUnsolved(word) << endl;

    //PROCESSING: Variable given a constantly updated string with dashes
    //            and letters
    puzzle = setupUnsolved(word);

    //PROCESSING: Keeps asking for guesses until all guesses are used up
    //            or if the word is guessed
    while(incorrect > 0 && puzzle != word)
    {
        //constant for the guesses
        char guess;

        //INPUT & OUTPUT: Prompt the user for some guesses and only accept
        //                valid guesses
        cout << "Enter a guess: ";
        guess = getGuess(guesses);
        cout << endl;

        //PROCESSING: Current guess will be added to the previous guesses
        guesses +=guess;

        val = true;

        for(int i = 0; i < word.length(); i++)
        {
            if(tolower(word.at(i)) == guess)
                val = false;
        }
        //PROCESSING: Will decrement the chances for guesses if the guess
        //            is not in the word inputted
        if(val) //word.find(guess) == -1
        {
            --incorrect;

            //OUTPUT: Display the guesed letters and the amount of wrong
            //        guesses left
            cout << "Guessed so far: " << guesses << endl
                 << "Wrong guesses left: " << incorrect << endl;

            cout << updateUnsolved(word, puzzle, guess) << endl << endl;
        }
        //OUTPUT & PROCESSING: Display the updated dashed string and
        //                     store/update it in the puzzle variable
        else {
            //OUTPUT: Display the guesed letters and the amount of wrong
            //        guesses left
            cout << "Guessed so far: " << guesses << endl
                 << "Wrong guesses left: " << incorrect << endl;

            //updateUnsolved - Will return an upadted string of dashes and
            //                 letters based on the guesses
            puzzle = updateUnsolved(word, puzzle, guess);
            cout << puzzle << endl << endl;
        }
    }

    //OUTPUT: Once the program is done, it will display a failure or
    //        success based on whether the puzzle matches the word
    if(puzzle == word)
        cout << "Congratulations!! You won!" << endl;
    else
        cout << "You lost!";
}

/*************************************************************************/

string setupUnsolved(string phrase)
{
    double len;
    string dashes;

    //Finds length of the word
    len = phrase.length();

    //PROCESSING: Will look at every space in the word and add a dash if
    //            it is an alphabet letter and a space if not
    for(int i = 0; i < len; i++)
    {
        if(isalpha(phrase.at(i)))
            dashes += "-";
        else {
            dashes += phrase.at(i);
        }
    }
    return dashes;
}

string updateUnsolved(string phrase, string unsolved, char guess)
{
    double len;
    string dashes;

    len = phrase.length();
    dashes = unsolved;

    //PROCESSING: Will check every letter to see if it should be replaced
    //            the guessed letter based on the word
    for(int i = 0; i < len; i++)
    {
        if(tolower(phrase.at(i)) == guess)
            dashes.at(i) = phrase.at(i);
    }
    return dashes;

}

char getGuess(string prevGuesses)
{
    char guess;
    bool val;

    //Boolean which will be used to continue to ask for input
    val = false;

    //INPUT: Takes in the guessed character and stores it in guess
    cin >> guess;

    //PROCESSING: Will return the guessed letter if it is in the alphabet
    //            and cannot be found in the previous guesses string
    if(prevGuesses.find(guess) == -1)
    {
        if(isalpha(guess))
            if(islower(guess))
                return guess;
            else
                val = true;
        else
            val = true;
    }
    else
        val = true;

    //PROCESSING: Will contintue to ask for input if val is true
    while(val)
    {
        //OUTPUT & INPUT: Prompt the user for a new guess and store it
        cout << endl << "Invalid guess! Please re-enter a guess: ";
        cin >> guess;

        //PROCESSING: Once again test for the same requirements as above
        if(prevGuesses.find(guess) == -1)
        {
            if(isalpha(guess))
                if(islower(guess))
                    return guess;
        }
    }
}

