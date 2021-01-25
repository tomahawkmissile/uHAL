import os
import sys
import argparse
from pathlib import Path
import shutil
import subprocess

COMPILER_NAME = 'avr-gcc'
COMPILER_FLAGS = '-mmcu=atmega328p -DBACKEND=2 -Os -DF_CPU=16000000UL -DBAUD=9600 -Wall -Wno-main -Wundef -pedantic -Wno-unused-variable -Werror -Wfatal-errors -Wl,--relax,--gc-sections -g -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -fno-split-wide-types -fno-tree-scev-cprop'
LINKER_NAME = 'avr-gcc'
LINKER_FLAGS = '-mmcu=atmega328p'

THIS_DIRECTORY = os.path.dirname(os.path.realpath(__file__))
HAL_OUTPUT_DIRECTORY = 'output'

def get_compile_list(target):
    list_compile_c_files = []

    if target == 'default':
        print('Default is not a target!')
        exit(-1)

    for file in os.listdir("targets/"):
        if os.path.isdir("targets/"+file):
            #filename = file.split(".")[0]
            filename = file
            if filename.lower() == target.lower(): #case insensitive
                text = 'targets/'+filename+'/files.txt'
                if not os.path.isfile(text):
                    # If target does not exist
                    print('Target does not exist! Check to make sure your target is supported.')
                    exit(-1)
                with open(text) as f_list:
                    for line in f_list:
                        if not line.startswith('#') and not line.isspace():
                            list_compile_c_files.append(line.rstrip('\n'))
                with open('targets/default/files.txt') as default_files:
                    for line in default_files:
                        if not line.startswith('#') and not line.isspace():
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
    os.chdir(THIS_DIRECTORY)

    parser=argparse.ArgumentParser()
    parser.add_argument('--target', type=str, help='select compilation target', required=True)
    args=parser.parse_args()

    compile_list = get_compile_list(args.target)
    if compile_list is None:
        print("No files to be compiled! Check your target platform compilation list!")
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