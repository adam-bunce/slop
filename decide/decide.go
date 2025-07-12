package decide

import "fmt"

// NOTE(adam): do generics even add any value here?
// yeah i think so, otherwise we have to hand this function with no types (any, any, any)

type Graph struct {
	Nodes []Processor
}

func (g *Graph) AddNodes(n ...Processor) {
	g.Nodes = append(g.Nodes, n...)
}

func (g *Graph) Start(input any) any {
	node := g.Nodes[0]

	// while there are nodes to traverse, traverse
	for node != nil {
		out, key := node.Exec(input)
		node = node.GetNeighbour(key)
		input = out
	}

	return input
}

func NewProcessor[In, Out any, Key comparable](predicate func(In) (Out, Key)) Processor {
	return &Node[In, Out, Key]{
		Label:      "unset",
		Predicate:  predicate,
		Neighbours: make(map[Key]Processor),
	}
}

type Node[In, Out any, Key comparable] struct {
	// Label is used to identify the node during debugging and output verification
	Label string

	// Predicate is a function that fires during graph traversal if a node is visited.
	// The second return value (Key) is used to determine the next node to visit.
	Predicate func(In) (Out, Key)

	// Neighbours maps edge values to destination nodes. When this node
	// executes, it's return value is used as the key to select the next node.
	Neighbours map[Key]Processor
}

func (n *Node[In, Out, Key]) On(output any, neighbour Processor) {
	// not using key here is sketchy ngl, need to do this to get Processor interface tow ork tho
	// we do type asser tthat it is the key but.. idk
	n.Neighbours[output.(Key)] = neighbour
}

// Exec runs the Node's Predicate, returning it's output
func (n *Node[In, Out, Key]) Exec(input any) (any, any) {
	typedInput, ok := input.(In)
	if !ok {
		panic(fmt.Sprintf("Type mismatch: expected %T, got %T", *new(In), input))
	}

	return n.Predicate(typedInput)
}

// GetNeighbour returns the Node's neighbour associated with the key
func (n *Node[In, Out, Key]) GetNeighbour(key any) Processor {
	neighbour, ok := n.Neighbours[key.(Key)]
	if !ok { // returns typed nil otherwise
		return nil
	}
	return neighbour
}

// we use Processor  to do type erasure
type Processor interface {
	Exec(any) (any, any)
	GetNeighbour(any) Processor
	On(any, Processor)
}
