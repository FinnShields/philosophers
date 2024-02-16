# philosophers
Hive Helsinki project about multithreading

This project is based on the well known 'dining philosophers'
problem in computer science, and requires the creation of a multithreaded program.
The challenges involved avoiding data races (which was achieved by using
mutexes upon any data accessed by more than one thread) and writing a program
that is fast enough for the requirements of the project.

Compiled with make, and operated with the following syntax:
./philo [number of philosophers] [time to die] [time to eat] [time to sleep] [how many meals (optional)]
