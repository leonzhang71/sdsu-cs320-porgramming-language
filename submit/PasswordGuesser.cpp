#include <iostream>
#include <thread>
#include <list>

class PasswordGuesser{
    
    private:
        int numOfTokens; //number of tokens per password
        std::string password;

        //private method to set the number of tokens per password
        void setNumOfTokens(int givenTokenAmount){
            numOfTokens = givenTokenAmount;
        }

        void setPassword(std::string pw){
            password = pw;
        }

    
    public:
        //default constructor
        PasswordGuesser(int numOfTokens, std::list<std::string> tokens){
            setNumOfTokens(numOfTokens);
            
            //creates password generator object for making the random password to find as well as to guess with
            PasswordGenerator pg = new PasswordGenerator(numOfTokens);
            setPassword(pg.getRandomPassword(numOfTokens)); //gets a random password (may want to change the parameters of this one)
            guessPassword(password);

        }

        //method that does the password checking
        void guessPassword(std::string password){
            //generated password for comparison to the password given/already generated
            std::string randPass;
            std::string nextPass;
            int randomCount = 0;
            int iteratorCount = 0;

            
            //creates the thread objects, I think the second arg is where the return val of the functions goes but Im not quite sure
            std::thread random(pg.getRandomPassword(numOfTokens), randPass);
            std::thread iterator(pg.Next(), nextPass);
            
            //this should handle the two threads and check against password
            //probably need to switch this to the observer design pattern but thisis a placeholder
            while(randPass != password && nextPass != nextPass){
                random.join();
                randomCount++;
                iterator.join();
                iteratorCount++;

            }
            std::cout << "The password guesser took "  << randomCount <<" of random guesses" << std::endl;
            std::cout << "The password guesser took " << iteratorCount << " of iterations to find the password." <<std::endl;
        }

}