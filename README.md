# Philosophers - I never thought philosophy would be so deadly

This project consists of implementing a simulation of the **Dining Philosophers problem**, focusing on **low-level programming, multithreading, process synchronization, and algorithm efficiency**. The goal is to solve a classic concurrency problem while learning how to manage resources and prevent deadlocks and data races.

## 📋 Project Overview
One or more philosophers sit at a round table with a large bowl of spaghetti. They alternate between **eating, thinking, and sleeping**. To eat, a philosopher must hold two forks (one in each hand). The simulation ends if a philosopher dies of starvation.

### ⚙️ Features
*   **Mandatory Part:** Philosophers are represented as **threads**, and forks are protected by **mutexes** to prevent data races.
*   **Bonus Part:** Each philosopher is a separate **process**, and the forks are managed as a **semaphore** in the middle of the table.

## 🚀 Usage

### Arguments
The program(s) must take the following arguments:
1.  `number_of_philosophers`: The number of philosophers and forks.
2.  `time_to_die` (ms): Time limit for a philosopher to start eating before they die.
3.  `time_to_eat` (ms): Time it takes to eat (holding two forks).
4.  `time_to_sleep` (ms): Time spent sleeping.
5.  `[number_of_times_each_philosopher_must_eat]` (optional): The simulation stops if everyone eats this many times.

### Compilation
Both versions include a **Makefile** with standard rules (`all`, `clean`, `fclean`, `re`, `bonus`).

**Mandatory:**
```bash
cd philo && make
./philo 5 800 200 200 7
```

**Bonus:**
```bash
cd philo_bonus && make
./philo_bonus 5 800 200 200 7
```

## 🧠 What I Learned
*   **Multithreading & Processes:** Creating and managing threads (`pthread_create`) and processes (`fork`).
*   **Synchronization Primitives:** Using **mutexes** and **semaphores** to protect shared resources.
*   **Concurrency Issues:** Identifying and avoiding **data races**, deadlocks, and starvation.
*   **Time Management:** Using `gettimeofday` and `usleep` for high-precision timing.
*   **Manual Memory Management:** Ensuring clean exits without memory leaks.

## ⚠️ Project Constraints
This project was developed under the strict regulations of the 42 School:
*   **Norminette Compliance:** The code follows strict formatting and structural rules.
*   **Zero Global Variables:** All state must be passed via structures.
*   **Memory Efficiency:** No memory leaks are tolerated.
*   **Data Integrity:** The program must not have any data races.

## 👨‍💻 Author
**mateferr** (Mateus Leite)
42 Lisboa Student
