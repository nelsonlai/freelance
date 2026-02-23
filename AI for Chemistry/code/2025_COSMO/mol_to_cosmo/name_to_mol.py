# RDkit need to be installed and activated through Anaconda
# Please check https://www.rdkit.org/docs/Install.html
# After install RDKit please change the project interpreter to Anaconda environment
# Normally, route of interpreter should be C:\Users\“your_user_name”\“Anaconda_yourversion”\envs\my-rdkit-env\python.exe
# (my-rdkit-env) can be seen while run terminal in pycharm, means you succeed
# check the RDkit version if have no module bug, the version of Rdkit should be higher than 2020.03
from rdkit.Chem import MolToMolFile, AddHs, MolFromSmiles
from rdkit.Chem.AllChem import EmbedMolecule, UFFHasAllMoleculeParams, UFFOptimizeMolecule
from pubchempy import get_compounds
from csv import reader
import os
import pandas as pd

compound_list = []
# read namelist and save without the same one
# with open(".\\name.csv", "r", encoding="utf-8") as compound_csv:
#     csv_rc = reader(compound_csv)
#     for line in csv_rc:
#         name = line[0]
#         if name not in compound_list:
#             compound_list.append(name)

data = pd.read_csv("name.csv")
compound_list = data["CID"]


# read the file name in folder
def GetFileName(dir, x):
    listName = []
    for fileName in os.listdir(dir):
        if os.path.splitext(fileName)[1] == x:
            fileName = os.path.splitext(fileName)[0]
            listName.append(fileName)
    return listName


# read the file name of . mol in folder mol
mol_list = GetFileName(".\\mol\\", ".mol")
require_list = [name for name in compound_list if name not in mol_list]
number_mol = len(require_list)
print(number_mol, "mol files are needed to be generated")
smiles_list = []
error_list = []
error_judge = 0
# Transform the name to smiles code by searching in Pubchem database
for index in range(0, number_mol):
    c = get_compounds(str(require_list[index]), 'cid')
    # the major one will be save while targeted molecular name have Chirality
    # for chiral molecular with R- or S- is preferred.
    try:
        sm = c[0].isomeric_smiles
        if index == number_mol - 1:
            char = "\n"
        else:
            char = ""
        print("\r", index + 1 - len(error_list), "/", number_mol, "smiles found in Pubchem",
              len(error_list), "/", number_mol, "smiles not found in Pubchem",   end=char, flush=True)
    except:
        error_list.append(require_list[index])
        error_judge = 1
    if error_judge == 1:
        print("Warning!!!! the following name is incorrect, please revise them with Pubchem database and restart the program")
        for error in error_list:
            print(error)
        os.system("pause")

    # transform to smiles code to 3D structure by RDkit
    mols_from_sm = MolFromSmiles(sm)

    # Optimization function by Distance Geometry method followed with UFF method
    def DG_UFF(mols,index):
        mh = AddHs(mols)        #Add H 
        EmbedMolecule(mh, useBasicKnowledge=True, useExpTorsionAnglePrefs=False)
        if UFFHasAllMoleculeParams(mh):
            UFFOptimizeMolecule(mh)
            if index == number_mol - 1:
                char2 = "\n"
            else:
                char2 = ""
        print("\r", index+1, "/", number_mol, "Geo_Opt by DG_UFF is done", end=char2, flush=True)
        return mh

    # Optimize for all molecular
    DG_UFF = DG_UFF(mols_from_sm,index)
    MolToMolFile(DG_UFF, ".\\mol\\"+str(require_list[index])+'.mol') # save each one with corresponding name
print("Finish")
os.system("pause")

