from setuptools import setup, find_packages, Extension
import numpy as np

setup(
    name='mykmeanssp',
    packages=find_packages(),
    ext_modules=[
        Extension('mykmeanssp',[
            'spkmeansmodule.c',
            'calculate_w.c', 
            'datastructures.c', 
            'eigengap.c', 
            'shaijacobi.c', 
            'kmeans.c', 
            'lnorm.c', 
            'myIO.c',
            'spkmeans.c', 
            ], include_dirs=[np.get_include()])
        ]
)