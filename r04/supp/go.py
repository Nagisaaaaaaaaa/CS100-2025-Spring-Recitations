import os
from PIL import Image
import shutil
import subprocess
import sys

# Total time of the video.
time = 8
# FPS of the video.
fps = 30

# Compile the C code.
subprocess.run(["gcc", sys.argv[1], "-o", "main.exe"])

# Clear and create directory `images`.
if os.path.exists("images"):
  shutil.rmtree("images")
os.makedirs("images")

# For each frame (image):
for frame in range(time * fps):
  # Execute the C code with `frame` and `fps` as arguments.
  with open("image.ppm", "w") as output_file:
    subprocess.run(["./main.exe", str(frame), str(fps)], stdout=output_file)

  # Save the image as `frame_{frame}.png`.
  image = Image.open("image.ppm")
  image.save(f"images/frame_{frame}.png", "png")

# Delete `video.mp4` if exist.
if os.path.exists("video.mp4"):
  os.remove("video.mp4")

# Generate `video.mp4` with `ffmpeg`.
# See https://www.ffmpeg.org.
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
