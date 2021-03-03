**Movie Theater Seating Challenge - 2020**

**Programming Language used:**  C

**Program Functionality and Objectives:**

This program takes an input file from command line arguments, parses the input file line by line for reservations, and reserves seats in a movie theater abiding by the constraints.

Objectives of this algorithm:

1. Allocate middle seats to earlier reservations.
2. People belonging to the same group will be seated in the same row. If the group is larger than the number of available seats in the row, the group will be split and seats will be allocated wherever there are available seats, again trying to seat people in the same group in the same row.
3. If there are no consecutive seats available, the remainder of the group(s) will be seated at any available seat.
4. Seats from one group must be a minimum 3 seats and one row apart from a different group.
5. If there are less available seats than seats requested for a group, then that reservation cannot be fulfilled and the next reservation that is able to be fulfilled is adressed.

**Assumptions:**

1. If the requested number of seats for a group is greater than the available seats, the theater will not reserve seats for that group.
2. The reservation numbers(R###) will be in sequential order like (R001, R002, R003...) in the input file and no reservation number will be skipped (Use 0 requested seats as a way to skip reservation). 
3. The maximum number of reservations is 999 total reservations.
4. Seats from one group must be a minimum 3 seats and one row apart from any other different group, but seats between members of the same group do not need to meet this constraint.

**How the goals of the problem statement are achieved?**

_Customer Satisfaction:_

1. Because seats in the middle rows of the theater provide the best viewing experience, earlier reservations will be allocated seats closer to the middle rows.
1. Since the reservations are for groups of people, they would prefer to sit next to each other. Groups will be allocated as many adjacent seats in a row as possible.

_Maximum Theater Usage:_

1. In order to fulfill as many reservation requests as possible and also keep the customers satisfied by allocating consecutive seats, seats will be allocated starting from the first column. This will allow us to maximize customer satisfaction and allocate the most seats.
2. If the theater is unable to accommodate a group in a single row, then we allocate the seats wherever there is a vacant seat in the theater.
3. If one reservation cannot be fully accommodated, then that reservation is skipped and the next reservation that can be fully accommodated is addressed.

_Public Safety_

1. The seats in the row right above and right below a seat belonging to one group will be unavailable to members of a different group, and only available to members of the same group.
2. Seats between members of different groups in the same row must be at least 3 seats apart.

**Problems with this algorithm:"**

1. While customer satisfaction is addressed, this algorithm does not quantify customer satisfaction.
2. Members of groups that are split up between rows may not get seats in rows right above or right below members of the same group even if those seats are available.

**Steps for running**
1. Download or clone the repository to a local or remote directory.
2. Open the terminal and navigate to the newly generated directory which contains the input files and movie.c.
3. Compile the C source file in the terminal using the command: gcc -o movie movie.c -ansi -Wall -std=c99. This should generate a new executable called "movie".
4. Run the newly generated executable with the command: ./movie ($filename)
5. If there are permission issues for the executable, run the command: chmod a+x movie