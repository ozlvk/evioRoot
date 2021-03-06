#-----------------------------------------------------------------------
#  SConstruct file for compiling the GooLibrary (date: 09/23/2011)
#  The New version includes Configure script for scons to determine
#  if the system has all neccessary components installed.
#
#  NOTE: Mainly needed libraries are HDF5 - for data input/output
#        also Minuit2 is needed if MINUIT fitting is to be used.
#        if   Minuit2 does not exist the genetic fitting algorythm
#        can be used to do the fits.
#-----------------------------------------------------------------------
import glob
import os
import sys
from loadROOTLibrary import initROOTLibrary
#-----------------------------------------------------------------------
#  Trying to Load modules for compilation scripts
#-----------------------------------------------------------------------
if os.getenv('ROOTSYS') == None:
   print '****************************************'
   print '**************   ERROR  ****************'
   print '****************************************'
   print '\n The environmental variable ROOTSYS is not set. Please set it'
   print '\n\n'
   sys.exit(1)
#-----------------------------------------------------------------------
#  Loaded the Library Files.
#-----------------------------------------------------------------------
#env = Environment(CPPPATH=["/opt/local/include","include",".","src/evioroot","src/reader"])
env = Environment(CPPPATH=["/opt/local/include","include",".","src/root","src/reader","src/tools"])
env.Append(ENV = os.environ)
env.Append(CPPPATH=["src/root","src/evio"])
env.Append(CCFLAGS=["-O2","-fPIC","-m64","-fmessage-length=0","-g"])
#env.Append(CCFLAGS=["-O2","-fPIC","-m32","-fmessage-length=0"])
env.Append(LIBPATH=["/opt/local/lib","/usr/lib","lib"])
#env.Append(LIBS=["iG5io"])
#-----------------------------------------------------------------------
#  Parsing input Arguments
#-----------------------------------------------------------------------
compileMode = ARGUMENTS.get('debug',0)

if ARGUMENTS.get('verbose') != '1':
   print 'Entering quite mode. type scons verbose=1 for more output'
#   env['CXXCOMSTR']  = "--> Compiling : $TARGET"
#   env['CCCOMSTR']   = "--> Compiling : $TARGET"
   env['LINKCOMSTR'] = "[==] --> Linking : $TARGET"
#   env['ARCOMSTR']   = "[==] --> Archiving : $TARGET"
   env.Append(CCFLAGS=["-w"])

if int(compileMode):
   print '-->  Compiling library in debug mode...'
   env.Append(CCFLAGS=['-g'])

if os.getenv('OSTYPE') != None:
   if os.getenv('OSTYPE')=='darwin':
      env.Append(CCFLAGS=['-DDarwin'])
#------------------------------------------------------------------------
# Check Essential setup of enviromental variables (GOOLIB and HDF5_DIR) -
#------------------------------------------------------------------------
conf = Configure(env)

if not conf.CheckLib('libexpat'):
   print '\n---> Please install XML2 library..'
   sys.exit(1)

if not conf.CheckLib('libdl'):
   sys.exit(1)

if not conf.CheckLib('libpthread'):
   sys.exit(1)

env = conf.Finish()

#------------------------------------------------------------------------
#  Compile the libraries
#------------------------------------------------------------------------
# List of the files for HDF5/IO library
#
#rootcint -f TEventReaderDict.cc -c -p -I../writer TEventReader.h TEventReaderLinkDef.h
#env.Command('env','','env | grep LD_',ENV = {'LD_LIBRARY_PATH','ROOT'})


initROOTLibrary(env)

env.Append(LIBS=["XMLParser","XMLIO"])

listEVIOLIB = glob.glob('src/evio/*.cc') + glob.glob('src/evio/*.c')
listROOTLIB = glob.glob('src/root/*.cc')
listCPPLIB  = glob.glob('src/reader/*.cc')
listTOOLS   = glob.glob('src/tools/*.cc')
listDECODER = ['src/convertor/evio2root.cc']

if 'src/root/TTreeEvioDict.cc' in listROOTLIB:
   listDICT = []


env.Program(target="bin/evio2root",source = listEVIOLIB + listCPPLIB + listDECODER)


