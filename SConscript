# -*- python -*-
# $Header: /nfs/slac/g/glast/ground/cvs/Interleave/SConscript,v 1.10.4.1 2011/08/19 02:48:09 heather Exp $
# Authors: T. Burnett <tburnett@u.washington.edu> 
# Version: Interleave-01-06-07-tr01
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
             xml=listFiles(['xml/*]'),
             jo=['src/test/jobOptions.txt', 'src/interleave.txt',
                 'src/test/testXml/jobOptionsXml.txt'])




