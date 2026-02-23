import os

for j in os.listdir("mol"):
    mol = open(f"mol/{j}", "r")
    lines = mol.readlines()
    mol.close()

    cid = j.replace(".mol", "")
    print(lines)
    file = open(f"gjf/{cid}.gjf", "w")
    file.write(f"%chk={cid}-opt-b3lyp.chk\n")
    file.write("%mem=10GB\n")
    file.write("%NProcShared=12\n")
    file.write("# opt=(calcfc) b3lyp/6-31g(d,p) scf=tight\n")
    file.write("\n")
    file.write("pe cosmo generation\n")
    file.write("\n")
    file.write("0 1\n")

    n = int(lines[3][1:3])

    data = lines[4:4+n]

    # for i in data:
        # print(i)

    for i in range(len(data)):
        delete = data[i][33:]
        # print(delete)
        data[i] = data[i].replace(delete, "")

        atom = data[i][31:]   #get data
        data[i] = data[i].replace(atom, "")   #delete atom
        atom = atom.replace(" ", "")   #delete space
        data[i] = atom+data[i]+ "\n"
        # print(data[i])

    file.writelines(data)
    file.write("\n")
    file.write("--Link1--\n")
    file.write(f"%chk={cid}-opt-b3lyp.chk\n")
    file.write("%mem=10GB\n")
    file.write("%NProcShared=12\n")
    file.write("# b3lyp/6-31g(d,p) geom=checkpoint guess=read scf=tight SCRF=(COSMORS)\n")
    file.write("\n")
    file.write("pe cosmo generation\n")
    file.write("\n")
    file.write("0 1\n")
    file.write("\n")
    file.write(f"{cid}-opt-b3lyp.cosmo\n")

    file.close()