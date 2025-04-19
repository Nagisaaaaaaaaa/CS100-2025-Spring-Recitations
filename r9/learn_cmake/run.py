import subprocess

subprocess.run(["cmake", "--build", "build", "-j"], check=True)
subprocess.run(["./bin/LearnCMake.exe"], check=True)
