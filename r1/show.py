from PIL import Image
import sys

image = Image.open(sys.argv[1])
image.show()
