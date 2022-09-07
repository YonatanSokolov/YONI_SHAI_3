from setuptools import setup, find_packages, Extension

setup(
    name='mykmeanssp',
    packages=find_packages(),
    ext_modules=[
        Extension('mykmeanssp',[
            'calculate_w.c', 
            'datastructures.c', 
            'eigengap.c', 
            'Jacobi_algo.c', 
            'kmeans.c', 
            'lnorm.c', 
            'myIO.c',
            'spkmeans.c', 
            ])
        ]
)