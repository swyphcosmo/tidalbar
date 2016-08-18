#include <Python.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>

static PyObject* keypress_helloworld( PyObject* self, PyObject* args )
{
	printf( "Hello World!\n" );

	Py_RETURN_NONE;
}

static PyObject* keypress_keypress( PyObject* self, PyObject* args )
{
	const char *character;

	if( !PyArg_ParseTuple(args, "s", &character ) )
		return NULL;

	system( "/bin/stty raw cbreak time 0 -echo" );
	
	bool retval = false;

	fd_set readfds;
	FD_ZERO( &readfds );
	FD_SET( STDIN_FILENO, &readfds );
	fd_set savefds = readfds;

	struct timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;

	if( select( 1, &readfds, NULL, NULL, &timeout ) )
	{
		char c = getchar();
		// printf( "\npressed: %c\n", c );

		fflush( stdin );

		if( c == character[ 0 ] )
			retval = true;
	}
	readfds = savefds;

	system( "/bin/stty cooked -cbreak echo" );

	return PyBool_FromLong( (long)retval );
}

static PyMethodDef keypressMethods[] = 
{
		{ "helloworld", keypress_helloworld, METH_VARARGS, "Print hello world." },
		{ "keypress", keypress_keypress, METH_VARARGS, "Detects whether key has been pressed." },
		{ NULL, NULL, 0, NULL }
};

static struct PyModuleDef keypressModule = 
{
	PyModuleDef_HEAD_INIT,
	"keypress",   /* name of module */
	NULL, /* module documentation, may be NULL */
	-1,       /* size of per-interpreter state of the module,
				or -1 if the module keeps state in global variables. */
	keypressMethods
};

PyMODINIT_FUNC PyInit_keypress( void )
{
	// (void)Py_InitModule( "keypress", keypressMethods );
	return PyModule_Create( &keypressModule );
}
