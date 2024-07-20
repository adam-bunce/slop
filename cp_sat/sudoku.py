from collections import defaultdict
from ortools.sat.python import cp_model

from problems.util import print_statistics


def main() -> None:
    model = cp_model.CpModel()

    # https://anysudokusolver.com/ (example grid at bottom of page)
    board: list[list[str]] = [
        ["_", "_", "_", "_", "_", "4", "_", "9", "_"],
        ["8", "_", "2", "9", "7", "_", "_", "_", "_"],
        ["9", "_", "1", "2", "_", "_", "3", "_", "_"],
        ["_", "_", "_", "_", "4", "9", "1", "5", "7"],
        ["_", "1", "3", "_", "5", "_", "9", "2", "_"],
        ["5", "7", "9", "1", "2", "_", "_", "_", "_"],
        ["_", "_", "7", "_", "_", "2", "6", "_", "3"],
        ["_", "_", "_", "_", "3", "8", "2", "_", "5"],
        ["_", "2", "_", "5", "_", "_", "_", "_", "_"],
    ]

    ROWS, COLS = range(len(board)), range(len(board[0]))
    size = len(board)

    positions = dict()
    for row in ROWS:
        for col in ROWS:
            # cells can be values 1->9
            positions[(row, col)] = model.new_int_var(1, size, name=f"r_{row}_c_{col}")
            if board[row][col] != "_":
                # ~Constraint(kinda): cannot change existing values
                value = int(board[row][col])
                model.add(value == positions[(row, col)])

    # Constraint 1: each row must have values from 1->9 (no duplicated in row)
    for row in ROWS:
        model.add_all_different([positions[(row, col)] for col in COLS])

    # Constraint 2: each col must have values from 1->9 (no duplicates in col)
    for col in COLS:
        model.add_all_different([positions[(row, col)] for row in ROWS])

    box_groups = defaultdict(list)
    # group cells into their respective 3x3 boxes
    for row in ROWS:
        for col in COLS:
            bucket = (row // 3, col // 3)
            box_groups[bucket].append(positions[(row, col)])

    # Constraint 3: each 3x3 box must contain only values from 1->9 (no duplicated in box)
    for box in box_groups:
        model.add_all_different(box_groups[box])

    solver = cp_model.CpSolver()
    status = solver.solve(model)

    if status in [cp_model.OPTIMAL, cp_model.FEASIBLE]:
        print("Solution Found:")
        for row in ROWS:
            for col in COLS:
                print(solver.value(positions[(row, col)]), end=" ")
            print()

        print_statistics(solver)
    else:
        print("No solution found")


if __name__ == "__main__":
    main()
