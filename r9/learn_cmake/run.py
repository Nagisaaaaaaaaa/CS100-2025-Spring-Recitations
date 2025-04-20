import platform
import subprocess

subprocess.run(["cmake", "--build", "build", "-j"], check=True)
subprocess.run(["./bin/LearnCMake" + 
                (".exe" if platform.system() == "Windows" else "")], check=True)
