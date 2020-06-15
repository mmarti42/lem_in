# lem-in

42 School project

This project is a game about ant farm. Its goal is to find the shortest path from start room to the end.

## About lem-in

At the beginning from standart output the program recieves information about number of ants had to be leaded through path, room names (can be numbers, words, characters etc.) with coordinates and links. Here is an example:

<img width="142" alt="screen shot 2017-07-16 at 7 23 13 pm" align="middle" src="https://user-images.githubusercontent.com/25576444/28254024-ea2c5eb6-6a5d-11e7-922c-5808975b2419.png" >

Comments "##start" and "##end" are provided to show the start and end room information. We don't care about any other comments.

## Installation and usage

Simply clone repository and run following commands:

```
make

./lem-in < maps/subject-1.map
```
Here 'maps/subject-1.map' is an example of game map.

## Solving a task

The task is solved using the suurbale algorithm

https://www.drrameshbhandari.net/app/download/6624745304/surv_diversity.pdf (sec 3, vertex-disjoint)

http://www.macfreek.nl/memory/Disjoint_Path_Finding

## Output

The final step is to take every singe ant and lead it through the created path all the way to the end, 
considering that all of the ants are in a start room at the beginning. 
The result has to be written in format Ln-r, where n - the number of ant, r - room name.
