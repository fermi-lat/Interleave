# -*- python -*-
# $Header: /nfs/slac/g/glast/ground/cvs/Interleave/SConscript,v 1.7 2009/12/16 19:40:08 usher Exp $
# Authors: T. Burnett <tburnett@u.washington.edu> 
# Version: Interleave-01-06-06
Import('baseEnv')
Import('listFiles')
Import('packages')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('InterleaveLib', depsOnly = 1)
Interleave = libEnv.SharedLibrary('Interleave', listFiles(['src/*.cxx']) + listFiles(['src/Dll/*.cxx']))


progEnv.Tool('InterleaveLib')
test_Interleave = progEnv.GaudiProgram('test_Interleave',
                                       listFiles(['src/test/*.cxx']), test = 1)

progEnv.Tool('registerTargets', package = 'Interleave',
             libraryCxts = [[Interleave,libEnv]],
             testAppCxts = [[test_Interleave, progEnv]])




