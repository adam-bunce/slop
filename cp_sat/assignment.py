from ortools.sat.python import cp_model

from problems.util import print_statistics


def main() -> None:
    model = cp_model.CpModel()

    # https://en.wikipedia.org/wiki/Assignment_problem
    task_assignments = [
        [8, 4, 7],
        [5, 2, 3],
        [9, 6, 7],
        [9, 4, 8],
    ]

    workers = range(len(task_assignments))
    tasks = range(len(task_assignments[0]))

    worker_task_costs_used = dict()
    for worker in workers:
        for task in tasks:
            cost = task_assignments[worker][task]
            task_cost = model.new_int_var(
                cp_model.INT32_MIN,
                cp_model.INT32_MAX,
                f"worker:{worker}_task:{task}_cost:{cost}",
            )
            worker_used = model.new_bool_var(f"worker:{worker}_task:{task}")

            # the worker is either used or not so the cost is 0 or <worker cost>
            model.add(task_cost == 0).only_enforce_if(worker_used.negated())
            model.add(cost == task_cost).only_enforce_if(worker_used)
            worker_task_costs_used[(worker, task)] = [task_cost, worker_used]

    # Constraint 1: must have someone do the task
    for task in tasks:
        model.add_at_least_one(
            [worker_task_costs_used[(worker, task)][1] for worker in workers]
        )

    # Constraint 2: a worker can only be assigned one task
    for worker in workers:
        model.add_at_most_one(
            [worker_task_costs_used[(worker, task)][1] for task in tasks]
        )

    model.minimize(sum(cost for cost, _ in worker_task_costs_used.values()))

    solver = cp_model.CpSolver()
    status = solver.Solve(model)

    if status in [cp_model.OPTIMAL, cp_model.FEASIBLE]:
        print("Solved")
        for worker in workers:
            for task in tasks:
                cost, used = worker_task_costs_used[(worker, task)]
                print(f"{solver.value(cost) if solver.value(used) else '_'}", end=" ")
            print()
        print_statistics(solver)
    else:
        print("No solution found")


if __name__ == "__main__":
    main()
