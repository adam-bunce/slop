import operator
from functools import reduce

from ortools.sat.python import cp_model


def main() -> None:
    nums = [2, 3, -2, 4]
    all_nums = range(len(nums))
    out = 6

    model = cp_model.CpModel()

    num_chosen = [model.new_bool_var(f"num_{i}") for i in range(len(nums))]

    # maximize product of valid arrays
    model.maximize(sum(max(nums[pos] * num_chosen[pos], 1) for pos in all_nums))

    solver = cp_model.CpSolver()
    status = solver.solve(model)

    if status in [cp_model.FEASIBLE, cp_model.OPTIMAL]:
        print("Solution:")
        print(solver.objective_value)
    else:
        print("No Solution")


if __name__ == "__main__":
    main()
