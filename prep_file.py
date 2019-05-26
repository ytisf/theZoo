#!/usr/bin/python

import os
import sys
import hashlib

try:
    import pyminizip
except ImportError:
    sys.stderr.write("Could not import 'pyminizip'. Did you install requirements?\n")
    sys.stderr.write("You can always just get 'pyminizip' by 'pip install --user pyminizip'.\n")
    sys.exit(1)


OUTPUT_FOLDER = "OUTPUT"


def _help():
    """
    hmmmm. nope.
    :return:
    """
    print("Please run with '%s filename'." % sys.argv[0])
    return


def _Do(file_path):
    """
    Prep file from file path for submission. Take file name, encrypt in ZIP with password 'infected', create MD5
    and SHA1 sums and store all of that in a directory of it's own.
    :param file_path: str
    :return: Bool
    """
    if not os.path.isfile(file_path):
        _help()
        sys.stderr.write("Seems like '%s' is not a file.\n" % file_path)
        return False

    try:
        os.mkdir(OUTPUT_FOLDER)
    except OSError:
        sys.stderr.write("Folder exists. Please remove it before continuing.\n")
        return False

    if "\\" in file_path:
        filename = file_path.split("\\")[:-1]
    elif "/" in file_path:
        filename = file_path.split("/")[:-1]
    else:
        filename = file_path

    # Create ZIP Archive:
    # We used 7z because 'zipfile' did not support adding a password. Apparently 'pyminizip' works just as well.
    try:
        pyminizip.compress(file_path, OUTPUT_FOLDER, "%s.zip" % filename, "infected", 9)
    except Exception as e:
        sys.stderr.write("Unknown error occurred. Please report this to us so that we can fix this.\n")
        sys.stderr.write(str(e))
        return False

    compressed_path = '%s/%s.zip' % (OUTPUT_FOLDER, filename)
    sys.stdout.write("[+]\tCreated ZIP Archive.\n")
    md5sum = hashlib.md5(open(compressed_path, 'rb').read()).hexdigest()
    sha1sum = hashlib.sha1(open(compressed_path, 'rb').read()).hexdigest()
    open("%s/%s.md5" % (OUTPUT_FOLDER, filename), 'w').write(md5sum)
    open("%s/%s.sha" % (OUTPUT_FOLDER, filename), 'w').write(sha1sum)
    open("%s/%s.pass" % (OUTPUT_FOLDER, filename), 'w').write("infected")
    return True


if __name__ == "__main__":
    if len(sys.argv) != 2:
        _help()
        sys.exit(1)
    stt = _Do(sys.argv[1])
    if stt:
        sys.stdout.write("Please don't forget to add details to 'conf/maldb.db' "
                         "and placing the folder in the appropriate directory.\n")
        sys.stdout.write("Thanks for helping us get this accessible to everyone.\n")
        sys.stdout.write("\n")
        sys.exit(0)
    else:
        sys.exit(1)
    
