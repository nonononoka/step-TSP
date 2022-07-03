from common import  read_input,format_tour, read_input

import TSP

CHALLENGES = 2


def generate_sample_output():
    for i in range(CHALLENGES,CHALLENGES+1):
        
        cities = read_input(f'input_{i}.csv')
        tour = TSP.solve(cities)
        print(tour)
        with open(f'output_{i}.csv', 'w') as f:
            f.write(format_tour(tour) + '\n')
      


if __name__ == '__main__':
    generate_sample_output()