#include "shared/Menu.hpp"
#include "shared/Colors.hpp"
#include "shared/statistics.hpp"
#include "shared/Concert.hpp"
#include "shared/Play.hpp"
#include "shared/Screening.hpp"
#include "shared/Persistence.hpp"
#include <memory>
#include <utility>
#include <iostream>
#include <string>
#include <vector>

bool Menu::Cancel(const std::string &text) const
{
    return text == "CANCEL" || text == "cancel" || text == "Cancel";
}

bool Menu::YesNo(const std::string &question) const
{
    std::string answer;

    while (true)
    {
        std::cout << question;
        std::getline(std::cin, answer);

        if (answer == "Y" || answer == "y")
        {
            return true;
        }

        if (answer == "N" || answer == "n")
        {
            return false;
        }

        std::cout << "Please enter Y or N.\n";
    }
}

Menu::Menu(Program &program, Admin &admin)
    : program(program), admin(admin)
{
}

int Menu::readChoice() const
{
    std::string line;

    if (!std::getline(std::cin, line))
    {
        return -1;
    }

    try
    {
        return std::stoi(line);
    }
    catch (...)
    {
        return -1;
    }
}

void Menu::run()
{
    bool running = true;

    Persistence persistence;
    persistence.loadfile("data.bin", program);

    while (running)
    {

        std::cout << Colors::TITLE << "\n__________ THE VENUE __________\n" << Colors::RESET;
        std::cout << "1. Browse programme\n";
        std::cout << "2. Book seats\n";
        std::cout << "3. Administration\n";
        std::cout << "4. Quit\n";
        std::cout << "Your choice: \n";

        int choice = readChoice();

        switch (choice)
        {

        case 1:
            browseProgram();
            break;

        case 2:
            bookSeats();
            break;

        case 3:
            adminMenu();
            break;

        case 4:
            running = false;
            std::cout << Colors::GREEN << "Goodbye!\n" << Colors::RESET;
            break;

        default:
            std::cout << Colors::RED << "Invalid choice. Please try again.\n"  << Colors::RESET;
            break;
        }
    }
}

void Menu::browseProgram() const
{
    bool browsing = true;

    while (browsing)
    {
        std::cout << Colors::BROWSE << "\n__________ BROWSE PROGRAMME __________\n" << Colors::RESET;
        std::cout << "1. Show all events\n";
        std::cout << "2. Find an event by title\n";
        std::cout << "0. Back\n";
        std::cout << "Your choice: \n";

        int choice = readChoice();

        switch (choice)
        {
        case 1:
            program.displayAll();
            break;

        case 2:
        {
            bool searching = true;

            while (searching)
            {
                std::string title;

                std::cout << "\nEnter event title (or CANCEL): \n";
                std::getline(std::cin, title);

                if (Cancel(title))
                {
                    searching = false;
                    continue;
                }

                if (program.displayByTitle(title))
                {
                    searching = YesNo("\nSearch another event? (Y/N): ");
                }
                else
                {
                    std::cout << Colors::RED << "\nEvent not found.\n" << Colors::RESET;
                    searching = YesNo("Try again? (Y/N): ");
                }
            }

            break;
        }

        case 0:
            browsing = false;
            break;

        default:
            std::cout << Colors::RED << "Invalid choice. Please try again.\n" << Colors::RESET;
            break;
        }
    }
}

void Menu::bookSeats()
{
    Persistence persistence;
    bool booking = true;

    while (booking)
    {

        std::cout << Colors::BOOKING << "\n__________ BOOK SEATS __________\n" << Colors::RESET;

        program.displayAll();

        std::cout << "\nEnter event number (0 to cancel): ";

        int eventNumber = readChoice();

        if (eventNumber == 0)
        {
            booking = false;
            continue;
        }

        if (eventNumber < 1 ||
            eventNumber > program.getScheduleCount())
        {

            std::cout << Colors::RED << "Invalid event number.\n" << Colors::RESET;
            std::cout << "1. Try again\n";
            std::cout << "0. Cancel\n";

            if (readChoice() == 0)
            {
                booking = false;
            }

            continue;
        }

        std::string clientName;

        std::cout << "Enter your name (or CANCEL): ";
        std::getline(std::cin, clientName);

        if (clientName == "CANCEL" || clientName == "cancel")
        {
            continue;
        }

        std::cout << "Enter number of seats (0 to cancel): ";

        int seats = readChoice();

        if (seats == 0)
        {
            continue;
        }

        if (seats < 0)
        {
            std::cout << Colors::RED << "Invalid number of seats.\n" << Colors::RESET;
            continue;
        }

        if (program.book(eventNumber - 1, clientName, seats))
        {
            std::cout << Colors::GREEN << "\nBooking successful!\n" << Colors::RESET;
            persistence.savefile("data.bin", program);
        }
        else
        {
            std::cout << Colors::RED << "\nBooking failed.\n";
            std::cout << "The event may be sold out or the number "
                         "of seats may be unavailable.\n" << Colors::RESET;
        }

        std::cout << "\n1. Make another booking\n";
        std::cout << "0. Back to main menu\n";

        if (readChoice() == 0)
        {
            booking = false;
        }
    }
}

void Menu::adminMenu()
{
    Persistence persistence;
    bool authenticated = false;

    while (!authenticated)
    {

        std::cout << Colors::ADMIN << "\n__________ ADMIN LOGIN __________\n" << Colors::RESET;
        std::cout << "Admin login (or CANCEL): ";

        std::string login;
        std::getline(std::cin, login);

        if (login == "CANCEL" || login == "cancel")
        {
            return;
        }

        std::cout << "Password: ";

        std::string password;
        std::getline(std::cin, password);

        if (login == admin.getLogin() && admin.logIn(password))
        {
            authenticated = true;
            std::cout << Colors::GREEN << "\nLogin successful!\n" << Colors::RESET;
        }
        else
        {
            std::cout << Colors::RED << "\nIncorrect login or password.\n" << Colors::RESET;
            std::cout << "1. Try again\n";
            std::cout << "0. Cancel\n";

            if (readChoice() == 0)
            {
                return;
            }
        }
    }

    bool managing = true;

    while (managing)
    {

        std::cout << Colors::ADMIN << "\n__________ ADMINISTRATION __________\n" << Colors::RESET;
        std::cout << "1. Add a room\n";
        std::cout << "2. Add an event\n";
        std::cout << "3. Display all rooms\n";
        std::cout << "4. Find a room\n";
        std::cout << "5. Show reservations\n";
        std::cout << "6. Display busiest rooms\n";
        std::cout << "7. Total revenue\n";
        std::cout << "8. Statistics\n";
        std::cout << "9. Log out\n";
        std::cout << "Your choice: \n";

        int choice = readChoice();

        switch (choice)
        {

        case 1:
        {
            std::string name;
            int capacity;

            std::cout << "Room name: ";
            std::getline(std::cin, name);

            if (Cancel(name))
                break;

            if (program.findRoom(name) != nullptr)
            {
                std::cout << Colors::RED << "This room already exists.\n" << Colors::RESET;
                break;
            }

            std::cout << "Room capacity: ";
            capacity = readChoice();

            if (capacity <= 0)
            {
                std::cout << Colors::RED << "Invalid capacity.\n" << Colors::RESET;
                break;
            }

            Room room(name, capacity);
            program.addRoom(room);
            persistence.savefile("data.bin", program);

            std::cout << Colors::GREEN << "Room added successfully.\n" << Colors::RESET;
            break;
        }

        case 2:
        {
            std::string roomName;

            std::cout << "Room name: ";
            std::getline(std::cin, roomName);

            if (Cancel(roomName))
                break;

            const Room *room = program.findRoom(roomName);

            if (room == nullptr)
            {
                std::cout << Colors::RED << "Room not found.\n" << Colors::RESET;
                break;
            }

            std::cout << "\n1. Concert\n";
            std::cout << "2. Play\n";
            std::cout << "3. Screening\n";
            std::cout << "Your choice: \n";

            int type = readChoice();

            if (type < 1 || type > 3)
            {
                std::cout << Colors::RED << "Invalid event type.\n" << Colors::RESET;
                break;
            }

            std::unique_ptr<Event> event;

            if (type == 1)
            {
                std::string title, style, lineUp, soundCheck;
                double price;
                int duration;

                std::cout << "Title: ";
                std::getline(std::cin, title);

                std::cout << "Price: ";
                std::cin >> price;
                std::cin.ignore();

                std::cout << "Duration: ";
                duration = readChoice();

                std::cout << "Style: ";
                std::getline(std::cin, style);

                std::cout << "Line-up: ";
                std::getline(std::cin, lineUp);

                std::cout << "Sound check: ";
                std::getline(std::cin, soundCheck);

                event = std::make_unique<Concert>(
                    title, price, duration, style, lineUp, soundCheck);
            }

            else if (type == 2)
            {
                std::string title, intervalInfo;
                double price;
                int duration;

                std::cout << "Title: ";
                std::getline(std::cin, title);

                std::cout << "Price: ";
                std::cin >> price;
                std::cin.ignore();

                std::cout << "Duration: ";
                duration = readChoice();

                std::cout << "Interval information: ";
                std::getline(std::cin, intervalInfo);

                event = std::make_unique<Play>(
                    title, price, duration, intervalInfo);
            }

            else
            {
                std::string title, rating;
                double price;
                int duration;

                std::cout << "Title: ";
                std::getline(std::cin, title);

                std::cout << "Price: ";
                std::cin >> price;
                std::cin.ignore();

                std::cout << "Duration: ";
                duration = readChoice();

                std::cout << "Rating: ";
                std::getline(std::cin, rating);

                event = std::make_unique<Screening>(
                    title, price, duration, rating);
            }

            int year, month, day, hour, minute, seats;

            std::cout << "Year: ";
            year = readChoice();

            std::cout << "Month: ";
            month = readChoice();

            std::cout << "Day: ";
            day = readChoice();

            std::cout << "Start hour: ";
            hour = readChoice();

            std::cout << "Start minute: ";
            minute = readChoice();

            std::cout << "Number of seats for sale: ";
            seats = readChoice();

            if (year < 1 || month < 1 || month > 12 ||
                day < 1 || day > 31 || hour < 0 || hour > 23 ||
                minute < 0 || minute > 59 ||
                seats <= 0 || seats > room->getCapacity())
            {
                std::cout << Colors::RED << "Invalid schedule information.\n" << Colors::RESET;
                break;
            }

            std::unique_ptr<Schedule> schedule =
                std::make_unique<Schedule>(
                    std::move(event),
                    *room,
                    year, month, day,
                    hour, minute,
                    seats);

            if (program.addSchedule(std::move(schedule)))
            {
                persistence.savefile("data.bin", program);
                std::cout << Colors::GREEN << "Event added successfully.\n" << Colors::RESET;
            }
            else
                std::cout << Colors::RED << "Unable to add event. Schedule conflict.\n" << Colors::RESET;

            break;
        }

        case 3:
            program.displayRooms();
            break;

        case 4:
        {
            bool searching = true;

            while (searching)
            {
                std::string name;

                std::cout << "\nEnter room name (or CANCEL): ";
                std::getline(std::cin, name);

                if (Cancel(name))
                {
                    searching = false;
                    continue;
                }

                const Room *room = program.findRoom(name);

                if (room != nullptr)
                {
                    std::cout << "Room found: " << Colors::ROOM << room->getName() << "\n" << Colors::RESET;

                    searching = YesNo("\nSearch another room? (Y/N): ");
                }
                else
                {
                    std::cout << Colors::RED << "Room not found.\n" << Colors::RESET;

                    searching = YesNo("Try again? (Y/N): ");
                }
            }

            break;
        }

        case 5:
        {

            if (program.getScheduleCount() == 0)
            {
                std::cout << Colors::RED << "No event scheduled.\n" << Colors::RESET;
            }
            else
            {
                for (int i = 0; i < program.getScheduleCount(); i++)
                {
                    std::cout << "\n";
                    program.displayBookings(i);
                }
            }

            break;
        }

        case 6:
            program.displayBusiestRooms();
            break;

        case 7:
            std::cout << "Total revenue: " << Colors::PRICE << program.totalRevenue() << " EUR\n" << Colors::RESET;
            break;

        case 8:
            statistics();
            break;

        case 9:
            admin.logOut();
            managing = false;
            std::cout << Colors::GREEN << "You have been logged out.\n" << Colors::RESET;
            break;

        default:
            std::cout << Colors::RED << "Invalid choice. Please try again.\n" << Colors::RESET;
            break;
        }
    }
}

void Menu::statistics() const
{
    bool viewing = true;

    while (viewing)
    {
        std::cout << Colors::STATISTICS << "\n__________ STATISTICS __________\n" << Colors::RESET;
        std::cout << "1. Event prices\n";
        std::cout << "2. Event attendances\n";
        std::cout << "3. Event durations\n";
        std::cout << "0. Back\n";
        std::cout << "Your choice: \n";

        int choice = readChoice();

        switch (choice)
        {
        case 1:
        {
            std::vector<double> values = program.getPrices();
            std::vector<std::string> titles = program.getTitles();

            if (values.empty())
            {
                std::cout << Colors::RED << "No events available.\n" << Colors::RESET;
                break;
            }

            Statistics<double> stats;

            for (std::size_t i = 0; i < values.size(); i++)
            {
                stats.add(values[i]);
            }

            std::cout << Colors::STATISTICS << "\nHIGHEST PRICE:\n" << Colors::RESET;
            for (std::size_t i = 0; i < values.size(); i++)
            {
                if (values[i] == stats.largest())
                {
                    std::cout << titles[i] << " - " << values[i] << " EUR\n";
                }
            }

            std::cout << Colors::STATISTICS << "\nLOWEST PRICE:\n" << Colors::RESET;
            for (std::size_t i = 0; i < values.size(); i++)
            {
                if (values[i] == stats.smallest())
                {
                    std::cout << titles[i] << " - " << values[i] << " EUR\n";
                }
            }

            std::cout << Colors::STATISTICS << "\nAVERAGE PRICE: " << Colors::RESET
                      << stats.average() << " EUR\n";

            break;
        }

        case 2:
        {
            std::vector<int> values = program.getAttendances();
            std::vector<std::string> titles = program.getTitles();

            if (values.empty())
            {
                std::cout << Colors::RED << "No events available.\n" << Colors::RESET;
                break;
            }

            Statistics<int> stats;

            for (std::size_t i = 0; i < values.size(); i++)
            {
                stats.add(values[i]);
            }

            std::cout << Colors::STATISTICS << "\nHIGHEST ATTENDANCE:\n" << Colors::RESET;
            for (std::size_t i = 0; i < values.size(); i++)
            {
                if (values[i] == stats.largest())
                {
                    std::cout << titles[i] << " - " << values[i] << " seats\n";
                }
            }

            std::cout << Colors::STATISTICS << "\nLOWEST ATTENDANCE:\n" << Colors::RESET;
            for (std::size_t i = 0; i < values.size(); i++)
            {
                if (values[i] == stats.smallest())
                {
                    std::cout << titles[i] << " - " << values[i] << " seats\n";
                }
            }

            std::cout << Colors::STATISTICS << "\nAVERAGE ATTENDANCE: " << Colors::RESET
                      << stats.average() << " seats\n";

            break;
        }

        case 3:
        {
            std::vector<int> values = program.getDurations();
            std::vector<std::string> titles = program.getTitles();

            if (values.empty())
            {
                std::cout << Colors::RED << "No events available.\n" << Colors::RESET;
                break;
            }

            Statistics<int> stats;

            for (std::size_t i = 0; i < values.size(); i++)
            {
                stats.add(values[i]);
            }

            std::cout << Colors::STATISTICS << "\nLONGEST EVENT:\n" << Colors::RESET;
            for (std::size_t i = 0; i < values.size(); i++)
            {
                if (values[i] == stats.largest())
                {
                    std::cout << titles[i] << " - " << values[i] << " minutes\n";
                }
            }

            std::cout << Colors::STATISTICS << "\nSHORTEST EVENT:\n" << Colors::RESET;
            for (std::size_t i = 0; i < values.size(); i++)
            {
                if (values[i] == stats.smallest())
                {
                    std::cout << titles[i] << " - " << values[i] << " minutes\n";
                }
            }

            std::cout << Colors::STATISTICS << "\nAVERAGE DURATION: " << Colors::RESET
                      << stats.average() << " minutes\n";

            break;
        }

        case 0:
            viewing = false;
            break;

        default:
            std::cout << Colors::RED << "Invalid choice. Please try again.\n" << Colors::RESET;
            break;
        }
    }
}
