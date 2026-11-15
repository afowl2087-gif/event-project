# The Venue

C++ console application that replaces the paper organizer of a venue manager. It allows scheduling concerts, plays, and screenings in multiple rooms (without time conflicts), taking reservations (rejected when the room is full), answering the manager's questions (program by date, search by title, revenues, busiest rooms, statistics), and saving everything to a binary file.

Repository: https://github.com/afowl2087-gif/event-project.git
Authors: KRAMO Midelio and TAREGUE Guiliane


Installation and execution

## Windows

-To launch the application, simply double-click on planner.exe. 
-For run the unit tests, open a terminal (CMD or PowerShell) and go to the folder cd "the folder's address" (for example cd C:\Users\HP\Documents\event-project), then run this command:
```
.\tests\tests.exe
```

## macOS

-Open a terminal and navigate to the project folder: cd "the folder's address" (for example cd ~/Document/event-project)
-install cMake if you don't have it :
```
brew install cmake
```
-Make sure Apple's command-line developer tools are installed:
```
xcode-select --install
```

-If you want to run the unit tests, also install GoogleTest if you don't have it:
```
brew install googletest
```
-Configure and build the project:
```
cmake -S . -B build
cmake --build build
```
-Run the application:
```
./build/planner
```
-Run the test:
```
./build/tests
```

## Linux

-Open a terminal and navigate to the project folder: cd "the folder's address" (for example cd ~/Document/event-project)
-install cMake if you don't have it :
```
sudo apt update
sudo apt install build-essential cmake
```
-If you want to run the unit tests, also install GoogleTest if you don't have it:
```
sudo apt install libgtest-dev
```
-Configure and build the project:
```
cmake -S . -B build
cmake --build build
```
-Run the application:
```
./build/planner
```
-Run the test:
```
./build/tests
```

data.bin is the application's binary save file. If the file doesn't exist, the application starts with default rooms and events. When you exit the application, all your additions (rooms, bookings, etc...) will be saved.

