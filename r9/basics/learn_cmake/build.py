import subprocess

subprocess.run(["cmake", "--build", "build/", "-j"], check=True)
