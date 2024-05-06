import sys, re
from pathlib import Path


def resolve(fn: str, included: Path):
    code = open(fn).read()

    def replacer(fullpath: str):
        if fullpath in included:
            return ""

        included.add(fullpath)
        return resolve(fullpath, included)

    return re.sub(
        r'^#include "(.+)"$',
        lambda match: replacer((Path(fn).parent / match.group(1)).resolve()),
        code,
        flags=re.MULTILINE,
    )


included = set()
print("\n".join([resolve(fn, included) for fn in sys.argv[1:]]))
