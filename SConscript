# -*- python -*-
# $Header: /nfs/slac/g/glast/ground/cvs/GlastRelease-scons/Interleave/SConscript,v 1.17 2012/01/08 01:48:01 lsrea Exp $
# Authors: T. Burnett <tburnett@u.washington.edu> 
# Version: Interleave-01-07-02
Import('baseEnv')
Import('listFiles')
Import('packages')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('addLinkDeps', package='Interleave', toBuild='component')
Interleave = libEnv.ComponentLibrary('Interleave',
                                     listFiles(['src/*.cxx']))


progEnv.Tool('InterleaveLib')
test_Interleave = progEnv.GaudiProgram('test_Interleave',
                                       listFiles(['src/test/*.cxx']),
                                       test = 1, package='Interleave')

progEnv.Tool('registerTargets', package = 'Interleave',
             libraryCxts = [[Interleave,libEnv]],
             testAppCxts = [[test_Interleave, progEnv]],
             xml= listFiles(['xml/*']),
             jo=['src/test/jobOptions.txt', 'src/interleave.txt',
                 'src/test/testXml/jobOptionsXml.txt'])




