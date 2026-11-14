
#include "shared/Program.hpp"
#include "shared/Admin.hpp"
#include "shared/Menu.hpp"
#include <iostream>
#include <memory>
#include <exception>
#include "shared/Concert.hpp"
#include "shared/Play.hpp"
#include "shared/Screening.hpp"
#include "shared/Room.hpp"
#include "shared/Schedule.hpp"

int main()
{
    try
    {
        Program program;

        Room mainHall("Main hall", 400);
        Room studio("Studio", 150);

        program.addRoom(mainHall);
        program.addRoom(studio);


        std::unique_ptr<Event> concert =
            std::make_unique<Concert>(
                "Malandain Trio",
                18.00,
                100,
                "Jazz",
                "Airelle Besson, Lionel Suarez, Emile Parisien",
                "18:00"
            );

        std::unique_ptr<Schedule> concertSchedule =
            std::make_unique<Schedule>(
                std::move(concert),
                mainHall,
                2026, 12, 15,
                19, 0,
                400
            );

        program.addSchedule(std::move(concertSchedule));

        std::unique_ptr<Event> play =
            std::make_unique<Play>(
                "The Chalk Circle",
                14.0,
                120,
                "after act two"
            );

        std::unique_ptr<Schedule> playSchedule =
            std::make_unique<Schedule>(
                std::move(play),
                studio,
                2026, 12, 16,
                18, 0,
                150
            );

        program.addSchedule(std::move(playSchedule));

        std::unique_ptr<Event> screening =
            std::make_unique<Screening>(
                "Wild Nights",
                7.50,
                90,
                "not recommended under 12"
            );

        std::unique_ptr<Schedule> screeningSchedule =
            std::make_unique<Schedule>(
                std::move(screening),
                mainHall,
                2026, 12, 17,
                20, 0,
                400
            );

        program.addSchedule(std::move(screeningSchedule));

        Admin admin("admin", "admin59");

        Menu menu(program, admin);

        menu.run();
    }
    catch (const std::exception& error)
    {
        std::cerr << "An error occurred: "
                  << error.what() <<"\n";

        return 1;
    }

    return 0;
}