# $Header: /nfs/slac/g/glast/ground/cvs/GlastRelease-scons/Interleave/InterleaveLib.py,v 1.2 2008/11/10 16:04:51 ecephas Exp $
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
def exists(env):
    return 1;
