from ortools.sat.python import cp_model

# https://www.csplib.org/Problems/prob034/
# https://cs.pwr.edu.pl/zielinski/lectures/om/opl/workbook.pdf page 188


def main() -> None:
    fixed = 30  # cost of opening a warehouse
    warehouses = ["Bonn", "Bordeaux", "London", "Paris", "Rome"]
    all_warehouses = range(len(warehouses))
    nb_stores, all_stores = 10, range(10)
    capacity = [1, 4, 2, 1, 3]  # num of stores each warehouse can supply

    # supply_cost[store][warehouse]
    supply_cost = [
        [20, 24, 11, 25, 30],
        [28, 27, 82, 83, 74],
        [74, 97, 71, 96, 70],
        [2, 55, 73, 69, 61],
        [46, 96, 59, 83, 4],
        [42, 22, 29, 67, 59],
        [1, 5, 73, 59, 56],
        [10, 73, 13, 43, 96],
        [93, 35, 63, 85, 46],
        [47, 65, 55, 71, 95],
    ]

    model = cp_model.CpModel()

    # If warehouse will supply store
    warehouse_store_pairs = dict()
    for store in all_stores:
        for warehouse in all_warehouses:
            warehouse_store_pairs[(store, warehouse)] = model.new_bool_var(
                f"w:{warehouse}-s{store}"
            )

    warehouse_is_open = []
    for warehouse in all_warehouses:
        warehouse_is_open.append(model.new_bool_var(f"w:{warehouse}"))

    # Constraint 1: each store must be supplied by a warehouse
    for store in all_stores:
        model.add_at_least_one(
            [warehouse_store_pairs[(store, warehouse)] for warehouse in all_warehouses]
        )

    # Constraint 2: a store can only be supplied by an open warehouse
    for store in all_stores:
        for warehouse in all_warehouses:
            model.Add(
                warehouse_store_pairs[(store, warehouse)]
                <= warehouse_is_open[warehouse]
            )

    # Constraint 3: no warehouse can be assigned to more stores than it's allowed capacity
    for warehouse in all_warehouses:
        model.add(
            sum(warehouse_store_pairs[(store, warehouse)] for store in all_stores)
            <= capacity[warehouse]
        )

    # Minimize the cost of opening warehouses/supplying stores
    cost_of_opening_warehouses = sum(
        [fixed * warehouse_is_open[warehouse] for warehouse in all_warehouses]
    )
    cost_of_stocking_store = sum(
        supply_cost[store][warehouse] * warehouse_store_pairs[(store, warehouse)]
        for store in all_stores
        for warehouse in all_warehouses
    )
    model.minimize(cost_of_opening_warehouses + cost_of_stocking_store)

    solver = cp_model.CpSolver()
    status = solver.solve(model)

    if status in [cp_model.FEASIBLE, cp_model.OPTIMAL]:
        print("Solution:")
        for warehouse in all_warehouses:
            assigned_stores = [
                store
                for store in all_stores
                if solver.value(warehouse_store_pairs[(store, warehouse)]) == 1
            ]
            print(warehouses[warehouse], assigned_stores)

        print("Cost:", solver.objective_value)
    else:
        print("No Solution")


if __name__ == "__main__":
    main()
