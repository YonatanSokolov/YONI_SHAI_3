import mykmeanssp

import sys
import numpy as np


INVALID_INPUT_MSG = 'Invalid Input!'
ERROR_MSG = 'An Error Has Occurred'

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
    assert args[2].endswith(('.txt', '.csv'))
    k = int(args[0])
    assert k >= 0
    return k, goals[args[1]], args[2]

def kmeans_pp(vectors: np.ndarray):
    """
    runs k-means++ algorithms and returns its result (k = dim.)
    """
    num_vecs, dim = vectors.shape
    np.random.seed(0)
    centroids = [ np.random.choice(num_vecs) ]
    norm_squared = lambda v: np.inner(v, v)

    for _ in range(1, dim):
        P = np.fromiter(
            (
                min(
                    norm_squared(vectors[l] - vectors[j]) for j in centroids
                ) 
                for l in range(num_vecs)
            ), 
            float
        ) 
        P = P / np.sum(P)
        centroids.append(np.random.choice(num_vecs, p=P))
    print(','.join(str(i) for i in centroids))
    return vectors[centroids]


def main():
    try:
        k, goal, input_file_name = get_input()
    except:
        sys.exit(INVALID_INPUT_MSG)
    try:
        if goal == goals['spk']:
            vectors = mykmeanssp.transform(input_file_name, k)
            initial_centroids = kmeans_pp(vectors)
            assert mykmeanssp.kmeans(
                vectors, initial_centroids, *vectors.shape
                ) == 0
        else:
            assert mykmeanssp.run(goal, input_file_name) == 0
    except:
        sys.exit(ERROR_MSG)

if __name__ == '__main__':
    main()