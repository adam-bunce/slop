from collections import defaultdict
from typing import Tuple
from ortools.sat.python import cp_model
from problems.util import print_statistics


# https://www.csplib.org/Problems/prob023/


class MagicHexagonSolutionPrinter(cp_model.CpSolverSolutionCallback):

    def __init__(self, hexagon_vars: list[list[cp_model.IntVar]]) -> None:
        cp_model.CpSolverSolutionCallback.__init__(self)
        self._rows = len(hexagon_vars)
        self._hexagon_vars = hexagon_vars
        self._solutions_count = 0

    def on_solution_callback(self):
        self._solutions_count += 1

        for row in range(self._rows):
            for col in range(len(self._hexagon_vars[row])):
                print(f"{self.value(self._hexagon_vars[row][col])} ", end="")
            print()
        print()

    @property
    def solution_count(self) -> int:
        return self._solutions_count


def gen_board(order: int) -> Tuple[list[list[str]], list[int]]:
    board, padding = [], []
    curr_padding, curr_cols = 0, order
    rows = order * 2 - 1
    decrease_flag = False

    for row in range(rows):
        row_vals = []
        for col in range(curr_cols):
            row_vals.append(f"{row}:{col}")

        board.append(row_vals)

        if row == order - 1:
            decrease_flag = True

        if decrease_flag:
            padding.append(curr_padding)
            curr_cols -= 1
            curr_padding += 1
        else:
            padding.append(0)
            curr_cols += 1

    return board, padding


def main() -> None:
    model = cp_model.CpModel()

    order = 3
    m = 38
    lb, ub = 1, 19

    hexagon, padding = gen_board(order)
    print(padding)

    rows = range(len(hexagon))

    hexagon_vars = [[] for _ in rows]
    for row in rows:
        for col in range(len(hexagon[row])):
            hexagon_vars[row].append(
                model.new_int_var(lb, ub, f"r:{row}_c:{col}_l:{hexagon[row][col]}")
            )

    # Constraint 1: all rows sum to m
    for row in rows:
        model.add(sum(hexagon_vars[row]) == m)

    # Constraint 2: can't use the same number twice
    model.add_all_different(
        [hexagon_vars[row][col] for row in rows for col in range(len(hexagon[row]))]
    )

    positive_diagonals = defaultdict(list)
    for row in rows:
        for col in range(len(hexagon[row])):
            positive_diagonals[col + padding[row]].append(hexagon_vars[row][col])

    negative_diagonals = defaultdict(list)
    for row in rows:
        for col in range(len(hexagon[row])):
            negative_diagonals[col + padding[::-1][row]].append(hexagon_vars[row][col])

    # Constraint 3/4: positive/negative diagonals should sum to 38
    for p_diag, n_diag in zip(positive_diagonals.values(), negative_diagonals.values()):
        model.add(sum(p_diag) == m)
        model.add(sum(n_diag) == m)

    solver = cp_model.CpSolver()
    solver.parameters.enumerate_all_solutions = True
    solution_printer = MagicHexagonSolutionPrinter(hexagon_vars)
    solver.solve(model, solution_printer)

    print_statistics(solver)
    print(
        f"Found {solution_printer.solution_count} solutions"
    )  # these are all rotated versions of the same


if __name__ == "__main__":
    main()
