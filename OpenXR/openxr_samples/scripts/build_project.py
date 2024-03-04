# %BANNER_BEGIN%
# ---------------------------------------------------------------------
# %COPYRIGHT_BEGIN%
# Copyright (c) 2022 Magic Leap, Inc. All Rights Reserved.
# Use of this file is governed by the Software License Agreement,
# located here: https://www.magicleap.com/software-license-agreement-ml2
# Terms and conditions applicable to third-party materials accompanying
# this distribution may also be found in the top-level NOTICE file
# appearing herein.
# %COPYRIGHT_END%
# ---------------------------------------------------------------------
# %BANNER_END%

import argparse
import os
import sys
import re
import platform
from itertools import chain

from mlsdk_helpers import *
from vs_helper import *

vi = sys.version_info
if (vi.major, vi.minor) < (3, 5):
  print("Please run this script with Python 3.5 or newer")
  exit(1)

win = platform.system() == "Windows"
osx = platform.system() == "Darwin"

CMAKE_TEMP_BUILD_DIR = "build_host"

def gradle_stop(build_args):
    run([build_args.gradle, '--stop'], build_args.verbose)


def build_projects_device(build_args):
  def cleanup_on_failure(err):
    if not build_args.no_daemon:
      gradle_stop(build_args)

  print("> Running build step for device")
  if build_args.project:
    gradle_prefix = ":{}:app:".format(build_args.project.replace("/", ":").replace("\\", ":"))
  # elif build_args.areas:
  #   gradle_prefix = "{}_".format(build_args.areas)
  else:
    gradle_prefix = ""

  cmd = [build_args.gradle]
  if build_args.no_daemon:
    cmd += ['--no-daemon']

  if RELEASE in build_args.config:
    if DEBUG in build_args.config:
      cmd += [gradle_prefix + 'build']
    else:
      cmd += [gradle_prefix + 'assembleRelease', gradle_prefix + 'check']
    cmd += ['-Proot_path={}'.format(build_args.project_path)]
  else:
    cmd += [gradle_prefix + 'assembleDebug', gradle_prefix + 'check']

  if build_args.jobs is not None:
    cmd += ['--parallel']

  if build_args.local_deps:
    cmd += ['-Puse_local_deps=1']

  run(cmd, build_args.verbose, failure_callback=cleanup_on_failure)


# Checks for certificates needed for building signed release APKs and returned boolean.
# When certificates are not found, a proper information is printed.
def check_certificates( project_path ):
  scripts_dir = os.path.join(project_path, 'scripts')
  cert_keystore_exists = os.path.exists(os.path.join(scripts_dir, 'mlsdk.keystore'))
  cert_properties_exists = os.path.exists(os.path.join(scripts_dir, 'keystore.properties'))
  if not cert_keystore_exists or not cert_properties_exists:
    print("\nNo certificates found for signing the release APKs for device!\n"
        + "Please put \"mlsdk.keystore\" and \"keystore.properties\" in \"{}\"!\n".format(scripts_dir)
        + "Note that keystore.properties should contain:\n - storePassword\n - keyPassword\n - keyAlias\n - storeFile\n"
        + "where storeFile is a path that will be appended to the samples root path, e.x. \"scripts/mlsdk.keystore\".\n")
    return False
  return True


def DetectClangArchitectures():
    if not osx:
        return []

    comp = subprocess.run(['clang', '--version'], stdout=subprocess.PIPE, universal_newlines=True)

    archs = ['x86_64']
    if comp.returncode != 0:
        # this would be really bad (until proven otherwise)
        print("could not run 'clang', assuming Intel-only for now")
        return archs

    # Apple clang version 12.0.0 (clang-1200.0.32.28) ...
    m = re.search(r'Apple clang version (\d+)', comp.stdout)
    if not m:
        print("could not detect version info from 'clang', assuming Intel-only for now\n%s" % comp.stdout)
        return archs

    if int(m.group(1)) >= 12:
        # Xcode/clang 12 is where M1 support added
        archs.append('arm64')

    return archs


def build_projects_host(build_args):
  print("> Build for host")

  os.makedirs(CMAKE_TEMP_BUILD_DIR, exist_ok=True)
  os.chdir(CMAKE_TEMP_BUILD_DIR)

  for config in build_args.config:
    print("> Running configuration step for host {}".format(config))
    cmd = [build_args.cmake]

    # use ninja if possible
    custom_env = get_ninja_env(build_args.force_vs_rescan, build_args.msvc)
    if custom_env:
      ninja_path = get_ninja_path(custom_env.get('PATH'))
      if ninja_path:
        cmd += ['-D', 'CMAKE_MAKE_PROGRAM={}'.format(ninja_path), '-G', 'Ninja']

    # if we didn't find ninja, revert to msvc
    if win and not ninja_path:
      msvc = build_args.msvc if build_args.msvc else "Visual Studio 16 2019"
      cmd += ['-G', msvc, '-A', 'x64']

    if osx:
      cmd += [ '-DCMAKE_OSX_ARCHITECTURES=' + ';'.join(DetectClangArchitectures()) ]

    cmd += ["-D", "CMAKE_BUILD_TYPE={}".format(config.capitalize())]

    if build_args.no_appsim:
      cmd += ["-DNO_ML_CAPI=1", "-DNO_APPSIM=1"]
    else:
      cmd += ["-DNO_ML_CAPI=0", "-DNO_APPSIM=0"]

    if build_args.local_deps:
      cmd += ["-DUSE_LOCAL_DEPS=1"]

    cmd += [".."]
    run(cmd, verbose=build_args.verbose, custom_env=custom_env)


    print("> Running build step for host {}".format(config))
    if build_args.project:
      cmake_target = ["--target", build_args.project.replace("\\", "/").split("/")[-1]]
    # elif build_args.areas:
    #   cmake_target = ["--target", build_args.areas]
    else:
      cmake_target = []
    cmd = [build_args.cmake, "--build", "."]
    cmd += ["--config", config.capitalize()]
    cmd += cmake_target
    if build_args.jobs:
      cmd += ["--parallel", build_args.jobs]
    run(cmd, build_args.verbose)
  os.chdir("..")


def clean_artifacts_host(build_args):
  print("> Cleaning host build artifacts")
  if os.path.exists(CMAKE_TEMP_BUILD_DIR):
    print("Removing build dir:", CMAKE_TEMP_BUILD_DIR)
    shutil.rmtree(CMAKE_TEMP_BUILD_DIR, ignore_errors=True)

  if os.path.exists(build_args.out_host_path):
    print("Removing out dir:", build_args.out_host_path)
    shutil.rmtree(build_args.out_host_path, ignore_errors=True)



def clean_artifacts_device(build_args):
  def cleanup_on_failure(err):
    if not build_args.no_daemon:
      gradle_stop(build_args)

  print("> Cleaning device build artifacts")
  if build_args.project:
    gradle_prefix = ":{}:app:".format(build_args.project.replace("/", ":").replace("\\", ":"))
  # elif build_args.areas:
  #   gradle_prefix = "{}_".format(build_args.areas)
  else:
    gradle_prefix = ""

  cmd = [build_args.gradle]
  if build_args.no_daemon:
    cmd += ['--no-daemon']
  if (RELEASE in build_args.config and DEBUG in build_args.config):
    cmd += [gradle_prefix + 'clean']
  elif RELEASE in build_args.config:
    cmd += [gradle_prefix + 'externalNativeBuildCleanMl2Release']
  elif DEBUG in build_args.config:
    cmd += [gradle_prefix + 'externalNativeBuildCleanMl2Debug']
  run(cmd, build_args.verbose, failure_callback=cleanup_on_failure)

  if os.path.exists(build_args.out_device_path):
    print("Removing artifacts dir:", build_args.out_device_path)
    shutil.rmtree(build_args.out_device_path, ignore_errors=True)


def post_build(build_args):
  # Make sure the gradle daemon exits.
  if DEVICE in chain(build_args.clean, build_args.build):
    print("\n\n> Post build cleanup up tasks.")
    gradle_stop(build_args)

  if DEVICE in build_args.build:
    shutil.copy(os.path.join(build_args.root_path, 'README.md'), os.path.join(build_args.out_device_path, 'README.md'))


def build_projects(build_args):
  os.chdir(build_args.root_path)
  if build_args.clean:
    if DEVICE in build_args.clean:
      clean_artifacts_device(build_args)
    if HOST in build_args.clean:
      clean_artifacts_host(build_args)

  if build_args.build:
    if DEVICE in build_args.build:
      build_projects_device(build_args)
    if HOST in build_args.build:
      build_projects_host(build_args)


def build(root_path, out_device_path, out_host_path, projects):
  build_args = parse_args(projects)

  is_host = HOST in build_args.build or HOST in build_args.clean
  if osx and is_host:
    print("Building for host on MacOS machines is not supported!")
    exit(-1)

  build_args.root_path = root_path
  build_args.out_device_path  = out_device_path
  build_args.out_host_path  = out_host_path
  build_args.out_path = os.path.abspath(os.path.join(out_device_path, '..'))

  print(build_args)

  if DEVICE in build_args.clean and HOST in build_args.clean:
    if os.path.exists(build_args.out_path):
      print("\n\n> Cleaning the out folder")
      shutil.rmtree(build_args.out_path)

  build_args.project_path = os.path.join(os.path.normpath(os.path.join(build_args.root_path, "..")), "")

  if DEVICE in build_args.build and RELEASE in build_args.config and not check_certificates(build_args.project_path):
      exit(-1)

  build_args.cmake = os.path.join(get_cmake_path('3.22.1'), 'cmake')
  build_args.gradle = get_gradle_path(build_args.verbose, build_args.prefer_system_gradle)
  build_projects(build_args)
  post_build(build_args)


def parse_args(projects):
  parser = argparse.ArgumentParser()
  parser.add_argument('--verbose', '-v', action='count', default=0, dest='verbose', help='''increase verbosity incrementally''')
  parser.add_argument('--build', '-b', nargs='*', type=str.lower, choices=TARGETS_CHOICE, dest='build', help='Builds projects for selected targets. Assumes both targets, when called with no values.')
  parser.add_argument('--clean', '-c', nargs='*', type=str.lower, choices=TARGETS_CHOICE, dest='clean', help='Deletes the projects for selected targets. Assumes both targets, when called with no values.')
  parser.add_argument('--config', nargs='*', type=str.lower, choices=CONFIG_CHOICE, dest='config', help='Builds projects for selected configs. Assumes both release and debug config, when called with no values.')
  parser.add_argument('--jobs', '-j', dest='jobs', help='Number of build parallel build jobs')
  parser.add_argument('--project', '-p', default='', dest='project', help='Project to build.')
  parser.add_argument('--no-appsim', action='store_true', default=False, help='For host target build executables that do not rely on ML CAPI or AppSim.')
  # parser.add_argument('--areas', '-a', choices=projects, dest='areas', help='specify area to build')

  parser.add_argument('--no-daemon', action='store_true', default=False, dest='no_daemon', help='Disables using the daemon for building')
  parser.add_argument('--prefer-system-gradle', action='store_true', default=False, dest='prefer_system_gradle', help='Use the system installed gradle if available, fallback to local gradle if not found.')
  parser.add_argument('--local-deps', action='store_true', default=False, dest='local_deps', help='Use local dependencies for OpenXR App Framework build. Assumes that scripts/fetch_externals.py script has been ran manually beforehand.')

  if win:
    parser.add_argument('--msvc', default=None, dest='msvc', help="Selects specific Visual Studio version to use.")
    parser.add_argument('--no-rescan', action='store_false', default=True, dest='force_vs_rescan', help="Forces no rescan of Visual Studio environments.")

  build_args = parser.parse_args()

  translate_default_arguments(build_args)
  build_args.force_vs_rescan = getattr(build_args, 'force_vs_rescan', True)
  build_args.msvc = getattr(build_args, 'msvc', None)

  # if build_args.project and build_args.areas:
  #   print("Don't use both 'project' and 'areas' parameters at the same time!")
  #   exit(1)
  # elif not build_args.project and not build_args.areas and projects:
  #   build_args.areas = projects[0]

  build_args.projects = projects
  return build_args
