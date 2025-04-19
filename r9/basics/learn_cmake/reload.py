import platform
import subprocess

cmd = ["cmake", "-B", "build"]

if platform.system() == "Windows":
  cmd += [
    "-G", "MinGW Makefiles",
    "-DCMAKE_C_COMPILER=gcc",
    "-DCMAKE_CXX_COMPILER=g++"
  ]

subprocess.run(cmd, check=True)
