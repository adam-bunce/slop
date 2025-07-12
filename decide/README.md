# Decide

attempt at created a type insensitive, function based graph traversal library


idea is that users can register functions that:
- accept some domain object
- compute stuff
- return the next node they should go to based on that stuff
- repeat until no nodes left (solution/status found)

i feel like go's type system is letting me down, i need to spam any/interface{}