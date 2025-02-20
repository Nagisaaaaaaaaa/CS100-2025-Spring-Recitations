from PIL import Image
import subprocess
import sys

subprocess.run(["gcc", sys.argv[1], "-o", "main.exe"])

with open("image.ppm", "w") as output_file:
  subprocess.run(["./main.exe"], stdout=output_file)

image = Image.open("image.ppm")

image.show()
