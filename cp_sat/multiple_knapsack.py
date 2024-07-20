from ortools.sat.python import cp_model


def main() -> None:
    data = {}
    data["weights"] = [48, 30, 42, 36, 36, 48, 42, 42, 36, 24, 30, 30, 42, 36, 36]
    data["values"] = [10, 30, 25, 50, 35, 30, 15, 40, 30, 35, 45, 10, 20, 30, 25]
    assert len(data["weights"]) == len(data["values"])
    num_items = len(data["weights"])
    all_items = range(num_items)

    data["bin_capacities"] = [100, 100, 100, 100, 100]
    num_bins = len(data["bin_capacities"])
    all_bins = range(num_bins)

    model = cp_model.CpModel()

    possible_positions = dict()
    for i in all_items:
        for b in all_bins:
            possible_positions[(i, b)] = model.new_bool_var(f"item:{i}_bin:{b}")

    # Constraint 1: item can only exist in one bin at a time
    for item in all_items:
        model.add_at_most_one([possible_positions[(item, b)] for b in all_bins])

    # Constraint 2: sum of items weights in bin <= bins capacity
    for b in all_bins:
        model.add(
            sum(
                possible_positions[(item, b)] * data["weights"][item]
                for item in all_items
            )
            <= data["bin_capacities"][b]
        )

    # maximize total value (all bins)
    model.maximize(
        sum(
            data["values"][item] * possible_positions[(item, b)]
            for b in all_bins
            for item in all_items
        )
    )

    solver = cp_model.CpSolver()
    status = solver.Solve(model)

    if status in [cp_model.OPTIMAL, cp_model.FEASIBLE]:
        print("Solution")

        for b in all_bins:
            print(f"Bin {b}")
            for item in all_items:
                if solver.value(possible_positions[(item, b)]) == 1:
                    print(
                        f"item {item} ({data['values'][item]}, {data['weights'][item]})"
                    )

            print()
        print(f"Objective Value(total value): {solver.ObjectiveValue()}")


if __name__ == "__main__":
    main()
