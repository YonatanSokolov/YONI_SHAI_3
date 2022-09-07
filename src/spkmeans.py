import mykmeanssp

import sys
import numpy as np
import pandas as pd

INVALID_INPUT_MSG = 'Invalid Input!'
ERROR_MSG = 'An Error Has Occurred'

# typedef enum {WAM, DDG, LNORM, JACOBI, INVALID} GOAL;
goals = {
    'spk' : -1,
    'wam' : 0,
    'ddg' : 1,
    'lnorm' : 2,
    'jacobi' : 3,
}


def get_input():
    """returns k, goal, input_file_name"""
    args = sys.argv[1:]
    assert len(args) == 3
    assert args[3].endswith(('.txt', '.csv'))
    k = int(args[0])
    assert k > 0
    return k, goals[args[1]], args[2]

def kmeans_pp(vectors: np.ndarray):
    pass

def main():
    try:
        k, goal, input_file_name = get_input()
    except:
        sys.exit(INVALID_INPUT_MSG)
    try:
        if goal == -1:
            vectors = mykmeanssp.fit(k, input_file_name)
            initial_centroids = kmeans_pp(vectors)
            mykmeanssp.kmeans(vectors, initial_centroids)
        else:
            mykmeanssp.run(goal, input_file_name)
    except:
        sys.exit(ERROR_MSG)
    pass

if __name__ == '__main__':
    main()