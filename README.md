# bio115Sim
This program simulates the population growth of Caminacules and Pollards in a 10x10 biome. The initial populations of both species and the Caminacule reproduction rate are entered by the user. The simulation runs for 20 generations, and the user can choose whether to display the population array and/or the coordinates of the Caminacules and Pollards in each generation.

The printBiome function prints the 10x10 array of occupied and unoccupied spaces in the biome. The printCoordinates function prints the (x,y) coordinates of the occupied spaces for Caminacules and Pollards separately.

The beginSim function simulates the population growth for each generation. It first generates a random location for each Caminacule and occupies that location. If a location is already occupied, it generates a new random location until it finds an unoccupied one. Then, for each Pollard, it randomly selects a location in the biome and checks if there is a Caminacule in one of the eight adjacent cells. If there is, it marks the Caminacule as eaten and the Pollard occupies the cell. If there is no Caminacule nearby, the Pollard remains in its randomly selected cell. The simulation then checks the number of Caminacules that survived and reproduces them based on the reproduction rate entered by the user.
