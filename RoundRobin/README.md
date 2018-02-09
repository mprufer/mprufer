Make-up scheduling simluator
------------------------------
<b>Language</b>: C++

<b>Desc</b><br>
This program simluates the application of make-up to actors given a certain scheduling rule. Each actor that arrives has an arrival time
of when they arrive at the make-up station and the duration which is the number of rounds it will take to complete make-up application on the actor. 

The two scheudling rules that can be applied are: round-robin and first-in-first-out (fifo). Round-robin also has the additional argument of quantum,
which indicates the number of rounds an artist can spend on an actor before moving on to the next one. If a schedule isn't indicated or is not either of the two, the default schedule is fifo. 

Each actor that arrives to the make-up station is placed in a circular queue. The queue size is indicated in the argument and an actor that arrives
can only enter the queue once there is room for them (ie an actor has completed their make-up and therefore leaves the queue allowing another actor to enter the queue). 

The make-up artist has an additional rule where after 4 actors have completed make-up, they must take a break for two rounds before starting make-up application again. 

<b>Instruct</b><br>
To run the program, an argument in the format of: file='filename here';qsize='indicate queue size here';schedule='indicate either roundrobin or fifo here'
must be passed. 
If the schedule is roundrobin, an additional argument at the end indicating the quantum size must also be in the argument: quantum='# here'

The file passed to the program must list the actors line by line. Each line must indicate (parsed by tabs) the arrival time and the duration time. The list does not need to be sorted.

<b>Files</b>
upfront: houses the main argument
Fileops: Parses the argument passed, reads the file, fills the queue, passes all arguments to appropriate functions, and then passes control to the appropriate file (either roundrobin or fifo)
Actors: Creates an object for each actor that enters the queue
RoundRobin: Simluates the make-up application scheduling if a round robin schedule is selected
Fifo: Simluates the make-up application scheduling if fifo is selected.
