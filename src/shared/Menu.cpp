#include "Menu.hpp"
#include <iostream>
#include <string>
#include <fstream>   
#include <cstdio>    

int Menu::readChoice() const {
    std::string line;
    if (!std::getline(std::cin, line))
        return 0;                    
    try {
        return std::stoi(line);
    } catch (...) {
        return -1;                   
    }
}


void Menu::saveState(int screen) const {
    if (screen == 0) {
        std::remove("save.txt");
        return;
    }
    {
        std::ofstream f("save.tmp", std::ios::trunc);
        if (!f) return;
        f << screen << "\n";
    }
    std::remove("save.txt");
    std::rename("save.tmp", "save.txt");
}


int Menu::loadState() const {
    std::ifstream f("save.txt");
    int screen = 0;
    if (!f || !(f >> screen)) return 0;
    if (screen != 1 && screen != 2) return 0;
    return screen;
}

    #if 0
    std::cout << "Le menu de l admin sera appelé ici\n";
    #endif

void Menu::run() {
    bool running = true;
    int resume = loadState();   // SAVE

    while (running) {
        int choice;                                
        if (resume != 0) {                          
            choice = resume;                         
            resume = 0;                              
        } else {                                     
            std::cout << "\nWelcome to The Venue.\n";
            std::cout << "  1  Browse the programme\n";
            std::cout << "  2  Book seats\n";
            std::cout << "  3  Administration\n";
            std::cout << "  4  Quit\n";
            std::cout << "\nYour choice: ";
            choice = readChoice();                   
        }                                            

        switch (choice) {                            

            
            case 1: {
                saveState(1);                        
                bool browsing = true;
                while (browsing) {
                    std::cout << "\nBrowse the program\n";
                    std::cout << "  1  Show all events\n";
                    std::cout << "  2  Find by title \n";
                    std::cout << "  0  Cancel\n";
                    std::cout << "\nYour choice: ";

                    switch (readChoice()) {
                        case 1:
                            std::cout <<"fonction qui affiche tout les évènements sera appelé\n";
                            break;
                        case 2: {
                            std::cout << "Event number (0 to cancel): ";
                            int n = readChoice();
                            if (n == 0) break;
                            #if 0
                            std::cin<< 
                            #endif
                            std::cout << "la fonction qui affiche les details de l evenement sera appele ici\n";
                            break;
                        }
                        case 0:
                            browsing = false;
                            break;
                        default:
                            std::cout << "Invalid choice.\n";
                            break;
                    }
                }
                saveState(0);                        
                break;
            }

            
            case 2: {
                saveState(2);                        
                bool booking = true;
                while (booking) {
                    std::cout << "\nBook seats\n";
                    std::cout << "  1  Choose an event and book\n";
                    std::cout << "  2  Cancel a booking\n";
                    std::cout << "  3  Show my bookings\n";
                    std::cout << "  0  Cancel\n";
                    std::cout << "\nYour choice: ";

                    switch (readChoice()) {
                        case 1: {
                            std::cout << "Event number (0 to cancel): ";
                            int eventNumber = readChoice();
                            if (eventNumber == 0) break;

                            std::cout << "Number of seats (0 to cancel): ";
                            int seats = readChoice();
                            if (seats == 0) break;

                            std::cout << "Client name: ";
                            std::string name;
                            std::getline(std::cin, name);

                            std::cout << "Les fonctions de verification et de reservation seront appelées  ici \n";
                            break;
                        }
                        case 2:
                            std::cout << "la fonction qui effectue l'annulation de la réservationn sera appelée ici\n";
                            break;
                        case 3:
                            std::cout << "la fonction qui affiche les réservations sera appelée ici\n";
                            break;
                        case 0:
                            booking = false;
                            break;
                        default:
                            std::cout << "Invalid choice.\n";
                            break;
                    }
                }
                saveState(0);                        
                break;
            }

            
            case 3:
            std::cout<<" appele la fonction de l'admin";
                break;

            
            case 0:
            case 4:
                running = false;
                break;

            default:
                std::cout << "Invalid choice.\n";
                break;
        }
    }
}