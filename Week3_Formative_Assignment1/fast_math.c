#define PY_SSIZE_T_CLEAN
#include <Python.h>

/**
 * fast_sum - calculates sum of squares in C
 * @self: pointer to module
 * @args: arguments from python
 *
 * Return: Python Long object
 */
static PyObject *fast_sum(PyObject *self, PyObject *args)
{
	long n, i, result = 0;

	if (!PyArg_ParseTuple(args, "l", &n))
		return (NULL);

	for (i = 0; i < n; i++)
		result += (i * i);

	return PyLong_FromLong(result);
}

static PyMethodDef FastMethods[] = {
	{"fast_sum", fast_sum, METH_VARARGS, "Calculate sum of squares"},
	{NULL, NULL, 0, NULL}
};

static struct PyModuleDef fastmathmodule = {
	PyModuleDef_HEAD_INIT, "fast_math", NULL, -1, FastMethods
};

/**
 * PyInit_fast_math - initializes the module
 *
 * Return: module pointer
 */
PyObject *PyInit_fast_math(void)
{
	return PyModule_Create(&fastmathmodule);
}
