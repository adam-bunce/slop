from ortools.sat.python import cp_model

# https://leetcode.com/problems/house-robber-ii/description/


def main() -> None:
    houses = [2, 3, 2]  # 3
    houses = [1, 2, 3, 1]  # 4
    houses = [1, 2, 3]  # 3

    house_count = len(houses)
    all_houses = range(house_count)

    model = cp_model.CpModel()
    house_vars = [model.new_bool_var(f"house:{house}") for house in houses]

    # Constraint 1: Can't rob adjacent houses
    l, r = 0, 1
    while r < house_count:
        model.add_at_most_one([house for house in house_vars[l : r + 1]])
        l += 1
        r += 1

    # Constraint 2: neighbour of first house is the neighbour of the last one
    model.add_at_most_one(house_vars[0], house_vars[-1])

    model.maximize(sum([houses[house] * house_vars[house] for house in all_houses]))

    solver = cp_model.CpSolver()
    status = solver.solve(model)

    if status in [cp_model.OPTIMAL or cp_model.FEASIBLE]:
        print("Solved:")
        for house in all_houses:
            if solver.value(house_vars[house]) == 1:
                print(f"Robbed House {house}, +{houses[house]}")
            else:
                print(f"Didn't rob house {house}")
        print(f"Profit: {solver.objective_value}")

    else:
        print("No Solution")


if __name__ == "__main__":
    main()
