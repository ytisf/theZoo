#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Name: Prep File
Author: ytisf
Date of Creation: Unknown
Last Modified: May 26, 2019

Dev: K4YT3X
Last Modified: August 21, 2019

Licensed under the GNU General Public License Version 3 (GNU GPL v3),
    available at: https://www.gnu.org/licenses/gpl-3.0.txt
(C) 2014-2019 ytisf
"""

# built-in imports
import hashlib
import pathlib
import sys
import time
import traceback

try:
    import pyzipper
except ImportError as e:
    print('Could not import "pyzipper". Did you install requirements?', file=sys.stderr)
    print('You can always just get "pyzipper" by "pip install --user pyzipper"', file=sys.stderr)
    raise e


COMPRESSION_PASSWORD = 'infected'
OUTPUT_FOLDER = pathlib.Path('OUTPUT')


def print_help():
    """ print help message

    print program help message and return None
    """
    print(f'usage: {__file__} [INPUT_FILE]')
    return


def prepare_file(file_path):
    """ prep file from file path for submission

    take file name, encrypt in ZIP with password 'infected', create MD5
    and SHA1 sums and store all of that in a directory of it's own

    Arguments:
        file_path {pathlib.Path} -- path object of input file
    """
    OUTPUT_FOLDER.mkdir(parents=True, exist_ok=True)

    # create ZIP Archive
    # we are using 7z because "zipfile" did not support adding a password
    # Apparently "pyminizip" works just as well.
    print('Info: Creating encrypted ZIP archive')
    with pyzipper.AESZipFile(OUTPUT_FOLDER / f'{file_path.name}.zip', 'w', compression=pyzipper.ZIP_LZMA, encryption=pyzipper.WZ_AES) as zip_file:
        zip_file.setpassword(COMPRESSION_PASSWORD.encode())
        zip_file.write(file_path)
    print('Info: Created ZIP archive')

    # calculating file hashes
    md5sum = hashlib.md5(open(OUTPUT_FOLDER / f'{file_path.name}.zip', 'rb').read()).hexdigest()
    sha1sum = hashlib.sha1(open(OUTPUT_FOLDER / f'{file_path.name}.zip', 'rb').read()).hexdigest()

    # writing file hashes and password to files
    open(OUTPUT_FOLDER / f'{file_path.name}.md5', 'w').write(md5sum)
    open(OUTPUT_FOLDER / f'{file_path.name}.sha', 'w').write(sha1sum)
    open(OUTPUT_FOLDER / f'{file_path.name}.pass', 'w').write(COMPRESSION_PASSWORD)


# start timer
start_time = time.time()

# if this file is being imported
if __name__ != '__main__':
    print('Error: This file cannot be imported', file=sys.stderr)
    ImportError('File not importable')

# check if there's a right amount of arguments provided
if len(sys.argv) != 2:
    print_help()
    exit(1)

# convert input file path into file object
try:
    input_file = pathlib.Path(sys.argv[1])
except Exception:
    print('Error: input file format invalid', file=sys.stderr)

# input file validity check
if not input_file.is_file():
    print_help()
    print(f'Seems like {str(input_file)} is not a file', file=sys.stderr)
    exit(1)

# zip file
try:
    prepare_file(input_file)
except Exception:
    print('Unexpected exception has been caught')
    print('Compression has failed')
    print('Please report the following error message to us so we can fix it')
    traceback.print_exc()
    exit(1)

print('Script finished')
print(f'Time taken: {round((time.time() - start_time), 5)} seconds')
print('Please don\'t forget to add details to "conf/maldb.db" and placing the folder in the appropriate directory')
print('Thanks for helping us to get this accessible to everyone')
