#include "RMS.h"
#include <iostream>
#include <limits>
#include <cctype>
#include <string>

static bool askYesNo(const std::string& prompt) {
    while (true) {
        std::cout << prompt << " (y/n): ";
        char c;
        if (!(std::cin >> c)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        if (c == 'y') return true;
        if (c == 'n') return false;
        std::cout << "Please enter 'y' or 'n'.\n";
    }
}

int main(int argc, char* argv[]) {
    RMS rms;
    int choice = -1;
    rms.PrintHello();
    while (choice != 0) {
        std::cout << "\n=== RMS Menu ===\n";
        std::cout << "1. Run RMS Checker\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter choice: ";
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                rms.GetTaskSet();
                rms.ComputeUtilFactor();

                bool ok = rms.CheckSceduleGuarantee();
                if (ok) {
                    std::cout << "Provided task set IS schedulable by RM\n";
                    break;
                } else if(rms.isCheckable){
                    std::cout << "Provided schedule is NOT GUARANTEED to be schedulable by RM\n";
                }else {
                    std::cout << "Provided task set is NOT schedulable by RM\n";
                }

                if (askYesNo("Run Response Time Analysis?")) {
                    rms.SortAndAssignPriOrder();
                    if (rms.ResponseTimeAnalysis()) {
                        std::cout << "Response Time Analysis: PASS\n";
                        std::cout << "Provided task set IS schedulable by RM\n";
                    } else {
                        std::cout << "Response Time Analysis: FAIL\n";
                        std::cout << "Provided task set is NOT schedulable by RM\n";
                    }
                } else {
                    std::cout << "Skipped sorting and response time analysis.\n";
                }
                break;
            }
            case 0:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice.\n";
                break;
        }
    }

    return EXIT_SUCCESS;
}