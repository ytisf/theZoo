#!/usr/bin/python

import os
import sys
import zipfile
import hashlib
import subprocess


OUTPUT_FOLDER = "OUTPUT"


def _help():
    print("Please run with '%s filename'." % sys.argv[0])
    return

def _Do(file_path):
    if not os.path.isfile(file_path):
        _help()
        print("Seems like '%s' is not a file." % file_path)
        sys.exit(1)

    try:
        os.mkdir(OUTPUT_FOLDER)
    except OSError:
        print("Folder exists. Please remove it before continuing.")
        sys.exit(1)

    if "\\" in file_path:
        filename = file_path.split("\\")[:-1]
    elif "/" in file_path:
        filename = file_path.split("/")[:-1]
    else:
        filename = file_path

    # Create ZIP Archive:
    try:
        rc = subprocess.call(['7z', 'a', '-pinfected', '-y', '%s/%s.zip' % (OUTPUT_FOLDER, filename)] + [file_path])
    except:
        print("Seems like you don't have 7z in your path. Please install or add with:\n\tbrew install 7zip #(OSX)\n\tsudo apt-get install p7zip-full #(Linux)")
        sys.exit(1)

    compressed_path = '%s/%s.zip' % (OUTPUT_FOLDER, filename)
    print("Created ZIP Archive.")
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
    _Do("README.md")
    print("Please don't forget to add details to 'conf/maldb.db'.")
    print("Thanks for helping us get this accessible to everyone.")
    print("")
