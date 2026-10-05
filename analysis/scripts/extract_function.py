import sys,re
src=open('out/ks0.c' if len(sys.argv)<3 else sys.argv[2]).read()
parts=re.split(r'\n(?=//==== )',src)
for n in sys.argv[1].split(','):
    for p in parts:
        if p.startswith('//==== '+n+' '): print(p)
