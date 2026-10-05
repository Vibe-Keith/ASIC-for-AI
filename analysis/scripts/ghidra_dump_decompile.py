# @runtime Jython
from ghidra.app.decompiler import DecompInterface
from ghidra.util.task import ConsoleTaskMonitor
import os
out = getScriptArgs()[0]
di = DecompInterface(); di.openProgram(currentProgram)
fm = currentProgram.getFunctionManager()
f = open(out, "w")
for fn in fm.getFunctions(True):
    r = di.decompileFunction(fn, 120, ConsoleTaskMonitor())
    f.write("\n//==== %s @ %s size=%d\n" % (fn.getName(), fn.getEntryPoint(), fn.getBody().getNumAddresses()))
    if r and r.decompileCompleted():
        f.write(r.getDecompiledFunction().getC())
    else:
        f.write("// decompile failed\n")
f.close()
