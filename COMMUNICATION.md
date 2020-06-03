# Communication between client and server

## Request (client -> server) [TCP]

Create a new lobby
```
req cl \n
```

Join a lobby
```
req jl <ID OF THE LOBBY> \n
```

Start the game
```
req sg <ID OF THE LOBBY> \n
```

## Responses (server -> client) [TCP]

The lobby is created
```
res cl <ID OF THE LOBBY> \n
```

The lobby is joined
```
res jl <ID OF THE LOBBY> \n
```

The game is start, and player number attribution
```
res sg <ID OF THE PLAYER> \n
```

## Events (client -> server -> client in the lobby) [UDP]

Event to share local player position and rotation
```
evt ps <ID OF THE LOBBY> <ID OF THE PLAYER> <POS X> <POS Y> <ROT Y> \n
```

## Errors [TCP]

Lobby not found
```
err lnf \n
```