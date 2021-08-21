# dining_philosophers

This is a program for thread and process exclusion control, based on the concept of the philosopher's meal problem.


### Arguments
```
. /philo* number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_you_have_to_eat]
```
- Necessary  
number_of_philosophers: Number of philosophers performing the simulation (0 < n <= 200)  
time_to_die: Maximum time between the start of one meal and the start of the next (50 < =n)  
time_to_eat: How long it takes to eat (50 <= n)  
time_to_sleep: How long it takes to sleep (50 <= n)  

- option  
number_of_times_you_have_to_eat: Number of times the simulation will end when all philosophers have eaten.
