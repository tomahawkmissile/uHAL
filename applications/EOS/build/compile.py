import os
import sys
import argparse
from pathlib import Path
import shutil
import subprocess

# Edit compiler flags for your system
COMPILER_NAME = 'avr-gcc'
COMPILER_FLAGS = '-mmcu=atmega328p -DBACKEND=2 -Os -DF_CPU=16000000UL -DBAUD=9600 -Wall -Wno-main -Wundef -pedantic -Wno-unused-variable -Werror -Wfatal-errors -Wl,--relax,--gc-sections -g -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -fno-split-wide-types -fno-tree-scev-cprop'
LINKER_NAME = 'avr-gcc'
LINKER_FLAGS = '-mmcu=atmega328p'

def get_compile_list():
    list_compile_c_files = []

    with open('targets/default/files.txt') as default_files:
        for line in default_files:
            if line.startswith('#include'): # If we want to include another list
                include_file = line.split(' ')[1]
                with open(include_file) as included_file:
                    for included_line in included_file:
                        if included_line not in list_compile_c_files: # Duplication check
                            list_compile_c_files.append(included_line)
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

    compile_list = get_compile_list()
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

    executable_list_string = ''
    for file_name in compile_list:
        executable_location = '../build/output/'+file_name+'.o'
        mkdir_for_output_file(executable_location)
        executable_list_string += executable_location+' '
        cmd = (COMPILER_NAME+' '+COMPILER_FLAGS+' -c -o '+executable_location+' '+file_name)
        print('Compiling with command: '+cmd)
        os.system(cmd)

    binary_location = '../build/output/eos.elf'
    link = (LINKER_NAME+' '+LINKER_FLAGS+' -o '+binary_location+' '+executable_list_string)    
    print('Linking with command: '+link)
    os.system(link)

    # Change back to build/
    os.chdir('../build/')

    post_script = 'targets/'+args.target+'/postprocessing.sh'
    if os.path.isfile(post_script): # If a postprocessing script is given
        print('Executing postprocessing script...')
        subprocess.call(['bash', '../'+post_script], cwd='output/')

    print('Finished')

if __name__ == "__main__":
    main()