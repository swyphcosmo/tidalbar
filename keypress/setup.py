from distutils.core import setup, Extension

module1 = Extension( 'keypress', sources = [  'keypress.cpp' ] )

setup( name = 'KeyPress', version = 1.0, description = 'Asyc keyboard I/O in a console application', ext_modules = [ module1 ] )
