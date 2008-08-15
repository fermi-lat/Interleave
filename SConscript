# -*- python -*-
# $Header$
# Authors: T. Burnett <tburnett@u.washington.edu> 
# Version: Interleave-00-08-01
Import('baseEnv')
Import('listFiles')
Import('packages')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('InterleaveLib', depsOnly = 1)
Interleave = libEnv.SharedLibrary('Interleave', listFiles(['src/*.cxx']) + listFiles(['src/Dll/*.cxx']))


progEnv.Tool('InterleaveLib')
test_Interleave = progEnv.GaudiProgram('test_Interleave', ['src/test/*.cxx'], test = 1)

progEnv.Tool('registerObjects', package = 'Interleave', libraries = [Interleave], testApps = [test_Interleave])
