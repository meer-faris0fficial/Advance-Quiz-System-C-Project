# Computer-Assisted-Instruction
📌 Project Overview

This project is a console-based Arithmetic Quiz System written in C.
It includes:

🔐 User Signup & Login system (file-based)

⏱ Time-limited input system

🧮 Arithmetic quizzes (Addition, Subtraction, Multiplication, Division)

🎯 Multiple difficulty levels

🏆 Score calculation and progression system

The project is designed to help students practice arithmetic, understand file handling, timers, and modular programming in C.

✨ Features
🔐 Authentication System

Signup with unique username

Login with password verification

User data stored in users.txt

🧮 Quiz Types

Addition

Subtraction

Multiplication

Division

Mixture of all operations

🎚 Difficulty Levels
Level	Number Range
Easy	1 – 10
Medium	1 – 100
Hard	1 – 1000
⏱ Time Management

2 minutes total quiz time

5 minutes timeout for menu selections

Real-time input handling using kbhit() and getch()

📊 Scoring System

10 questions per level

Score percentage displayed

Progress to next level if score ≥ 70%

🧠 Core Concepts Used

File Handling (fopen, fgets, fprintf)

Modular Programming (functions)

Random Number Generation

Time-based input (time.h)

Keyboard input without Enter (conio.h)

Floating point comparison

ANSI escape codes for colored output

🗂️ File Structure
├── main.c
├── users.txt
├── README.md


main.c → Complete quiz application

users.txt → Stores usernames and passwords

🧑‍💻 User Flow

User starts the program

Chooses Signup / Login

Logs in successfully

Selects quiz operation

Chooses difficulty level

Answers timed questions

Receives score & feedback

Proceeds to next level (if eligible)

🧮 Example Output
What is the answer of 12 + 5 : 17
Excellent

What is the answer of 8 X 6 : 48
Very Good

You got 8 correct and 2 wrong.
Your score: 80.0%

You are ready to go for the next level

⏱ Input Timeout Behaviour

If the user does not answer in time, the quiz ends

If timeout occurs during menu selection, a default option is chosen

Input returns special values (-1, -9999) on timeout

🛠 Compilation & Execution
Compile
gcc main.c -o quiz

Run
./quiz


⚠️ Note:
This program uses conio.h, so it works best on Windows or Turbo C / MinGW environments.

📌 Limitations

Passwords are stored in plain text

conio.h is not portable to Linux/macOS

Maximum username/password length is limited

📚 Learning Outcomes

By studying this project, you will learn:

How to build a menu-driven application

How to implement login/signup systems

How to handle time-based user input

How to structure a large C program

How to use file handling effectively

🚀 Future Improvements

Encrypt passwords

Add leaderboard system

Improve UI

Add sound effects

Cross-platform input handling

📄 License

This project is for educational purposes and is free to use and modify.
