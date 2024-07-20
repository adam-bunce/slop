from dataclasses import dataclass
from typing import Literal
from ortools.sat.python import cp_model

# https://www.csplib.org/Problems/prob001/


@dataclass
class CarInfo:
    index: int
    required_number: int
    options: list[Literal[1, 0]]


class CarSequencingSolutionPrinter(cp_model.CpSolverSolutionCallback):
    def __init__(
        self, sequence: list[list[cp_model.IntVar]], cars_to_make: list[CarInfo]
    ):
        cp_model.CpSolverSolutionCallback.__init__(self)
        self.__sequence = sequence
        self.__cars_to_make = cars_to_make
        self.__solutions_count = 0

    def on_solution_callback(self):
        self.__solutions_count += 1
        for car in self.__sequence:
            for pos, car_class in enumerate(car):
                if self.value(car_class) == 1:
                    print(car_class, self.__cars_to_make[pos].options)
        print()

    @property
    def solutions_count(self) -> int:
        return self.__solutions_count


def main() -> None:
    model = cp_model.CpModel()
    num_cars: int = 10
    num_options: int = 5
    num_classes: int = 6

    block_limits: list[int] = [1, 2, 1, 2, 1]
    block_sizes: list[int] = [2, 3, 3, 5, 5]
    assert len(block_limits) == len(block_sizes)

    cars_to_make: list[CarInfo] = [
        CarInfo(0, 1, [1, 0, 1, 1, 0]),
        CarInfo(1, 1, [0, 0, 0, 1, 0]),
        CarInfo(2, 2, [0, 1, 0, 0, 1]),
        CarInfo(3, 2, [0, 1, 0, 1, 0]),
        CarInfo(4, 2, [1, 0, 1, 0, 0]),
        CarInfo(5, 2, [1, 1, 0, 0, 0]),
    ]

    sequence = [
        [model.new_bool_var(f"car_{car.index}") for car in cars_to_make]
        for _ in range(num_cars)
    ]

    # Constraint 1: We need to make enough cars of each class
    for car_class in range(num_classes):
        model.add(
            sum(position[car_class] for position in sequence)
            == cars_to_make[car_class].required_number
        )

    # Constraint 2: we can only make one car at a time
    for car_class in sequence:
        model.add_exactly_one(car_class)

    for option in range(num_options):
        block_size = block_sizes[option]
        block_limit = block_limits[option]

        l, r = 0, block_size - 1
        while r < num_cars:

            # Constraint 3: we can't exceed the limit for each feature block
            model.add(
                sum(
                    [
                        is_class * cars_to_make[car_class].options[option]
                        for possible_cars in sequence[l : r + 1]
                        for car_class, is_class in enumerate(possible_cars)
                    ]
                )
                <= block_limit
            )

            r += 1
            l += 1

    solver = cp_model.CpSolver()
    solver.parameters.enumerate_all_solutions = True
    solutions_printer = CarSequencingSolutionPrinter(sequence, cars_to_make)
    solver.Solve(model, solutions_printer)
    print(f"Number of solutions: {solutions_printer.solutions_count}")


if __name__ == "__main__":
    main()
