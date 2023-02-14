// Name: Chonglin Zhang
// Class : CS320
// Instructor : Shawn Healey
// Date : 4 - 21 - 2021
// Program: Metalhead

/*

Method:

1. Initializes the guitar to EADGBE tuning and a 21 fret guitar
Guitar ()

2. Copy constructor (if the guitar allocates heap memory)
Guitar(const Guitar& board)

3. Private field
private: unsigned char numberOfFrets;

4. Sets the corresponding private field and verifies the input is between 1 and 24
bool setFretBoardLength(const unsigned char numFrets);

Returns the corresponding frequency in Hz for the given string and fret. 
Unlike array indices, these use natural numbers, so the low E string shall be 
string 1 and the high E string shall be 6
unsigned double pitchAt(const unsigned char &stringNumber, const unsigned char &fret);

5. Given the pitch, the method shall return a std::pair object with the string/fret combination 
that comes closest to producing that pitch. There may be multiple solutions. The function 
shall return the first it identifies
std::pair<unsigned char, unsigned char> getStringAndFret( double pitch );

6. Changes the tuning for an individual string.
void tuneString(unsigned char& string, const double& pitch )

*/

#include <iostream>
#include <utility>
#include <cmath>


class Guitar {

private: char numberOfFrets;
private: double guitarStr[6];

public:

    Guitar() {
        numberOfFrets = 21;
        guitarStr[0] = 82.41; //low E
        guitarStr[1] = 110; //A
        guitarStr[2] = 146.8; //D
        guitarStr[3] = 196; //G
        guitarStr[4] = 246.9; //B
        guitarStr[5] = 329.6; //high E
    }

    Guitar(const Guitar& board) {
        numberOfFrets = board.numberOfFrets;
        guitarStr[0] = board.guitarStr[0]; //low E
        guitarStr[1] = board.guitarStr[1]; //A
        guitarStr[2] = board.guitarStr[2]; //D
        guitarStr[3] = board.guitarStr[3]; //G
        guitarStr[4] = board.guitarStr[4]; //B
        guitarStr[5] = board.guitarStr[5]; //high E
    }

    bool setFretBoardLength(const unsigned char numFrets) {
        if (((int)numFrets >= 1) && ((int)numFrets <= 24)) {
            numberOfFrets = numFrets;
            std::cout << "The number of frets: " << (int)numberOfFrets;
            return true;
        }
        else {
            std::cout << "Out of bounds.";
            return false;
        }
    }

    double pitchAt(const unsigned char& stringNumber, const unsigned char& fret) {
        if (((int)stringNumber < 1 || (int)stringNumber > 6) || ((int)fret < 1 || (int)fret > numberOfFrets)) {
            std::cout << "String or Fret number is out of bounds.\n";
            return NULL;
        }

        double pitch = guitarStr[(int)stringNumber - 1];
        double newPitch = pitch * (double)pow(2, ((double)fret / 12));
        return newPitch;
    }

    std::pair<unsigned char, unsigned char> getStringAndFret(double pitch) {
        double minDif = pitch;
        unsigned char matchStr = NULL;
        unsigned char matchFret = NULL;
        for (int i = 1; i <= 6; i++) {
            for (int j = 1; j < (int)numberOfFrets; j++) {
                double tempPitch = (guitarStr[i - 1] * (double)pow(2, ((double)j / 12)));
                double diff = abs(pitch - tempPitch);
                if (diff < minDif) {
                    minDif = diff;
                    matchStr = (char)i;
                    matchFret = (char)j;
                }
            }
        }
        if ((matchStr == NULL) || (matchFret == NULL)) {
            std::cout << "A combination was not found \n";
        }
        else {
            std::cout << "\nThe most accurate string is " << (int)matchStr << " (" << getStringLetter((int)matchStr) << ") and the most accurate fret is " << (int)matchFret << ". \n\n";
        }
        return std::make_pair(matchStr, matchFret);
    }

    void tuneString(const unsigned char& string, const double& pitch) {
        std::cout << "This string's frequency was at " << guitarStr[(int)string - 1] << " and now it is at ";
        guitarStr[(int)string - 1] = pitch;
        std::cout << guitarStr[(int)string - 1] << ". \n";
    }


    int getNumberOfFrets() {
        return (int)numberOfFrets;
    }

    void getFreq() {
        for (int i = 0; i < (sizeof(guitarStr) / sizeof(guitarStr[0])); i++) {
            if (i == 5) {
                std::cout << guitarStr[i];
                break;
            }
            std::cout << guitarStr[i] << ", ";
        }
    }

    std::string getStringLetter(int numberStr) {
        if (numberStr == 1)
            return "low E";
        else if (numberStr == 2)
            return "A";
        else if (numberStr == 3)
            return "D";
        else if (numberStr == 4)
            return "G";
        else if (numberStr == 5)
            return "B";
        else
            return "high E";
    }

};

int main(int argc, const char* argv[]) {

    Guitar board = Guitar();
    Guitar gibson = Guitar(board); 
    int choice = NULL;

    std::cout << "Enter the number of option 1 to 5: \n\n";
    while (choice != 5) {
        std::cout << "Current Guitar List\n";
        std::cout << "\nNumber of frets: " << board.getNumberOfFrets() << "\n";
        std::cout << "\nFrequencies of EADGBE string in order: ";
        board.getFreq();
        std::cout << "\n";
        std::cout << "\n1. Change and enter the fret board length \n";
        std::cout << "2. Find a pitch with a given string and fret \n";
        std::cout << "3. Enter a given pitch to find the most accurate string and fret combination \n";
        std::cout << "4. Change the tuning for an individual string \n";
        std::cout << "5. Exit \n";
        std::cout << "Enter the option:";
        std::cin >> choice;

        if (choice == 1) {
            int newFrets;
            std::cout << "\n Enter the number of frets (1 - 24): ";
            std::cin >> newFrets;
            board.setFretBoardLength(newFrets);
            std::cout << "\n\n";
        }
        else if (choice == 2) {
            int string;
            int fret;
            std::cout << "\nEnter the string (1 = low E, 2 = A, 3 = D, 4 = G, 5 = B, 6 = high E): ";
            std::cin >> string;
            std::cout << "\nEnter the fret (1 - " << board.getNumberOfFrets() << "): ";
            std::cin >> fret;
            std::cout << "\nThe pitch at this string or fret combination is " << board.pitchAt(string, fret) << " hz.\n\n";
        }
        else if (choice == 3) {
            double pitch;
            std::cout << "\nEnter the pitch: ";
            std::cin >> pitch;
            board.getStringAndFret(pitch);
        }
        else if (choice == 4) {
            int string;
            double pitch;
            std::cout << "\nEnter the string that you want to change (1 = low E, 2 = A, 3 = D, 4 = G, 5 = B, 6 = high E): ";
            std::cin >> string;
            std::cout << "\nEnter the pitch from the board: ";
            std::cin >> pitch;
            board.tuneString(string, pitch);
        }
        else if (choice == 5) {
            std::cout << "\nGoodbye.\n";
            choice = 5;
        }
        else {
            std::cout << "\nThat is not a choice.";
            choice = 5;
            std::cout << "\nGoodbye.\n";
        }

    }
    return 0;
}