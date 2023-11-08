
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

const std::string RED_TEXT = "\033[31m"; // Red text color
const std::string BLACK_TEXT = "\033[30m"; // Black text color
const std::string RESET_COLOR = "\033[0m"; // Reset text color to default

void displayHandRankings() {
    // Set a fixed width for card strings to ensure alignment
    const int cardWidth = 6;
    const int rankWidth = 16;

    cout << "================ Hand Rankings ================" << endl;
    cout << "            (Strongest to weakest)" << endl;
    cout << right << setw(rankWidth) << "Royal Flush:" << "  " << BLACK_TEXT << left << setw(cardWidth) << "AS" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "KS" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "QS" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "JS" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "10S" << RESET_COLOR << endl;
    cout << right << setw(rankWidth) << "Straight Flush:" << "  " << RED_TEXT << left << setw(cardWidth) << "8H" << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << "7H" << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << "6H" << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << "5H" << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << "4H" << RESET_COLOR << endl;
    cout << right << setw(rankWidth) << "Four of a Kind:" << "  " << BLACK_TEXT << left << setw(cardWidth) << "7C" << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << "7D" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "7S" << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << "7H" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "3C" << RESET_COLOR << endl;
    cout << right << setw(rankWidth) << "Full House:" << "  " << RED_TEXT << left << setw(cardWidth) << "QH" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "QC" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "QS" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "4S" << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << "4H" << RESET_COLOR << endl;
    cout << right << setw(rankWidth) << "Flush:" << "  " << BLACK_TEXT << left << setw(cardWidth) << "4C" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "JS" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "AS" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "7C" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "9C" << RESET_COLOR << endl;
    cout << right << setw(rankWidth) << "Straight:" << "  " << BLACK_TEXT << left << setw(cardWidth) << "QC" << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << "JD" << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << "10H" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "9C" << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << "3H" << RESET_COLOR << endl;
    cout << right << setw(rankWidth) << "Three of a Kind:" << "  " << RED_TEXT << left << setw(cardWidth) << "KH" << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << "KD" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "KS" << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << "10H" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "7S" << RESET_COLOR << endl;
    cout << right << setw(rankWidth) << "Two Pair:" << "  " << BLACK_TEXT << left << setw(cardWidth) << "8S" << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << "8H" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "5S" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "5C" << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << "3H" << RESET_COLOR << endl;
    cout << right << setw(rankWidth) << "One Pair:" << "  " << BLACK_TEXT << left << setw(cardWidth) << "10C" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "10S" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "7C" << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << "4H" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "2C" << RESET_COLOR << endl;
    cout << right << setw(rankWidth) << "High Card:" << "  " << RED_TEXT << left << setw(cardWidth) << "AH" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "QC" << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << "10H" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "7C" << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << "4D" << RESET_COLOR << endl;
    cout << "===============================================" << endl;
}



// ANSI escape codes for text color


int main() {
    displayHandRankings();
    return 0;
}

