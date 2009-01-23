# -*- python -*-
# $Header: /nfs/slac/g/glast/ground/cvs/GlastRelease-scons/Interleave/SConscript,v 1.2 2008/11/10 16:01:32 ecephas Exp $
# Authors: T. Burnett <tburnett@u.washington.edu> 
# Version: Interleave-01-06-03
Import('baseEnv')
Import('listFiles')
Import('packages')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('InterleaveLib', depsOnly = 1)
Interleave = libEnv.SharedLibrary('Interleave', listFiles(['src/*.cxx']) + listFiles(['src/Dll/*.cxx']))


progEnv.Tool('InterleaveLib')
test_Interleave = progEnv.GaudiProgram('test_Interleave', listFiles(['src/test/*.cxx']), test = 1)

progEnv.Tool('registerObjects', package = 'Interleave', libraries = [Interleave], testApps = [test_Interleave])




