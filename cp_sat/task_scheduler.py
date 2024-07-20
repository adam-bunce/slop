# https://leetcode.com/problems/task-scheduler/

from collections import defaultdict
from ortools.sat.python import cp_model


def solve(tasks: list[str], n: int) -> int:
    inf = 10_000
    model = cp_model.CpModel()
    task_vars = defaultdict(list)
    for i, task in enumerate(tasks):
        task_vars[task].append(model.new_int_var(0, inf, f"task:f{task}_{i}"))

    # Constraint 1: all variables of the same letter must be at least n away from each other
    for task_type_grouping in task_vars.values():
        for i, t1 in enumerate(task_type_grouping):
            for j, t2 in enumerate(task_type_grouping):
                if i != j:
                    condition = model.new_bool_var("tmp_condition")
                    model.add(t1 < t2 - n).only_enforce_if(condition)
                    model.add(t1 > t2 + n).only_enforce_if(condition.negated())

                    condition2 = model.new_bool_var("tmp_condition2")
                    model.add(t2 < t1 - n).only_enforce_if(condition2)
                    model.add(t2 > t1 + n).only_enforce_if(condition2.negated())

    # Constraint 2: variables can't have the same values
    all_tasks = [task for task_vars in task_vars.values() for task in task_vars]
    model.add_all_different(all_tasks)

    # keep cycles low
    model.minimize(sum(all_tasks))

    solver = cp_model.CpSolver()
    solver.solve(model)

    values = [[task, solver.value(task)] for task in all_tasks]
    return solver.value(max(values, key=lambda x: x[1])[0]) + 1


def main() -> None:

    cases = [
        # n, tasks, expected output
        [2, ["A", "A", "A", "B", "B", "B"], 8],
        [1, ["A", "C", "A", "B", "D", "B"], 6],
        [3, ["A", "A", "A", "B", "B", "B"], 10], ]

    for n, tasks, expected in cases:
        cycles = solve(tasks, n)
        assert cycles == expected
        print(cycles, '==', expected)


if __name__ == "__main__":
    main()
