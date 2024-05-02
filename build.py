import platform
import subprocess
import argparse

platforms = ["windows-gnu", "linux-gnu", "macosx-none"]
architectures = ["aarch64", "x86_64"]

def check_tool(tool_args):
    try:
        # Try running the tool with the "--version" flag to check if it's installed
        subprocess.run(tool_args, stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=True, shell=True)
        return True
    except subprocess.CalledProcessError:
        return False 


def match_any(input, list):
    return any(input == element for element in list)

def build(zig_cmd, output_path, is_shared, is_spirv, architecture, platform, cpu_specific = None):
    if not match_any(platform, platforms):
        raise Exception(f"Invalid platform '{platform}'. Must be one of the following: {platforms}.") 

    if not match_any(platform_arch, architectures):
        raise Exception(f"Invalid architecture '{platform_arch}'. Must be one of the following: {architectures}.")

    print(f"Compiling for {architecture}-{platform}. SPIR-V support: {is_spirv}. Shared Library: {is_shared}. Output directory: {output_path}")

    zig_cmd.extend([
        'build',
        '-p', output_path,
        '-Dshared', '-Dspirv',
        '-Doptimize=ReleaseFast',
        '-Dfrom_source',
        f'-Dtarget={architecture}-{platform}'
    ])

    if cpu_specific is not None:
        zig_cmd.append(f'-Dcpu={cpu_specific}')

    print(zig_cmd)
    
    subprocess.run(zig_cmd, check = True, shell=True)


# should not run as submodule
if __name__ != "__main__":
    exit()


parser = argparse.ArgumentParser(description = 'Build mach-dxcompiler')
parser.add_argument('-P', '--platform', dest = 'platform', required = False, help = f'Platform type- Can be {platforms}. Defaults to current platform.')
parser.add_argument('-A', '--architecture', dest = 'architecture', required = False, help = f'Platform architecture- Can be {architectures}. Defaults to current architecture.')
parser.add_argument('-O', '--output', dest = 'output', required = False, help = 'Output directory')
parser.add_argument('-Z', '--zig-installation', dest = 'zig_installation', required = False, help = 'Zig installation')

platform_type = parser.parse_args().platform or None
platform_arch = parser.parse_args().architecture or None
output_dir = parser.parse_args().output or 'zig-out/'
zig_installation = (parser.parse_args().zig_installation or 'zigup run 0.12.0-dev.3180+83e578a18').split(' ')

zig_check = zig_installation.copy()
zig_check.append('version')

if not check_tool(zig_check):
    print('Zig installation not found. Ensure zig 0.12.0-dev.3180+83e578a18 is installed on the system and specified with -Z. You can download a verison of zig from here: https://machengine.org/about/nominated-zig/#202430-mach')
    exit()

if platform_type is None:
    current_platform = platform.system()

    if current_platform == 'Linux':
        platform_type = 'linux-gnu'
    elif current_platform == 'Darwin':
        platform_type = 'macosx-none'
    elif current_platform == 'Windows':
        platform_type = 'windows-gnu'
    else:
        platform_type = current_platform

if platform_arch is None:
    current_arch = platform.machine().lower()

    if not '64' in current_arch:
        print('Not targeting a 64-bit platform! Exiting.')
        exit()

    if 'aarch' in current_arch or 'arm' in current_arch:
        platform_arch = 'aarch64'
    elif 'x86' in current_arch or 'amd' in current_arch:
        platform_arch = 'x86_64'

build(zig_installation, output_dir, True, True, platform_arch, platform_type)

