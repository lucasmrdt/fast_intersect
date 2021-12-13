#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <iostream>
#include <unordered_set>

static PyObject *intersection_1(PyObject *self, PyObject *args) {
  PyObject *l1, *l2;

  if (!PyArg_ParseTuple(args, "OO", &l1, &l2)) {
    return nullptr;
  }
  if (!PyList_Check(l1) || !PyList_Check(l2)) {
    PyErr_SetString(PyExc_TypeError, "both arguments must be lists");
    return nullptr;
  }
  if (PyList_Size(l1) > PyList_Size(l2)) {
    PyObject *tmp = l1;
    l1 = l2;
    l2 = tmp;
  }
  PyObject *result = PyList_New(0);
  std::unordered_set<Py_hash_t> s1(PyList_Size(l1));
  for (int i = 0; i < PyList_Size(l1); i++) {
    PyObject *item = PyList_GetItem(l1, i);
    s1.insert(PyObject_Hash(item));
  }
  for (int i = 0; i < PyList_Size(l2); i++) {
    PyObject *item = PyList_GetItem(l2, i);
    if (s1.find(PyObject_Hash(item)) != s1.end()) {
      PyList_Append(result, item);
    }
  }

  return result;
}

static PyObject *intersection_2(PyObject *self, PyObject *args) {
  PyObject *l1, *l2;

  if (!PyArg_ParseTuple(args, "OO", &l1, &l2)) {
    return nullptr;
  }
  if (!PyList_Check(l1) || !PyList_Check(l2)) {
    PyErr_SetString(PyExc_TypeError, "both arguments must be lists");
    return nullptr;
  }
  if (PyList_Size(l1) > PyList_Size(l2)) {
    PyObject *tmp = l1;
    l1 = l2;
    l2 = tmp;
  }
  PyObject *result = PyList_New(0);
  PyList_Sort(l1);
  PyList_Sort(l2);
  int i = 0, j = 0;
  for (; i < PyList_Size(l1) && j < PyList_Size(l2);) {
    PyObject *item1 = PyList_GetItem(l1, i);
    PyObject *item2 = PyList_GetItem(l2, j);
    if (PyObject_RichCompareBool(item1, item2, Py_LT) == 1) {
      PyList_Append(result, item1);
      i++;
    } else if (PyObject_RichCompareBool(item1, item2, Py_GT) == 1) {
      j++;
    } else {
      PyList_Append(result, item1);
      i++;
      j++;
    }
  }

  return result;
}

static PyMethodDef methods[] = {
    {"intersection_1", intersection_1, METH_VARARGS, "Intersect 2 sets."},
    {"intersection_2", intersection_2, METH_VARARGS, "Intersect 2 sets."},
    {nullptr, nullptr, 0, nullptr}};

static struct PyModuleDef module = {PyModuleDef_HEAD_INIT, "fast_intersect",
                                    nullptr, -1, methods};

PyMODINIT_FUNC PyInit_fast_intersect(void) { return PyModule_Create(&module); }