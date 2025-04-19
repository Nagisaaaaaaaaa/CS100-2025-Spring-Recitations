import platform
import subprocess

cmd = ["cmake", "-B", "build", "-DCMAKE_EXPORT_COMPILE_COMMANDS=ON"]

if platform.system() == "Windows":
  cmd += [
    "-G", "MinGW Makefiles",
    "-DCMAKE_C_COMPILER=gcc",
    "-DCMAKE_CXX_COMPILER=g++"
  ]

subprocess.run(cmd, check=True)
