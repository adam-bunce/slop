import itertools
from collections import defaultdict

from ortools.sat.python import cp_model


def main() -> None:
    edges = [
        [0, 1],
        [0, 2],
        [1, 2],
        [2, 3],
        [2, 4],
        [3, 1],
        [3, 0],
        [4, 3],
        [1, 4],
        [4, 0],
    ]
    all_edges = range(len(edges))
    edge_costs = [1 for _ in all_edges]  # all the same cost's
    nodes = 5

    model = cp_model.CpModel()

    # if edge was chosen for tour
    arcs = [model.new_bool_var(f"e:{edge}") for edge in edges]

    incoming = defaultdict(list)
    outgoing = defaultdict(list)
    for index, edge in enumerate(edges):
        incoming[edge[1]].append(arcs[index])
        outgoing[edge[0]].append(arcs[index])

    # Constraint 1: each incoming arc (if used) should have an outgoing arc
    for edge in all_edges:
        model.add(sum(incoming[edge]) == sum(outgoing[edge]))

    # Constraint 2: for a cycle through n nodes, we need at least n edges
    model.add(sum(arcs) >= nodes)

    subsets = []
    # proper subset so until n-1
    for set_size in range(2, nodes):
        subsets.extend(
            list(itertools.combinations([i for i in range(nodes)], set_size))
        )

    for subset in subsets:
        # collect edges common to nodes in subset
        subset_edges = [
            arcs[i]
            for i, edge in enumerate(edges)
            if edge[0] in subset and edge[1] in subset
        ]

        # Constrain 3: prevent sub-tours (DFJ formulation)
        model.add(sum(subset_edges) <= len(subset) - 1)

    # Minimize edges used
    model.minimize(sum(arcs[edge] * edge_costs[edge] for edge in all_edges))

    solver = cp_model.CpSolver()
    status = solver.solve(model)

    if status in [cp_model.FEASIBLE, cp_model.OPTIMAL]:
        print("Solution:")
        for edge in all_edges:
            if solver.value(arcs[edge]) == 1:
                print("used:", edges[edge])

    else:
        print("No Solution")


if __name__ == "__main__":
    main()
