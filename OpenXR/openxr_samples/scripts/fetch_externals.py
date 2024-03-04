#!/usr/bin/env python3
# %BANNER_BEGIN%
# ---------------------------------------------------------------------
# %COPYRIGHT_BEGIN%
# Copyright (c) 2023 Magic Leap, Inc. All Rights Reserved.
# Use of this file is governed by the Software License Agreement,
# located here: https://www.magicleap.com/software-license-agreement-ml2
# Terms and conditions applicable to third-party materials accompanying
# this distribution may also be found in the top-level NOTICE file
# appearing herein.
# %COPYRIGHT_END%
# ---------------------------------------------------------------------
# %BANNER_END%

from collections.abc import Callable
import argparse
import csv
import os
import shutil
import stat
import sys
import urllib.request

vi = sys.version_info
if (vi.major, vi.minor) < (3, 5):
  print("Please run this script with Python 3.5 or newer")
  exit(1)

last_known_sizes = {
   "imgui"             : 1638658,
   "openxr_source_sdk" : 3367371,
   "tinygltf"          : 6855769,
   "vma"               : 1086639,
   "vulkan_headers"    : 1512000,
}


def on_err_cb(func: Callable, path: str, exc_info: tuple):
    '''Callback for shutil.rmtree() onerror attribute

    Args:
        func (Callable): platform and implementation dependent function that failed
        path (str): argument to the *func* function that caused it to fail
        exc_info (tuple): tuple returned by sys.exc_info()
    '''
    # Retry deletion to workaround "PermissionDenied" errors on Windows
    if os.path.exists(path) and not os.access(path, os.W_OK):
        os.chmod(path, stat.S_IWUSR)
        func(path)
    else:
        pass # Behave in the same way as ignore_errors=True


def rm(path: str):
  '''Removes given file or directory path if exists

  Args:
    path (str): The path to be removed
  '''

  if not os.path.exists(path):
    return

  if os.path.isdir(path):
    shutil.rmtree(path, onerror=on_err_cb)
  else:
    os.remove(path)


def clone_git_repo_to(_: str, git_repo: str, dst_base_path):
  '''Clones git repository in the specified path

  Args:
      _ (str): Repository name, not used
      git_repo (str): Url of the git repository
      dst_base_path (str): Path to initiate the cloning in
  '''

  curr_pwd = os.path.abspath('.')
  repo_name = git_repo.rsplit('/', 1)[-1]
  repo, _ = os.path.splitext(repo_name)
  os.makedirs(dst_base_path, exist_ok=True)
  os.chdir(dst_base_path)
  rm(os.path.join(dst_base_path, repo))
  cmd = 'git clone ' + git_repo
  res = os.system(cmd)
  os.chdir(curr_pwd)
  if res != 0:
    print(f"Error while cloning \"{git_repo}\"! Received {res} from cmd execution.")
  return os.path.join(dst_base_path, repo)


def download_file(name: str, url: str, dst_base_path):
  '''Downloads file to the specified path.
  Path will be dst_base_path/name/filename_from_url.

  Args:
      name (str): Name for the subdirectory
      url (str): Url of the file
      dst_base_path (str): Path to initiate the cloning in
  '''

  file_name = url.rsplit('/', 1)[-1]
  dst_path = os.path.join(dst_base_path, name)
  os.makedirs(dst_path, exist_ok=True)
  file_path = os.path.join(dst_path, file_name)
  rm(file_path)

  try:
    # Setting Accept-Encoding to None may help to get length: https://github.com/psf/requests/issues/3953
    # Content-Length won't be returned if response has {Transfer-Encoding: chunked} header
    #
    # req = urllib.request.Request(url)#, headers={'Accept-Encoding': 'None'})
    # with urllib.request.urlopen(req) as response, open(file_path, 'wb') as out_file:
    with urllib.request.urlopen(url) as response, open(file_path, 'wb') as out_file:
      block_size = 1024000  # Default block size 1MB
      total_size = response.getheader('Content-Length')
      current_size = 0
      if total_size:
        total_size = int(total_size)
      else:
        default_10_mb = 10240000
        total_size = last_known_sizes.get(name, default_10_mb)
        print(f"\tContent-Length header not returned, using hardcoded size for {name}: {total_size}")

      block_size = max(4096, total_size // 100)
      print_progress(f"Downloading {name}", current_size, total_size)
      while True:
        chunk = response.read(block_size)
        if not chunk:
          break
        out_file.write(chunk)
        current_size += len(chunk)
        if total_size:
          print_progress(f"Downloading {name}", current_size, total_size)

      print(f"Download completed successfully! Downloaded {current_size} bytes.")
  except Exception as e:
    print(f"An error occurred while downloading the file: {e}")
  return file_path


def print_progress(prefix: str, current: int, total: int):
  '''Prints progress bar

  Args:
      prefix (str): Prefix printed before the bar
      current (int): Current value
      total (int): Total value
  '''

  bar_length = 25
  progress = current / total
  block = int(round(bar_length * progress))
  left = bar_length - block
  print("{}[{}{}] {}/{}".format(prefix, "#"*block, "."*left, current, total),
          end='\r', file=sys.stdout, flush=True)
  if current < 0 or total == 0 or current >= total:
    print('', file=sys.stdout, flush=True)


def import_csv(csv_path: str):
  '''Imports csv file and returns as list of lists

  Args:
      csv_path (str): Path to the csv file
  '''

  file_list = []
  with open(csv_path, newline='') as f:
    reader = csv.reader(f)
    for row in reader:
        file_list += [row]
  return file_list


def export_csv(data: list, csv_path: str):
  '''Exports given data to a csv file

  Args:
      data (list): List of rows of data (also lists)
      csv_path (str): Path to the csv file
  '''

  with open(csv_path, 'w', newline='') as f:
    writer = csv.writer(f)
    for row in data:
      writer.writerow(row)


def is_git_url(url: str):
  '''Returns True if given url is to a git repo, False otherwise

  Args:
      url (str): Url to check
  '''

  return url.endswith('.git')


def build_download_list(expected_deps: list, local_deps: list):
  '''Constructs a list of tuples with format (name, should_dl, location, hash) based
  on expected deps and current local deps.
  List entries that have should_dl equal to True needs to be redownloaded,
  the location is an url in that case.
  List entries that have should_dl equal to False can be reused as they are,
  the location is a "file://path_to_downloaded_deps" string.

  If local_deps is None, will include whole expected_deps in output list.

  Args:
      expected_deps (list): List of rows of data (also lists with name, url, hash)
      local_deps (list): List of rows of data (also lists with name, location, hash)
  '''

  if local_deps is None:
    return [[name, True, url, hashsum] for (name, url, hashsum) in expected_deps]

  local_deps_map = {}
  for name, location, hashsum in local_deps:
    local_deps_map[name] = (location, hashsum)

  download_list = []
  for name, url, hashsum in expected_deps:
    location = url
    should_download = True

    if name in local_deps_map:
      (local_location, local_hashsum) = local_deps_map[name]
      if local_hashsum == hashsum:
        should_download = False
        location = local_location
    download_list += [[name, should_download, location, hashsum]]

  return download_list


if __name__ == "__main__":
  parser = argparse.ArgumentParser(description="Script to download external dependencies. Will only re-/download new/stale dependencies.")
  parser.add_argument("-f", "--force", action="store_true", help="Force redownload of all dependencies.", required=False)
  args = parser.parse_args()
  force_download = args.force

  root_path = os.path.dirname(os.path.realpath( __file__))
  externals_path = os.path.join(root_path, '..', 'externals')
  in_csv_name = 'external_deps.csv'
  in_csv_path = os.path.normpath(os.path.join(root_path, '..', 'cmake', in_csv_name))
  out_csv_name = 'external_deps_local.csv'
  out_csv_path = os.path.normpath(os.path.join(root_path, '..', 'cmake', out_csv_name))

  print(f"Opening {in_csv_name}.\n")
  expected_deps = import_csv(in_csv_path)

  # Build the download list
  if force_download or not os.path.exists(out_csv_path):
    print("Either first run or --force has been used - downloading all dependencies!\n")
    local_deps = None
    if os.path.exists(externals_path):
      print(f"Removing old external directory: {externals_path}.\n")
      rm(externals_path)
  else:
    local_deps = import_csv(out_csv_path)
  download_list = build_download_list(expected_deps, local_deps)

  # Iterate the download list and dl required (new/stale) deps
  output_csv_list = []
  local_deps_updated = False
  for name, should_dl, location, hashsum in download_list:
    if should_dl:
      print(f"Downloading {name} from {location}...")
      download_fun = clone_git_repo_to if is_git_url(location) else download_file
      ret_path = download_fun(name, location, externals_path)
      ret_path = os.path.abspath(ret_path)
      ret_path = ret_path.replace('\\', '/')
      output_csv_list += [[name, f"file://{ret_path}", hashsum]]
      print('')
      local_deps_updated = True
    else:
      output_csv_list += [[name, location, hashsum]]

  if local_deps_updated:
    print(f"Creating new csv file: {out_csv_path}.\n")
    export_csv(output_csv_list, out_csv_path)
  else:
    print("Everything seems up to date, nothing to do.\nUse the -f/--force flag to force an update.\n")

  print("Done!")
  exit(0)
