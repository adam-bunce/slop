from ortools.linear_solver import pywraplp


def main() -> None:
    solver = pywraplp.Solver.CreateSolver("GLOP")
    if not solver:
        print("No solver")
        return

    total_hours = 80
    total_wood = 200

    wood_per_table = 10
    wood_per_bookshelf = 20
    max_tables = total_wood // wood_per_table
    max_bookcases = total_wood // wood_per_bookshelf

    # Create Variables
    tables = solver.NumVar(0, max_tables, "tables")
    bookcases = solver.NumVar(0, max_bookcases, "bookcases")

    # Constraint 1: we can't use more time than we have
    solver.Add(5 * tables + 4 * bookcases <= total_hours)

    # Constraint 2: we can't use more wood than we have
    solver.Add(10 * tables + 20 * bookcases <= total_wood)

    # Maximize profit
    solver.Maximize(180 * tables + 200 * bookcases)

    status = solver.Solve()
    if status == pywraplp.Solver.OPTIMAL:
        print("Solution:")
        print(f"Profit (objective value): {solver.Objective().Value():0.1f}")
        print(f"tables = {tables.solution_value():0.1f}")
        print(f"bookcases = {bookcases.solution_value():0.1f}")
    else:
        print("Couldn't find optimal solution")


if __name__ == "__main__":
    main()
