from dataclasses import dataclass
from ortools.sat.python import cp_model

# https://leetcode.com/problems/coin-change/description/


def test():
    @dataclass
    class Case:
        coins: list[int]
        target_amount: int
        solution: int

    cases: list[Case] = [
        Case([1, 2, 5], 11, 3),
        Case([2], 3, -1),
        Case([1], 0, 0),
    ]

    for i, case in enumerate(cases):
        result = coin_change(case.coins, case.target_amount)
        if result != case.solution:
            print(f"Failed case {i+1}, got {result} expected {case.solution}")
        else:
            print(f"Passed case {i+1}")


def coin_change(coins, amount) -> int:
    model = cp_model.CpModel()
    coin_vars = [
        model.new_int_var(0, cp_model.INT32_MAX, f"coin:{coin}") for coin in coins
    ]

    model.add(
        sum([coins[coin] * coin_vars[coin] for coin in range(len(coins))]) == amount
    )

    model.minimize(sum(coin_vars))

    solver = cp_model.CpSolver()
    status = solver.solve(model)

    if status in [cp_model.FEASIBLE, cp_model.OPTIMAL]:
        return int(solver.objective_value)
    else:
        return -1


if __name__ == "__main__":
    test()
