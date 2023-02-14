//CS320-01: Nicolas Artates
//CS320-02: Chonglin Zhang
//CS320-02: Vishwesh Gobre
//Password guess program

#include <string>
#include <iostream>
#include <list>
#include <iterator>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <thread>
#include <cctype>
#include <clocale>

using namespace std;

class UniqueToken {
private:
    int numOfTokens = 0;
public:

    std::list<string> tokenDetector(string input) {
        transform(input.begin(),input.end(), input.begin(), ::tolower);
        for(int i = 0, newLength = input.size(); i < newLength; i++) {
            if (ispunct(input[i])) {
                if(input[i] == '-'){
                    continue;
                }
                input.erase(i--, 1);
                newLength = input.size();
            }
        }
        istringstream ss(input);
        string token;
        
        std::list<string> tokens;
        while (ss >> token){
            tokens.push_back(token);
            numOfTokens++;
        }
        for (auto const&i: tokens) {
            std::cout << i << std::endl;
        }
        return tokens;
    }
};

class PasswordGenerator
{
private:
    int iteration;
    int pwdLength;
    int sizeOfTokens;
    int numOfSequence;
    list<string> TokenList;
    list<string> sequence;
public:

    PasswordGenerator(list<string> inputList)
    {
        TokenList = inputList;
        sizeOfTokens = inputList.size();
        iteration = 0;
        numOfSequence = 0;
    }

    //get the random password from the input file
    string getRandomPassword(int numWords)
    {
        string newPwd;
        int passwordUsed[100000000];

        for (int i = 0; i < numWords; i++) {
            bool usedPwd = 0;
            int randomPassword = rand() % TokenList.size();
            list<string>::iterator it = TokenList.begin();
            
            //check password use before or not, and make sure will not get the same password
            for (int j = 0; j < i; j++) {
                if (randomPassword == passwordUsed[j]) {
                    usedPwd = 1;
                    i--;
                }
            }
            // password does't use, and get a new password
            if (!usedPwd) {
                advance(it, randomPassword);
                string tokens = *it;
                if (i != 0) { newPwd.append(" "); }
                newPwd.append(tokens);
                passwordUsed[i] = randomPassword;
            }
        }
        return newPwd;
    }
    void setIterationLength(int numWords)
    {
        pwdLength = numWords;
    }

    string next()
    {
        if (hasNext()) {
            list<string>::iterator it = sequence.begin();
            advance(it, iteration);
            string password = *it;
            iteration++;
            return password;
        }
        else { 
            // return " ";
            return "Error"; 
        }
    }
    bool hasNext()
    {
        if (iteration != numOfSequence) {
            return 1;
        }
        else {
            return 0;
        }
    }
};

class PasswordGuesser {

private:
    int numOfTokens; //number of tokens per password
    std::string password;

    //private method to set the number of tokens per password
    void setNumOfTokens(int givenTokenAmount) {
        numOfTokens = givenTokenAmount;
    }

    void setPassword(std::string pw) {
        password = pw;
    }


public:
    //default constructor
    PasswordGuesser(int numOfTokens, std::list<std::string> tokens) {
        setNumOfTokens(numOfTokens);

        //creates password generator object for making the random password to find as well as to guess with
        PasswordGenerator pg = PasswordGenerator(tokens);
        setPassword(pg.getRandomPassword(numOfTokens)); //gets a random password (may want to change the parameters of this one)
        guessPassword(password, pg);

    }

    //method that does the password checking
    void guessPassword(std::string password, PasswordGenerator pg) {
        //generated password for comparison to the password given/already generated
        
        std::string randPass;
        std::string nextPass;
        int randomCount = 0;
        int iteratorCount = 0;



        //creates the thread objects, I think the second arg is where the return val of the functions goes but Im not quite sure
        std::thread random(pg.getRandomPassword(numOfTokens), randPass);
        std::thread iterator(pg.next(), nextPass);

        //this should handle the two threads and check against password
        //probably need to switch this to the observer design pattern but thisis a placeholder
        while (randPass != password && nextPass != nextPass && pg.hasNext()) {
            random.join();
            //randPass = pg.getRandomPassword(numOfTokens);
            randomCount++;
            iterator.join();
            //nextPass = pg.Next();
            iteratorCount++;

        }
        std::cout << "The password guesser took " << randomCount << " of random guesses" << std::endl;
        std::cout << "The password guesser took " << iteratorCount << " of iterations to find the password." << std::endl;
    }

}; 

int main(int argc, char* argv[])
{
    //reading in the file and checking for errors.
    fstream openFile;
    if (argc < 2 ){
        cout << "No file name detected." << endl;
        cout << "Please give a file name after the launch command." << endl;
        return 1;
    } 
    else {
    string fileName = argv[1];
    openFile.open(fileName);
    }
    if (!openFile.good()) {
        cout << "The file was not detected in the folder." << endl;
        cout << "Please make sure that the file is in the same folder as the program." << endl;
        return 1;
    }
    else if (!openFile.is_open()) {
        cout << "The file could not open." << endl;
        cout << "Please try again." << endl;
        return 1;
    } 
    else {
        //detect the token

        //password generator with 1 to 5 tokens, users only get one random password each time

        //password guess
        return 0;
    }
}
