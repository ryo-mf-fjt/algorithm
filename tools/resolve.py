import sys, os, re


def resolve(fn):
    code = open(fn).read()
    return re.sub(
        r'^#include "(.+)"$',
        lambda match: resolve(os.path.join(os.path.dirname(fn), match.group(1))),
        code,
        flags=re.MULTILINE,
    )


print(resolve(sys.argv[1]))
