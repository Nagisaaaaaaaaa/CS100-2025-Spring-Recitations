import os
from PIL import Image
import shutil
import subprocess
import sys

subprocess.run(["gcc", sys.argv[1], "-o", "main.exe"])

if os.path.exists("images"):
  shutil.rmtree("images")
os.makedirs("images")

for frame in range(30):
  with open("image.ppm", "w") as output_file:
    subprocess.run(["./main.exe", str(frame)], stdout=output_file)

  image = Image.open("image.ppm")
  image.save(f"images/frame_{frame}.png", "png")

if os.path.exists("video.mp4"):
  os.remove("video.mp4")

subprocess.run([
  "ffmpeg",
  "-framerate", "15",
  "-i", "images/frame_%d.png",
  "-c:v", "libx264",
  "-profile:v", "high",
  "-crf", "20",
  "-pix_fmt", "yuv420p",
  "video.mp4"
], check=True)
shutil.rmtree("images")
