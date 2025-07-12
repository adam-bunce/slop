package decide

import (
	"testing"
)

type Animal struct {
	Weight    int
	Height    int
	Color     string
	HasFur    bool
	LimbCount int
}

func IsSmall(a Animal) (Animal, bool) {
	if a.Weight < 50 {
		return a, true
	}
	return a, false
}

func IsSafe(a Animal) (Animal, bool) {
	if a.Weight > 100 || a.Height > 150 {
		return a, false
	}
	return a, true
}

func IsBug(a Animal) (Animal, bool) {
	if a.LimbCount > 4 {
		return a, true
	}
	return a, false
}

func TestAnimalCategorization(t *testing.T) {
	var testcases = []struct {
		name     string
		animal   Animal
		expected string
	}{
		// Should pass: small, safe, not bugs
		{name: "Small Dog", animal: Animal{Weight: 2, Height: 5, Color: "brown", HasFur: true, LimbCount: 4}, expected: "OK"},
		{name: "Cat", animal: Animal{Weight: 4, Height: 8, Color: "orange", HasFur: true, LimbCount: 4}, expected: "OK"},
		{name: "Hamster", animal: Animal{Weight: 1, Height: 3, Color: "white", HasFur: true, LimbCount: 4}, expected: "OK"},
		{name: "Small Snake", animal: Animal{Weight: 2, Height: 3, Color: "green", HasFur: false, LimbCount: 0}, expected: "OK"},
		{name: "Small Bird", animal: Animal{Weight: 1, Height: 8, Color: "yellow", HasFur: false, LimbCount: 2}, expected: "OK"},

		// Should fail: too large
		{name: "Large Dog", animal: Animal{Weight: 60, Height: 80, Color: "black", HasFur: true, LimbCount: 4}, expected: "BAD"},
		{name: "Horse", animal: Animal{Weight: 500, Height: 150, Color: "brown", HasFur: true, LimbCount: 4}, expected: "BAD"},

		// Should fail: bugs
		{name: "Spider", animal: Animal{Weight: 0, Height: 1, Color: "black", HasFur: false, LimbCount: 8}, expected: "BAD"},
		{name: "Ant", animal: Animal{Weight: 0, Height: 1, Color: "red", HasFur: false, LimbCount: 6}, expected: "BAD"},
		{name: "Beetle", animal: Animal{Weight: 1, Height: 2, Color: "green", HasFur: false, LimbCount: 6}, expected: "BAD"},
	}

	isSmallNode := NewProcessor(IsSmall)
	isSafeNode := NewProcessor(IsSafe)
	isBugNode := NewProcessor(IsBug)
	finalStateOk := NewProcessor(func(animal Animal) (string, bool) {
		return "OK", true
	})
	finalStateBad := NewProcessor(func(animal Animal) (string, bool) {
		return "BAD", true
	})

	// Graph that represents us trying to find animals, that are small, safe and not bugs
	isSmallNode.On(false, finalStateBad)
	isSmallNode.On(true, isSafeNode)

	isSafeNode.On(true, isBugNode)
	isSafeNode.On(false, finalStateBad)

	isBugNode.On(false, finalStateOk)
	isBugNode.On(true, finalStateBad)
	g := Graph{}
	g.AddNodes(isSmallNode, isSafeNode, isBugNode, finalStateOk, finalStateBad)

	for _, tc := range testcases {
		out := g.Start(tc.animal)
		if tc.expected != out {
			t.Errorf("%s: expected %s, got %s", tc.name, tc.expected, out)
		}
	}
}
