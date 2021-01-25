import os
import sys
import argparse
from pathlib import Path
import shutil
import subprocess
import glob

# Edit compiler flags for your system
COMPILER_NAME = 'avr-gcc'
COMPILER_FLAGS = '-mmcu=atmega328p -Os -DBACKEND=2 -DF_CPU=16000000UL -DBAUD=9600 -Wall -Wno-main -Wundef -pedantic -Wno-unused-variable -Werror -Wfatal-errors -Wl,--relax,--gc-sections -g -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -fno-split-wide-types -fno-tree-scev-cprop'
LINKER_NAME = 'avr-gcc'
LINKER_FLAGS = '-mmcu=atmega328p'

INCLUDE_PATH = '-I'+os.path.abspath('../../../src') # Relative to this src/ directory

COMPILE_TARGET = 'atmega328p'

THIS_DIRECTORY = os.path.dirname(os.path.realpath(__file__))
HAL_OUTPUT_DIRECTORY = '../../../build/output'

def get_compile_list(list_file):
    list_compile_c_files = []

    with open(list_file) as default_files:
        for line in default_files:
            if line.startswith('#include'): # If we want to include another list
                include_file = line.split(' ')[1].strip('\n')
                iList = get_compile_list(include_file)
                for iElement in iList:
                    list_compile_c_files.append(iElement)
            elif not line.startswith('#') and not line.isspace():
                if line not in list_compile_c_files: # Catch duplicates
                    list_compile_c_files.append(line.rstrip('\n'))
    return list_compile_c_files

def convert_c_filename_to_o(c_file_name):
    file_name_raw = c_file_name.split(".")[0]
    return file_name_raw+'.o'
def convert_path_to_filename(path_file):
    return path_file.split('/')[-1]
def mkdir_for_output_file(file_name):
    arr=file_name.split('/')
    directory=''
    for i in range(0,len(arr)-1): #assumes working directory is src/. If changed to build/, make start index 2
        directory+=arr[i]+'/'
    Path(directory).mkdir(parents=True, exist_ok=True)

def main():
    parser=argparse.ArgumentParser()
    args=parser.parse_args()

    # First, compile HAL and add .o files to linker list
    os.system('python3 ../../../build/compile.py --target='+COMPILE_TARGET)
    executable_list_string = ''
    os.chdir(HAL_OUTPUT_DIRECTORY)
    print("Switching directories to: "+HAL_OUTPUT_DIRECTORY)
    for f in glob.glob("**/*.o", recursive=True):
        executable_list_string += HAL_OUTPUT_DIRECTORY+'/'+f+' '
    print("Switching directories to: "+THIS_DIRECTORY)
    os.chdir(THIS_DIRECTORY)

    compile_list = get_compile_list('targets/default/files.txt')
    if compile_list is None:
        print("No files to be compiled! Check your compilation list!")
        exit(-1)

    # Clean output folder
    print('Cleaning output directory...')
    if os.path.exists('output/'):
        shutil.rmtree('output/')
    os.mkdir('output/')
    print('Done')

    print('Beginning compilation...')
    # Change directory to src/
    os.chdir('../src/')

    for file_name in compile_list:
        executable_location = '../build/output/'+file_name+'.o'
        mkdir_for_output_file(executable_location)
        executable_list_string += executable_location+' '
        cmd = (COMPILER_NAME+' '+INCLUDE_PATH+' '+COMPILER_FLAGS+' -c -o '+executable_location+' '+file_name)
        print('Compiling with command: '+cmd)
        os.system(cmd)

    binary_location = '../build/output/eos.elf'
    link = (LINKER_NAME+' '+LINKER_FLAGS+' -o '+binary_location+' '+executable_list_string)    
    print('Linking with command: '+link)
    os.system(link)

    # Change back to build/
    os.chdir('../build/')

    post_script = 'targets/default/postprocessing.sh'
    if os.path.isfile(post_script): # If a postprocessing script is given
        print('Executing postprocessing script...')
        subprocess.call(['bash', '../'+post_script], cwd='output/')

    print('Finished')

if __name__ == "__main__":
    main()