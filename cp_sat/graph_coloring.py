from collections import defaultdict
from typing import Mapping

from ortools.sat.python import cp_model


def main() -> None:
    adjacency_list: Mapping[int, list[int]] = {
        # fmt: off
        0: [1],
        1: [2, 3],
        2: [1],
        3: [1]
        # fmt: on
    }

    adjacency_list = {
        # fmt: off
        0: [1, 2, 3],
        1: [0, 4],
        2: [0, 3],
        3: [0, 2, 4],
        4: [1, 3]
        # fmt: on
    }

    node_count = len(adjacency_list)

    model = cp_model.CpModel()

    node_vars = [0] * node_count
    for node, neighbours in adjacency_list.items():
        if isinstance(node_vars[node], int):
            node_vars[node] = model.new_int_var(1, node_count, f"n:{node}")

        for neighbour in neighbours:
            if isinstance(node_vars[neighbour], int):
                node_vars[neighbour] = model.new_int_var(
                    1, node_count, f"n:{neighbour}"
                )

            # Constraint 1: these nodes cant have the same color
            model.add_all_different(node_vars[node], node_vars[neighbour])

    # Keep color id #'s small
    model.minimize(sum(node_vars))

    solver = cp_model.CpSolver()
    status = solver.solve(model)
    if status in [cp_model.FEASIBLE, cp_model.OPTIMAL]:
        print("Solved:")

        colors = [solver.value(color) for color in node_vars]
        print(f"   - Used {max(colors)} colors")

        color_to_node = defaultdict(list)
        for node, color in enumerate(colors):
            color_to_node[color].append(node)

        for color, nodes in color_to_node.items():
            print(f"   - Color: {color} Nodes: {nodes}")

    else:
        print("No Solution")


if __name__ == "__main__":
    main()
