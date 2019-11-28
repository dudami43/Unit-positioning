from shutil import copyfile
import glob 
#files = glob.glob("varias_unidades")
for i in range(15, 50):
    file = "varias_unidades/vicosa"+str(i)+".txt"
    copyfile("varias_unidades/vicosa.txt", file)
    f = open(file, "r")
    contents = f.readlines()
    f.close()

    contents.insert(0, str(i)+"\n")

    f = open(file, "w")
    contents = "".join(contents)
    f.write(contents)
    f.close()