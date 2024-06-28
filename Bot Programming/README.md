# Simulation of a 4-Player Game with Graph Algorithms

## Introduction:

Simulation a complex 4-player game set on the fictional planet Crematoria from the Riddick saga. The 4 players must incorporate a bot which will need to use graph algorithms and strategies to manage interactions among various units and aim for victory.

## How to Run:

### Compilation:

To compile the game, run the following command in the terminal:
```bash
make all
```

Execute the game with the following command:
```bash
./Game WESTCOAST Dummy Dummy Dummy -s 30 -i default.cnf -o default.res
```

Viewing the Match:
After compilation and execution, follow these steps to witness the match:

    1. Open a console and cd to the directory where you extracted the source code.
    2. Run make all
    3. This creates an executable file called Game. This executable allows you to run
    a game using a command like:
```bash
./Game WESTCOAST Demo Demo Demo -s 30 -i default.cnf -o default.res
```
    This starts a match, with random seed 30, of three instances of the player Demo and the bot WESTCOAST (created by me), in the board defined in default.cnf. The output of this match is redirected to
    default.res.
    4. To watch a game, open the viewer file viewer.html with your browser and
    load the file default.res.
