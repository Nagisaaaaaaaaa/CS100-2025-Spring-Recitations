import os
from PIL import Image
import shutil
import subprocess
import sys

time = 5
fps = 30

subprocess.run(["gcc", sys.argv[1], "-o", "main.exe"])

if os.path.exists("images"):
  shutil.rmtree("images")
os.makedirs("images")

for frame in range(time * fps):
  with open("image.ppm", "w") as output_file:
    subprocess.run(["./main.exe", str(frame), str(fps)], stdout=output_file)

  image = Image.open("image.ppm")
  image.save(f"images/frame_{frame}.png", "png")

if os.path.exists("video.mp4"):
  os.remove("video.mp4")

subprocess.run([
  "ffmpeg",
  "-framerate", str(fps),
  "-i", "images/frame_%d.png",
  "-c:v", "libx264",
  "-profile:v", "high",
  "-crf", "20",
  "-pix_fmt", "yuv420p",
  "video.mp4"
], check=True)
shutil.rmtree("images")
