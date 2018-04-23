import os

dir_name = "test_dir"
os.mkdir(dir_name)

eng_dict = open("words_alpha.txt", "r")
names = eng_dict.readlines()[:10000]

for name in names:
	filename = name[:-2] + '.txt'
	fo = open(os.path.join(dir_name, filename), 'w')
	fo.write("%s" % name)
	fo.close()

