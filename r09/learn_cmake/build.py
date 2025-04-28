import subprocess

subprocess.run(["cmake", "--build", "build", "--parallel"], check=True)
