# Question lifted from Dr. Trefor Bazett's YouTube video `intro to linear optimization`
#
#   Tables take 10 units of lumber and 5 hours of labour, makes $180
#   Bookcases take 20 units of lumber and 4 hours of labour, makes $200
#   have: 200 units of lumber, 80 hours
#   want to maximize profit within constraints
#
# # _actual_ solution is 3.33 tables and 13.33 bookshelves (cant sell .33 of a bookshelf though)
# In order to increase computational speed, the CP-SAT solver works over the integers (no floats)

from ortools.sat.python import cp_model

from util import print_statistics

model = cp_model.CpModel()

total_hours = 80
total_wood = 200

wood_per_table = 10
wood_per_bookshelf = 20
max_tables = total_wood // wood_per_table
max_bookcases = total_wood // wood_per_bookshelf

# Create Variables
tables = model.new_int_var(lb=0, ub=max_tables, name="hours")
bookcases = model.new_int_var(lb=0, ub=max_bookcases, name="bookcases")

# Constraint 1: we can't use more time than we have
model.add(5 * tables + 4 * bookcases <= total_hours)

# Constraint 2: we can't use more wood than we have
model.add(10 * tables + 20 * bookcases <= total_wood)

# We want to maximize profit
profit = 180 * tables + 200 * bookcases
model.maximize(profit)

# Solve
solver = cp_model.CpSolver()
status = solver.solve(model)

if status in [cp_model.OPTIMAL, cp_model.FEASIBLE]:
    profit = solver.value(profit)
    tables = solver.value(tables)
    bookcases = solver.value(bookcases)

    print("Solution Found:")
    # fmt: off
    print(f"Tables:    {tables}\n"
          f"Bookcases: {bookcases}\n"
          f"Profit:    {profit}")
    # fmt: on
    print_statistics(solver)
else:
    print("No solution found :(")
