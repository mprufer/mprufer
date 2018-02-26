<b> Language: </b> C++
<b> IDE </b>: XCode or Unix
<b> Arguments: </b> Int representing total weight allowed on bridge & name of input textfile (example given: input1.txt)

This program demonstrates multi-threading. It simluates a bridge that only holds a certain amount of weight. The program must keep track o
car on the bridge, the total weight currently on the bridge, and when to allow new cars on the brdige. 
Each line in the textfile has a license plate no., the time it arrives at the bridge, and the total time it takes the car to cross the bridge.
An object for each is created with the variables: license, arrivalTime, and weight. <br>A thread is then created for each car when it arrives at the bridge.
Once a car has crossed the bride, its thread is closed and the next car (whose weight does not exceed the bridge's total weight) has a thread created for it and crosses the bridge. 
If a car arrives at the bridge and cannot currently cross it, the thread is held while others continue running. It is held until enough cars cross & their respective threads are closed
so that the car can cross the bridge without collapsing it. 
