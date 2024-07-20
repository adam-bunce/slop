from ortools.sat.python import cp_model
from problems.util import print_statistics


def make_pairs() -> list[tuple[int, int]]:
    values = [
        # fmt:off
        360, 83, 59, 130, 431, 67, 230, 52, 93, 125, 670, 892, 600, 38, 48, 147,
        78, 256, 63, 17, 120, 164, 432, 35, 92, 110, 22, 42, 50, 323, 514, 28,
        87, 73, 78, 15, 26, 78, 210, 36, 85, 189, 274, 43, 33, 10, 19, 389, 276,
        312
        # fmt:on
    ]
    weights = [
        # fmt: off
        7, 0, 30, 22, 80, 94, 11, 81, 70, 64, 59, 18, 0, 36, 3, 8, 15, 42, 9, 0,
        42, 47, 52, 32, 26, 48, 55, 6, 29, 84, 2, 4, 18, 56, 7, 29, 93, 44, 71,
        3, 86, 66, 31, 65, 0, 79, 20, 65, 52, 13
        # fmt: on
    ]

    return [(values[i], weights[i]) for i in range(len(values))]


def main() -> None:
    items = make_pairs()
    capacity: int = 850
    model = cp_model.CpModel()

    item_was_chosen: list[cp_model.IntVar] = [
        model.new_bool_var(f"item:{item_index}_v:{item[0]}")
        for item_index, item in enumerate(items)
    ]

    # Constraint 1: total weight of items <= capacity
    model.add(
        sum(
            [
                item[1] * item_was_chosen[item_index]
                for item_index, item in enumerate(items)
            ]
        )
        <= capacity
    )

    # Maximize Value
    model.maximize(
        sum(
            [
                item[0] * item_was_chosen[item_index]
                for item_index, item in enumerate(items)
            ]
        )
    )

    solver = cp_model.CpSolver()
    status = solver.solve(model)

    if status in [cp_model.FEASIBLE, cp_model.OPTIMAL]:
        print("Solution Found")

        total_value, total_weight = 0, 0
        for item_index, item in enumerate(item_was_chosen):
            if solver.value(item):
                print(
                    f"Item {item_index} chosen ({items[item_index][0]}, {items[item_index][1]})"
                )
                total_value += items[item_index][0]
                total_weight += items[item_index][1]
            else:
                print(
                    f"Item {item_index} not chosen ({items[item_index][0]}, {items[item_index][1]})"
                )

        assert total_value == 7534
        assert total_weight == 850

        print()
        print(f"Total Value: {total_value}")
        print(f"Total Weight: {total_weight}")

        print_statistics(solver)


if __name__ == "__main__":
    main()
