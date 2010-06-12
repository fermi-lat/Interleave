# -*- python -*-
# $Header: /nfs/slac/g/glast/ground/cvs/Interleave/SConscript,v 1.9 2010/06/11 00:38:05 jrb Exp $
# Authors: T. Burnett <tburnett@u.washington.edu> 
# Version: Interleave-01-06-07
Import('baseEnv')
Import('listFiles')
Import('packages')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('addLinkDeps', package='Interleave', toBuild='component')
Interleave = libEnv.SharedLibrary('Interleave',
                                  listFiles(['src/*.cxx', 'src/Dll/*.cxx']))


progEnv.Tool('InterleaveLib')
test_Interleave = progEnv.GaudiProgram('test_Interleave',
                                       listFiles(['src/test/*.cxx']),
                                       test = 1, package='Interleave')

progEnv.Tool('registerTargets', package = 'Interleave',
             libraryCxts = [[Interleave,libEnv]],
             testAppCxts = [[test_Interleave, progEnv]],
             jo=['src/test/jobOptions.txt', 'src/interleave.txt',
                 'src/test/testXml/jobOptionsXml.txt'])




