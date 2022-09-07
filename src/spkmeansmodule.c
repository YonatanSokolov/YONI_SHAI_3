#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

#include "spkmeans.h"
#include <Python.h>
#include <numpy/arrayobject.h>

static MATRIX matrix_from_python_array(PyArrayObject *py_arr) {
    MATRIX M;
    unsigned *dims = (unsigned *) PyArray_DIMS(py_arr);
    M.num_rows = dims[0];
    M.num_cols = dims[1];
    M.data = (double *) PyArray_DATA(py_arr);
    return M;
}

PyMODINIT_FUNC PyInit_mykmeanssp(void);

static PyObject* _run(PyObject* self, PyObject *args);
static PyObject* _transform(PyObject* self, PyObject *args);
static PyObject* _kmeans(PyObject* self, PyObject *args);

static PyMethodDef methods[] = {
    {"run", (PyCFunction) _run, METH_VARARGS, PyDoc_STR("Run partial algorithms")},
    {"transform", (PyCFunction) _transform, METH_VARARGS, PyDoc_STR("Perform spectralization")},
    {"kmeans", (PyCFunction) _kmeans, METH_VARARGS, PyDoc_STR("Cluster via kmeans")},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef module_def = {
    PyModuleDef_HEAD_INIT,
    "mykmeanssp",
    NULL,
    -1,
    methods
};

PyMODINIT_FUNC PyInit_mykmeanssp() {
    import_array()
    PyObject *m;
    m = PyModule_Create(&module_def);
    if (!m)
        return NULL;
    return m;
}

static PyObject* _run(PyObject* self, PyObject *args) {
    GOAL goal; 
    char *input_file_name;
    if (!PyArg_ParseTuple(args, "is", &goal, &input_file_name))
        return NULL;
    return Py_BuildValue("i", run(goal, input_file_name));
}

static PyObject* _transform(PyObject* self, PyObject *args) {
    unsigned k, dims[2]; 
    char *input_file_name;
    MATRIX res;
    if (!PyArg_ParseTuple(args, "sI", &input_file_name, &k))
        return NULL;
    res = spectralization(input_file_name, k);
    dims[0] = res.num_rows;
    dims[1] = res.num_cols;
    return Py_BuildValue("O", PyArray_SimpleNewFromData(2, (npy_intp *) dims, NPY_DOUBLE, res.data));
}

static PyObject* _kmeans(PyObject* self, PyObject *args) {
    PyArrayObject *vectors, *intial_centroids;
    if (!PyArg_ParseTuple(args, "O!O!", &PyArray_Type, &vectors, 
                                        &PyArray_Type, &intial_centroids))
        return NULL;
    return Py_BuildValue("i", kmeans(matrix_from_python_array(vectors), 
                                     matrix_from_python_array(intial_centroids)));
}
