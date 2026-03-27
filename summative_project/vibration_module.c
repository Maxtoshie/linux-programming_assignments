#include <Python.h>
#include <math.h>

/**
 * peak_to_peak - Calculates difference between max and min
 */
static PyObject *method_peak_to_peak(PyObject *self, PyObject *args)
{
	PyObject *list;
	Py_ssize_t i, n;
	double min_v, max_v, current;

	if (!PyArg_ParseTuple(args, "O", &list))
		return (NULL);

	n = PyList_Size(list);
	if (n == 0) return PyFloat_FromDouble(0.0);

	min_v = max_v = PyFloat_AsDouble(PyList_GetItem(list, 0));
	for (i = 1; i < n; i++)
	{
		current = PyFloat_AsDouble(PyList_GetItem(list, i));
		if (current < min_v) min_v = current;
		if (current > max_v) max_v = current;
	}
	return PyFloat_FromDouble(max_v - min_v);
}

static PyMethodDef VibrationMethods[] = {
	{"peak_to_peak", method_peak_to_peak, METH_VARARGS, "Calculate peak-to-peak"},
	{NULL, NULL, 0, NULL}
};

static struct PyModuleDef vibrationmodule = {
	PyModuleDef_HEAD_INIT, "vibration", NULL, -1, VibrationMethods
};

PyMODINIT_FUNC PyInit_vibration(void)
{
	return PyModule_Create(&vibrationmodule);
}
