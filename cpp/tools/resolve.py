import sys, os, re


def resolve(fn: str, included: set):
    code = open(fn).read()

    def replacer(fullpath: str):
        if fullpath in included:
            return ""

        included.add(fullpath)
        return resolve(fullpath, included)

    return re.sub(
        r'^#include "(.+)"$',
        lambda match: replacer(os.path.join(os.path.dirname(fn), match.group(1))),
        code,
        flags=re.MULTILINE,
    )


included = set()
print("\n".join([resolve(fn, included) for fn in sys.argv[1:]]))
