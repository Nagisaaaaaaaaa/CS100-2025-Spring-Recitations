import subprocess

subprocess.run(["cmake", "--build", "build", "-j"], check=True)
subprocess.run(["./LearnCMake.exe"], check=True)
