from common import  read_input,format_tour, read_input

import TSP

CHALLENGES = 6


def generate_sample_output():
    for i in range(CHALLENGES):
        
        cities = read_input(f'input_{i}.csv')
        tour = TSP.solve(cities)
        with open(f'output_{i}.csv', 'w') as f:
            f.write(format_tour(tour) + '\n')
        print(i)


if __name__ == '__main__':
    generate_sample_output()