# $Header: /nfs/slac/g/glast/ground/cvs/GlastRelease-scons/Interleave/InterleaveLib.py,v 1.3 2009/11/13 23:22:40 jrb Exp $
def generate(env, **kw):
    if not kw.get('depsOnly', 0):
        env.Tool('addLibrary', library = ['Interleave'])
    env.Tool('rootUtilLib')
    env.Tool('FluxSvcLib')
    env.Tool('EventLib')
    env.Tool('xmlBaseLib')
    env.Tool('facilitiesLib')
    env.Tool('addLibrary', library = env['gaudiLibs'])
    env.Tool('addLibrary', library = env['clhepLibs'])
    env.Tool('addLibrary', library = env['xercesLibs'])
    if env['PLATFORM']=='win32' and env.get('CONTAINERNAME','')=='GlastRelease':
        env.Tool('findPkgPath', package = 'RootIo') 
def exists(env):
    return 1;
